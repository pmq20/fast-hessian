# Fast Hessian

High-performance C++ implementation of Hessian 2.0 Serialization Protocol for Node.js.

External Javascript API are 100% compatible with [Hessian.js](https://github.com/node-modules/hessian.js), serving as a drop-in replacement. Only the Hessian 2.0 part is re-implemented in C++; Hessian 1.0 is untouched with its original implementation. 

## Compete with Hessian.js

**Environment: node 8.0.0-pre + v8 5.7.492.69**

## API

There are only 2 top level API, which internally calls different types of encoding and decoding API automatically.

- `void hessian_encode(const v8::FunctionCallbackInfo<v8::Value>& args)`
- `void hessian_decode(const v8::FunctionCallbackInfo<v8::Value>& args)`

### Encoding

All API returns `1` when encoding succeeds and `0` on failures.

- `short hessian_encode_null(uint8_t **out, size_t *len)`
- `short hessian_encode_int(int32_t val, uint8_t **out, size_t *len)`
- `short hessian_encode_date(uint64_t milliEpoch, uint8_t **out, size_t *len)`
- `short hessian_encode_long(int64_t val, uint8_t **out, size_t *len)`
- `short hessian_encode_string(v8::Local<v8::String> &str, uint8_t **out, size_t *len)`

### Decoding

All API returns `1` when decoding succeeds and `0` on failures.
All API accept argument `args` of type `const v8::FunctionCallbackInfo<v8::Value>&`, into which the decoded result shall be put.

- `short hessian_decode_string(uint8_t * const buf, const size_t buf_length, args)`
- `short hessian_decode_bytes(uint8_t * const buf, const size_t buf_length, args)`
- `short hessian_decode_long(uint8_t * const buf, const size_t buf_length, args)`
- `short hessian_decode_object(uint8_t * const buf, const size_t buf_length, args)`
- `short hessian_decode_double(uint8_t * const buf, const size_t buf_length, args)`
- `short hessian_decode_bool(uint8_t * const buf, const size_t buf_length, args)`
- `short hessian_decode_hash_map(uint8_t * const buf, const size_t buf_length, args)`
- `short hessian_decode_int(uint8_t * const buf, const size_t buf_length, args)`
- `short hessian_decode_date(uint8_t * const buf, const size_t buf_length, args)`
- `short hessian_decode_map(uint8_t * const buf, const size_t buf_length, args)`
- `short hessian_decode_null(uint8_t * const buf, const size_t buf_length, args)`
- `short hessian_decode_ref(uint8_t * const buf, const size_t buf_length, args)`
- `short hessian_decode_array(uint8_t * const buf, const size_t buf_length, args)`

## See Also

* [Hessian 2.0 Serialization Protocol](http://hessian.caucho.com/doc/hessian-serialization.html): a dynamically-typed, binary serialization and Web Services protocol designed for object-oriented transmission.
* [Hessian.js](https://github.com/node-modules/hessian.js): Hessian Serialization 1.0 and 2.0 written in pure JavaScript.
