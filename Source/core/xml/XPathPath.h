/*
 * Copyright (C) 2005 Frerich Raabe <raabe@kde.org>
 * Copyright (C) 2006, 2009 Apple Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef XPathPath_h
#define XPathPath_h

#include "core/xml/XPathExpressionNode.h"
#include "core/xml/XPathNodeSet.h"

namespace blink {

namespace XPath {

class Predicate;
class Step;

class Filter final : public Expression {
public:
    Filter(PassOwnPtrWillBeRawPtr<Expression>, WillBeHeapVector<OwnPtrWillBeMember<Predicate> >&);
    virtual ~Filter();
    DECLARE_VIRTUAL_TRACE();

    virtual Value evaluate(EvaluationContext&) const override;

private:
    virtual Value::Type resultType() const override { return Value::NodeSetValue; }

    OwnPtrWillBeMember<Expression> m_expr;
    WillBeHeapVector<OwnPtrWillBeMember<Predicate> > m_predicates;
};

class LocationPath final : public Expression {
public:
    LocationPath();
    virtual ~LocationPath();
    DECLARE_VIRTUAL_TRACE();

    virtual Value evaluate(EvaluationContext&) const override;
    void setAbsolute(bool value) { m_absolute = value; setIsContextNodeSensitive(!m_absolute); }
    void evaluate(EvaluationContext&, NodeSet&) const; // nodes is an input/output parameter
    void appendStep(Step*);
    void insertFirstStep(Step*);

private:
    virtual Value::Type resultType() const override { return Value::NodeSetValue; }

    WillBeHeapVector<RawPtrWillBeMember<Step> > m_steps;
    bool m_absolute;
};

class Path final : public Expression {
public:
    Path(Expression*, LocationPath*);
    virtual ~Path();
    DECLARE_VIRTUAL_TRACE();

    virtual Value evaluate(EvaluationContext&) const override;

private:
    virtual Value::Type resultType() const override { return Value::NodeSetValue; }

    OwnPtrWillBeMember<Expression> m_filter;
    OwnPtrWillBeMember<LocationPath> m_path;
};

}

}
#endif // XPathPath_h