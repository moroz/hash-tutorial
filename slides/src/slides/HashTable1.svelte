<script lang="ts">
  import Buckets from "../components/Buckets.svelte";
  import Layout from "../components/Layout.svelte";
  import FireText from "../components/FireText.svelte";
  import CodeSnippet from "../components/CodeSnippet.svelte";
  import Entry from "../components/Entry.svelte";
  import Arrow from "../components/Arrow.svelte";

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

  let entry: HTMLTableElement | null = $state(null);
  let table: HTMLTableElement | null = $state(null);

  let p1 = $state<{ x: number; y: number } | null>(null);
  let p2 = $state<{ x: number; y: number } | null>(null);

  $effect(() => {
    if (!entry || !table) return;
    const r1 = entry.getBoundingClientRect();
    p1 = { x: r1.right, y: r1.top + r1.height / 2 };
    const row = table.querySelector("tbody tr:last-child");
    if (!row) return;
    const r2 = row.getBoundingClientRect();
    p2 = { x: r2.left, y: r2.top + 10 };
  });
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
  <div class="grid grid-cols-2 items-start justify-center grid-rows-2 my-auto">
    <CodeSnippet language="python" code={snippet} class="mt-[50px]" />
    <div class="col-1 row-2">
      <Entry key="foo" value={42} bind:entry />
    </div>
    <div class="grid place-items-center row-span-2">
      <Buckets {values} bind:table />
    </div>
  </div>
  <Arrow {p1} {p2} />
</Layout>
