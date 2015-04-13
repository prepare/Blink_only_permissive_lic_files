// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py. DO NOT MODIFY!

#ifndef V8TestInterfaceConstructor_h
#define V8TestInterfaceConstructor_h

#include "bindings/core/v8/ScriptWrappable.h"
#include "bindings/core/v8/ToV8.h"
#include "bindings/core/v8/V8Binding.h"
#include "bindings/core/v8/V8DOMWrapper.h"
#include "bindings/core/v8/WrapperTypeInfo.h"
#include "bindings/tests/idls/core/TestInterfaceConstructor.h"
#include "core/CoreExport.h"
#include "platform/heap/Handle.h"

namespace blink {

class V8TestInterfaceConstructorConstructor {
public:
    static v8::Local<v8::FunctionTemplate> domTemplate(v8::Isolate*);
    static const WrapperTypeInfo wrapperTypeInfo;
};

class V8TestInterfaceConstructor {
public:
    CORE_EXPORT static bool hasInstance(v8::Local<v8::Value>, v8::Isolate*);
    static v8::Local<v8::Object> findInstanceInPrototypeChain(v8::Local<v8::Value>, v8::Isolate*);
    CORE_EXPORT static v8::Local<v8::FunctionTemplate> domTemplate(v8::Isolate*);
    static TestInterfaceConstructor* toImpl(v8::Local<v8::Object> object)
    {
        return blink::toScriptWrappable(object)->toImpl<TestInterfaceConstructor>();
    }
    CORE_EXPORT static TestInterfaceConstructor* toImplWithTypeCheck(v8::Isolate*, v8::Local<v8::Value>);
    CORE_EXPORT static const WrapperTypeInfo wrapperTypeInfo;
    static void refObject(ScriptWrappable*);
    static void derefObject(ScriptWrappable*);
    template<typename VisitorDispatcher>
    static void trace(VisitorDispatcher visitor, ScriptWrappable* scriptWrappable)
    {
    }
    static void constructorCallback(const v8::FunctionCallbackInfo<v8::Value>&);
    static const int internalFieldCount = v8DefaultWrapperInternalFieldCount + 0;
    static void installConditionallyEnabledProperties(v8::Local<v8::Object>, v8::Isolate*) { }
    static void installConditionallyEnabledMethods(v8::Local<v8::Object>, v8::Isolate*) { }
};

template <>
struct V8TypeOf<TestInterfaceConstructor> {
    typedef V8TestInterfaceConstructor Type;
};

} // namespace blink

#endif // V8TestInterfaceConstructor_h
