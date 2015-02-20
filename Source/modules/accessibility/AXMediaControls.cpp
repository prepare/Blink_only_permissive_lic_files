/*
 * Copyright (C) 2009 Apple Inc. All rights reserved.
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


#include "config.h"
#include "modules/accessibility/AXMediaControls.h"

#include "modules/accessibility/AXObjectCacheImpl.h"
#include "platform/text/PlatformLocale.h"

namespace blink {

using blink::WebLocalizedString;
using namespace HTMLNames;

static inline String queryString(WebLocalizedString::Name name)
{
    return Locale::defaultLocale().queryString(name);
}

AccessibilityMediaControl::AccessibilityMediaControl(LayoutObject* renderer, AXObjectCacheImpl* axObjectCache)
    : AXRenderObject(renderer, axObjectCache)
{
}

PassRefPtr<AXObject> AccessibilityMediaControl::create(LayoutObject* renderer, AXObjectCacheImpl* axObjectCache)
{
    ASSERT(renderer->node());

    switch (mediaControlElementType(renderer->node())) {
    case MediaSlider:
        return AccessibilityMediaTimeline::create(renderer, axObjectCache);

    case MediaCurrentTimeDisplay:
    case MediaTimeRemainingDisplay:
        return AccessibilityMediaTimeDisplay::create(renderer, axObjectCache);

    case MediaControlsPanel:
        return AXMediaControlsContainer::create(renderer, axObjectCache);

    default:
        return adoptRef(new AccessibilityMediaControl(renderer, axObjectCache));
    }
}

MediaControlElementType AccessibilityMediaControl::controlType() const
{
    if (!renderer() || !renderer()->node())
        return MediaTimelineContainer; // Timeline container is not accessible.

    return mediaControlElementType(renderer()->node());
}

String AccessibilityMediaControl::title(TextUnderElementMode mode) const
{
    // FIXME: the ControlsPanel container should never be visible in the
    // accessibility hierarchy.
    if (controlType() == MediaControlsPanel)
        return queryString(WebLocalizedString::AXMediaDefault);

    return AXRenderObject::title(mode);
}

String AccessibilityMediaControl::accessibilityDescription() const
{
    switch (controlType()) {
    case MediaEnterFullscreenButton:
        return queryString(WebLocalizedString::AXMediaEnterFullscreenButton);
    case MediaExitFullscreenButton:
        return queryString(WebLocalizedString::AXMediaExitFullscreenButton);
    case MediaMuteButton:
        return queryString(WebLocalizedString::AXMediaMuteButton);
    case MediaPlayButton:
        return queryString(WebLocalizedString::AXMediaPlayButton);
    case MediaUnMuteButton:
        return queryString(WebLocalizedString::AXMediaUnMuteButton);
    case MediaPauseButton:
        return queryString(WebLocalizedString::AXMediaPauseButton);
    case MediaStatusDisplay:
        return queryString(WebLocalizedString::AXMediaStatusDisplay);
    case MediaCurrentTimeDisplay:
        return queryString(WebLocalizedString::AXMediaCurrentTimeDisplay);
    case MediaTimeRemainingDisplay:
        return queryString(WebLocalizedString::AXMediaTimeRemainingDisplay);
    case MediaShowClosedCaptionsButton:
        return queryString(WebLocalizedString::AXMediaShowClosedCaptionsButton);
    case MediaHideClosedCaptionsButton:
        return queryString(WebLocalizedString::AXMediaHideClosedCaptionsButton);
    case MediaCastOffButton:
        return queryString(WebLocalizedString::AxMediaCastOffButton);
    case MediaCastOnButton:
        return queryString(WebLocalizedString::AxMediaCastOnButton);
    default:
        return queryString(WebLocalizedString::AXMediaDefault);
    }
}

String AccessibilityMediaControl::helpText() const
{
    switch (controlType()) {
    case MediaEnterFullscreenButton:
        return queryString(WebLocalizedString::AXMediaEnterFullscreenButtonHelp);
    case MediaExitFullscreenButton:
        return queryString(WebLocalizedString::AXMediaExitFullscreenButtonHelp);
    case MediaMuteButton:
        return queryString(WebLocalizedString::AXMediaMuteButtonHelp);
    case MediaPlayButton:
        return queryString(WebLocalizedString::AXMediaPlayButtonHelp);
    case MediaUnMuteButton:
        return queryString(WebLocalizedString::AXMediaUnMuteButtonHelp);
    case MediaPauseButton:
        return queryString(WebLocalizedString::AXMediaPauseButtonHelp);
    case MediaStatusDisplay:
        return queryString(WebLocalizedString::AXMediaStatusDisplayHelp);
    case MediaCurrentTimeDisplay:
        return queryString(WebLocalizedString::AXMediaCurrentTimeDisplayHelp);
    case MediaTimeRemainingDisplay:
        return queryString(WebLocalizedString::AXMediaTimeRemainingDisplayHelp);
    case MediaShowClosedCaptionsButton:
        return queryString(WebLocalizedString::AXMediaShowClosedCaptionsButtonHelp);
    case MediaHideClosedCaptionsButton:
        return queryString(WebLocalizedString::AXMediaHideClosedCaptionsButtonHelp);
    case MediaCastOffButton:
        return queryString(WebLocalizedString::AxMediaCastOffButtonHelp);
    case MediaCastOnButton:
        return queryString(WebLocalizedString::AxMediaCastOnButtonHelp);
    default:
        return queryString(WebLocalizedString::AXMediaDefault);
    }
}

bool AccessibilityMediaControl::computeAccessibilityIsIgnored() const
{
    if (!m_renderer || !m_renderer->style() || m_renderer->style()->visibility() != VISIBLE || controlType() == MediaTimelineContainer)
        return true;

    return accessibilityIsIgnoredByDefault();
}

AccessibilityRole AccessibilityMediaControl::roleValue() const
{
    switch (controlType()) {
    case MediaEnterFullscreenButton:
    case MediaExitFullscreenButton:
    case MediaMuteButton:
    case MediaPlayButton:
    case MediaUnMuteButton:
    case MediaPauseButton:
    case MediaShowClosedCaptionsButton:
    case MediaHideClosedCaptionsButton:
        return ButtonRole;

    case MediaStatusDisplay:
        return StaticTextRole;

    case MediaTimelineContainer:
        return GroupRole;

    default:
        break;
    }

    return UnknownRole;
}



//
// AXMediaControlsContainer

AXMediaControlsContainer::AXMediaControlsContainer(LayoutObject* renderer, AXObjectCacheImpl* axObjectCache)
    : AccessibilityMediaControl(renderer, axObjectCache)
{
}

PassRefPtr<AXObject> AXMediaControlsContainer::create(LayoutObject* renderer, AXObjectCacheImpl* axObjectCache)
{
    return adoptRef(new AXMediaControlsContainer(renderer, axObjectCache));
}

String AXMediaControlsContainer::accessibilityDescription() const
{
    return queryString(isControllingVideoElement() ? WebLocalizedString::AXMediaVideoElement : WebLocalizedString::AXMediaAudioElement);
}

String AXMediaControlsContainer::helpText() const
{
    return queryString(isControllingVideoElement() ? WebLocalizedString::AXMediaVideoElementHelp : WebLocalizedString::AXMediaAudioElementHelp);
}

bool AXMediaControlsContainer::computeAccessibilityIsIgnored() const
{
    return accessibilityIsIgnoredByDefault();
}

//
// AccessibilityMediaTimeline

static String localizedMediaTimeDescription(float /*time*/)
{
    // FIXME: To be fixed. See
    // http://trac.webkit.org/browser/trunk/Source/WebCore/platform/LocalizedStrings.cpp#L928
    return String();
}

AccessibilityMediaTimeline::AccessibilityMediaTimeline(LayoutObject* renderer, AXObjectCacheImpl* axObjectCache)
    : AXSlider(renderer, axObjectCache)
{
}

PassRefPtr<AXObject> AccessibilityMediaTimeline::create(LayoutObject* renderer, AXObjectCacheImpl* axObjectCache)
{
    return adoptRef(new AccessibilityMediaTimeline(renderer, axObjectCache));
}

String AccessibilityMediaTimeline::valueDescription() const
{
    Node* node = m_renderer->node();
    if (!isHTMLInputElement(node))
        return String();

    return localizedMediaTimeDescription(toHTMLInputElement(node)->value().toFloat());
}

String AccessibilityMediaTimeline::helpText() const
{
    return queryString(isControllingVideoElement() ? WebLocalizedString::AXMediaVideoSliderHelp : WebLocalizedString::AXMediaAudioSliderHelp);
}


//
// AccessibilityMediaTimeDisplay

AccessibilityMediaTimeDisplay::AccessibilityMediaTimeDisplay(LayoutObject* renderer, AXObjectCacheImpl* axObjectCache)
    : AccessibilityMediaControl(renderer, axObjectCache)
{
}

PassRefPtr<AXObject> AccessibilityMediaTimeDisplay::create(LayoutObject* renderer, AXObjectCacheImpl* axObjectCache)
{
    return adoptRef(new AccessibilityMediaTimeDisplay(renderer, axObjectCache));
}

bool AccessibilityMediaTimeDisplay::computeAccessibilityIsIgnored() const
{
    if (!m_renderer || !m_renderer->style() || m_renderer->style()->visibility() != VISIBLE)
        return true;

    if (!m_renderer->style()->width().value())
        return true;

    return accessibilityIsIgnoredByDefault();
}

String AccessibilityMediaTimeDisplay::accessibilityDescription() const
{
    if (controlType() == MediaCurrentTimeDisplay)
        return queryString(WebLocalizedString::AXMediaCurrentTimeDisplay);
    return queryString(WebLocalizedString::AXMediaTimeRemainingDisplay);
}

String AccessibilityMediaTimeDisplay::stringValue() const
{
    if (!m_renderer || !m_renderer->node())
        return String();

    MediaControlTimeDisplayElement* element = static_cast<MediaControlTimeDisplayElement*>(m_renderer->node());
    float time = element->currentValue();
    return localizedMediaTimeDescription(fabsf(time));
}

} // namespace blink
