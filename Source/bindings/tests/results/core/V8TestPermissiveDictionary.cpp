// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py. DO NOT MODIFY!

#include "config.h"
#include "V8TestPermissiveDictionary.h"

#include "bindings/core/v8/ExceptionState.h"

namespace blink {

void V8TestPermissiveDictionary::toImpl(v8::Isolate* isolate, v8::Local<v8::Value> v8Value, TestPermissiveDictionary& impl, ExceptionState& exceptionState)
{
    if (isUndefinedOrNull(v8Value))
        return;
    if (!v8Value->IsObject()) {
        // Do nothing.
        return;
    }

    v8::Local<v8::Object> v8Object = v8Value->ToObject(isolate);
    v8::TryCatch block;
    v8::Local<v8::Value> booleanMemberValue = v8Object->Get(v8String(isolate, "booleanMember"));
    if (block.HasCaught()) {
        exceptionState.rethrowV8Exception(block.Exception());
        return;
    }
    if (booleanMemberValue.IsEmpty() || booleanMemberValue->IsUndefined()) {
        // Do nothing.
    } else {
        bool booleanMember = booleanMemberValue->BooleanValue();
        impl.setBooleanMember(booleanMember);
    }

}

v8::Local<v8::Value> toV8(const TestPermissiveDictionary& impl, v8::Local<v8::Object> creationContext, v8::Isolate* isolate)
{
    v8::Local<v8::Object> v8Object = v8::Object::New(isolate);
    toV8TestPermissiveDictionary(impl, v8Object, creationContext, isolate);
    return v8Object;
}

void toV8TestPermissiveDictionary(const TestPermissiveDictionary& impl, v8::Local<v8::Object> dictionary, v8::Local<v8::Object> creationContext, v8::Isolate* isolate)
{
    if (impl.hasBooleanMember()) {
        dictionary->Set(v8String(isolate, "booleanMember"), v8Boolean(impl.booleanMember(), isolate));
    }

}

TestPermissiveDictionary NativeValueTraits<TestPermissiveDictionary>::nativeValue(const v8::Local<v8::Value>& value, v8::Isolate* isolate, ExceptionState& exceptionState)
{
    TestPermissiveDictionary impl;
    V8TestPermissiveDictionary::toImpl(isolate, value, impl, exceptionState);
    return impl;
}

} // namespace blink
