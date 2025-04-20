<script lang="ts">
  import Binary from "../components/Binary.svelte";
  import Digest from "../components/Digest.svelte";
  import { SHARED_SECRET_BIN } from "../lib/config";
  import useUNIXTime from "../lib/useUNIXTime.svelte";

  const time = useUNIXTime();
</script>

<h2>3. Sign time step with secret</h2>

<Binary binary={SHARED_SECRET_BIN} label="Shared secret (binary)" />
<Binary
  binary={time.timeStepEncoded}
  label="Time step (64-bit big-endian)"
  wide
/>
<div class="transition">👇 <code> HMAC() </code>👇</div>
<Digest
  secret={SHARED_SECRET_BIN}
  timeStep={time.timeStepEncoded}
  label="HMAC-SHA-1 signature"
/>
