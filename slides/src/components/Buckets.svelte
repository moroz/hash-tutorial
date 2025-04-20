<script lang="ts">
  type Entry = {
    key: string | null;
    value: number | null;
  };

  interface Props {
    values: (Entry | null)[];
  }

  const { values }: Props = $props();
</script>

<table>
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
  table {
    table-layout: fixed;
    width: 600px;
    text-align: center;
    border-collapse: collapse;
    font-size: 1.25rem;
  }

  .empty {
    td:not(:first-child) {
      color: #8c8c8c;
    }
  }

  tr:not(.empty) td:not(:first-child) {
    background: rgba(255, 255, 255, 0.1);
  }

  td,
  th {
    border: 1px solid #fff;
    height: 40px;
  }

  th[scope="row"] {
    width: 3rem;
    text-align: center;
    border-left-color: transparent;
    border-top-color: transparent;
    border-bottom-color: transparent;
  }
</style>
