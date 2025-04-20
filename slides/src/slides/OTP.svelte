<script lang="ts">
  import { SHARED_SECRET_BIN } from "../lib/config";
  import useDigest from "../lib/useDigest.svelte";
  import useUNIXTime from "../lib/useUNIXTime.svelte";
  import Digest from "../components/Digest.svelte";
  import hljs from "highlight.js/lib/core";

  const time = useUNIXTime();
  const digest = useDigest(SHARED_SECRET_BIN, time.timeStepEncoded);

  const last = $derived.by(() => {
    if (!digest.ready) {
      return 0;
    }

    return digest.digest[19];
  });

  const offset = $derived(last & 0xf);

  const bytes = $derived.by(() => {
    if (!digest.ready) return [];
    console.log(offset);

    return [
      digest.digest[offset],
      digest.digest[offset + 1],
      digest.digest[offset + 2],
      digest.digest[offset + 3],
    ];
  });

  const binary = $derived.by(() => {
    if (!digest.ready) return 0;

    return (
      ((bytes[0] & 0x7f) << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3]
    );
  });

  $effect(() => {
    digest.update(time.timeStepEncoded);
  });

  function formatHex(num: number) {
    return num.toString(16).padStart(2, "0").toUpperCase();
  }

  const code = `\
uint32_t binary = (digest[offset + 0] & 0x7F) << 24 | // %{bytes[0]} << 24
                   digest[offset + 1]         << 16 | // %{bytes[1]} << 16
                   digest[offset + 2]         <<  8 | // %{bytes[2]} << 8
                   digest[offset + 3];                // %{bytes[3]}

int otp = binary % 1000000; // %{binary} % 1000000 = %{otp}`;

  const highlighted = $state(hljs.highlight(code, { language: "c" }).value);

  let html = $derived.by(() => {
    if (!digest.ready) return highlighted;
    return highlighted
      .replace(`%{bytes[0]}`, `0x${formatHex(bytes[0] & 0x7f)}`)
      .replace(`%{bytes[1]}`, `0x${formatHex(bytes[1])}`)
      .replace(`%{bytes[2]}`, `0x${formatHex(bytes[2])}`)
      .replace(`%{bytes[3]}`, `0x${formatHex(bytes[3])}`)
      .replace(`%{binary}`, String(binary))
      .replace(`%{otp}`, String(binary % 1000000));
  });
</script>

<h2>5. Calculate One-Time Password</h2>

<p>
  Finally, take the last 6 decimal digits of this number. This is your TOTP
  code.<br />Pad it with zeroes using (e. g. using <code>left-pad</code>) if it
  is too short.
</p>

<Digest
  secret={SHARED_SECRET_BIN}
  timeStep={time.timeStepEncoded}
  highlighted={[offset, offset + 1, offset + 2, offset + 3]}
  label="HMAC-SHA-1 digest (highlighted bytes)"
  indexed
/>

<pre data-language="c"><code class="hljs">{@html html}</code></pre>
