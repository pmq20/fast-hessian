# Fast Hessian

High-performance C++ implementation of Hessian 2.0 Serialization Protocol for Node.js.

External Javascript API are 100% compatible with [Hessian.js](https://github.com/node-modules/hessian.js), serving as a drop-in replacement. Only the Hessian 2.0 part is re-implemented in C++; Hessian 1.0 is untouched with its original implementation. 

## Why is it fast?

- When encoding, Fast Hessian maintains a shared memory pool so that less memory allocations are invoked.
  - cf. [include/hessian/pool.h](https://github.com/pmq20/fast-hessian/blob/master/include/hessian/pool.h) and [src/hessian_pool.cc](https://github.com/pmq20/fast-hessian/blob/master/src/hessian_pool.cc)
- When decoding, Fast Hessian produces no temporary buffers and outputs the result directly.

## Compete with Hessian.js

**Environment: node 8.0.0-pre + v8 5.7.492.69**

### Encoding

    hessian2 encode: number         x 1,560,679 ops/sec ±0.73% (90 runs sampled)
    Fast hessian2 encode: number    x 3,032,388 ops/sec ±0.44% (90 runs sampled)

    hessian2 encode: date           x   906,503 ops/sec ±1.42% (87 runs sampled)
    Fast hessian2 encode: date      x 1,893,531 ops/sec ±0.51% (92 runs sampled)

    hessian2 encode: string         x 1,137,613 ops/sec ±1.30% (91 runs sampled)
    Fast hessian2 encode: string    x 1,877,451 ops/sec ±0.44% (95 runs sampled)

### Decoding

    hessian2 decode: number         x 2,358,902 ops/sec ±1.18% (90 runs sampled)
    Fast hessian2 decode: number    x 10,408,116 ops/sec ±1.10% (87 runs sampled)

    hessian2 decode: date           x   508,694 ops/sec ±0.98% (90 runs sampled)
    Fast hessian2 decode: date      x  4,139,701 ops/sec ±1.04% (88 runs sampled)

    hessian2 decode: string         x   253,542 ops/sec ±1.45% (87 runs sampled)
    Fast hessian2 decode: string    x  1,843,122 ops/sec ±5.17% (61 runs sampled)

## See Also

* [Hessian 2.0 Serialization Protocol](http://hessian.caucho.com/doc/hessian-serialization.html): a dynamically-typed, binary serialization and Web Services protocol designed for object-oriented transmission.
* [Hessian.js](https://github.com/node-modules/hessian.js): Hessian Serialization 1.0 and 2.0 written in pure JavaScript.
