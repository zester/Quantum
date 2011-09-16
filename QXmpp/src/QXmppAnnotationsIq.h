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

#ifndef QXMPPANNOTATIONSIQ_H
#define QXMPPANNOTATIONSIQ_H

#include "QXmppIq.h"

#include <QDateTime>

/// \brief Represents an IQ containing a list of annotations as defined
/// by XEP-0145.
///
/// \ingroup Stanzas

class QXmppAnnotationsIq : public QXmppIq
{
public:
    class NoteItem
    {
    public:
        NoteItem();
        NoteItem(const QString&, const QString&);

        QString jid() const;
        void setJid(const QString&);

        QString note() const;
        void setNote(const QString&);

        QDateTime cdate() const;
        void setCdate(const QDateTime&);

        QDateTime mdate() const;
        void setMdate(const QDateTime&);
    private:
        QString m_jid;
        QString m_note;
        QDateTime m_cdate;
        QDateTime m_mdate;
    };

    QXmppAnnotationsIq();

    QList<NoteItem> items() const;
    void setItems(const QList<NoteItem>&);

protected:
    /// \cond
    void parseElementFromChild(const QDomElement &element);
    void toXmlElementFromChild(QXmlStreamWriter *writer) const;
    /// \endcond

private:
    QList<NoteItem> m_items;
};

#endif // QXMPPANNOTATIONSIQ_H
