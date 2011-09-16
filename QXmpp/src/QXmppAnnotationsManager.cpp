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

#include "QXmppAnnotationsManager.h"

#include <QDomElement>

#include "QXmppConstants.h"
#include "QXmppClient.h"

void QXmppAnnotationsManager::setNotes(const QList<QXmppAnnotationsIq::NoteItem> &notes)
{
    QXmppAnnotationsIq iq;
    iq.setType(QXmppIq::Set);
    iq.setItems(notes);
    client()->sendPacket(iq);
}

void QXmppAnnotationsManager::requestNotes()
{
    QXmppAnnotationsIq iq;
    iq.setType(QXmppIq::Get);
    client()->sendPacket(iq);
}

bool QXmppAnnotationsManager::handleStanza(const QDomElement &element)
{
    if (element.tagName() != "iq")
        return false;

    if (element.firstChildElement("query").firstChildElement("storage").namespaceURI() != ns_rosternotes)
        return false;

    QXmppAnnotationsIq iq;
    iq.parse(element);
    emit notesReceived(iq.items());
	return true;
}
