// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "config.h"
#include "core/layout/LayoutAnalyzer.h"

#include "core/frame/FrameView.h"
#include "core/layout/LayoutObject.h"
#include "core/layout/LayoutText.h"
#include "platform/TracedValue.h"
#include "public/platform/Platform.h"

namespace blink {

LayoutAnalyzer::Scope::Scope(const LayoutObject& o)
    : m_layoutObject(o)
    , m_analyzer(o.frameView()->layoutAnalyzer())
{
    m_analyzer.push(o);
}

LayoutAnalyzer::Scope::~Scope()
{
    m_analyzer.pop(m_layoutObject);
}

void LayoutAnalyzer::reset()
{
    m_startMs = currentTimeMS();
    m_depth = 0;
    for (size_t i = 0; i < NumCounters; ++i) {
        m_counters[i] = 0;
    }
}

void LayoutAnalyzer::push(const LayoutObject& o)
{
    increment(TotalLayoutObjectsThatWereLaidOut);
    if (!o.everHadLayout())
        increment(LayoutObjectsThatHadNeverHadLayout);
    if (o.selfNeedsLayout())
        increment(LayoutObjectsThatNeedLayoutForThemselves);
    if (o.needsPositionedMovementLayout())
        increment(LayoutObjectsThatNeedPositionedMovementLayout);
    if (o.isOutOfFlowPositioned())
        increment(LayoutObjectsThatAreOutOfFlowPositioned);
    if (o.isTableCell())
        increment(LayoutObjectsThatAreTableCells);
    if (o.isFloating())
        increment(LayoutObjectsThatAreFloating);
    if (o.style()->specifiesColumns())
        increment(LayoutObjectsThatSpecifyColumns);
    if (o.hasLayer())
        increment(LayoutObjectsThatHaveALayer);
    if (o.isLayoutInline() && o.alwaysCreateLineBoxesForLayoutInline())
        increment(LayoutInlineObjectsThatAlwaysCreateLineBoxes);
    if (o.isText()) {
        const LayoutText& t = *toLayoutText(&o);
        if (t.canUseSimpleFontCodePath()) {
            increment(LayoutObjectsThatAreTextAndCanUseTheSimpleFontCodePath);
            increment(CharactersInLayoutObjectsThatAreTextAndCanUseTheSimpleFontCodePath, t.textLength());
        } else {
            increment(LayoutObjectsThatAreTextAndCanNotUseTheSimpleFontCodePath);
            increment(CharactersInLayoutObjectsThatAreTextAndCanNotUseTheSimpleFontCodePath, t.textLength());
        }
    }

    ++m_depth;

    // This refers to LayoutAnalyzer depth, which is generally closer to C++
    // stack recursion depth, not layout tree depth or DOM tree depth.
    m_counters[LayoutAnalyzerStackMaximumDepth] = max(m_counters[LayoutAnalyzerStackMaximumDepth], m_depth);
}

void LayoutAnalyzer::pop(const LayoutObject& o)
{
    ASSERT(m_depth > 0);
    --m_depth;
}

void LayoutAnalyzer::recordCounters()
{
    unsigned totalNodes = m_counters[TotalLayoutObjectsThatWereLaidOut];
    if (totalNodes < 100)
        return;
    unsigned usPerNode = (1000.0 * (currentTimeMS() - m_startMs)) / totalNodes;
    Platform::current()->histogramCustomCounts("Layout.MicroSecondsPerNode", usPerNode, 0, 1000 * 1000, 50);
    unsigned halfTotalNodes = totalNodes / 2;
    const char* histogram = nullptr;
    if (m_counters[LayoutAnalyzer::LayoutObjectsThatAreFloating] > halfTotalNodes) {
        histogram = "Layout.MicroSecondsPerFloat";
    } else if (m_counters[LayoutAnalyzer::LayoutObjectsThatAreTableCells] > halfTotalNodes) {
        histogram = "Layout.MicroSecondsPerTD";
    } else if (m_counters[LayoutAnalyzer::LayoutObjectsThatAreOutOfFlowPositioned] > halfTotalNodes) {
        histogram = "Layout.MicroSecondsPerPositioned";
    } else if (m_counters[LayoutAnalyzer::LayoutObjectsThatAreTextAndCanUseTheSimpleFontCodePath] > halfTotalNodes) {
        histogram = "Layout.MicroSecondsPerSimpleText";
    } else if (m_counters[LayoutAnalyzer::LayoutObjectsThatAreTextAndCanNotUseTheSimpleFontCodePath] > halfTotalNodes) {
        histogram = "Layout.MicroSecondsPerComplexText";
    }
    if (histogram)
        Platform::current()->histogramCustomCounts(histogram, usPerNode, 0, 1000 * 1000, 50);
}

PassRefPtr<TracedValue> LayoutAnalyzer::toTracedValue()
{
    RefPtr<TracedValue> tracedValue(TracedValue::create());
    for (size_t i = 0; i < NumCounters; ++i) {
        if (m_counters[i] > 0)
            tracedValue->setInteger(nameForCounter(static_cast<Counter>(i)), m_counters[i]);
    }
    return tracedValue.release();
}

const char* LayoutAnalyzer::nameForCounter(Counter counter) const
{
    switch (counter) {
    case LayoutBlockRectangleChanged: return "LayoutBlockRectangleChanged";
    case LayoutBlockRectangleDidNotChange: return "LayoutBlockRectangleDidNotChange";
    case LayoutObjectsThatSpecifyColumns: return "LayoutObjectsThatSpecifyColumns";
    case LayoutAnalyzerStackMaximumDepth: return "LayoutAnalyzerStackMaximumDepth";
    case LayoutObjectsThatAreFloating: return "LayoutObjectsThatAreFloating";
    case LayoutObjectsThatHaveALayer: return "LayoutObjectsThatHaveALayer";
    case LayoutInlineObjectsThatAlwaysCreateLineBoxes: return "LayoutInlineObjectsThatAlwaysCreateLineBoxes";
    case LayoutObjectsThatHadNeverHadLayout: return "LayoutObjectsThatHadNeverHadLayout";
    case LayoutObjectsThatAreOutOfFlowPositioned: return "LayoutObjectsThatAreOutOfFlowPositioned";
    case LayoutObjectsThatNeedPositionedMovementLayout: return "LayoutObjectsThatNeedPositionedMovementLayout";
    case PerformLayoutRootLayoutObjects: return "PerformLayoutRootLayoutObjects";
    case LayoutObjectsThatNeedLayoutForThemselves: return "LayoutObjectsThatNeedLayoutForThemselves";
    case LayoutObjectsThatNeedSimplifiedLayout: return "LayoutObjectsThatNeedSimplifiedLayout";
    case LayoutObjectsThatAreTableCells: return "LayoutObjectsThatAreTableCells";
    case LayoutObjectsThatAreTextAndCanNotUseTheSimpleFontCodePath: return "LayoutObjectsThatAreTextAndCanNotUseTheSimpleFontCodePath";
    case CharactersInLayoutObjectsThatAreTextAndCanNotUseTheSimpleFontCodePath: return "CharactersInLayoutObjectsThatAreTextAndCanNotUseTheSimpleFontCodePath";
    case LayoutObjectsThatAreTextAndCanUseTheSimpleFontCodePath: return "LayoutObjectsThatAreTextAndCanUseTheSimpleFontCodePath";
    case CharactersInLayoutObjectsThatAreTextAndCanUseTheSimpleFontCodePath: return "CharactersInLayoutObjectsThatAreTextAndCanUseTheSimpleFontCodePath";
    case TotalLayoutObjectsThatWereLaidOut: return "TotalLayoutObjectsThatWereLaidOut";
    }
    ASSERT_NOT_REACHED();
    return "";
}

} // namespace blink
