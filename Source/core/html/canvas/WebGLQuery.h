// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WebGLQuery_h
#define WebGLQuery_h

#include "core/html/canvas/WebGLSharedObject.h"
#include "wtf/PassRefPtr.h"

namespace blink {

class WebGL2RenderingContextBase;

class WebGLQuery : public WebGLSharedObject {
    DEFINE_WRAPPERTYPEINFO();
public:
    ~WebGLQuery() override;

    static PassRefPtrWillBeRawPtr<WebGLQuery> create(WebGL2RenderingContextBase*);

protected:
    explicit WebGLQuery(WebGL2RenderingContextBase*);

    void deleteObjectImpl(blink::WebGraphicsContext3D*, Platform3DObject) override;

private:
    bool isQuery() const override { return true; }
};

} // namespace blink

#endif // WebGLQuery_h