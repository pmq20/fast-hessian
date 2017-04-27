# Libhessian

Pure C implementation of Hessian 2.0 Serialization Protocol

[![Build status](https://travis-ci.org/pmq20/libhessian.svg?branch=master)](https://travis-ci.org/pmq20/libhessian)
[![Build status](https://ci.appveyor.com/api/projects/status/rsu3tk3bmfhw76ye/branch/master?svg=true)](https://ci.appveyor.com/project/pmq20/libhessian/branch/master)

## API

All API return `1` on success and `0` on failures.

### Encoding

        short hessian_encode_null(uint8_t **out, size_t *len);
        short hessian_encode_int(int32_t val, uint8_t **out, size_t *len);
        short hessian_encode_date(uint64_t milliEpoch, uint8_t **out, size_t *len);
        short hessian_encode_long(int64_t val, uint8_t **out, size_t *len);
        short hessian_encode_string(char *str, size_t length, uint8_t **out, size_t *len);

### Decoding

        short hessian_decode_null(uint8_t *buffer);
        short hessian_decode_int(uint8_t *buffer, int32_t *out);
        short hessian_decode_date(uint8_t *buffer, uint64_t *out);
        short hessian_decode_long(uint8_t *buffer, int64_t *out);
        short hessian_decode_string(uint8_t *buffer, char *out_str, size_t *out_length);

## See Also

* [Hessian 2.0 Serialization Protocol](http://hessian.caucho.com/doc/hessian-serialization.html): a dynamically-typed, binary serialization and Web Services protocol designed for object-oriented transmission.
