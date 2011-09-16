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

#ifndef QXMPPCAPTCHAIQ_H
#define QXMPPCAPTCHAIQ_H

#include <QXmppIq.h>
#include "QXmppDataForm.h"


class QXmppCaptchaIq : public QXmppIq
{
public:
    QXmppCaptchaIq(Type type = QXmppIq::Get);

    QXmppDataForm dataForm() const;
    void setDataForm(const QXmppDataForm &dataForm);

protected:
    virtual void toXmlElementFromChild(QXmlStreamWriter* writer) const;

private:
    QXmppDataForm m_form;
};

#endif // QXMPPCAPTCHAIQ_H
