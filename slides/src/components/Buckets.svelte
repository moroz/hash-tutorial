<script lang="ts">
  type Entry = {
    key: string | null;
    value: number | null;
  };

  interface Props {
    values: Entry[];
  }

  const { values }: Props = $props();
</script>

<table>
  <thead>
    <tr>
      <th data-col="index"></th>
      <th>key</th>
      <th>value</th>
    </tr>
  </thead>
  <tbody>
    {#each values as entry, i}
      <tr>
        <td data-col="index">{i}</td>
        <td>{entry.key ?? ""}</td>
        <td>{entry.value ?? ""}</td>
      </tr>
    {/each}
  </tbody>
</table>

<style>
  table {
    table-layout: fixed;
    width: 800px;
    border-collapse: collapse;
    font-size: 1.25rem;
  }

  td,
  th {
    border: 1px solid currentColor;
    height: 40px;
  }

  [data-col="index"] {
    width: 4rem;
    border-left-color: transparent;
    border-top-color: transparent;
    border-bottom-color: transparent;
  }
</style>
