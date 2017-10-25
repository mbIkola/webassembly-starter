#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#pragma message "EmScripten/Binaryen"
#endif

// expect what wa-compile launched with -D __WEBASSEMBLY__
#ifdef __WEBASSEMBLY__ 
#include <webassembly.h>
#pragma message "WebAssembly"
#endif 


#ifndef export 
#define export 
#endif 

#ifndef EMSCRIPTEN_KEEPALIVE 
#define EMSCRIPTEN_KEEPALIVE __attribute__((used))
#endif


export unsigned long EMSCRIPTEN_KEEPALIVE fibonacci(unsigned int num ) { 
    unsigned int first=0, second=1, next = 1; 
    for ( int i = 1; i<= num ; i++ ) {
        next = first + second; 
        first = second; 
        second = next; 
    }
    return next; 
}

export float EMSCRIPTEN_KEEPALIVE inv_sqrt(float x) {
    float xhalf = 0.5f * x; 
    int i = *(int *)&x; 
    i = 0x5f3759df - (i>>1); // WTF ?
    x = *(float *)&i;
    x = x * (1.5f - (xhalf * x * x)); // newton method, 1 iteration;
    return x;
}




#ifndef __EMSCRIPTEN__
#ifndef __WEBASSEMBLY__
#include <stdio.h>
#pragma message "Compiling as executable"

int main() {
    for ( unsigned int i=0; i<100; i++) {
        printf("%d : %lu\n", i, fibonacci(i)); 
    }
    return 0;
}


#endif 
#endif 
