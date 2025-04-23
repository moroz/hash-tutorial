<script lang="ts">
  type Entry = {
    pending?: boolean;
    key: string | null;
    value: number | null;
  };

  interface Props {
    values: (Entry | null)[];
    class?: string;
    table?: any;
  }

  let { values, class: className, table = $bindable() }: Props = $props();
</script>

<div class="wrapper">
  <table class={className} bind:this={table}>
    <thead>
      <tr>
        <th scope="row"></th>
        <th>key</th>
        <th>value</th>
      </tr>
    </thead>
    <tbody>
      {#each values as entry, i}
        <tr class={{ empty: !entry, pending: entry?.pending }}>
          <th scope="row">{i}</th>
          <td>{entry?.key ? `"${entry.key}"` : "NULL"}</td>
          <td>{entry?.value ? entry.value : "0"}</td>
        </tr>
      {/each}
    </tbody>
  </table>
</div>

<style>
  @reference "../style.css";

  .wrapper {
    --table-width: 650px;
    width: calc(var(--table-width) - 3em);
    display: flex;
    justify-content: flex-end;

    @apply text-3xl;
  }

  table {
    @apply table-fixed border-collapse text-center;

    width: var(--table-width);
    flex-shrink: 0;
  }

  .empty {
    td {
      @apply bg-gray-800 text-gray-400;
    }
  }

  tr {
    height: 60px;
  }

  tr:not(.empty) td {
    @apply bg-green-600 text-white;
  }

  tr.pending td {
    @apply bg-neutral-600 text-neutral-300;
  }

  td,
  th {
    border: 1px solid #fff;
  }

  thead th {
    border-top: 0;
    border-left: 0;
    border-right: 0;
  }

  th[scope="row"] {
    width: 3em;
    text-align: center;
    border-left-color: transparent;
    border-top-color: transparent;
    border-bottom-color: transparent;
  }
</style>
