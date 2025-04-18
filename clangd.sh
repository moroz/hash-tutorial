#!/bin/sh

uname="$(uname | tr -d '\n')"

if [ "$uname" = "Darwin" ]; then
cat <<-EOF > .clangd
CompileFlags:
  Add:
    - "-I$(brew --prefix criterion)/include"
    - "-L$(brew --prefix criterion)/lib"
    - "-lcunit"
EOF
fi

