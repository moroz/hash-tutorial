<script lang="ts">
  import Buckets from "../components/Buckets.svelte";
  import Layout from "../components/Layout.svelte";
  import FireText from "../components/FireText.svelte";
  import CodeSnippet from "../components/CodeSnippet.svelte";
  import Entry from "../components/Entry.svelte";

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

  const snippet = `# Inserting key = "foo", value = 42
index = hash("foo") % 8 # 7`;
</script>

<Layout title="Hash function">
  <p>
    The secret sauce that makes a hash table <FireText>blazingly fast</FireText>
    is a <strong>hash function</strong>.<br />
    Whenever you <strong>look up</strong> an entry, the hash function converts
    the <strong>key</strong> to a <strong>number</strong>.<br />When you
    <strong>reduce it modulo</strong>
    the array's <strong>capacity</strong> (size), you get the item's
    <strong>index</strong>.
  </p>
  <div class="grid grid-cols-2 flex-1 items-center justify-center grid-rows-2">
    <CodeSnippet language="python" code={snippet} />
    <div class="col-1 row-2">
      <Entry key="foo" value={42} />
    </div>
    <div class="grid place-items-center row-span-2">
      <Buckets {values} />
    </div>
  </div>
</Layout>
