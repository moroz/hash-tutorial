<script lang="ts">
  import Buckets from "../components/Buckets.svelte";
  import Layout from "../components/Layout.svelte";

  const values = Array.from(new Array(8)).fill({ key: null, value: null });
</script>

<Layout title="How a hash table works">
  <p>
    The hash table is a dynamically growing array. At first, most of its
    elements are empty.
  </p>
  <Buckets {values} />
</Layout>
