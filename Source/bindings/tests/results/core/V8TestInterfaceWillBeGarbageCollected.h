// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py. DO NOT MODIFY!

#ifndef V8TestInterfaceWillBeGarbageCollected_h
#define V8TestInterfaceWillBeGarbageCollected_h

#include "bindings/core/v8/ScriptWrappable.h"
#include "bindings/core/v8/ToV8.h"
#include "bindings/core/v8/V8Binding.h"
#include "bindings/core/v8/V8DOMWrapper.h"
#include "bindings/core/v8/V8EventTarget.h"
#include "bindings/core/v8/WrapperTypeInfo.h"
#include "bindings/tests/idls/core/TestInterfaceWillBeGarbageCollected.h"
#include "core/CoreExport.h"
#include "platform/heap/Handle.h"

namespace blink {

class V8TestInterfaceWillBeGarbageCollectedConstructor {
public:
    static v8::Local<v8::FunctionTemplate> domTemplate(v8::Isolate*);
    static const WrapperTypeInfo wrapperTypeInfo;
};

class V8TestInterfaceWillBeGarbageCollected {
public:
    CORE_EXPORT static bool hasInstance(v8::Local<v8::Value>, v8::Isolate*);
    static v8::Local<v8::Object> findInstanceInPrototypeChain(v8::Local<v8::Value>, v8::Isolate*);
    CORE_EXPORT static v8::Local<v8::FunctionTemplate> domTemplate(v8::Isolate*);
    static TestInterfaceWillBeGarbageCollected* toImpl(v8::Local<v8::Object> object)
    {
        return blink::toScriptWrappable(object)->toImpl<TestInterfaceWillBeGarbageCollected>();
    }
    CORE_EXPORT static TestInterfaceWillBeGarbageCollected* toImplWithTypeCheck(v8::Isolate*, v8::Local<v8::Value>);
    CORE_EXPORT static const WrapperTypeInfo wrapperTypeInfo;
    static void refObject(ScriptWrappable*);
    static void derefObject(ScriptWrappable*);
    template<typename VisitorDispatcher>
    static void trace(VisitorDispatcher visitor, ScriptWrappable* scriptWrappable)
    {
#if ENABLE(OILPAN)
        visitor->trace(scriptWrappable->toImpl<TestInterfaceWillBeGarbageCollected>());
#endif
    }
    static void constructorCallback(const v8::FunctionCallbackInfo<v8::Value>&);
    static const int eventListenerCacheIndex = v8DefaultWrapperInternalFieldCount + 0;
    static const int internalFieldCount = v8DefaultWrapperInternalFieldCount + 1;
    static void installConditionallyEnabledProperties(v8::Local<v8::Object>, v8::Isolate*) { }
    static void installConditionallyEnabledMethods(v8::Local<v8::Object>, v8::Isolate*) { }
};

template <>
struct V8TypeOf<TestInterfaceWillBeGarbageCollected> {
    typedef V8TestInterfaceWillBeGarbageCollected Type;
};

} // namespace blink

#endif // V8TestInterfaceWillBeGarbageCollected_h
