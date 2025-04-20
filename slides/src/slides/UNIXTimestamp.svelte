<script>
  import useUNIXTime from "../lib/useUNIXTime.svelte";
  import hljs from "highlight.js/lib/core";
  let unix = useUNIXTime();

  const code = `\
#include <time.h>
#include <stdio.h>

time_t unixepoch() {
  struct timespec tp;
  clock_gettime(CLOCK_REALTIME, &tp);
  return tp.tv_sec;
}

int main() {
  time_t now = unixepoch();
  printf("%ld\\n", now); // %{epoch}
  return 0;
}`;

  const highlighted = $state(hljs.highlight(code, { language: "c" }).value);

  let html = $derived.by(() => {
    return highlighted.replace(`%{epoch}`, String(unix.time));
  });
</script>

<h2>2. Get current UNIX timestamp</h2>

<pre data-language="c"><code class="hljs">{@html html}</code></pre>
