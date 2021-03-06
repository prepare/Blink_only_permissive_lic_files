// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SubresourceIntegrity_h
#define SubresourceIntegrity_h

#include "core/CoreExport.h"
#include "platform/Crypto.h"

namespace WTF {
class String;
};

namespace blink {

class Document;
class Element;
class KURL;
class Resource;

class CORE_EXPORT SubresourceIntegrity {
public:
    enum IntegrityParseResult {
        IntegrityParseValidResult,
        IntegrityParseNoValidResult
    };

    static bool CheckSubresourceIntegrity(const Element&, const WTF::String& content, const KURL& resourceUrl, const WTF::String& mimeType, const Resource&);

private:
    // FIXME: After the merge with the Chromium repo, this should be refactored
    // to use FRIEND_TEST in base/gtest_prod_util.h.
    friend class SubresourceIntegrityTest;
    friend class SubresourceIntegrityTest_Parsing_Test;
    friend class SubresourceIntegrityTest_ParseAlgorithm_Test;

    enum AlgorithmParseResult {
        AlgorithmValid,
        AlgorithmUnparsable,
        AlgorithmUnknown
    };

    struct IntegrityMetadata {
        WTF::String digest;
        HashAlgorithm algorithm;
        WTF::String type;
    };

    static AlgorithmParseResult parseAlgorithm(const UChar*& begin, const UChar* end, HashAlgorithm&);
    static bool parseDigest(const UChar*& begin, const UChar* end, String& digest);
    static bool parseMimeType(const UChar*& begin, const UChar* end, String& type);

    static IntegrityParseResult parseIntegrityAttribute(const WTF::String& attribute, WTF::Vector<IntegrityMetadata>& metadataList, Document&);
};

} // namespace blink

#endif
