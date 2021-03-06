// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "config.h"

#include "core/html/canvas/CanvasRenderingContext2DState.h"

#include "core/css/CSSFontSelector.h"
#include "core/html/canvas/CanvasGradient.h"
#include "core/html/canvas/CanvasPattern.h"
#include "core/html/canvas/CanvasStyle.h"
#include "platform/graphics/DrawLooperBuilder.h"
#include "platform/graphics/skia/SkiaUtils.h"
#include "third_party/skia/include/effects/SkDashPathEffect.h"
#include "third_party/skia/include/effects/SkDropShadowImageFilter.h"

static const char defaultFont[] = "10px sans-serif";

namespace blink {

CanvasRenderingContext2DState::CanvasRenderingContext2DState()
    : m_unrealizedSaveCount(0)
    , m_strokeStyle(CanvasStyle::createFromRGBA(SK_ColorBLACK))
    , m_fillStyle(CanvasStyle::createFromRGBA(SK_ColorBLACK))
    , m_shadowBlur(0)
    , m_shadowColor(Color::transparent)
    , m_globalAlpha(1)
    , m_lineDashOffset(0)
    , m_unparsedFont(defaultFont)
    , m_textAlign(StartTextAlign)
    , m_textBaseline(AlphabeticTextBaseline)
    , m_direction(DirectionInherit)
    , m_realizedFont(false)
    , m_isTransformInvertible(true)
    , m_hasClip(false)
    , m_hasComplexClip(false)
    , m_fillStyleDirty(true)
    , m_strokeStyleDirty(true)
    , m_lineDashDirty(false)
{
    m_fillPaint.setStyle(SkPaint::kFill_Style);
    m_fillPaint.setAntiAlias(true);
    m_strokePaint.setStyle(SkPaint::kStroke_Style);
    m_strokePaint.setStrokeWidth(1);
    m_strokePaint.setStrokeCap(SkPaint::kButt_Cap);
    m_strokePaint.setStrokeMiter(10);
    m_strokePaint.setStrokeJoin(SkPaint::kMiter_Join);
    m_strokePaint.setAntiAlias(true);
    setImageSmoothingEnabled(true);
}

CanvasRenderingContext2DState::CanvasRenderingContext2DState(const CanvasRenderingContext2DState& other, ClipListCopyMode mode)
    : CSSFontSelectorClient()
    , m_unrealizedSaveCount(other.m_unrealizedSaveCount)
    , m_unparsedStrokeColor(other.m_unparsedStrokeColor)
    , m_unparsedFillColor(other.m_unparsedFillColor)
    , m_strokeStyle(other.m_strokeStyle)
    , m_fillStyle(other.m_fillStyle)
    , m_strokePaint(other.m_strokePaint)
    , m_fillPaint(other.m_fillPaint)
    , m_shadowOffset(other.m_shadowOffset)
    , m_shadowBlur(other.m_shadowBlur)
    , m_shadowColor(other.m_shadowColor)
    , m_emptyDrawLooper(other.m_emptyDrawLooper)
    , m_shadowOnlyDrawLooper(other.m_shadowOnlyDrawLooper)
    , m_shadowAndForegroundDrawLooper(other.m_shadowAndForegroundDrawLooper)
    , m_shadowOnlyImageFilter(other.m_shadowOnlyImageFilter)
    , m_shadowAndForegroundImageFilter(other.m_shadowAndForegroundImageFilter)
    , m_globalAlpha(other.m_globalAlpha)
    , m_transform(other.m_transform)
    , m_lineDashOffset(other.m_lineDashOffset)
    , m_unparsedFont(other.m_unparsedFont)
    , m_font(other.m_font)
    , m_textAlign(other.m_textAlign)
    , m_textBaseline(other.m_textBaseline)
    , m_direction(other.m_direction)
    , m_realizedFont(other.m_realizedFont)
    , m_isTransformInvertible(other.m_isTransformInvertible)
    , m_hasClip(other.m_hasClip)
    , m_hasComplexClip(other.m_hasComplexClip)
    , m_fillStyleDirty(other.m_fillStyleDirty)
    , m_strokeStyleDirty(other.m_strokeStyleDirty)
    , m_lineDashDirty(other.m_lineDashDirty)
{
    if (mode == CopyClipList) {
        m_clipList = other.m_clipList;
    }
    if (m_realizedFont)
        static_cast<CSSFontSelector*>(m_font.fontSelector())->registerForInvalidationCallbacks(this);
}

CanvasRenderingContext2DState& CanvasRenderingContext2DState::operator=(const CanvasRenderingContext2DState& other)
{
    if (this == &other)
        return *this;

#if !ENABLE(OILPAN)
    if (m_realizedFont)
        static_cast<CSSFontSelector*>(m_font.fontSelector())->unregisterForInvalidationCallbacks(this);
#endif

    m_unrealizedSaveCount = other.m_unrealizedSaveCount;
    m_unparsedStrokeColor = other.m_unparsedStrokeColor;
    m_unparsedFillColor = other.m_unparsedFillColor;
    m_strokeStyle = other.m_strokeStyle;
    m_fillStyle = other.m_fillStyle;
    m_strokePaint = other.m_strokePaint;
    m_fillPaint = other.m_fillPaint;
    m_shadowOffset = other.m_shadowOffset;
    m_shadowBlur = other.m_shadowBlur;
    m_shadowColor = other.m_shadowColor;
    m_emptyDrawLooper = other.m_emptyDrawLooper;
    m_shadowOnlyDrawLooper = other.m_shadowOnlyDrawLooper;
    m_shadowAndForegroundDrawLooper = other.m_shadowAndForegroundDrawLooper;
    m_shadowOnlyImageFilter = other.m_shadowOnlyImageFilter;
    m_shadowAndForegroundImageFilter = other.m_shadowAndForegroundImageFilter;
    m_globalAlpha = other.m_globalAlpha;
    m_transform = other.m_transform;
    m_lineDashOffset = other.m_lineDashOffset;
    m_unparsedFont = other.m_unparsedFont;
    m_font = other.m_font;
    m_textAlign = other.m_textAlign;
    m_textBaseline = other.m_textBaseline;
    m_direction = other.m_direction;
    m_realizedFont = other.m_realizedFont;
    m_isTransformInvertible = other.m_isTransformInvertible;
    m_hasClip = other.m_hasClip;
    m_hasComplexClip = other.m_hasComplexClip;
    m_fillStyleDirty = other.m_fillStyleDirty;
    m_strokeStyleDirty = other.m_strokeStyleDirty;
    m_lineDashDirty = other.m_lineDashDirty;
    m_clipList = other.m_clipList;

    if (m_realizedFont)
        static_cast<CSSFontSelector*>(m_font.fontSelector())->registerForInvalidationCallbacks(this);

    return *this;
}

CanvasRenderingContext2DState::~CanvasRenderingContext2DState()
{
#if !ENABLE(OILPAN)
    if (m_realizedFont)
        static_cast<CSSFontSelector*>(m_font.fontSelector())->unregisterForInvalidationCallbacks(this);
#endif
}

void CanvasRenderingContext2DState::fontsNeedUpdate(CSSFontSelector* fontSelector)
{
    ASSERT_ARG(fontSelector, fontSelector == m_font.fontSelector());
    ASSERT(m_realizedFont);

    m_font.update(fontSelector);
}

DEFINE_TRACE(CanvasRenderingContext2DState)
{
    visitor->trace(m_strokeStyle);
    visitor->trace(m_fillStyle);
    CSSFontSelectorClient::trace(visitor);
}

void CanvasRenderingContext2DState::setLineDashOffset(float offset)
{
    m_lineDashOffset = offset;
    m_lineDashDirty = true;
}

void CanvasRenderingContext2DState::setLineDash(const Vector<float>& dash)
{
    m_lineDash = dash;
    // Spec requires the concatenation of two copies the dash list when the
    // number of elements is odd
    if (dash.size() % 2)
        m_lineDash.appendVector(dash);

    m_lineDashDirty = true;
}

void CanvasRenderingContext2DState::updateLineDash() const
{
    if (!m_lineDashDirty)
        return;

    if (m_lineDash.size() == 0) {
        m_strokePaint.setPathEffect(0);
    } else {
        m_strokePaint.setPathEffect(SkDashPathEffect::Create(m_lineDash.data(), m_lineDash.size(), m_lineDashOffset));
    }

    m_lineDashDirty = false;
}

void CanvasRenderingContext2DState::setStrokeStyle(PassRefPtrWillBeRawPtr<CanvasStyle> style)
{
    m_strokeStyle = style;
    m_strokeStyleDirty = true;
}

void CanvasRenderingContext2DState::setFillStyle(PassRefPtrWillBeRawPtr<CanvasStyle> style)
{
    m_fillStyle = style;
    m_fillStyleDirty = true;
}

void CanvasRenderingContext2DState::updateStrokeStyle() const
{
    if (!m_strokeStyleDirty)
        return;

    int clampedAlpha = clampedAlphaForBlending(m_globalAlpha);
    ASSERT(m_strokeStyle);
    m_strokePaint.setShader(m_strokeStyle->shader());
    m_strokePaint.setColor(scaleAlpha(m_strokeStyle->paintColor(), clampedAlpha));
    m_strokeStyleDirty = false;
}

void CanvasRenderingContext2DState::updateFillStyle() const
{
    if (!m_fillStyleDirty)
        return;

    int clampedAlpha = clampedAlphaForBlending(m_globalAlpha);
    ASSERT(m_fillStyle);
    m_fillPaint.setShader(m_fillStyle->shader());
    m_fillPaint.setColor(scaleAlpha(m_fillStyle->paintColor(), clampedAlpha));
    m_fillStyleDirty = false;
}

CanvasStyle* CanvasRenderingContext2DState::style(PaintType paintType) const
{
    switch (paintType) {
    case FillPaintType:
        return fillStyle();
    case StrokePaintType:
        return strokeStyle();
    }
    ASSERT_NOT_REACHED();
    return nullptr;
}

void CanvasRenderingContext2DState::setGlobalAlpha(float alpha)
{
    m_globalAlpha = alpha;
    m_strokeStyleDirty = true;
    m_fillStyleDirty = true;
}

void CanvasRenderingContext2DState::clipPath(const SkPath& path, AntiAliasingMode antiAliasingMode)
{
    m_clipList.clipPath(path, antiAliasingMode, affineTransformToSkMatrix(m_transform));
    m_hasClip = true;
    if (!path.isRect(0))
        m_hasComplexClip = true;
}

void CanvasRenderingContext2DState::setFont(const Font& font, CSSFontSelector* selector)
{
#if !ENABLE(OILPAN)
    if (m_realizedFont)
        static_cast<CSSFontSelector*>(m_font.fontSelector())->unregisterForInvalidationCallbacks(this);
#endif
    m_font = font;
    m_font.update(selector);
    m_realizedFont = true;
    selector->registerForInvalidationCallbacks(this);
}

const Font& CanvasRenderingContext2DState::font() const
{
    ASSERT(m_realizedFont);
    return m_font;
}

void CanvasRenderingContext2DState::setTransform(const AffineTransform& transform)
{
    m_isTransformInvertible = transform.isInvertible();
    m_transform = transform;
}

void CanvasRenderingContext2DState::resetTransform()
{
    m_transform.makeIdentity();
    m_isTransformInvertible = true;
}

SkDrawLooper* CanvasRenderingContext2DState::emptyDrawLooper() const
{
    if (!m_emptyDrawLooper) {
        OwnPtr<DrawLooperBuilder> drawLooperBuilder = DrawLooperBuilder::create();
        m_emptyDrawLooper = drawLooperBuilder->detachDrawLooper();
    }
    return m_emptyDrawLooper.get();
}

SkDrawLooper* CanvasRenderingContext2DState::shadowOnlyDrawLooper() const
{
    if (!m_shadowOnlyDrawLooper) {
        OwnPtr<DrawLooperBuilder> drawLooperBuilder = DrawLooperBuilder::create();
        drawLooperBuilder->addShadow(m_shadowOffset, m_shadowBlur, m_shadowColor, DrawLooperBuilder::ShadowIgnoresTransforms, DrawLooperBuilder::ShadowRespectsAlpha);
        m_shadowOnlyDrawLooper = drawLooperBuilder->detachDrawLooper();
    }
    return m_shadowOnlyDrawLooper.get();
}

SkDrawLooper* CanvasRenderingContext2DState::shadowAndForegroundDrawLooper() const
{
    if (!m_shadowAndForegroundDrawLooper) {
        OwnPtr<DrawLooperBuilder> drawLooperBuilder = DrawLooperBuilder::create();
        drawLooperBuilder->addShadow(m_shadowOffset, m_shadowBlur, m_shadowColor, DrawLooperBuilder::ShadowIgnoresTransforms, DrawLooperBuilder::ShadowRespectsAlpha);
        drawLooperBuilder->addUnmodifiedContent();
        m_shadowAndForegroundDrawLooper = drawLooperBuilder->detachDrawLooper();
    }
    return m_shadowAndForegroundDrawLooper.get();
}

SkImageFilter* CanvasRenderingContext2DState::shadowOnlyImageFilter() const
{
    if (!m_shadowOnlyImageFilter) {
        float sigma = skBlurRadiusToSigma(m_shadowBlur);
        m_shadowOnlyImageFilter = adoptRef(SkDropShadowImageFilter::Create(m_shadowOffset.width(), m_shadowOffset.height(), sigma, sigma, m_shadowColor, SkDropShadowImageFilter::kDrawShadowOnly_ShadowMode));
    }
    return m_shadowOnlyImageFilter.get();
}

SkImageFilter* CanvasRenderingContext2DState::shadowAndForegroundImageFilter() const
{
    if (!m_shadowAndForegroundImageFilter) {
        float sigma = skBlurRadiusToSigma(m_shadowBlur);
        m_shadowAndForegroundImageFilter = adoptRef(SkDropShadowImageFilter::Create(m_shadowOffset.width(), m_shadowOffset.height(), sigma, sigma, m_shadowColor, SkDropShadowImageFilter::kDrawShadowAndForeground_ShadowMode));
    }
    return m_shadowAndForegroundImageFilter.get();
}

void CanvasRenderingContext2DState::shadowParameterChanged()
{
    m_shadowOnlyDrawLooper.clear();
    m_shadowAndForegroundDrawLooper.clear();
    m_shadowOnlyImageFilter.clear();
    m_shadowAndForegroundImageFilter.clear();
}

void CanvasRenderingContext2DState::setShadowOffsetX(float x)
{
    m_shadowOffset.setWidth(x);
    shadowParameterChanged();
}

void CanvasRenderingContext2DState::setShadowOffsetY(float y)
{
    m_shadowOffset.setHeight(y);
    shadowParameterChanged();
}

void CanvasRenderingContext2DState::setShadowBlur(float shadowBlur)
{
    m_shadowBlur = shadowBlur;
    shadowParameterChanged();
}

void CanvasRenderingContext2DState::setShadowColor(SkColor shadowColor)
{
    m_shadowColor = shadowColor;
    shadowParameterChanged();
}

void CanvasRenderingContext2DState::setGlobalComposite(SkXfermode::Mode mode)
{
    m_strokePaint.setXfermodeMode(mode);
    m_fillPaint.setXfermodeMode(mode);
}

SkXfermode::Mode CanvasRenderingContext2DState::globalComposite() const
{
    SkXfermode* xferMode = m_strokePaint.getXfermode();
    SkXfermode::Mode mode;
    if (!xferMode || !xferMode->asMode(&mode))
        return SkXfermode::kSrcOver_Mode;
    return mode;
}

void CanvasRenderingContext2DState::setImageSmoothingEnabled(bool enabled)
{
    SkFilterQuality filterQuality = enabled ? kLow_SkFilterQuality : kNone_SkFilterQuality;
    m_strokePaint.setFilterQuality(filterQuality);
    m_fillPaint.setFilterQuality(filterQuality);
}

bool CanvasRenderingContext2DState::imageSmoothingEnabled() const
{
    return m_strokePaint.getFilterQuality() == kLow_SkFilterQuality;
}

bool CanvasRenderingContext2DState::shouldDrawShadows() const
{
    return alphaChannel(m_shadowColor) && (m_shadowBlur || !m_shadowOffset.isZero());
}

const SkPaint* CanvasRenderingContext2DState::getPaint(PaintType paintType, ShadowMode shadowMode, ImageType imageType) const
{
    SkPaint* paint;
    if (paintType == StrokePaintType) {
        updateLineDash();
        updateStrokeStyle();
        paint = &m_strokePaint;
    } else {
        updateFillStyle();
        paint = &m_fillPaint;
    }

    if ((!shouldDrawShadows() && shadowMode == DrawShadowAndForeground) || shadowMode == DrawForegroundOnly) {
        paint->setLooper(0);
        paint->setImageFilter(0);
        return paint;
    }

    if (!shouldDrawShadows() && shadowMode == DrawShadowOnly) {
        paint->setLooper(emptyDrawLooper()); // draw nothing
        paint->setImageFilter(0);
        return paint;
    }

    if (shadowMode == DrawShadowOnly) {
        if (imageType == NonOpaqueImage) {
            paint->setLooper(0);
            paint->setImageFilter(shadowOnlyImageFilter());
            return paint;
        }
        paint->setLooper(shadowOnlyDrawLooper());
        paint->setImageFilter(0);
        return paint;
    }

    ASSERT(shadowMode == DrawShadowAndForeground);
    if (imageType == NonOpaqueImage) {
        paint->setLooper(0);
        paint->setImageFilter(shadowAndForegroundImageFilter());
        return paint;
    }
    paint->setLooper(shadowAndForegroundDrawLooper());
    paint->setImageFilter(0);
    return paint;
}

} // blink
