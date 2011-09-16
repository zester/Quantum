/*
 * Copyright (C) 2008-2011 The QXmpp developers
 *
 * Author:
 *  Jeremy Lainé
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

#ifndef QXMPPPUBSUBMANAGER_H
#define QXMPPPUBSUBMANAGER_H

#include "QXmppClientExtension.h"

class QXmppPubSubItem;
class QXmppPubSubNodePrivate;

class QXmppPubSubNode : public QObject
{
    Q_OBJECT

public:
    QXmppPubSubNode(const QString &jid, const QString &node, QObject *parent);
    ~QXmppPubSubNode();

    QString jid() const;
    QString node() const;

private:
    QXmppPubSubNodePrivate * const d;
};

/// \brief The QXmppPubSubManager class represents an IQ used for the
/// publish-subscribe mechanisms defined by XEP-0060: Publish-Subscribe.
///
/// \ingroup Stanzas

class QXmppPubSubManager : public QXmppClientExtension
{
    Q_OBJECT

public:
    bool requestItems(const QString &jid, const QString &node);
    bool setItems(const QString &jid, const QString &node, const QList<QXmppPubSubItem> items);

    /// \cond
    bool handleStanza(const QDomElement &stanza);
    /// \endcond

signals:
    void itemsReceived(const QString &jid, const QString &node, const QList<QXmppPubSubItem> &items);
};

#endif
