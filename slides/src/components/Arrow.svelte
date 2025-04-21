<script lang="ts">
  import { getArrow } from "perfect-arrows";
  import { onMount } from "svelte";

  interface Point {
    x: number;
    y: number;
  }

  interface Props {
    p1: Point | null;
    p2: Point | null;
  }

  const { p1, p2 }: Props = $props();
  $inspect(p1, p2);

  let arrow = $derived.by(() => {
    if (!p1 || !p2) return [];
    return getArrow(p1.x, p1.y, p2.x, p2.y, {
      bow: 0,
      padEnd: 0,
      flip: true,
    });
  });

  const [sx, sy, cx, cy, ex, ey, ae] = $derived(arrow);
  const endAngleAsDegrees = $derived(ae * (180 / Math.PI));

  let width = $state(window.visualViewport?.width);
  let height = $state(window.visualViewport?.height);

  function getViewport() {
    width = window.visualViewport?.width;
    height = window.visualViewport?.width;
  }

  onMount(() => {
    window.addEventListener("resize", getViewport);

    return () => {
      window.removeEventListener("resize", getViewport);
    };
  });
</script>

{#if p1 && p2}
  <svg
    viewBox="0 0 {width} {height}"
    {width}
    {height}
    stroke="currentColor"
    fill="currentColor"
    stroke-width="3"
    class="absolute inset-0"
  >
    <circle cx={sx} cy={sy} r="4" />
    <path d={`M${sx},${sy} Q${cx},${cy} ${ex},${ey}`} fill="none" />
    <polygon
      points="0,-6 12,0 0,6"
      transform={`translate(${ex},${ey}) rotate(${endAngleAsDegrees})`}
    />
  </svg>
{/if}
