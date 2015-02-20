/*
 * Copyright (C) 2006, 2007, 2009, 2010, 2011, 2012 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CanvasRenderingContext2D_h
#define CanvasRenderingContext2D_h

#include "bindings/core/v8/ScriptWrappable.h"
#include "bindings/core/v8/UnionTypesCore.h"
#include "core/css/CSSFontSelectorClient.h"
#include "core/html/canvas/Canvas2DContextAttributes.h"
#include "core/html/canvas/CanvasContextCreationAttributes.h"
#include "core/html/canvas/CanvasPathMethods.h"
#include "core/html/canvas/CanvasRenderingContext.h"
#include "core/html/canvas/ClipList.h"
#include "core/html/canvas/HitRegion.h"
#include "core/svg/SVGMatrixTearOff.h"
#include "platform/fonts/Font.h"
#include "platform/graphics/Color.h"
#include "platform/geometry/FloatSize.h"
#include "platform/graphics/GraphicsTypes.h"
#include "platform/graphics/ImageBuffer.h"
#include "platform/graphics/Path.h"
#include "platform/transforms/AffineTransform.h"
#include "wtf/HashMap.h"
#include "wtf/ListHashSet.h"
#include "wtf/Vector.h"
#include "wtf/text/WTFString.h"

namespace blink { class WebLayer; }

namespace blink {

class CanvasImageSource;
class CanvasGradient;
class CanvasPattern;
class CanvasStyle;
class Path2D;
class Element;
class ExceptionState;
class FloatRect;
class HTMLCanvasElement;
class HTMLImageElement;
class HTMLVideoElement;
class ImageData;
class TextMetrics;

typedef HTMLImageElementOrHTMLVideoElementOrHTMLCanvasElementOrImageBitmap CanvasImageSourceUnion;

typedef WillBeHeapHashMap<String, RefPtrWillBeMember<MutableStylePropertySet>> MutableStylePropertyMap;

class CanvasRenderingContext2D final: public CanvasRenderingContext, public ScriptWrappable, public CanvasPathMethods {
    DEFINE_WRAPPERTYPEINFO();
public:
    static PassOwnPtrWillBeRawPtr<CanvasRenderingContext2D> create(HTMLCanvasElement* canvas, const CanvasContextCreationAttributes& attrs, Document& document)
    {
        return adoptPtrWillBeNoop(new CanvasRenderingContext2D(canvas, attrs, document));
    }
    virtual ~CanvasRenderingContext2D();

    void strokeStyle(StringOrCanvasGradientOrCanvasPattern&) const;
    void setStrokeStyle(const StringOrCanvasGradientOrCanvasPattern&);

    void fillStyle(StringOrCanvasGradientOrCanvasPattern&) const;
    void setFillStyle(const StringOrCanvasGradientOrCanvasPattern&);

    float lineWidth() const;
    void setLineWidth(float);

    String lineCap() const;
    void setLineCap(const String&);

    String lineJoin() const;
    void setLineJoin(const String&);

    float miterLimit() const;
    void setMiterLimit(float);

    const Vector<float>& getLineDash() const;
    void setLineDash(const Vector<float>&);

    float lineDashOffset() const;
    void setLineDashOffset(float);

    float shadowOffsetX() const;
    void setShadowOffsetX(float);

    float shadowOffsetY() const;
    void setShadowOffsetY(float);

    float shadowBlur() const;
    void setShadowBlur(float);

    String shadowColor() const;
    void setShadowColor(const String&);

    float globalAlpha() const;
    void setGlobalAlpha(float);

    bool isContextLost() const;

    String globalCompositeOperation() const;
    void setGlobalCompositeOperation(const String&);

    void save() { ++m_stateStack.last()->m_unrealizedSaveCount; }
    void restore();

    PassRefPtrWillBeRawPtr<SVGMatrixTearOff> currentTransform() const
    {
        return SVGMatrixTearOff::create(state().m_transform);
    }
    void setCurrentTransform(PassRefPtrWillBeRawPtr<SVGMatrixTearOff>);

    void scale(float sx, float sy);
    void rotate(float angleInRadians);
    void translate(float tx, float ty);
    void transform(float m11, float m12, float m21, float m22, float dx, float dy);
    void setTransform(float m11, float m12, float m21, float m22, float dx, float dy);
    void resetTransform();

    void beginPath();

    void fill(const String& winding = "nonzero");
    void fill(Path2D*, const String& winding = "nonzero");
    void stroke();
    void stroke(Path2D*);
    void clip(const String& winding = "nonzero");
    void clip(Path2D*, const String& winding = "nonzero");

    bool isPointInPath(const float x, const float y, const String& winding = "nonzero");
    bool isPointInPath(Path2D*, const float x, const float y, const String& winding = "nonzero");
    bool isPointInStroke(const float x, const float y);
    bool isPointInStroke(Path2D*, const float x, const float y);

    void scrollPathIntoView();
    void scrollPathIntoView(Path2D*);

    void clearRect(float x, float y, float width, float height);
    void fillRect(float x, float y, float width, float height);
    void strokeRect(float x, float y, float width, float height);

    void drawImage(const CanvasImageSourceUnion&, float x, float y, ExceptionState&);
    void drawImage(const CanvasImageSourceUnion&, float x, float y, float width, float height, ExceptionState&);
    void drawImage(const CanvasImageSourceUnion&, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh, ExceptionState&);
    void drawImage(CanvasImageSource*, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh, ExceptionState&);

    PassRefPtrWillBeRawPtr<CanvasGradient> createLinearGradient(float x0, float y0, float x1, float y1);
    PassRefPtrWillBeRawPtr<CanvasGradient> createRadialGradient(float x0, float y0, float r0, float x1, float y1, float r1, ExceptionState&);
    PassRefPtrWillBeRawPtr<CanvasPattern> createPattern(const CanvasImageSourceUnion&, const String& repetitionType, ExceptionState&);

    PassRefPtrWillBeRawPtr<ImageData> createImageData(PassRefPtrWillBeRawPtr<ImageData>) const;
    PassRefPtrWillBeRawPtr<ImageData> createImageData(float width, float height, ExceptionState&) const;
    PassRefPtrWillBeRawPtr<ImageData> getImageData(float sx, float sy, float sw, float sh, ExceptionState&) const;
    void putImageData(ImageData*, float dx, float dy);
    void putImageData(ImageData*, float dx, float dy, float dirtyX, float dirtyY, float dirtyWidth, float dirtyHeight);

    void reset();

    String font() const;
    void setFont(const String&);

    String textAlign() const;
    void setTextAlign(const String&);

    String textBaseline() const;
    void setTextBaseline(const String&);

    String direction() const;
    void setDirection(const String&);

    void fillText(const String& text, float x, float y);
    void fillText(const String& text, float x, float y, float maxWidth);
    void strokeText(const String& text, float x, float y);
    void strokeText(const String& text, float x, float y, float maxWidth);
    PassRefPtrWillBeRawPtr<TextMetrics> measureText(const String& text);

    LineCap getLineCap() const { return state().m_lineCap; }
    LineJoin getLineJoin() const { return state().m_lineJoin; }

    bool imageSmoothingEnabled() const;
    void setImageSmoothingEnabled(bool);

    void getContextAttributes(Canvas2DContextAttributes&) const;

    void drawFocusIfNeeded(Element*);
    void drawFocusIfNeeded(Path2D*, Element*);

    void addHitRegion(const HitRegionOptions&, ExceptionState&);
    void removeHitRegion(const String& id);
    void clearHitRegions();
    HitRegion* hitRegionAtPoint(const LayoutPoint&);
    unsigned hitRegionsCount() const;

    void loseContext();
    void restoreContext();

    void restoreCanvasMatrixClipStack();

    virtual void trace(Visitor*) override;

private:
    friend class CanvasRenderingContext2DAutoRestoreSkCanvas;

    enum Direction {
        DirectionInherit,
        DirectionRTL,
        DirectionLTR
    };

    enum ClipListCopyMode {
        CopyClipList,
        DontCopyClipList
    };

    class State final : public CSSFontSelectorClient {
    public:
        State();
        virtual ~State();

        State(const State&, ClipListCopyMode = CopyClipList);
        State& operator=(const State&);

        // CSSFontSelectorClient implementation
        virtual void fontsNeedUpdate(CSSFontSelector*) override;

        virtual void trace(Visitor*) override;

        unsigned m_unrealizedSaveCount;

        String m_unparsedStrokeColor;
        String m_unparsedFillColor;
        RefPtrWillBeMember<CanvasStyle> m_strokeStyle;
        RefPtrWillBeMember<CanvasStyle> m_fillStyle;

        float m_lineWidth;
        LineCap m_lineCap;
        LineJoin m_lineJoin;
        float m_miterLimit;
        FloatSize m_shadowOffset;
        float m_shadowBlur;
        RGBA32 m_shadowColor;
        float m_globalAlpha;
        SkXfermode::Mode m_globalComposite;
        AffineTransform m_transform;
        bool m_invertibleCTM;
        Vector<float> m_lineDash;
        float m_lineDashOffset;
        bool m_imageSmoothingEnabled;

        // Text state.
        TextAlign m_textAlign;
        TextBaseline m_textBaseline;
        Direction m_direction;

        String m_unparsedFont;
        Font m_font;
        bool m_realizedFont;

        bool m_hasClip;
        bool m_hasComplexClip;

        ClipList m_clipList;
    };

    CanvasRenderingContext2D(HTMLCanvasElement*, const CanvasContextCreationAttributes& attrs, Document&);

    State& modifiableState() { ASSERT(!state().m_unrealizedSaveCount); return *m_stateStack.last(); }
    const State& state() const { return *m_stateStack.last(); }

    void applyLineDash() const;
    void setShadow(const FloatSize& offset, float blur, RGBA32 color);
    void applyShadow(ShadowMode = DrawShadowAndForeground);
    bool shouldDrawShadows() const;

    void dispatchContextLostEvent(Timer<CanvasRenderingContext2D>*);
    void dispatchContextRestoredEvent(Timer<CanvasRenderingContext2D>*);
    void tryRestoreContextEvent(Timer<CanvasRenderingContext2D>*);

    bool computeDirtyRect(const FloatRect& localBounds, FloatRect*);
    bool computeDirtyRect(const FloatRect& localBounds, const FloatRect& transformedClipBounds, FloatRect*);
    void didDraw(const FloatRect&);

    GraphicsContext* drawingContext() const; // Deprecated: use drawingCanvas
    SkCanvas* drawingCanvas() const;

    void unwindStateStack();
    void realizeSaves(SkCanvas*);

    void applyStrokePattern();
    void applyFillPattern();

    void fillInternal(const Path&, const String& windingRuleString);
    void strokeInternal(const Path&);
    void clipInternal(const Path&, const String& windingRuleString);

    bool isPointInPathInternal(const Path&, const float x, const float y, const String& windingRuleString);
    bool isPointInStrokeInternal(const Path&, const float x, const float y);

    void scrollPathIntoViewInternal(const Path&);

    void drawTextInternal(const String& text, float x, float y, bool fill, float maxWidth = 0, bool useMaxWidth = false);

    const Font& accessFont();
    int getFontBaseline(const FontMetrics&) const;

    void clearCanvas();
    bool rectContainsTransformedRect(const FloatRect&, const FloatRect&) const;

    void inflateStrokeRect(FloatRect&) const;

    void fullCanvasCompositedDraw(PassOwnPtr<Closure> draw);

    void drawFocusIfNeededInternal(const Path&, Element*);
    bool focusRingCallIsValid(const Path&, Element*);
    void drawFocusRing(const Path&);

    bool hasClip() { return state().m_hasClip; }

    void validateStateStack();

    enum DrawType {
        ClipFill, // Fill that is already known to cover the current clip
        UntransformedUnclippedFill
    };

    enum ImageType {
        NoImage,
        OpaqueImage,
        NonOpaqueImage
    };

    void checkOverdraw(const SkRect&, const SkPaint*, ImageType, DrawType);

    virtual bool is2d() const override { return true; }
    virtual bool isAccelerated() const override;
    virtual bool hasAlpha() const override { return m_hasAlpha; }
    virtual void setIsHidden(bool) override;

    virtual bool isTransformInvertible() const override { return state().m_invertibleCTM; }

    virtual WebLayer* platformLayer() const override;
    TextDirection toTextDirection(Direction, LayoutStyle** computedStyle = nullptr) const;

    WillBeHeapVector<OwnPtrWillBeMember<State>> m_stateStack;
    OwnPtrWillBeMember<HitRegionManager> m_hitRegionManager;
    bool m_usesCSSCompatibilityParseMode;
    AntiAliasingMode m_clipAntialiasing;
    bool m_hasAlpha;
    bool m_isContextLost;
    bool m_contextRestorable;
    MutableStylePropertyMap m_fetchedFonts;
    ListHashSet<String> m_fetchedFontsLRUList;
    unsigned m_tryRestoreContextAttemptCount;
    Timer<CanvasRenderingContext2D> m_dispatchContextLostEventTimer;
    Timer<CanvasRenderingContext2D> m_dispatchContextRestoredEventTimer;
    Timer<CanvasRenderingContext2D> m_tryRestoreContextEventTimer;
};

DEFINE_TYPE_CASTS(CanvasRenderingContext2D, CanvasRenderingContext, context, context->is2d(), context.is2d());

} // namespace blink

#endif // CanvasRenderingContext2D_h
