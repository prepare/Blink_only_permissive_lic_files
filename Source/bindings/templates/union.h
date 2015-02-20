// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by {{code_generator}}. DO NOT MODIFY!

#ifndef {{macro_guard}}
#define {{macro_guard}}

{% for filename in header_includes %}
#include "{{filename}}"
{% endfor %}

namespace blink {

{% for decl in header_forward_decls %}
class {{decl}};
{% endfor %}

{% for container in containers %}
class {{container.cpp_class}} final {
    ALLOW_ONLY_INLINE_ALLOCATION();
public:
    {{container.cpp_class}}();
    bool isNull() const { return m_type == SpecificTypeNone; }

    {% for member in container.members %}
    bool is{{member.type_name}}() const { return m_type == {{member.specific_type_enum}}; }
    {{member.rvalue_cpp_type}} getAs{{member.type_name}}() const;
    void set{{member.type_name}}({{member.rvalue_cpp_type}});

    {% endfor %}
    {% if container.needs_trace %}
    void trace(Visitor*);

    {% endif %}
private:
    enum SpecificTypes {
        SpecificTypeNone,
        {% for member in container.members %}
        {{member.specific_type_enum}},
        {% endfor %}
    };
    SpecificTypes m_type;

    {% for member in container.members %}
    {{member.cpp_type}} m_{{member.cpp_name}};
    {% endfor %}

    friend v8::Local<v8::Value> toV8(const {{container.cpp_class}}&, v8::Local<v8::Object>, v8::Isolate*);
};

class V8{{container.cpp_class}} final {
public:
    static void toImpl(v8::Isolate*, v8::Local<v8::Value>, {{container.cpp_class}}&, ExceptionState&);
};

v8::Local<v8::Value> toV8(const {{container.cpp_class}}&, v8::Local<v8::Object>, v8::Isolate*);

template <class CallbackInfo>
inline void v8SetReturnValue(const CallbackInfo& callbackInfo, {{container.cpp_class}}& impl)
{
    v8SetReturnValue(callbackInfo, toV8(impl, callbackInfo.Holder(), callbackInfo.GetIsolate()));
}

template <>
struct NativeValueTraits<{{container.cpp_class}}> {
    static {{container.cpp_class}} nativeValue(const v8::Local<v8::Value>&, v8::Isolate*, ExceptionState&);
};

{% endfor %}
{% for cpp_type in nullable_cpp_types %}
class V8{{cpp_type}}OrNull final {
public:
    static void toImpl(v8::Isolate* isolate, v8::Local<v8::Value> v8Value, {{cpp_type}}& impl, ExceptionState& exceptionState)
    {
        {# http://heycam.github.io/webidl/#es-union #}
        {# 1. null or undefined #}
        if (isUndefinedOrNull(v8Value))
            return;
        V8{{cpp_type}}::toImpl(isolate, v8Value, impl, exceptionState);
    }
};

{% endfor %}
} // namespace blink

#endif // {{macro_guard}}