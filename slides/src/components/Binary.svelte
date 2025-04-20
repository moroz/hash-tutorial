<script lang="ts">
  export interface Props {
    binary: Uint8Array | number[];
    label?: string;
    highlighted?: number[];
    indexed?: boolean;
    wide?: boolean;
  }

  let {
    label,
    binary,
    indexed = false,
    highlighted = [],
    wide = false,
  }: Props = $props();
</script>

<table class="mapping" class:wide>
  {#if label}
    <thead>
      <tr>
        <th colspan="20">{label}</th>
      </tr>
    </thead>
  {/if}
  <tbody>
    <tr>
      {#each binary as byte, index}
        <td class:hl={highlighted.includes(index)}
          >{byte.toString(16).padStart(2, "0").toUpperCase()}</td
        >
      {/each}
    </tr>
    {#if indexed}
      <tr class="index"
        >{#each binary as _, index}
          <td>0x{index.toString(16).toUpperCase()}</td>
        {/each}</tr
      >
    {/if}
  </tbody>
</table>

<style>
  :global(.mapping + .mapping) {
    margin-top: 1.5rem;
  }

  .wide {
    table-layout: initial;
    width: auto;

    td {
      width: 3.5rem;
    }
  }

  .hl {
    background: oklch(0.865 0.127 207.078);
    color: black;
  }

  .index {
    color: rgba(255, 255, 255, 0.7);
    font-size: 0.75em;
  }
</style>
