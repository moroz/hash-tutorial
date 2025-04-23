<script lang="ts">
  import Arrow from "../components/Arrow.svelte";
  import Buckets from "../components/Buckets.svelte";
  import Layout from "../components/Layout.svelte";

  const smaller = [
    { key: "bepis", value: 1337 },
    { key: "power level", value: 9001 },
    { key: "bar", value: 69 },
    { key: "baz", value: 420 },
    { key: "stonks", value: -1000 },
    null,
    null,
    {
      key: "foo",
      value: 42,
    },
  ];

  const larger = [
    { key: "power level", value: 9001 },
    null,
    { key: "baz", value: 420 },
    null,
    null,
    null,
    null,
    { key: "foo", value: 42 },
    { key: "bepis", value: 1337 },
    { key: "stonks", value: -1000 },
    { key: "bar", value: 69 },
    null,
    null,
    null,
    null,
    null,
  ];

  let left: HTMLTableElement | null = $state(null);
  let right: HTMLTableElement | null = $state(null);

  let arrows = $state<any[]>([]);

  function recalculateArrows() {
    if (!left || !right) return;

    let newArrows = [];

    for (let i = 0; i < smaller.length; i++) {
      const l = smaller[i];
      if (l === null) continue;

      const rIndex = larger.findIndex((entry) => entry?.key === l.key);
      if (rIndex === -1) continue;

      const leftRow = left.querySelector(`tbody tr:nth-child(${i + 1})`);
      const rightRow = right.querySelector(`tbody tr:nth-child(${rIndex + 1})`);
      if (!leftRow || !rightRow) continue;

      const r1 = leftRow.getBoundingClientRect();
      const r2 = rightRow.getBoundingClientRect();

      const p1 = { x: r1.right, y: r1.top + r1.height / 2 };
      const p2 = { x: r2.left, y: r2.top + r2.height / 2 };

      newArrows.push([p1, p2]);
    }

    arrows = newArrows;
  }

  $effect(() => {
    recalculateArrows();

    window.addEventListener("resize", recalculateArrows);

    return () => {
      window.removeEventListener("resize", recalculateArrows);
    };
  });
</script>

<Layout title="Tabular enlargement">
  <p>
    When a table becomes <strong>too full</strong> (when it reaches the
    <strong>maximum load factor</strong>), we need to <strong>resize</strong>
    it.<br />We allocate a new, larger table, and
    <strong>insert all existing entries</strong>, one by one.<br />Some entries
    will end up at new indices.
  </p>

  <div class="flex gap-[500px] items-center m-auto">
    <div class="flex justify-start flex-col text-center gap-2">
      <Buckets values={smaller} bind:table={left} />
      <span class="text-xl">Old table: 6/8, load factor: 0.75.</span>
    </div>
    <div class="flex justify-end text-center flex-col gap-2">
      <Buckets values={larger} bind:table={right} />
      <span class="text-xl">New table: 6/16, load factor: 0.375.</span>
    </div>
  </div>

  {#each arrows as [p1, p2]}
    <Arrow {p1} {p2} />
  {/each}
</Layout>
