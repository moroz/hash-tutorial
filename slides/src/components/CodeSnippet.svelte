<script lang="ts">
  import { Highlight } from "svelte-highlight";
  import c from "svelte-highlight/languages/c";
  import python from "svelte-highlight/languages/python";
  import ruby from "svelte-highlight/languages/ruby";
  import style from "svelte-highlight/styles/horizon-dark";
  import go from "svelte-highlight/languages/go";
  import js from "svelte-highlight/languages/javascript";

  const langs = { c, python, ruby, go, js };

  const { code, language = "c", class: className = undefined } = $props();
</script>

<svelte:head>
  {@html style}
</svelte:head>

<Highlight
  language={langs[language as keyof typeof langs]}
  {code}
  class={className}
/>
