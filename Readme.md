# WebAssembly Starter Project / Boilerplate 

Simple boilerplate to compile and run `.wasm` files



## Development
You'll need to have EMSDK installed somewhere in your system. 
I would recommend downloading and installing 
[Portable Emscripten SDK](https://kripken.github.io/emscripten-site/docs/getting_started/downloads.html)

## HowTo wasm

### C source -> asm2wasm -> wasm (cmake + emscripten) 
```bash
# EMSCRIPTEN=/opt/emsdk-portable/emscripten/1.37.22
$ CFLAGS="-O3"
$ LFLAGS="-O3 -g0 -s 'EXPORTED_FUNCTIONS=[\"fibonacci\"] -s BINARYEN=1'"
$ cmake -DCMAKE_TOOLCHAIN_FILE=$EMSCRIPTEN/cmake/Modules/Platform/Emscripten.cmake \
 -DCMAKE_C_FLAGS="$CFLAGS"  \
 -DCMAKE_EXE_LINKER_FLAGS="$LFLAGS"
$ cmake --build .
```
Output would be: 
 - wast file (S-Expressions, human readable representation of webAssembly)
 - mapped globals: json with list of imported and exported functions (including $EXPORTED_FUNCTIONS).
 - js-wrapper with fallback code to asm.js
 - asm.js code

After compile step you have to convert wast to wasm using Binaryen's wasm-as tool:
```bash
/opt/binaryen/bin/wasm-as fibonacci.wast > fibonacci.wasm
```

Unfortunatelly you'll get "wasm load error" in browser. Need to play with -O3/-Os to get it working everywhere
  
### C source -> LLVM -> s2wasm -> wasm 
   
```bash
cmake -DLLVM_EXPERIMENTAL_TARGETS_TO_BUILD=WebAssembly -DCMAKE_EXE_LINKER_FLAGS="-s WASM_BACKEND=1"
```   

### clang  -> llc -> s2wasm -> wasm-as 
```bash
$ clang -emit-llvm --target=wasm32 -S fibonacci.c 
$ llc fibonacci.ll -march wasm
$ s2wasm fibonacii.s > fibonacci.wast
$ wasm-as fibonacci.wast > fibonacci.wasm
```
Тот еще пиздец. 

### Рабочий вариант без мозготраха

```bash
$ npm install --save webassembly
$ $(npm bin)/wa compile -D __WEBASSEMBLY__ -l -O src/fibonacci.c -o ./dist/wa/fibonacci.wasm
```

```javascript
/// fibonacci.loader.js
const assembly = require('webassembly');
assembly.load("fibonacci.wasm").then( module => {
    module.exports.fibonacci(100500); 
});
```

```bash
$ # browserify may be replaced with webpack/gulp/systemjs/whatever. Just an example. 
$ $(npm bin)/browserify ./fibonacci.loader.js -o dist/fibo.js
```


## References / Further reading
- [WebAssembly Interpreter][wasm-interpreter]
- [WebAssembly Specification][spec]
- [WABT: WebAssemblt Binary Toolkit][wabt] 
- [wat2wasm and wast2json][wabt-git]
- [Sanitizers : ASAN MSAN LSAN UBSAN][sanitizers]

## License   ![WTFPL Logo](/doc/img/wtfpl-badge-1.png)  
Project is made available under the terms of the [WTFPL][wtfpl]. 

See the [LICENSE][license] file that accompanies this distribution for the full text of license.

[license]:  https://github.com/mbIkola/webassembly-starter/blob/master/LICENSE
[wtfpl]: http://www.wtfpl.net/
[wasm-interpreter]: https://github.com/WebAssembly/spec/tree/master/interpreter
[spec]: https://webassembly.github.io/spec/
[wabt]: http://webassembly.org/getting-started/advanced-tools/
[wabt-git]: https://github.com/WebAssembly/wabt
[sanitizers]: https://github.com/google/sanitizers



