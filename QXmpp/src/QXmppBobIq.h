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

#ifndef QXMPPBOBIQ_H
#define QXMPPBOBIQ_H

#include "QXmppIq.h"


class QXmppBobIq : public QXmppIq
{
public:
    QXmppBobIq(Type type = QXmppIq::Get);
    
    QByteArray data() const;
    void setData(const QByteArray &data);

    QString cid() const;
    void setCid(const QString &cid);
    
    QString mimeType() const;
    void setMimeType(const QString &type);
    
    int maxAge() const;
    void setMaxAge(int maxAge);
    
    static bool isBobIq(const QDomElement &element);

protected:
    virtual void parseElementFromChild(const QDomElement& element);
    virtual void toXmlElementFromChild(QXmlStreamWriter* writer) const;
    
private:
    QByteArray m_data;
    QString m_cid;
    QString m_mimeType;
    int m_maxAge;
};

#endif // QXMPPBOBIQ_H
