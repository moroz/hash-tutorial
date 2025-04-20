<script lang="ts">
  import useDigest from "../lib/useDigest.svelte";
  import Binary from "../components/Binary.svelte";

  interface Props {
    timeStep: Uint8Array;
    secret: Uint8Array;
    label?: string;
    highlighted?: number[];
    indexed?: boolean;
  }

  const {
    timeStep,
    secret,
    label,
    highlighted = [],
    indexed = false,
  }: Props = $props();

  const digest = useDigest(secret, timeStep);

  $effect(() => {
    digest.update(timeStep);
  });
</script>

<Binary {label} binary={digest.digest} {highlighted} {indexed} />
