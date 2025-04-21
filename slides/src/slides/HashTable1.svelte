<script lang="ts">
import Buckets from "../components/Buckets.svelte";
import Layout from "../components/Layout.svelte";
import FireText from "../components/FireText.svelte";
import CodeSnippet from "../components/CodeSnippet.svelte";
import Entry from "../components/Entry.svelte";
import Arrow from "../components/Arrow.svelte";
import { onMount } from "svelte";

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

function calculateArrow() {
  if (!entry || !table) return;
  const r1 = entry.getBoundingClientRect();
  p1 = { x: r1.right, y: r1.top + r1.height / 2 };
  const row = table.querySelector("tbody tr:last-child");
  if (!row) return;
  const r2 = row.getBoundingClientRect();
  p2 = { x: r2.left, y: r2.top + r2.height / 2 - 5 };
}

onMount(() => {
  calculateArrow();

  window.addEventListener("resize", calculateArrow);

  return () => {
    window.removeEventListener("resize", calculateArrow);
  };
});
</script>

<Layout title="Hash function">
  <p class="h-[150px]">
    The secret sauce that makes a hash table <FireText>blazingly fast</FireText>
    is a <strong>hash function</strong>.<br />
    Whenever you <strong>look up</strong> an entry, the hash function converts
    the <strong>key</strong> to a <strong>number</strong>.<br />When you
    <strong>reduce this number modulo</strong>
    the array's <strong>capacity</strong> (size), you get the item's
    <strong>index</strong>.
  </p>
  <div class="my-auto grid grid-cols-2 grid-rows-2 items-start justify-center">
    <CodeSnippet language="python" code={snippet} class="mt-[50px]" />
    <div class="col-1 row-2">
      <Entry key="foo" value={42} bind:entry={entry} />
    </div>
    <div class="row-span-2 grid place-items-center">
      <Buckets values={values} bind:table={table} />
    </div>
  </div>
  <Arrow p1={p1} p2={p2} />
</Layout>
