// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py. DO NOT MODIFY!

#ifndef V8TestInterface5_h
#define V8TestInterface5_h

#if ENABLE(CONDITION)
#include "bindings/core/v8/ScriptWrappable.h"
#include "bindings/core/v8/ToV8.h"
#include "bindings/core/v8/V8Binding.h"
#include "bindings/core/v8/V8DOMWrapper.h"
#include "bindings/core/v8/V8TestInterfaceEmpty.h"
#include "bindings/core/v8/WrapperTypeInfo.h"
#include "bindings/tests/idls/modules/TestInterface5Implementation.h"
#include "platform/heap/Handle.h"

namespace blink {

class V8TestInterface5 {
public:
    static bool hasInstance(v8::Local<v8::Value>, v8::Isolate*);
    static v8::Local<v8::Object> findInstanceInPrototypeChain(v8::Local<v8::Value>, v8::Isolate*);
    static v8::Local<v8::FunctionTemplate> domTemplate(v8::Isolate*);
    static TestInterface5Implementation* toImpl(v8::Local<v8::Object> object)
    {
        return blink::toScriptWrappable(object)->toImpl<TestInterface5Implementation>();
    }
    static TestInterface5Implementation* toImplWithTypeCheck(v8::Isolate*, v8::Local<v8::Value>);
    static const WrapperTypeInfo wrapperTypeInfo;
    static void refObject(ScriptWrappable*);
    static void derefObject(ScriptWrappable*);
    static void trace(Visitor* visitor, ScriptWrappable* scriptWrappable)
    {
    }
    static void visitDOMWrapper(v8::Isolate*, ScriptWrappable*, const v8::Persistent<v8::Object>&);
    static ActiveDOMObject* toActiveDOMObject(v8::Local<v8::Object>);
    static void legacyCallCustom(const v8::FunctionCallbackInfo<v8::Value>&);
    static const int internalFieldCount = v8DefaultWrapperInternalFieldCount + 0;
    static void installConditionallyEnabledProperties(v8::Local<v8::Object>, v8::Isolate*);
    static void installConditionallyEnabledMethods(v8::Local<v8::Object>, v8::Isolate*);
};

template<typename CallbackInfo>
inline void v8SetReturnValue(const CallbackInfo& callbackInfo, TestInterface5Implementation* impl)
{
    v8SetReturnValue(callbackInfo, toV8(impl, callbackInfo.Holder(), callbackInfo.GetIsolate()));
}

template<typename CallbackInfo>
inline void v8SetReturnValueForMainWorld(const CallbackInfo& callbackInfo, TestInterface5Implementation* impl)
{
     v8SetReturnValue(callbackInfo, toV8(impl, callbackInfo.Holder(), callbackInfo.GetIsolate()));
}

template<typename CallbackInfo>
inline void v8SetReturnValueFast(const CallbackInfo& callbackInfo, TestInterface5Implementation* impl, const ScriptWrappable*)
{
     v8SetReturnValue(callbackInfo, toV8(impl, callbackInfo.Holder(), callbackInfo.GetIsolate()));
}

} // namespace blink
#endif // ENABLE(CONDITION)

#endif // V8TestInterface5_h
