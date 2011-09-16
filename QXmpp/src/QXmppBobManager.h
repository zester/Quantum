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

#ifndef QXMPPBOBMANAGER_H
#define QXMPPBOBMANAGER_H

#include <QXmppClientExtension.h>
#include <QCache>

/// \brief The QXmppBobManager class provided the functionality to get
/// the local time of an entity as defined by XEP-0231: Bits of Binary
///
/// \ingroup Managers

class QXmppBobIq;

class QXmppBobManager : public QXmppClientExtension
{
    Q_OBJECT

public:
    QXmppBobManager(unsigned int cacheSizeKb = 2048);

    virtual bool handleStanza(const QDomElement &stanza);
    virtual QStringList discoveryFeatures() const;

    QString requestBob(const QString &jid, const QString &cid);

    QByteArray take(const QString &jid, const QString &cid);
    
signals:
    /// \brief This signal is emitted when a bob data received.
    void bobReceived(const QXmppBobIq &bobIq);

private:
    QCache<QPair<QString, QString>, QByteArray> m_bobCache;
};

#endif // QXMPPBOBMANAGER_H
