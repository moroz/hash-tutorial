<script lang="ts">
  interface Props {
    title: string;
    children: any;
  }

  const { title, children }: Props = $props();
</script>

<div class="layout">
  <header><h2 class="font-bold text-3xl mt-0 mb-2">{title}</h2></header>
  <main>
    {@render children?.()}
  </main>
</div>

<style>
  .layout {
    display: flex;
    flex-direction: column;
    height: 100vh;
    padding: 3rem;
    width: 100%;
  }

  main {
    flex: 1;
    display: flex;
    flex-direction: column;
    align-items: stretch;
  }
</style>
