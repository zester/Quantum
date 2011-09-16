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

#include <QDomElement>

#include "QXmppBobIq.h"
#include "QXmppConstants.h"
#include "QXmppUtils.h"


QXmppBobIq::QXmppBobIq(QXmppIq::Type type)
    : QXmppIq(type), m_maxAge(86400)
{
}

QString QXmppBobIq::cid() const
{
    return m_cid;
}

void QXmppBobIq::setCid(const QString &cid)
{
    m_cid = cid;
}

QByteArray QXmppBobIq::data() const
{
    return m_data;
}

void QXmppBobIq::setData(const QByteArray &data)
{
    m_data = data;
}

QString QXmppBobIq::mimeType() const
{
    return m_mimeType;
}

void QXmppBobIq::setMimeType(const QString &type)
{
    m_mimeType = type;
}

int QXmppBobIq::maxAge() const
{
    return m_maxAge;
}

void QXmppBobIq::setMaxAge(int maxAge)
{
    m_maxAge = maxAge;
}

bool QXmppBobIq::isBobIq(const QDomElement& element)
{
    QDomElement dataElement = element.firstChildElement("data");
    return dataElement.namespaceURI() == ns_bob;
}

void QXmppBobIq::parseElementFromChild(const QDomElement &element)
{
    QDomElement dataElement = element.firstChildElement("data");
    m_cid = dataElement.attribute("cid");
    m_mimeType = dataElement.attribute("type");
    m_maxAge = dataElement.attribute("max-age", "-1").toInt();
    m_data = QByteArray::fromBase64(dataElement.text().toAscii());
}

void QXmppBobIq::toXmlElementFromChild(QXmlStreamWriter *writer) const
{
    writer->writeStartElement("data");
    writer->writeAttribute("xmlns", ns_bob);
    writer->writeAttribute("cid", m_cid);
    helperToXmlAddAttribute(writer, "type", m_mimeType);
    if (m_maxAge >= 0)
        writer->writeAttribute("max-age", QString::number(m_maxAge));
    if (!m_data.isEmpty())
        writer->writeCharacters(m_data.toBase64());
    writer->writeEndElement();
}

