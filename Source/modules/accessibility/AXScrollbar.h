/*
 * Copyright (C) 2010 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of Apple Computer, Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef AXScrollbar_h
#define AXScrollbar_h

#include "modules/accessibility/AXMockObject.h"

namespace blink {

class AXObjectCacheImpl;
class Scrollbar;

class AXScrollbar final : public AXMockObject {
public:
    static PassRefPtr<AXScrollbar> create(Scrollbar*, AXObjectCacheImpl*);

    Scrollbar* scrollbar() const { return m_scrollbar.get(); }

private:
    AXScrollbar(Scrollbar*, AXObjectCacheImpl*);

    virtual void detachFromParent() override;

    virtual bool canSetValueAttribute() const override { return true; }

    virtual bool isAXScrollbar() const override { return true; }
    virtual LayoutRect elementRect() const override;

    virtual AccessibilityRole roleValue() const override { return ScrollBarRole; }
    virtual AccessibilityOrientation orientation() const override;
    virtual Document* document() const override;

    virtual bool isEnabled() const override;

    // Assumes float [0..1]
    virtual void setValue(float) override;
    virtual float valueForRange() const override;

    // FIXME: Oilpan: turn this into a Member once the AXObject
    // hierarchy is on the heap.
    RefPtrWillBePersistent<Scrollbar> m_scrollbar;
};

DEFINE_AX_OBJECT_TYPE_CASTS(AXScrollbar, isAXScrollbar());

} // namespace blink

#endif // AXScrollbar_h
