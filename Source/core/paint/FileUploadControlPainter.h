// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FileUploadControlPainter_h
#define FileUploadControlPainter_h

namespace blink {

struct PaintInfo;
class LayoutPoint;
class LayoutFileUploadControl;

class FileUploadControlPainter {
public:
    FileUploadControlPainter(LayoutFileUploadControl& renderFileUploadControl) : m_renderFileUploadControl(renderFileUploadControl) { }

    void paintObject(const PaintInfo&, const LayoutPoint&);

private:
    LayoutFileUploadControl& m_renderFileUploadControl;
};

} // namespace blink

#endif // FileUploadControlPainter_h
