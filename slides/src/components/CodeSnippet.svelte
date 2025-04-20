<script lang="ts">
  import { Highlight } from "svelte-highlight";
  import c from "svelte-highlight/languages/c";
  import style from "svelte-highlight/styles/horizon-dark";

  const { code, onHighlight } = $props();

  function onhighlight() {
    console.log(arguments);
  }
</script>

<svelte:head>
  {@html style}
</svelte:head>

<Highlight language={c} {code} on:highlight={onhighlight} />
