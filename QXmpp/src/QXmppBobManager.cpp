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

#include <QDomDocument>

#include "QXmppBobManager.h"
#include "QXmppConstants.h"
#include "QXmppBobIq.h"
#include "QXmppClient.h"

QXmppBobManager::QXmppBobManager(unsigned int cacheSizeKb)
    : m_bobCache(cacheSizeKb)
{
}

bool QXmppBobManager::handleStanza(const QDomElement &stanza)
{
    QXmppBobIq bobIq;
    bool requestReceived = false;
    
    if (stanza.tagName() == "iq") {
        if (QXmppBobIq::isBobIq(stanza)) {
            requestReceived = true;
            bobIq.parse(stanza);
        }
        else if (QXmppBobIq::isBobIq(stanza.firstChildElement())) {
            bobIq.parse(stanza.firstChildElement());
        }
    }
    else if ((stanza.tagName() == "message" || stanza.tagName() == "presence") 
            && QXmppBobIq::isBobIq(stanza)) {
        bobIq.parse(stanza);
    }
    else {
        return false;
    }
   
    m_bobCache.insert(QPair<QString,QString>(bobIq.cid(), bobIq.from()), new QByteArray(bobIq.data()), bobIq.data().size() / 1024);
    
    if (requestReceived)
        emit bobReceived(bobIq);
    
    return requestReceived;
}

QStringList QXmppBobManager::discoveryFeatures() const
{
    return QStringList() << ns_bob;
}

QString QXmppBobManager::requestBob(const QString &jid, const QString &cid)
{
    QXmppBobIq request;
    request.setType(QXmppIq::Get);
    request.setTo(jid);
    request.setCid(cid);
    if(client()->sendPacket(request))
        return request.id();
    else
        return QString();
}

QByteArray QXmppBobManager::take(const QString& jid, const QString& cid)
{
    QPair<QString, QString> key(cid, jid);
    if (m_bobCache.contains(key))
        return *m_bobCache[key];
    return QByteArray();
}
