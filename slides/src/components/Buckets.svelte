<script lang="ts">
  type Entry = {
    key: string | null;
    value: number | null;
  };

  interface Props {
    values: (Entry | null)[];
    class?: string;
  }

  const { values, class: className }: Props = $props();
</script>

<table class={className}>
  <thead>
    <tr>
      <th scope="row"></th>
      <th>key</th>
      <th>value</th>
    </tr>
  </thead>
  <tbody>
    {#each values as entry, i}
      <tr class={{ empty: !entry }}>
        <th scope="row">{i}</th>
        <td>{entry?.key ? `"${entry.key}"` : "NULL"}</td>
        <td>{entry?.value ? entry.value : "0"}</td>
      </tr>
    {/each}
  </tbody>
</table>

<style>
  @reference "../style.css";

  table {
    @apply table-fixed text-center border-collapse;

    width: 600px;
    font-size: 1.75rem;
  }

  .empty {
    td:not(:first-child) {
      @apply bg-gray-800 text-gray-400;
    }
  }

  tr:not(.empty) td:not(:first-child) {
    @apply bg-green-600 text-white;
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
