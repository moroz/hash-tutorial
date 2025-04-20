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

<Layout title="How a hash table works">
  <p>
    A hash table is, in its essence, a dynamically growing array.<br />Each
    index in this array is called a &ldquo;bucket.&rdquo;
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
  }
</style>
