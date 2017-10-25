
// program.js



const assembly = require("webassembly");
const Benchmark = require('benchmark');
window.Benchmark = Benchmark;

const suite = new Benchmark.Suite;


var wa = null, emscripten = null, worker = null;

var promises = [
    assembly.load("wa/fibonacci.wasm")
       .then(module => {
            console.log("WebAssembly load ok : " , module.exports);
            wa = module;
        }),
/*
    assembly.load('side_module/fibonacci.wasm')
        .then(module => {
            console.log("emscripten side_module loaded: ", module.exports);
            emscripten = module;
        }, err => { console.error("side_module err", err)}),


    assembly.load('worker/fibonacci.worker.wasm')
        .then(module => {
            console.log("Worker loaded", module.exports);
            worker = module;
        }, err => { console.error("emscripten module err", err); })*/
];

function fiboJs(num){
    var a = 1, b = 0, temp;

    while (num >= 0){
        temp = a;
        a = a + b;
        b = temp;
        num--;
    }

    return b;
}

Promise.all(promises).then(() => {
    window.fibo  = wa; 
    suite.add('WA', () => wa.exports.fibonacci(40))
            .add('JS ', () => fiboJs(40) )
//         .add('Binaryen', () => emscripten.exports.fibonacci(40))
//         .add('EMSCripten Worker', () => worker.exports.fibonacci(40))
         .on('complete', () => { console.dir(this); console.log("Complete."); })
         .run({'async': true})

});



