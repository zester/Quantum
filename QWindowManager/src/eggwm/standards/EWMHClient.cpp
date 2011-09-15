/**
 * @file /src/eggwm/standards/EWMHClient.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Egg Window Manager, usted puede
 * redistribuirlo y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Egg Window Manager project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  EWMHClient
 * @author José Expósito
 */
#include "EWMHClient.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

EWMHClient::EWMHClient(const Window& clientID) {
    this->clientID = clientID;
    this->al       = AtomList::getInstance();
}


// ************************************************************************** //
// **********                    PRIVATE METHODS                   ********** //
// ************************************************************************** //

bool EWMHClient::getProperty(Atom property, Atom propertyType,
        unsigned char** propRet) const {
    unsigned long numItems;
    return this->getProperty(property, propertyType, propRet, &numItems);
}

bool EWMHClient::getProperty(Atom property, Atom propertyType,
        unsigned char** propRet, unsigned long* numItems) const {
    return this->getProperty(property, propertyType, propRet, numItems, 0, 100);
}

bool EWMHClient::getProperty(Atom property, Atom propertyType,
        unsigned char** propRet, unsigned long* numItems, long offset,
        long lenght) const {
    Atom atomRet;
    int size;
    unsigned long bytesAfterReturn;

    int ret = XGetWindowProperty(QX11Info::display(), this->clientID, property,
            offset, lenght, false, propertyType, &atomRet, &size, numItems,
            &bytesAfterReturn, propRet);

    return (ret == Success && *numItems >= 1);
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

QString EWMHClient::getTitle() const {
    unsigned char* propRet;

    if(this->getProperty(al->getAtom("_NET_WM_NAME"),
            al->getAtom("UTF8_STRING"), &propRet)) {
        QString title = QString::fromUtf8((char*) propRet);
        XFree(propRet);
        return title;
    } else
        return "";
}

QString EWMHClient::getVisibleTitle() const {
    unsigned char* propRet;

    if(this->getProperty(al->getAtom("_NET_WM_VISIBLE_NAME"),
            al->getAtom("UTF8_STRING"), &propRet)) {
        QString title = QString::fromUtf8((char*) propRet);
        XFree(propRet);
        return title;
    } else
        return "";
}

//------------------------------------------------------------------------------

Atom EWMHClient::getWindowType() const {
    unsigned char* propRet;

    if(this->getProperty(al->getAtom("_NET_WM_WINDOW_TYPE"), XA_ATOM,
            &propRet)) {
        Atom* types = (Atom*)propRet;
        Atom ret = types[0]; // Solo miramos el primer tipo especificado
        XFree(propRet);
        return ret;
    } else
        return al->getAtom("_NET_WM_WINDOW_TYPE_NORMAL");
}

//------------------------------------------------------------------------------

QPixmap EWMHClient::getIconPixmap() const {
    unsigned char* propRet;
    unsigned long numItems;
    int iconWidth;
    int iconHeight;
    QPixmap icon = NULL;

    // Ancho
    if(this->getProperty(al->getAtom("_NET_WM_ICON"), XA_CARDINAL, &propRet,
            &numItems, 0, 1)) {
        iconWidth = propRet[0];
        XFree(propRet);
    } else
        return NULL;

    // Alto
    if(this->getProperty(al->getAtom("_NET_WM_ICON"), XA_CARDINAL, &propRet,
            &numItems, 1, 1)) {
        iconHeight = propRet[0];
        XFree(propRet);
    } else
        return NULL;

    // Icono
    if(this->getProperty(al->getAtom("_NET_WM_ICON"), XA_CARDINAL, &propRet,
            &numItems, 2, iconWidth*iconHeight)) {
        QImage aux(propRet, iconWidth, iconHeight, QImage::Format_ARGB32);
        icon = QPixmap::fromImage(aux);
        XFree(propRet);
        return icon;
    } else
        return NULL;
}
