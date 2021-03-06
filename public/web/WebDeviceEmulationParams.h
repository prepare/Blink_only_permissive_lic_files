// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WebDeviceEmulationParams_h
#define WebDeviceEmulationParams_h

#include "../platform/WebFloatPoint.h"
#include "../platform/WebRect.h"
#include "../platform/WebSize.h"

namespace blink {

// All sizes are measured in device independent pixels.
struct WebDeviceEmulationParams {
    // For mobile, screen has the same size as view, which is positioned at (0;0).
    // For desktop, screen size and view position are preserved.
    enum ScreenPosition {
        Desktop,
        Mobile,
        ScreenPositionLast = Mobile
    };

    ScreenPosition screenPosition;

    // If zero, the original device scale factor is preserved.
    float deviceScaleFactor;

    // Emulated view size. Empty size means no override.
    WebSize viewSize;

    // Whether emulated view should be scaled down if necessary to fit into available space.
    bool fitToView;

    // Offset of emulated view inside available space, not in fit to view mode.
    WebFloatPoint offset;

    // Scale of emulated view inside available space, not in fit to view mode.
    float scale;

    WebDeviceEmulationParams()
        : screenPosition(Desktop)
        , deviceScaleFactor(0)
        , fitToView(false)
        , scale(1) { }
};

inline bool operator==(const WebDeviceEmulationParams& a, const WebDeviceEmulationParams& b)
{
    return a.screenPosition == b.screenPosition && a.deviceScaleFactor == b.deviceScaleFactor && a.viewSize == b.viewSize && a.fitToView == b.fitToView && a.offset == b.offset && a.scale == b.scale;
}

inline bool operator!=(const WebDeviceEmulationParams& a, const WebDeviceEmulationParams& b)
{
    return !(a == b);
}

} // namespace blink

#endif
