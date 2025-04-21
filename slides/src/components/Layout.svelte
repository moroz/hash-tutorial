<script lang="ts">
  interface Props {
    title: string;
    children: any;
  }

  const { title, children }: Props = $props();
</script>

<div class="layout">
  <header><h2>{title}</h2></header>
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

  h2 {
    margin: 0;
  }

  main {
    flex: 1;
    display: flex;
    flex-direction: column;
  }
</style>
