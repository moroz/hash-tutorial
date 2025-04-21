<script lang="ts">
  import Buckets from "../components/Buckets.svelte";
  import Layout from "../components/Layout.svelte";

  const values = [
    null,
    null,
    { key: "bar", value: 420 },
    { key: "baz", value: 69 },
    null,
    null,
    null,
    { key: "foo", value: 42 },
  ];
</script>

<Layout title="How a hash table works (1)">
  <p>
    A hash table is, in its essence, a <strong>dynamic array</strong>.<br />Each
    <strong>entry</strong> in this array is called a <strong>bucket</strong>. It
    stores both the key and the value.
  </p>
  <div class="container">
    <Buckets {values} />
  </div>
</Layout>

<style>
  .container {
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
    flex: 1;
  }
</style>
