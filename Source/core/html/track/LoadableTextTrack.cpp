/*
 * Copyright (C) 2011 Google Inc.  All rights reserved.
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

#include "config.h"
#include "core/html/track/LoadableTextTrack.h"

#include "core/dom/ElementTraversal.h"
#include "core/html/HTMLMediaElement.h"
#include "core/html/HTMLTrackElement.h"
#include "core/html/track/CueTimeline.h"
#include "core/html/track/TextTrackCueList.h"
#include "core/html/track/vtt/VTTRegionList.h"

namespace blink {

using namespace HTMLNames;

LoadableTextTrack::LoadableTextTrack(HTMLTrackElement* track)
    : TextTrack(emptyAtom, emptyAtom, emptyAtom, emptyAtom, TrackElement)
    , m_trackElement(track)
    , m_loadTimer(this, &LoadableTextTrack::loadTimerFired)
    , m_isDefault(false)
{
}

LoadableTextTrack::~LoadableTextTrack()
{
#if !ENABLE(OILPAN)
    ASSERT(!m_trackElement);
#endif
}

#if !ENABLE(OILPAN)
void LoadableTextTrack::clearTrackElement()
{
    m_trackElement = nullptr;
}
#endif

void LoadableTextTrack::setMode(const AtomicString& mode)
{
    TextTrack::setMode(mode);
#if !ENABLE(OILPAN)
    if (!m_trackElement)
        return;
#endif

    if (m_trackElement->readyState() == HTMLTrackElement::NONE)
        m_trackElement->scheduleLoad();
}

void LoadableTextTrack::scheduleLoad(const KURL& url)
{
    if (url == m_url) {
        // If loading of the resource from this URL is in progress, return early.
        ASSERT(m_loader && m_trackElement);
        if (m_loader->loadState() < TextTrackLoader::Finished)
            return;

        // The track element might have changed its state to HTMLTrackElement::Loading
        // waiting for a call to didCompleteLoad to continue.
        cueLoadingCompleted(m_loader.get(), m_loader->loadState() == TextTrackLoader::Failed);
        return;
    }

    // 4.8.10.12.3 Sourcing out-of-band text tracks (continued)

    // 2. Let URL be the track URL of the track element.
    m_url = url;

    // 3. Asynchronously run the remaining steps, while continuing with whatever task
    // was responsible for creating the text track or changing the text track mode.
    if (!m_loadTimer.isActive())
        m_loadTimer.startOneShot(0, FROM_HERE);
}

void LoadableTextTrack::loadTimerFired(Timer<LoadableTextTrack>*)
{
    if (m_loader)
        m_loader->cancelLoad();

#if !ENABLE(OILPAN)
    if (!m_trackElement)
        return;
#endif

    // 4.8.10.12.3 Sourcing out-of-band text tracks (continued)

    // 4. Download: If URL is not the empty string, perform a potentially CORS-enabled fetch of URL, with the
    // mode being the state of the media element's crossorigin content attribute, the origin being the
    // origin of the media element's Document, and the default origin behaviour set to fail.
    m_loader = TextTrackLoader::create(*this, m_trackElement->document());
    if (!m_loader->load(m_url, m_trackElement->mediaElementCrossOriginAttribute()))
        m_trackElement->didCompleteLoad(HTMLTrackElement::Failure);
}

void LoadableTextTrack::newCuesAvailable(TextTrackLoader* loader)
{
    ASSERT_UNUSED(loader, m_loader == loader);

    WillBeHeapVector<RefPtrWillBeMember<VTTCue>> newCues;
    m_loader->getNewCues(newCues);

    if (!m_cues)
        m_cues = TextTrackCueList::create();

    for (size_t i = 0; i < newCues.size(); ++i) {
        newCues[i]->setTrack(this);
        m_cues->add(newCues[i].release());
    }

    if (cueTimeline() && mode() != disabledKeyword())
        cueTimeline()->addCues(this, m_cues.get());
}

void LoadableTextTrack::cueLoadingCompleted(TextTrackLoader* loader, bool loadingFailed)
{
    ASSERT_UNUSED(loader, m_loader == loader);

#if !ENABLE(OILPAN)
    if (!m_trackElement)
        return;
#endif

    m_trackElement->didCompleteLoad(loadingFailed ? HTMLTrackElement::Failure : HTMLTrackElement::Success);
}

void LoadableTextTrack::newRegionsAvailable(TextTrackLoader* loader)
{
    ASSERT_UNUSED(loader, m_loader == loader);

    WillBeHeapVector<RefPtrWillBeMember<VTTRegion>> newRegions;
    m_loader->getNewRegions(newRegions);

    for (size_t i = 0; i < newRegions.size(); ++i) {
        newRegions[i]->setTrack(this);
        regions()->add(newRegions[i]);
    }
}

size_t LoadableTextTrack::trackElementIndex()
{
    ASSERT(m_trackElement);
    ASSERT(m_trackElement->parentNode());

    size_t index = 0;
    for (HTMLTrackElement* track = Traversal<HTMLTrackElement>::firstChild(*m_trackElement->parentNode()); track; track = Traversal<HTMLTrackElement>::nextSibling(*track)) {
        if (!track->parentNode())
            continue;
        if (track == m_trackElement)
            return index;
        ++index;
    }
    ASSERT_NOT_REACHED();

    return 0;
}

void LoadableTextTrack::trace(Visitor* visitor)
{
    visitor->trace(m_trackElement);
    visitor->trace(m_loader);
    TextTrack::trace(visitor);
}

} // namespace blink