/*
 * Copyright (C) 2007-2011 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "bindings/core/v8/V8CSSStyleDeclaration.h"

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/V8Binding.h"
#include "core/CSSPropertyNames.h"
#include "core/css/CSSPrimitiveValue.h"
#include "core/css/CSSPropertyMetadata.h"
#include "core/css/CSSStyleDeclaration.h"
#include "core/css/CSSValue.h"
#include "core/css/parser/CSSParser.h"
#include "core/events/EventTarget.h"
#include "core/frame/UseCounter.h"
#include "wtf/ASCIICType.h"
#include "wtf/PassRefPtr.h"
#include "wtf/RefPtr.h"
#include "wtf/StdLibExtras.h"
#include "wtf/Vector.h"
#include "wtf/text/StringBuilder.h"
#include "wtf/text/StringConcatenate.h"

using namespace WTF;

namespace blink {

// Check for a CSS prefix.
// Passed prefix is all lowercase.
// First character of the prefix within the property name may be upper or lowercase.
// Other characters in the prefix within the property name must be lowercase.
// The prefix within the property name must be followed by a capital letter.
static bool hasCSSPropertyNamePrefix(const String& propertyName, const char* prefix)
{
#if ENABLE(ASSERT)
    ASSERT(*prefix);
    for (const char* p = prefix; *p; ++p)
        ASSERT(isASCIILower(*p));
    ASSERT(propertyName.length());
#endif

    if (toASCIILower(propertyName[0]) != prefix[0])
        return false;

    unsigned length = propertyName.length();
    for (unsigned i = 1; i < length; ++i) {
        if (!prefix[i])
            return isASCIIUpper(propertyName[i]);
        if (propertyName[i] != prefix[i])
            return false;
    }
    return false;
}

static CSSPropertyID parseCSSPropertyID(v8::Isolate* isolate, const String& propertyName)
{
    unsigned length = propertyName.length();
    if (!length)
        return CSSPropertyInvalid;

    StringBuilder builder;
    builder.reserveCapacity(length);

    unsigned i = 0;
    bool hasSeenDash = false;

    if (hasCSSPropertyNamePrefix(propertyName, "css")) {
        i += 3;
        // getComputedStyle(elem).cssX is a non-standard behaviour
        // Measure this behaviour as CSSXGetComputedStyleQueries.
        UseCounter::countIfNotPrivateScript(isolate, callingExecutionContext(isolate), UseCounter::CSSXGetComputedStyleQueries);
    } else if (hasCSSPropertyNamePrefix(propertyName, "webkit"))
        builder.append('-');
    else if (isASCIIUpper(propertyName[0]))
        return CSSPropertyInvalid;

    bool hasSeenUpper = isASCIIUpper(propertyName[i]);

    builder.append(toASCIILower(propertyName[i++]));

    for (; i < length; ++i) {
        UChar c = propertyName[i];
        if (!isASCIIUpper(c)) {
            if (c == '-')
                hasSeenDash = true;
            builder.append(c);
        } else {
            hasSeenUpper = true;
            builder.append('-');
            builder.append(toASCIILower(c));
        }
    }

    // Reject names containing both dashes and upper-case characters, such as "border-rightColor".
    if (hasSeenDash && hasSeenUpper)
        return CSSPropertyInvalid;

    String propName = builder.toString();
    return unresolvedCSSPropertyID(propName);
}

// When getting properties on CSSStyleDeclarations, the name used from
// Javascript and the actual name of the property are not the same, so
// we have to do the following translation. The translation turns upper
// case characters into lower case characters and inserts dashes to
// separate words.
//
// Example: 'backgroundPositionY' -> 'background-position-y'
//
// Also, certain prefixes such as 'css-' are stripped.
static CSSPropertyID cssPropertyInfo(v8::Local<v8::String> v8PropertyName, v8::Isolate* isolate)
{
    String propertyName = toCoreString(v8PropertyName);
    typedef HashMap<String, CSSPropertyID> CSSPropertyIDMap;
    DEFINE_STATIC_LOCAL(CSSPropertyIDMap, map, ());
    CSSPropertyIDMap::iterator iter = map.find(propertyName);
    if (iter != map.end())
        return iter->value;

    CSSPropertyID unresolvedProperty = parseCSSPropertyID(isolate, propertyName);
    map.add(propertyName, unresolvedProperty);
    ASSERT(!unresolvedProperty || CSSPropertyMetadata::isEnabledProperty(unresolvedProperty));
    return unresolvedProperty;
}

void V8CSSStyleDeclaration::namedPropertyGetterCustom(v8::Local<v8::Name> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    // Search the style declaration.
    CSSPropertyID unresolvedProperty = cssPropertyInfo(name.As<v8::String>(), info.GetIsolate());

    // Do not handle non-property names.
    if (!unresolvedProperty)
        return;
    CSSPropertyID resolvedProperty = resolveCSSPropertyID(unresolvedProperty);

    CSSStyleDeclaration* impl = V8CSSStyleDeclaration::toImpl(info.Holder());
    RefPtrWillBeRawPtr<CSSValue> cssValue = impl->getPropertyCSSValueInternal(resolvedProperty);
    if (cssValue) {
        v8SetReturnValueStringOrNull(info, cssValue->cssText(), info.GetIsolate());
        return;
    }

    String result = impl->getPropertyValueInternal(resolvedProperty);
    v8SetReturnValueString(info, result, info.GetIsolate());
}

} // namespace blink
