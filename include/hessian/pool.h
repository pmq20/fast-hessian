/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of fast-hessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#ifndef HESSIAN_POOL_H_cQkdBmMC
#define HESSIAN_POOL_H_cQkdBmMC

#include "node.h"

class HessianPool {
public:
    static v8::Local<v8::Uint8Array> Get(v8::Isolate *isolate, size_t size);
    inline explicit HessianPool(v8::Isolate *isolate, v8::Local<v8::ArrayBuffer> ab) :
        isolate_(isolate), offset_(0), ab_(isolate, ab) { assert(!ab_.IsEmpty()); }
    inline ~HessianPool() { assert(ab_.IsEmpty()); }
    inline bool canAccomodate(size_t size) { return (size <= pool_size - offset_); }
    void MakeWeak();
    
private:
    static const size_t pool_size = /*128 */ 1024;
    static const size_t in_pool_threshold = pool_size / 2;
    static_assert(in_pool_threshold <= pool_size, "in-pool threshold should be bound by pool size");
    static HessianPool *pool;
    static void WeakCallback(const v8::WeakCallbackInfo<HessianPool>& data);
    v8::Local<v8::Uint8Array> HessianPool::Allocate(size_t size);
    v8::Isolate *isolate_;
    size_t offset_;
    v8::Persistent<v8::ArrayBuffer> ab_;
};

#endif /* end of include guard: HESSIAN_POOL_H_cQkdBmMC */
