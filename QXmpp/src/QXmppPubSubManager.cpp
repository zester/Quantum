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

#include <QDomElement>

#include "QXmppClient.h"
#include "QXmppPubSubIq.h"
#include "QXmppPubSubManager.h"

class QXmppPubSubNodePrivate
{
public:
    QString jid;
    QString node;
};

QXmppPubSubNode::QXmppPubSubNode(const QString &jid, const QString &node, QObject *parent)
    : QObject(parent), d(new QXmppPubSubNodePrivate)
{
    d->jid = jid;
    d->node = node;
}

QXmppPubSubNode::~QXmppPubSubNode()
{
    delete d;
}

QString QXmppPubSubNode::jid() const
{
    return d->jid;
}

QString QXmppPubSubNode::node() const
{
    return d->node;
}

bool QXmppPubSubManager::handleStanza(const QDomElement &stanza)
{
    if (stanza.tagName() == "iq" && QXmppPubSubIq::isPubSubIq(stanza))
    {
        QXmppPubSubIq iq;
        iq.parse(stanza);

        if (iq.type() == QXmppIq::Result || iq.type() == QXmppIq::Error)
        {
            if (iq.queryType() == QXmppPubSubIq::ItemsQuery)
            {
                emit itemsReceived(iq.from(), iq.queryNode(), iq.items());
            }
            return true;
        }
    }
    return false;
}

bool QXmppPubSubManager::requestItems(const QString &jid, const QString &node)
{
    QXmppPubSubIq iq;
    iq.setTo(jid);
    iq.setType(QXmppIq::Get);
    iq.setQueryType(QXmppPubSubIq::ItemsQuery);
    iq.setQueryNode(node);
    return client()->sendPacket(iq);
}

bool QXmppPubSubManager::setItems(const QString &jid, const QString &node, const QList<QXmppPubSubItem> items)
{
    QXmppPubSubIq iq;
    iq.setTo(jid);
    iq.setType(QXmppIq::Set);
    iq.setQueryType(QXmppPubSubIq::PublishQuery);
    iq.setQueryNode(node);
    iq.setItems(items);
    return client()->sendPacket(iq);
}

