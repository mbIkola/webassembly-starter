#!/bin/bash

$(npm bin)/wa compile -D __WEBASSEMBLY__ -l -O src/fibonacci.c -o ./dist/wa/fibonacci.wasm

