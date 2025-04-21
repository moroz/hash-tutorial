<script lang="ts">
  interface Props {
    key: string;
    value: any;
    entry?: any;
  }

  let { key, value, entry = $bindable() }: Props = $props();
</script>

<table
  class="table-fixed border-collapse border w-[calc(600px_-_3rem)] text-center bg-green-600 text-[1.75rem] h-[50px]"
  bind:this={entry}
>
  <tbody>
    <tr>
      <td class="border">"{key}"</td>
      <td class="border">{value}</td>
    </tr>
  </tbody>
</table>
