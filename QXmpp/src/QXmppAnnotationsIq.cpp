/*
 * Copyright (C) 2008-2011 The QXmpp developers
 *
 * Author:
 *  Georg Rudoy
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

#include "QXmppAnnotationsIq.h"

#include <QDomElement>

#include "QXmppConstants.h"

QXmppAnnotationsIq::NoteItem::NoteItem()
{
}

QXmppAnnotationsIq::NoteItem::NoteItem(const QString &jid, const QString &note)
    : m_jid(jid), m_note(note)
{
}

QString QXmppAnnotationsIq::NoteItem::jid() const
{
    return m_jid;
}

void QXmppAnnotationsIq::NoteItem::setJid(const QString &jid)
{
    m_jid = jid;
}

QString QXmppAnnotationsIq::NoteItem::note() const
{
    return m_note;
}

void QXmppAnnotationsIq::NoteItem::setNote(const QString &note)
{
    m_note = note;
}

QDateTime QXmppAnnotationsIq::NoteItem::cdate() const
{
    return m_cdate;
}

void QXmppAnnotationsIq::NoteItem::setCdate(const QDateTime &cdate)
{
    m_cdate = cdate;
}

QDateTime QXmppAnnotationsIq::NoteItem::mdate() const
{
    return m_mdate;
}

void QXmppAnnotationsIq::NoteItem::setMdate(const QDateTime &mdate)
{
    m_mdate = mdate;
}

QXmppAnnotationsIq::QXmppAnnotationsIq()
{
}

QList<QXmppAnnotationsIq::NoteItem> QXmppAnnotationsIq::items() const
{
    return m_items;
}

void QXmppAnnotationsIq::setItems(const QList<NoteItem> &items)
{
    m_items = items;
}

void QXmppAnnotationsIq::parseElementFromChild(const QDomElement &element)
{
    QDomElement storage = element.firstChildElement("query").firstChildElement("storage");
    QDomElement note = storage.firstChildElement("note");
    while (!note.isNull())
    {
        NoteItem item(note.attribute("jid"), note.text());

        if (note.hasAttribute("cdate"))
            item.setCdate(QDateTime::fromString(note.attribute("cdate"), Qt::ISODate));
        if (note.hasAttribute("mdate"))
            item.setMdate(QDateTime::fromString(note.attribute("mdate"), Qt::ISODate));

        m_items.append(item);

        note = note.nextSiblingElement("note");
    }
}

void QXmppAnnotationsIq::toXmlElementFromChild(QXmlStreamWriter *writer) const
{
    writer->writeStartElement("query");
    writer->writeAttribute("xmlns", ns_private);
    writer->writeStartElement("storage");
    writer->writeAttribute("xmlns", ns_rosternotes);

    foreach (const NoteItem &item, m_items)
    {
        writer->writeStartElement("note");
        writer->writeAttribute("jid", item.jid());
        if (item.cdate().isValid())
            writer->writeAttribute("cdate", item.cdate().toString(Qt::ISODate));
        if (item.mdate().isValid())
            writer->writeAttribute("mdate", item.mdate().toString(Qt::ISODate));
        writer->writeCharacters(item.note());
        writer->writeEndElement();
    }

    writer->writeEndElement();
    writer->writeEndElement();
}
