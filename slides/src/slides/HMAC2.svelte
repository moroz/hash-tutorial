<script lang="ts">
  import Digest from "../components/Digest.svelte";
  import { SHARED_SECRET_BIN } from "../lib/config";
  import useDigest from "../lib/useDigest.svelte";
  import useUNIXTime from "../lib/useUNIXTime.svelte";

  const time = useUNIXTime();

  const digest = useDigest(SHARED_SECRET_BIN, time.timeStepEncoded);

  const last = $derived.by(() => {
    if (!digest.ready) {
      return 0;
    }
    return digest.digest[19];
  });

  const offset = $derived(last & 0xf);

  $effect(() => {
    digest.update(time.timeStepEncoded);
  });

  function formatOffset(num: number) {
    return "0x" + num.toString(16).toUpperCase();
  }
</script>

<h2>4. Take the last 4 bits of the digest</h2>

<Digest
  secret={SHARED_SECRET_BIN}
  timeStep={time.timeStepEncoded}
  label="HMAC-SHA-1 signature"
  highlighted={[19]}
/>

<p>
  The last byte is <code
    >0x{last.toString(16).padStart(2, "0").toUpperCase()}</code
  >, so the last four bits =
  <code>{formatOffset(offset)}</code>.<br />
  Take four bytes of the digest, starting from index
  <code>{formatOffset(offset)}</code>:
  <code>{formatOffset(offset)}–{formatOffset(offset + 3)}</code>.
</p>

<Digest
  secret={SHARED_SECRET_BIN}
  timeStep={time.timeStepEncoded}
  highlighted={[offset, offset + 1, offset + 2, offset + 3]}
  indexed
/>

<p>
  Discard the first bit &mdash; we treat these four bytes as a 32-bit unsigned
  integer.
</p>
