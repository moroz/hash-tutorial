<script lang="ts">
import Buckets from "../components/Buckets.svelte";
import Layout from "../components/Layout.svelte";
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
  { key: "foo", value: 42 },
];

const snippet = `# Inserting key = "baz", value = 420
index = hash("baz") % 8 # 2`;

let entry: HTMLTableElement | null = $state(null);
let table: HTMLTableElement | null = $state(null);

let p1 = $state<{ x: number; y: number } | null>(null);
let p2 = $state<{ x: number; y: number } | null>(null);

$effect(() => {
  if (!entry || !table) return;
  const r1 = entry.getBoundingClientRect();
  p1 = { x: r1.right, y: r1.top + r1.height / 2 };
  const row = table.querySelector("tbody tr:nth-child(3)");
  if (!row) return;
  const r2 = row.getBoundingClientRect();
  p2 = { x: r2.left, y: r2.top + r2.height / 2 };
});
</script>

<Layout title="Handling collisions">
  <p class="h-[150px]">
    When the hashes of <strong>two different keys</strong> modulo the array size
    end up pointing to <strong>the same index</strong>, a&nbsp;<strong
      >key collision</strong
    >
    occurs. We search for the next empty bucket.
  </p>
  <div class="my-auto grid grid-cols-2 grid-rows-2 items-start justify-center">
    <CodeSnippet language="python" code={snippet} class="mt-[50px]" />
    <div class="col-1 row-2 mt-8">
      <Entry key="baz" value={420} bind:entry={entry} />
    </div>
    <div class="row-span-2 grid place-items-center">
      <Buckets values={values} bind:table={table} />
    </div>
  </div>
  <Arrow p1={p1} p2={p2} />
</Layout>
