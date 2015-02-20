// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CSSParserToken_h
#define CSSParserToken_h

#include "core/css/CSSPrimitiveValue.h"
#include "wtf/text/WTFString.h"

namespace blink {

enum CSSParserTokenType {
    IdentToken = 0,
    FunctionToken,
    AtKeywordToken,
    HashToken,
    UrlToken,
    BadUrlToken,
    DelimiterToken,
    NumberToken,
    PercentageToken,
    DimensionToken,
    IncludeMatchToken,
    DashMatchToken,
    PrefixMatchToken,
    SuffixMatchToken,
    SubstringMatchToken,
    ColumnToken,
    UnicodeRangeToken,
    WhitespaceToken,
    CDOToken,
    CDCToken,
    ColonToken,
    SemicolonToken,
    CommaToken,
    LeftParenthesisToken,
    RightParenthesisToken,
    LeftBracketToken,
    RightBracketToken,
    LeftBraceToken,
    RightBraceToken,
    StringToken,
    BadStringToken,
    EOFToken,
    CommentToken,
};

enum NumericSign {
    NoSign,
    PlusSign,
    MinusSign,
};

enum NumericValueType {
    IntegerValueType,
    NumberValueType,
};

enum HashTokenType {
    HashTokenId,
    HashTokenUnrestricted,
};

class CSSParserToken {
public:
    enum BlockType {
        NotBlock,
        BlockStart,
        BlockEnd,
    };

    CSSParserToken(CSSParserTokenType, BlockType = NotBlock);
    CSSParserToken(CSSParserTokenType, String value, BlockType = NotBlock);

    CSSParserToken(CSSParserTokenType, UChar); // for DelimiterToken
    CSSParserToken(CSSParserTokenType, double, NumericValueType, NumericSign); // for NumberToken
    CSSParserToken(CSSParserTokenType, UChar32, UChar32); // for UnicodeRangeToken

    CSSParserToken(HashTokenType, String);

    // Converts NumberToken to DimensionToken.
    void convertToDimensionWithUnit(String);

    // Converts NumberToken to PercentageToken.
    void convertToPercentage();

    CSSParserTokenType type() const { return static_cast<CSSParserTokenType>(m_type); }
    String value() const { return m_value; }

    UChar delimiter() const;
    NumericSign numericSign() const;
    NumericValueType numericValueType() const;
    double numericValue() const;
    HashTokenType hashTokenType() const { ASSERT(m_type == HashToken); return m_hashTokenType; }
    BlockType blockType() const { return static_cast<BlockType>(m_blockType); }
    CSSPrimitiveValue::UnitType unitType() const { return static_cast<CSSPrimitiveValue::UnitType>(m_unit); }
    UChar32 unicodeRangeStart() const { ASSERT(m_type == UnicodeRangeToken); return m_unicodeRange.start; }
    UChar32 unicodeRangeEnd() const { ASSERT(m_type == UnicodeRangeToken); return m_unicodeRange.end; }

    CSSPropertyID parseAsCSSPropertyID() const;

private:
    unsigned m_type : 6; // CSSParserTokenType
    unsigned m_blockType : 2; // BlockType
    unsigned m_numericValueType : 1; // NumericValueType
    unsigned m_numericSign : 2; // NumericSign
    unsigned m_unit : 7; // CSSPrimitiveValue::UnitType

    String m_value;

    union {
        UChar m_delimiter;
        HashTokenType m_hashTokenType;
        double m_numericValue;

        struct {
            UChar32 start;
            UChar32 end;
        } m_unicodeRange;
    };
};

} // namespace blink

namespace WTF {
template <>
struct IsTriviallyMoveAssignable<blink::CSSParserToken> {
    static const bool value = true;
};
}

#endif // CSSSParserToken_h
