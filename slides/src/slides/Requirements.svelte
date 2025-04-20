<script lang="ts">
  import shell from "svelte-highlight/languages/shell";
  import make from "svelte-highlight/languages/makefile";
  import { Highlight } from "svelte-highlight";

  const makefile = `\
# Set includes and linker flags in Makefile
UNAME_S := $(shell uname -s)
ARCH := $(shell arch)

ifeq ($(UNAME_S),Darwin)
	ifeq ($(ARCH),arm64)
		OPENSSL_PREFIX := /opt/homebrew/opt/openssl@3
	else
		OPENSSL_PREFIX := /usr/local/opt/openssl@3
	endif
	CFLAGS += -I$(OPENSSL_PREFIX)/include
	LDFLAGS = -L$(OPENSSL_PREFIX)/lib -lssl -lcrypto
endif`;

  const install = `\
# macOS
brew install openssl@3

# Debian/Ubuntu
sudo apt install -y openssl libssl-dev`;
</script>

<h2>Install OpenSSL 3.0</h2>

<section>
  <Highlight language={shell} code={install} />
  <Highlight language={make} code={makefile} />
</section>

<style>
  section {
    width: 1200px;
    height: auto;
    tab-size: 4;
    margin: 0;
  }

  section :global(pre) {
    width: 100%;
  }
</style>
