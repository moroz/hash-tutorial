<script lang="ts">
  import Buckets from "../components/Buckets.svelte";
  import Layout from "../components/Layout.svelte";

  const values = [
    null,
    null,
    { key: "bar", value: 69 },
    null,
    null,
    null,
    null,
    null,
  ];
</script>

<Layout title="How a hash table works">
  <p class="h-[150px]">
    A hash table is, in its essence, a <strong>dynamic array</strong>.<br />Each
    <strong>entry</strong> in this array is called a <strong>bucket</strong>.
    Each bucket stores a key and a value.
  </p>
  <div class="flex w-full flex-1 flex-col items-center justify-center">
    <Buckets {values} class="-ml-12" />
  </div>
</Layout>
