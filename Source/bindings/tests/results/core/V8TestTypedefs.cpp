// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py. DO NOT MODIFY!

#include "config.h"
#include "V8TestTypedefs.h"

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/UnionTypesCore.h"
#include "bindings/core/v8/V8DOMConfiguration.h"
#include "bindings/core/v8/V8ObjectConstructor.h"
#include "bindings/core/v8/V8TestCallbackInterface.h"
#include "bindings/core/v8/V8TestInterface.h"
#include "bindings/core/v8/V8TestInterfaceEmpty.h"
#include "core/dom/ContextFeatures.h"
#include "core/dom/Document.h"
#include "core/frame/LocalDOMWindow.h"
#include "platform/RuntimeEnabledFeatures.h"
#include "platform/TraceEvent.h"
#include "wtf/GetPtr.h"
#include "wtf/RefPtr.h"

namespace blink {

const WrapperTypeInfo V8TestTypedefs::wrapperTypeInfo = { gin::kEmbedderBlink, V8TestTypedefs::domTemplate, V8TestTypedefs::refObject, V8TestTypedefs::derefObject, V8TestTypedefs::trace, 0, 0, V8TestTypedefs::installConditionallyEnabledMethods, V8TestTypedefs::installConditionallyEnabledProperties, "TestTypedefs", 0, WrapperTypeInfo::WrapperTypeObjectPrototype, WrapperTypeInfo::ObjectClassId, WrapperTypeInfo::NotInheritFromEventTarget, WrapperTypeInfo::Independent, WrapperTypeInfo::RefCountedObject };

// This static member must be declared by DEFINE_WRAPPERTYPEINFO in TestTypedefs.h.
// For details, see the comment of DEFINE_WRAPPERTYPEINFO in
// bindings/core/v8/ScriptWrappable.h.
const WrapperTypeInfo& TestTypedefs::s_wrapperTypeInfo = V8TestTypedefs::wrapperTypeInfo;

namespace TestTypedefsV8Internal {

template<class CallbackInfo>
static void TestTypedefsForceSetAttributeOnThis(v8::Local<v8::Name> name, v8::Local<v8::Value> v8Value, const CallbackInfo& info)
{
    ASSERT(info.This()->IsObject());
    v8::Local<v8::Object>::Cast(info.This())->ForceSet(info.GetIsolate()->GetCurrentContext(), name, v8Value);
}

static void TestTypedefsConstructorAttributeSetterCallback(v8::Local<v8::Name>, v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<void>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMSetter");
    do {
        v8::Local<v8::Value> data = info.Data();
        ASSERT(data->IsExternal());
        V8PerContextData* perContextData = V8PerContextData::from(info.Holder()->CreationContext());
        if (!perContextData)
            break;
        const WrapperTypeInfo* wrapperTypeInfo = WrapperTypeInfo::unwrap(data);
        if (!wrapperTypeInfo)
            break;
        TestTypedefsForceSetAttributeOnThis(v8String(info.GetIsolate(), wrapperTypeInfo->interfaceName), v8Value, info);
    } while (false); // do ... while (false) just for use of break
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void uLongLongAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    v8::Local<v8::Object> holder = info.Holder();
    TestTypedefs* impl = V8TestTypedefs::toImpl(holder);
    v8SetReturnValue(info, static_cast<double>(impl->uLongLongAttribute()));
}

static void uLongLongAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMGetter");
    TestTypedefsV8Internal::uLongLongAttributeAttributeGetter(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void uLongLongAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info)
{
    v8::Local<v8::Object> holder = info.Holder();
    ExceptionState exceptionState(ExceptionState::SetterContext, "uLongLongAttribute", "TestTypedefs", holder, info.GetIsolate());
    TestTypedefs* impl = V8TestTypedefs::toImpl(holder);
    unsigned long long cppValue = toUInt64(info.GetIsolate(), v8Value, NormalConversion, exceptionState);
    if (exceptionState.throwIfNeeded())
        return;
    impl->setULongLongAttribute(cppValue);
}

static void uLongLongAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    v8::Local<v8::Value> v8Value = info[0];
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMSetter");
    TestTypedefsV8Internal::uLongLongAttributeAttributeSetter(v8Value, info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void tAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<void>& info)
{
    v8::Local<v8::String> propertyName = v8AtomicString(info.GetIsolate(), "tAttribute");
    TestTypedefsForceSetAttributeOnThis(propertyName, v8Value, info);
}

static void tAttributeAttributeSetterCallback(v8::Local<v8::Name>, v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<void>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMSetter");
    TestTypedefsV8Internal::tAttributeAttributeSetter(v8Value, info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void voidMethodArrayOfLongsArgMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "voidMethodArrayOfLongsArg", "TestTypedefs", info.Holder(), info.GetIsolate());
    TestTypedefs* impl = V8TestTypedefs::toImpl(info.Holder());
    Vector<int> arrayOfLongsArg;
    {
        if (UNLIKELY(info.Length() <= 0)) {
            impl->voidMethodArrayOfLongsArg();
            return;
        }
        arrayOfLongsArg = toImplArray<int>(info[0], 1, info.GetIsolate(), exceptionState);
        if (exceptionState.throwIfNeeded())
            return;
    }
    impl->voidMethodArrayOfLongsArg(arrayOfLongsArg);
}

static void voidMethodArrayOfLongsArgMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMMethod");
    TestTypedefsV8Internal::voidMethodArrayOfLongsArgMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void voidMethodFloatArgStringArgMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "voidMethodFloatArgStringArg", "TestTypedefs", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 2)) {
        setMinimumArityTypeError(exceptionState, 2, info.Length());
        exceptionState.throwIfNeeded();
        return;
    }
    TestTypedefs* impl = V8TestTypedefs::toImpl(info.Holder());
    float floatArg;
    V8StringResource<> stringArg;
    {
        floatArg = toRestrictedFloat(info.GetIsolate(), info[0], exceptionState);
        if (exceptionState.throwIfNeeded())
            return;
        stringArg = info[1];
        if (!stringArg.prepare())
            return;
    }
    impl->voidMethodFloatArgStringArg(floatArg, stringArg);
}

static void voidMethodFloatArgStringArgMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMMethod");
    TestTypedefsV8Internal::voidMethodFloatArgStringArgMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void voidMethodTestCallbackInterfaceTypeArgMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    if (UNLIKELY(info.Length() < 1)) {
        V8ThrowException::throwException(createMinimumArityTypeErrorForMethod(info.GetIsolate(), "voidMethodTestCallbackInterfaceTypeArg", "TestTypedefs", 1, info.Length()), info.GetIsolate());
        return;
    }
    TestTypedefs* impl = V8TestTypedefs::toImpl(info.Holder());
    TestCallbackInterface* testCallbackInterfaceTypeArg;
    {
        if (info.Length() <= 0 || !info[0]->IsFunction()) {
            V8ThrowException::throwTypeError(info.GetIsolate(), ExceptionMessages::failedToExecute("voidMethodTestCallbackInterfaceTypeArg", "TestTypedefs", "The callback provided as parameter 1 is not a function."));
            return;
        }
        testCallbackInterfaceTypeArg = V8TestCallbackInterface::create(v8::Local<v8::Function>::Cast(info[0]), ScriptState::current(info.GetIsolate()));
    }
    impl->voidMethodTestCallbackInterfaceTypeArg(testCallbackInterfaceTypeArg);
}

static void voidMethodTestCallbackInterfaceTypeArgMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMMethod");
    TestTypedefsV8Internal::voidMethodTestCallbackInterfaceTypeArgMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void uLongLongMethodTestInterfaceEmptyTypeSequenceArgMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "uLongLongMethodTestInterfaceEmptyTypeSequenceArg", "TestTypedefs", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 1)) {
        setMinimumArityTypeError(exceptionState, 1, info.Length());
        exceptionState.throwIfNeeded();
        return;
    }
    TestTypedefs* impl = V8TestTypedefs::toImpl(info.Holder());
    Vector<RefPtr<TestInterfaceEmpty>> testInterfaceEmptyTypeSequenceArg;
    {
        testInterfaceEmptyTypeSequenceArg = (toRefPtrNativeArray<TestInterfaceEmpty, V8TestInterfaceEmpty>(info[0], 1, info.GetIsolate(), exceptionState));
        if (exceptionState.throwIfNeeded())
            return;
    }
    v8SetReturnValue(info, static_cast<double>(impl->uLongLongMethodTestInterfaceEmptyTypeSequenceArg(testInterfaceEmptyTypeSequenceArg)));
}

static void uLongLongMethodTestInterfaceEmptyTypeSequenceArgMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMMethod");
    TestTypedefsV8Internal::uLongLongMethodTestInterfaceEmptyTypeSequenceArgMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void testInterfaceOrTestInterfaceEmptyMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TestTypedefs* impl = V8TestTypedefs::toImpl(info.Holder());
    TestInterfaceOrTestInterfaceEmpty result;
    impl->testInterfaceOrTestInterfaceEmptyMethod(result);
    v8SetReturnValue(info, result);
}

static void testInterfaceOrTestInterfaceEmptyMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMMethod");
    TestTypedefsV8Internal::testInterfaceOrTestInterfaceEmptyMethodMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void domStringOrDoubleMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TestTypedefs* impl = V8TestTypedefs::toImpl(info.Holder());
    StringOrDouble result;
    impl->domStringOrDoubleMethod(result);
    v8SetReturnValue(info, result);
}

static void domStringOrDoubleMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMMethod");
    TestTypedefsV8Internal::domStringOrDoubleMethodMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void arrayOfStringsMethodArrayOfStringsArgMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "arrayOfStringsMethodArrayOfStringsArg", "TestTypedefs", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 1)) {
        setMinimumArityTypeError(exceptionState, 1, info.Length());
        exceptionState.throwIfNeeded();
        return;
    }
    TestTypedefs* impl = V8TestTypedefs::toImpl(info.Holder());
    Vector<String> arrayOfStringsArg;
    {
        arrayOfStringsArg = toImplArray<String>(info[0], 1, info.GetIsolate(), exceptionState);
        if (exceptionState.throwIfNeeded())
            return;
    }
    v8SetReturnValue(info, toV8(impl->arrayOfStringsMethodArrayOfStringsArg(arrayOfStringsArg), info.Holder(), info.GetIsolate()));
}

static void arrayOfStringsMethodArrayOfStringsArgMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMMethod");
    TestTypedefsV8Internal::arrayOfStringsMethodArrayOfStringsArgMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void stringArrayMethodStringArrayArgMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "stringArrayMethodStringArrayArg", "TestTypedefs", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 1)) {
        setMinimumArityTypeError(exceptionState, 1, info.Length());
        exceptionState.throwIfNeeded();
        return;
    }
    TestTypedefs* impl = V8TestTypedefs::toImpl(info.Holder());
    Vector<String> stringArrayArg;
    {
        stringArrayArg = toImplArray<String>(info[0], 1, info.GetIsolate(), exceptionState);
        if (exceptionState.throwIfNeeded())
            return;
    }
    v8SetReturnValue(info, toV8(impl->stringArrayMethodStringArrayArg(stringArrayArg), info.Holder(), info.GetIsolate()));
}

static void stringArrayMethodStringArrayArgMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMMethod");
    TestTypedefsV8Internal::stringArrayMethodStringArrayArgMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void constructor(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    if (UNLIKELY(info.Length() < 1)) {
        V8ThrowException::throwException(createMinimumArityTypeErrorForConstructor(info.GetIsolate(), "TestTypedefs", 1, info.Length()), info.GetIsolate());
        return;
    }
    V8StringResource<> stringArg;
    {
        stringArg = info[0];
        if (!stringArg.prepare())
            return;
    }
    RefPtr<TestTypedefs> impl = TestTypedefs::create(stringArg);
    v8::Local<v8::Object> wrapper = info.Holder();
    impl->associateWithWrapper(info.GetIsolate(), &V8TestTypedefs::wrapperTypeInfo, wrapper);
    v8SetReturnValue(info, wrapper);
}

} // namespace TestTypedefsV8Internal

static const V8DOMConfiguration::AttributeConfiguration V8TestTypedefsAttributes[] = {
    {"tAttribute", v8ConstructorAttributeGetter, TestTypedefsV8Internal::tAttributeAttributeSetterCallback, 0, 0, const_cast<WrapperTypeInfo*>(&V8TestInterface::wrapperTypeInfo), static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::DontEnum), V8DOMConfiguration::ExposedToAllScripts, V8DOMConfiguration::OnInstance},
};

static const V8DOMConfiguration::AccessorConfiguration V8TestTypedefsAccessors[] = {
    {"uLongLongAttribute", TestTypedefsV8Internal::uLongLongAttributeAttributeGetterCallback, TestTypedefsV8Internal::uLongLongAttributeAttributeSetterCallback, 0, 0, 0, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::ExposedToAllScripts},
};

static const V8DOMConfiguration::MethodConfiguration V8TestTypedefsMethods[] = {
    {"voidMethodArrayOfLongsArg", TestTypedefsV8Internal::voidMethodArrayOfLongsArgMethodCallback, 0, 0, V8DOMConfiguration::ExposedToAllScripts},
    {"voidMethodFloatArgStringArg", TestTypedefsV8Internal::voidMethodFloatArgStringArgMethodCallback, 0, 2, V8DOMConfiguration::ExposedToAllScripts},
    {"voidMethodTestCallbackInterfaceTypeArg", TestTypedefsV8Internal::voidMethodTestCallbackInterfaceTypeArgMethodCallback, 0, 1, V8DOMConfiguration::ExposedToAllScripts},
    {"uLongLongMethodTestInterfaceEmptyTypeSequenceArg", TestTypedefsV8Internal::uLongLongMethodTestInterfaceEmptyTypeSequenceArgMethodCallback, 0, 1, V8DOMConfiguration::ExposedToAllScripts},
    {"testInterfaceOrTestInterfaceEmptyMethod", TestTypedefsV8Internal::testInterfaceOrTestInterfaceEmptyMethodMethodCallback, 0, 0, V8DOMConfiguration::ExposedToAllScripts},
    {"domStringOrDoubleMethod", TestTypedefsV8Internal::domStringOrDoubleMethodMethodCallback, 0, 0, V8DOMConfiguration::ExposedToAllScripts},
    {"arrayOfStringsMethodArrayOfStringsArg", TestTypedefsV8Internal::arrayOfStringsMethodArrayOfStringsArgMethodCallback, 0, 1, V8DOMConfiguration::ExposedToAllScripts},
    {"stringArrayMethodStringArrayArg", TestTypedefsV8Internal::stringArrayMethodStringArrayArgMethodCallback, 0, 1, V8DOMConfiguration::ExposedToAllScripts},
};

void V8TestTypedefs::constructorCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SCOPED_SAMPLING_STATE("blink", "DOMConstructor");
    if (!info.IsConstructCall()) {
        V8ThrowException::throwTypeError(info.GetIsolate(), ExceptionMessages::constructorNotCallableAsFunction("TestTypedefs"));
        return;
    }

    if (ConstructorMode::current(info.GetIsolate()) == ConstructorMode::WrapExistingObject) {
        v8SetReturnValue(info, info.Holder());
        return;
    }

    TestTypedefsV8Internal::constructor(info);
}

static void installV8TestTypedefsTemplate(v8::Local<v8::FunctionTemplate> functionTemplate, v8::Isolate* isolate)
{
    functionTemplate->ReadOnlyPrototype();

    v8::Local<v8::Signature> defaultSignature;
    defaultSignature = V8DOMConfiguration::installDOMClassTemplate(isolate, functionTemplate, "TestTypedefs", v8::Local<v8::FunctionTemplate>(), V8TestTypedefs::internalFieldCount,
        V8TestTypedefsAttributes, WTF_ARRAY_LENGTH(V8TestTypedefsAttributes),
        V8TestTypedefsAccessors, WTF_ARRAY_LENGTH(V8TestTypedefsAccessors),
        V8TestTypedefsMethods, WTF_ARRAY_LENGTH(V8TestTypedefsMethods));
    functionTemplate->SetCallHandler(V8TestTypedefs::constructorCallback);
    functionTemplate->SetLength(1);
    v8::Local<v8::ObjectTemplate> instanceTemplate = functionTemplate->InstanceTemplate();
    ALLOW_UNUSED_LOCAL(instanceTemplate);
    v8::Local<v8::ObjectTemplate> prototypeTemplate = functionTemplate->PrototypeTemplate();
    ALLOW_UNUSED_LOCAL(prototypeTemplate);

    // Custom toString template
    functionTemplate->Set(v8AtomicString(isolate, "toString"), V8PerIsolateData::from(isolate)->toStringTemplate());
}

v8::Local<v8::FunctionTemplate> V8TestTypedefs::domTemplate(v8::Isolate* isolate)
{
    return V8DOMConfiguration::domClassTemplate(isolate, const_cast<WrapperTypeInfo*>(&wrapperTypeInfo), installV8TestTypedefsTemplate);
}

bool V8TestTypedefs::hasInstance(v8::Local<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->hasInstance(&wrapperTypeInfo, v8Value);
}

v8::Local<v8::Object> V8TestTypedefs::findInstanceInPrototypeChain(v8::Local<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->findInstanceInPrototypeChain(&wrapperTypeInfo, v8Value);
}

TestTypedefs* V8TestTypedefs::toImplWithTypeCheck(v8::Isolate* isolate, v8::Local<v8::Value> value)
{
    return hasInstance(value, isolate) ? toImpl(v8::Local<v8::Object>::Cast(value)) : 0;
}

void V8TestTypedefs::refObject(ScriptWrappable* scriptWrappable)
{
    scriptWrappable->toImpl<TestTypedefs>()->ref();
}

void V8TestTypedefs::derefObject(ScriptWrappable* scriptWrappable)
{
    scriptWrappable->toImpl<TestTypedefs>()->deref();
}

} // namespace blink
