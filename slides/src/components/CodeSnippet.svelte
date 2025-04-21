<script lang="ts">
  import { Highlight } from "svelte-highlight";
  import c from "svelte-highlight/languages/c";
  import python from "svelte-highlight/languages/python";
  import style from "svelte-highlight/styles/horizon-dark";

  const langs = { c, python };

  const { code, language = "c" } = $props();
</script>

<svelte:head>
  {@html style}
</svelte:head>

<Highlight language={langs[language as keyof typeof langs]} {code} />
