/*
 * Copyright (C) 2008-2011 The QXmpp developers
 *
 * Authors:
 *  Andrey Batyiev
 *
 * Source:
 *  http://code.google.com/p/qxmpp
 *
 * This file is a part of QXmpp library.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 */

#include "QXmppCaptchaIq.h"
#include "QXmppConstants.h"

QXmppCaptchaIq::QXmppCaptchaIq(QXmppIq::Type type)
    : QXmppIq(type)
{
}

QXmppDataForm QXmppCaptchaIq::dataForm() const
{
    return m_form;
}

void QXmppCaptchaIq::setDataForm(const QXmppDataForm& dataForm)
{
    m_form = dataForm;
}

void QXmppCaptchaIq::toXmlElementFromChild(QXmlStreamWriter* writer) const
{
    writer->writeStartElement("captcha");
    writer->writeAttribute("xmlns", ns_captcha);
    m_form.toXml(writer);
    writer->writeEndElement();
}
