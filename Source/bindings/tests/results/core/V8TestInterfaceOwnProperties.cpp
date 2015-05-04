// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py. DO NOT MODIFY!

#include "config.h"
#include "V8TestInterfaceOwnProperties.h"

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/V8DOMConfiguration.h"
#include "bindings/core/v8/V8ObjectConstructor.h"
#include "core/dom/ContextFeatures.h"
#include "core/dom/Document.h"
#include "platform/RuntimeEnabledFeatures.h"
#include "platform/TraceEvent.h"
#include "wtf/GetPtr.h"
#include "wtf/RefPtr.h"

namespace blink {

const WrapperTypeInfo V8TestInterfaceOwnProperties::wrapperTypeInfo = { gin::kEmbedderBlink, V8TestInterfaceOwnProperties::domTemplate, V8TestInterfaceOwnProperties::refObject, V8TestInterfaceOwnProperties::derefObject, V8TestInterfaceOwnProperties::trace, 0, 0, V8TestInterfaceOwnProperties::preparePrototypeObject, V8TestInterfaceOwnProperties::installConditionallyEnabledProperties, "TestInterfaceOwnProperties", &V8TestInterfaceEmpty::wrapperTypeInfo, WrapperTypeInfo::WrapperTypeObjectPrototype, WrapperTypeInfo::ObjectClassId, WrapperTypeInfo::NotInheritFromEventTarget, WrapperTypeInfo::Independent, WrapperTypeInfo::RefCountedObject };

// This static member must be declared by DEFINE_WRAPPERTYPEINFO in TestInterfaceOwnProperties.h.
// For details, see the comment of DEFINE_WRAPPERTYPEINFO in
// bindings/core/v8/ScriptWrappable.h.
const WrapperTypeInfo& TestInterfaceOwnProperties::s_wrapperTypeInfo = V8TestInterfaceOwnProperties::wrapperTypeInfo;

namespace TestInterfaceOwnPropertiesV8Internal {

static void noExposeJSAccessorAttributeAttributeGetter(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    v8::Local<v8::Object> holder = info.Holder();
    TestInterfaceOwnProperties* impl = V8TestInterfaceOwnProperties::toImpl(holder);
    v8SetReturnValueInt(info, impl->noExposeJSAccessorAttribute());
}

static void noExposeJSAccessorAttributeAttributeGetterCallback(v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMGetter");
    TestInterfaceOwnPropertiesV8Internal::noExposeJSAccessorAttributeAttributeGetter(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void noExposeJSAccessorAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<void>& info)
{
    v8::Local<v8::Object> holder = info.Holder();
    ExceptionState exceptionState(ExceptionState::SetterContext, "noExposeJSAccessorAttribute", "TestInterfaceOwnProperties", holder, info.GetIsolate());
    TestInterfaceOwnProperties* impl = V8TestInterfaceOwnProperties::toImpl(holder);
    int cppValue = toInt32(info.GetIsolate(), v8Value, NormalConversion, exceptionState);
    if (exceptionState.throwIfNeeded())
        return;
    impl->setNoExposeJSAccessorAttribute(cppValue);
}

static void noExposeJSAccessorAttributeAttributeSetterCallback(v8::Local<v8::Name>, v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<void>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMSetter");
    TestInterfaceOwnPropertiesV8Internal::noExposeJSAccessorAttributeAttributeSetter(v8Value, info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void exposeJSAccessorAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    v8::Local<v8::Object> holder = info.Holder();
    TestInterfaceOwnProperties* impl = V8TestInterfaceOwnProperties::toImpl(holder);
    v8SetReturnValueInt(info, impl->exposeJSAccessorAttribute());
}

static void exposeJSAccessorAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMGetter");
    TestInterfaceOwnPropertiesV8Internal::exposeJSAccessorAttributeAttributeGetter(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void exposeJSAccessorAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info)
{
    v8::Local<v8::Object> holder = info.Holder();
    ExceptionState exceptionState(ExceptionState::SetterContext, "exposeJSAccessorAttribute", "TestInterfaceOwnProperties", holder, info.GetIsolate());
    TestInterfaceOwnProperties* impl = V8TestInterfaceOwnProperties::toImpl(holder);
    int cppValue = toInt32(info.GetIsolate(), v8Value, NormalConversion, exceptionState);
    if (exceptionState.throwIfNeeded())
        return;
    impl->setExposeJSAccessorAttribute(cppValue);
}

static void exposeJSAccessorAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    v8::Local<v8::Value> v8Value = info[0];
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMSetter");
    TestInterfaceOwnPropertiesV8Internal::exposeJSAccessorAttributeAttributeSetter(v8Value, info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void doNotExposeJSAccessorAttributeAttributeGetter(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    v8::Local<v8::Object> holder = info.Holder();
    TestInterfaceOwnProperties* impl = V8TestInterfaceOwnProperties::toImpl(holder);
    v8SetReturnValueInt(info, impl->doNotExposeJSAccessorAttribute());
}

static void doNotExposeJSAccessorAttributeAttributeGetterCallback(v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMGetter");
    TestInterfaceOwnPropertiesV8Internal::doNotExposeJSAccessorAttributeAttributeGetter(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void doNotExposeJSAccessorAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<void>& info)
{
    v8::Local<v8::Object> holder = info.Holder();
    ExceptionState exceptionState(ExceptionState::SetterContext, "doNotExposeJSAccessorAttribute", "TestInterfaceOwnProperties", holder, info.GetIsolate());
    TestInterfaceOwnProperties* impl = V8TestInterfaceOwnProperties::toImpl(holder);
    int cppValue = toInt32(info.GetIsolate(), v8Value, NormalConversion, exceptionState);
    if (exceptionState.throwIfNeeded())
        return;
    impl->setDoNotExposeJSAccessorAttribute(cppValue);
}

static void doNotExposeJSAccessorAttributeAttributeSetterCallback(v8::Local<v8::Name>, v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<void>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMSetter");
    TestInterfaceOwnPropertiesV8Internal::doNotExposeJSAccessorAttributeAttributeSetter(v8Value, info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

} // namespace TestInterfaceOwnPropertiesV8Internal

static const V8DOMConfiguration::AttributeConfiguration V8TestInterfaceOwnPropertiesAttributes[] = {
    {"noExposeJSAccessorAttribute", TestInterfaceOwnPropertiesV8Internal::noExposeJSAccessorAttributeAttributeGetterCallback, TestInterfaceOwnPropertiesV8Internal::noExposeJSAccessorAttributeAttributeSetterCallback, 0, 0, 0, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::ExposedToAllScripts, V8DOMConfiguration::OnInstance},
    {"doNotExposeJSAccessorAttribute", TestInterfaceOwnPropertiesV8Internal::doNotExposeJSAccessorAttributeAttributeGetterCallback, TestInterfaceOwnPropertiesV8Internal::doNotExposeJSAccessorAttributeAttributeSetterCallback, 0, 0, 0, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::ExposedToAllScripts, V8DOMConfiguration::OnInstance},
};

static const V8DOMConfiguration::AccessorConfiguration V8TestInterfaceOwnPropertiesAccessors[] = {
    {"exposeJSAccessorAttribute", TestInterfaceOwnPropertiesV8Internal::exposeJSAccessorAttributeAttributeGetterCallback, TestInterfaceOwnPropertiesV8Internal::exposeJSAccessorAttributeAttributeSetterCallback, 0, 0, 0, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::ExposedToAllScripts},
};

static void installV8TestInterfaceOwnPropertiesTemplate(v8::Local<v8::FunctionTemplate> functionTemplate, v8::Isolate* isolate)
{
    functionTemplate->ReadOnlyPrototype();

    v8::Local<v8::Signature> defaultSignature;
    defaultSignature = V8DOMConfiguration::installDOMClassTemplate(isolate, functionTemplate, "TestInterfaceOwnProperties", V8TestInterfaceEmpty::domTemplate(isolate), V8TestInterfaceOwnProperties::internalFieldCount,
        V8TestInterfaceOwnPropertiesAttributes, WTF_ARRAY_LENGTH(V8TestInterfaceOwnPropertiesAttributes),
        V8TestInterfaceOwnPropertiesAccessors, WTF_ARRAY_LENGTH(V8TestInterfaceOwnPropertiesAccessors),
        0, 0);
    v8::Local<v8::ObjectTemplate> instanceTemplate = functionTemplate->InstanceTemplate();
    ALLOW_UNUSED_LOCAL(instanceTemplate);
    v8::Local<v8::ObjectTemplate> prototypeTemplate = functionTemplate->PrototypeTemplate();
    ALLOW_UNUSED_LOCAL(prototypeTemplate);

    // Custom toString template
    functionTemplate->Set(v8AtomicString(isolate, "toString"), V8PerIsolateData::from(isolate)->toStringTemplate());
}

v8::Local<v8::FunctionTemplate> V8TestInterfaceOwnProperties::domTemplate(v8::Isolate* isolate)
{
    return V8DOMConfiguration::domClassTemplate(isolate, const_cast<WrapperTypeInfo*>(&wrapperTypeInfo), installV8TestInterfaceOwnPropertiesTemplate);
}

bool V8TestInterfaceOwnProperties::hasInstance(v8::Local<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->hasInstance(&wrapperTypeInfo, v8Value);
}

v8::Local<v8::Object> V8TestInterfaceOwnProperties::findInstanceInPrototypeChain(v8::Local<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->findInstanceInPrototypeChain(&wrapperTypeInfo, v8Value);
}

TestInterfaceOwnProperties* V8TestInterfaceOwnProperties::toImplWithTypeCheck(v8::Isolate* isolate, v8::Local<v8::Value> value)
{
    return hasInstance(value, isolate) ? toImpl(v8::Local<v8::Object>::Cast(value)) : 0;
}

void V8TestInterfaceOwnProperties::refObject(ScriptWrappable* scriptWrappable)
{
    scriptWrappable->toImpl<TestInterfaceOwnProperties>()->ref();
}

void V8TestInterfaceOwnProperties::derefObject(ScriptWrappable* scriptWrappable)
{
    scriptWrappable->toImpl<TestInterfaceOwnProperties>()->deref();
}

} // namespace blink
