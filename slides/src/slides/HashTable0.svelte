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
  <p>
    A hash table is, in its essence, a <strong>dynamic array</strong>.<br />Each
    <strong>entry</strong> in this array is called a <strong>bucket</strong>.
    Each bucket stores a key and a value.
  </p>
  <div class="flex flex-col justify-center items-center flex-1 w-full">
    <Buckets {values} class="-ml-12" />
  </div>
</Layout>
