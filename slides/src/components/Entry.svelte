<script lang="ts">
  interface Props {
    key: string;
    value: any;
  }

  const { key, value }: Props = $props();
</script>

<table
  class="table-fixed border-collapse border w-[calc(600px_-_3rem)] h-14 text-center bg-green-600 text-[1.75rem]"
>
  <tbody>
    <tr>
      <td class="border">{key}</td>
      <td class="border">{value}</td>
    </tr>
  </tbody>
</table>
