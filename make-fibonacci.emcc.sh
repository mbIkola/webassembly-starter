#!/bin/bash

emcc -s DISABLE_EXCEPTION_CATCHING=1 -s NO_FILESYSTEM=1  -s RETAIN_COMPILER_SETTINGS=1 -s MODULARIZE=1 -s ERROR_ON_UNDEFINED_SYMBOLS=1 -O3  -s WASM=1 -s BUILD_AS_WORKER=1 -s PROXY_TO_WORKER=1  -o dist/worker/fibonacci.worker.js ./src/fibonacci.c

emcc -s DISABLE_EXCEPTION_CATCHING=1 -s NO_FILESYSTEM=1  -s RETAIN_COMPILER_SETTINGS=1 -s ERROR_ON_UNDEFINED_SYMBOLS=1 -O3  -s WASM=1 -s SIDE_MODULE=1 -s "BINARYEN_METHOD='native-wasm,asmjs'" -s BINARYEN_ASYNC_COMPILATION=1 -o dist/side_module/fibonacci.wasm ./src/fibonacci.c
