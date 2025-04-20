<script lang="ts">
  import Buckets from "../components/Buckets.svelte";

  const values = Array.from(new Array(8)).fill({ key: null, value: null });
</script>

<h2>How a hash table works</h2>

<Buckets {values} />
