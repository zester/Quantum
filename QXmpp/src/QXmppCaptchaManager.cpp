/*
 * Copyright (C) 2008-2011 The QXmpp developers
 *
 * Author:
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

#include "QXmppCaptchaManager.h"
#include "QXmppDataForm.h"
#include "QXmppConstants.h"
#include "QXmppCaptchaIq.h"
#include "QXmppClient.h"

bool QXmppCaptchaManager::handleStanza(const QDomElement& stanza)
{
    if (stanza.tagName() != "message")
        return false;

    QDomElement captchaStanza = stanza.firstChildElement("captcha");

    if (captchaStanza.isNull() || captchaStanza.namespaceURI() != ns_captcha)
        return false;

    QDomElement dataFormStanza = captchaStanza.firstChildElement("x");
    if (dataFormStanza.isNull())
        return false;

    QXmppDataForm dataForm;
    dataForm.parse(dataFormStanza);

    if (dataForm.isNull())
        return false;

    emit captchaFormReceived(stanza.attribute("from"), dataForm);
    return true;
}

QString QXmppCaptchaManager::sendResponse(const QString& to, const QXmppDataForm& form)
{
    QXmppCaptchaIq request;
    request.setType(QXmppIq::Set);
    request.setTo(to);
    request.setDataForm(form);
    if(client()->sendPacket(request))
        return request.id();
    else
        return QString();
}
