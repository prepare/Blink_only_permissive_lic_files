// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py. DO NOT MODIFY!

#include "config.h"
#include "V8TestInterfaceEventInit.h"

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/V8EventInit.h"

namespace blink {

void V8TestInterfaceEventInit::toImpl(v8::Isolate* isolate, v8::Local<v8::Value> v8Value, TestInterfaceEventInit& impl, ExceptionState& exceptionState)
{
    if (isUndefinedOrNull(v8Value))
        return;
    if (!v8Value->IsObject()) {
        exceptionState.throwTypeError("cannot convert to dictionary.");
        return;
    }

    V8EventInitDictionary::toImpl(isolate, v8Value, impl, exceptionState);
    if (exceptionState.hadException())
        return;

    v8::TryCatch block;
    v8::Local<v8::Object> v8Object;
    if (!v8Call(v8Value->ToObject(isolate->GetCurrentContext()), v8Object, block)) {
        exceptionState.rethrowV8Exception(block.Exception());
        return;
    }
    {
        v8::Local<v8::Value> stringMemberValue;
        if (!v8Object->Get(isolate->GetCurrentContext(), v8String(isolate, "stringMember")).ToLocal(&stringMemberValue)) {
            exceptionState.rethrowV8Exception(block.Exception());
            return;
        }
        if (stringMemberValue.IsEmpty() || stringMemberValue->IsUndefined()) {
            // Do nothing.
        } else {
            V8StringResource<> stringMember = stringMemberValue;
            if (!stringMember.prepare(exceptionState))
                return;
            impl.setStringMember(stringMember);
        }
    }

}

v8::Local<v8::Value> toV8(const TestInterfaceEventInit& impl, v8::Local<v8::Object> creationContext, v8::Isolate* isolate)
{
    v8::Local<v8::Object> v8Object = v8::Object::New(isolate);
    if (!toV8EventInitDictionary(impl, v8Object, creationContext, isolate))
        return v8::Local<v8::Value>();
    if (!toV8TestInterfaceEventInit(impl, v8Object, creationContext, isolate))
        return v8::Local<v8::Value>();
    return v8Object;
}

bool toV8TestInterfaceEventInit(const TestInterfaceEventInit& impl, v8::Local<v8::Object> dictionary, v8::Local<v8::Object> creationContext, v8::Isolate* isolate)
{
    if (impl.hasStringMember()) {
        if (!v8CallBoolean(dictionary->Set(isolate->GetCurrentContext(), v8String(isolate, "stringMember"), v8String(isolate, impl.stringMember()))))
            return false;
    }

    return true;
}

TestInterfaceEventInit NativeValueTraits<TestInterfaceEventInit>::nativeValue(v8::Isolate* isolate, v8::Local<v8::Value> value, ExceptionState& exceptionState)
{
    TestInterfaceEventInit impl;
    V8TestInterfaceEventInit::toImpl(isolate, value, impl, exceptionState);
    return impl;
}

} // namespace blink
