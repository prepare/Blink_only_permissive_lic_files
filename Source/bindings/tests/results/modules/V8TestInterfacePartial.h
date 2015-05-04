// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py. DO NOT MODIFY!

#ifndef V8TestInterfacePartial_h
#define V8TestInterfacePartial_h

#include "bindings/core/v8/ScriptWrappable.h"
#include "bindings/core/v8/ToV8.h"
#include "bindings/core/v8/V8Binding.h"
#include "bindings/core/v8/V8DOMWrapper.h"
#include "bindings/core/v8/WrapperTypeInfo.h"
#include "bindings/tests/idls/core/TestInterfaceImplementation.h"
#include "platform/heap/Handle.h"

namespace blink {

class V8TestInterfacePartial {
public:
    static void initialize();
    static void implementsCustomVoidMethodMethodCustom(const v8::FunctionCallbackInfo<v8::Value>&);
    static void preparePrototypeObject(v8::Isolate*, v8::Local<v8::Object>);
private:
    static void installV8TestInterfaceTemplate(v8::Local<v8::FunctionTemplate>, v8::Isolate*);
};
}
#endif // V8TestInterfacePartial_h
