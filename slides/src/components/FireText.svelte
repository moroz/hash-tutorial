<script lang="ts">
  const { children } = $props();
</script>

<span class="fire-text">{@render children?.()}</span>

<style>
  .fire-text {
    font-weight: bold;
    background: linear-gradient(-45deg, #ff9a00, #ff6126, #ff0000, #ffe600);
    background-size: 400% 400%;
    -webkit-background-clip: text;
    background-clip: text;
    -webkit-text-fill-color: transparent;
    animation: fire 3s ease-in-out infinite;
  }

  @keyframes fire {
    0% {
      background-position: 0% 50%;
    }
    50% {
      background-position: 100% 50%;
    }
    100% {
      background-position: 0% 50%;
    }
  }
</style>
