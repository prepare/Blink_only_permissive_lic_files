// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DOMNodeIds_h
#define DOMNodeIds_h

#include "core/CoreExport.h"

namespace blink {

class Node;

class CORE_EXPORT DOMNodeIds {
public:
    static int idForNode(Node*);
    static Node* nodeForId(int);
};

} // namespace blink


#endif // DOMNodeIds_h
