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
  });
</script>

<Layout title="Tabular enlargement">
  <div class="grid grid-cols-2">
    <div class="flex justify-start items-start">
      <Buckets values={smaller} bind:table={left} />
    </div>
    <div class="flex justify-end">
      <Buckets values={larger} bind:table={right} />
    </div>
  </div>

  {#each arrows as [p1, p2]}
    <Arrow {p1} {p2} />
  {/each}
</Layout>
