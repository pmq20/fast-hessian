# Fast Hessian

High-performance C++ implementation of Hessian 2.0 Serialization Protocol for Node.js.

External Javascript API are 100% compatible with [Hessian.js](https://github.com/node-modules/hessian.js), serving as a drop-in replacement. Only the Hessian 2.0 part is re-implemented in C++; Hessian 1.0 is untouched with its original implementation. 

## Compete with Hessian.js

**Environment: node 8.0.0-pre + v8 5.7.492.69**

## Hessian.js

    hessian2 encode: number x 1,119,720 ops/sec ±1.39% (85 runs sampled)
    hessian2 encode: date   x   721,557 ops/sec ±1.16% (88 runs sampled)
    hessian2 encode: string x   841,823 ops/sec ±1.55% (83 runs sampled)

    hessian2 decode: number x 2,358,902 ops/sec ±1.18% (90 runs sampled)
    hessian2 decode: date   x   508,694 ops/sec ±0.98% (90 runs sampled)
    hessian2 decode: string x   253,542 ops/sec ±1.45% (87 runs sampled)

## Fast Hessian

    Fast hessian2 encode: number x 1,131,603 ops/sec ±1.20% (81 runs sampled)
    Fast hessian2 encode: date   x   952,233 ops/sec ±1.33% (82 runs sampled)
    Fast hessian2 encode: string x   668,330 ops/sec ±9.05% (68 runs sampled)

    Fast hessian2 decode: number x 10,408,116 ops/sec ±1.10% (87 runs sampled)
    Fast hessian2 decode: date   x  4,139,701 ops/sec ±1.04% (88 runs sampled)
    Fast hessian2 decode: string x  1,843,122 ops/sec ±5.17% (61 runs sampled)

## See Also

* [Hessian 2.0 Serialization Protocol](http://hessian.caucho.com/doc/hessian-serialization.html): a dynamically-typed, binary serialization and Web Services protocol designed for object-oriented transmission.
* [Hessian.js](https://github.com/node-modules/hessian.js): Hessian Serialization 1.0 and 2.0 written in pure JavaScript.
