# Libhessian

Pure C implementation of Hessian 2.0 Serialization Protocol

[![Build status](https://travis-ci.org/pmq20/libhessian.svg?branch=master)](https://travis-ci.org/pmq20/libhessian)

## API

### Encoding

All encoding API return the number of bytes that has been put into the output buffer `out`.

    size_t hessian_encode_int(int32_t val, uint8_t *out);
    size_t hessian_encode_date(uint64_t milliEpoch, uint8_t *out);
    size_t hessian_encode_long(uint64_t val, uint8_t *out);
    size_t hessian_encode_string(char *str, size_t length, uint8_t *out);

### Decoding

All decoding API return `1` on success and `0` on failures.

    short hessian_decode_int(uint8_t *buffer, int32_t *out);
    short hessian_decode_date(uint8_t *buffer, uint64_t *out);
    short hessian_decode_long(uint8_t *buffer, uint64_t *out);
    short hessian_decode_string(uint8_t *buffer, char *out_str, size_t *out_length);

## See Also

* [Hessian 2.0 Serialization Protocol](http://hessian.caucho.com/doc/hessian-serialization.html): a dynamically-typed, binary serialization and Web Services protocol designed for object-oriented transmission.
