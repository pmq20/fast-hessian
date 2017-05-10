/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of fast-hessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#include "hessian.h"

HessianPool *HessianPool::pool = nullptr;

v8::Local<v8::Uint8Array> HessianPool::Get(v8::Isolate *isolate, size_t size)
{
	// TODO mutex
	v8::EscapableHandleScope handle_scope(isolate);
	if (size < in_pool_threshold) {
		if (nullptr == pool) {
			pool = new HessianPool(isolate, v8::ArrayBuffer::New(isolate, pool_size));
		} else if (!pool->canAccomodate(size)) {
			pool->MakeWeak();
			pool = new HessianPool(isolate, v8::ArrayBuffer::New(isolate, pool_size));
		}
		return handle_scope.Escape(pool->Allocate(size));
	} else {
	    	return handle_scope.Escape(v8::Uint8Array::New(v8::ArrayBuffer::New(isolate, size), 0, size));
	}
}

v8::Local<v8::Uint8Array> HessianPool::Allocate(size_t size)
{
	v8::EscapableHandleScope handle_scope(isolate_);
	assert(offset_ + size <= pool_size);
	v8::Local<v8::Uint8Array> ret = v8::Uint8Array::New(ab_.Get(isolate_), offset_, size);
	offset_ += size;
	return handle_scope.Escape(ret);
}

void HessianPool::MakeWeak()
{
	ab_.MarkIndependent();
	ab_.SetWeak(this, WeakCallback, v8::WeakCallbackType::kParameter);
}

void HessianPool::WeakCallback(const v8::WeakCallbackInfo<HessianPool>& data)
{
	HessianPool *self = data.GetParameter();
	self->ab_.Reset();
	delete self;
}
