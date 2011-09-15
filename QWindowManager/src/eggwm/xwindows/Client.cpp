/**
 * @file /src/eggwm/xwindows/Client.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Egg Window Manager, usted puede
 * redistribuirlo y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Egg Window Manager project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  Client
 * @author José Expósito
 */
#include "Client.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

Client::Client(const Window& clientID) {
    this->clientID = clientID;    
    this->icccm    = new ICCCM(clientID);
    this->ewmh     = new EWMHClient(clientID);

    this->icccm->setIconSizes();
}

Client::~Client() {
    delete this->icccm;
    delete this->ewmh;
}


// ************************************************************************** //
// **********                      GET/SET/IS                      ********** //
// ************************************************************************** //

void Client::setVisible(bool visible) {
    if(visible)
        XMapWindow(QX11Info::display(), this->clientID);
    else
        XUnmapWindow(QX11Info::display(), this->clientID);
}

//------------------------------------------------------------------------------

int Client::getX() const {
    XWindowAttributes xwa;
    XGetWindowAttributes(QX11Info::display(), this->clientID, &xwa);
    return xwa.x;
}

int Client::getY() const {
    XWindowAttributes xwa;
    XGetWindowAttributes(QX11Info::display(), this->clientID, &xwa);
    return xwa.y;
}

int Client::getWidth() const {
    XWindowAttributes xwa;
    XGetWindowAttributes(QX11Info::display(), this->clientID, &xwa);
    return xwa.width;
}

int Client::getHeight() const {
    XWindowAttributes xwa;
    XGetWindowAttributes(QX11Info::display(), this->clientID, &xwa);
    return xwa.height;
}

int Client::getBorderWidth() const {
    XWindowAttributes xwa;
    XGetWindowAttributes(QX11Info::display(), this->clientID, &xwa);
    return xwa.border_width;
}

void Client::setX(int x) {
    XWindowChanges xwc;
    xwc.x = x;
    XConfigureWindow(QX11Info::display(), this->clientID, CWX, &xwc);
}

void Client::setY(int y) {
    XWindowChanges xwc;
    xwc.y = y;
    XConfigureWindow(QX11Info::display(), this->clientID, CWY, &xwc);
}

void Client::setWidth(int width) {
    int newWidth = this->icccm->roundWidth(width, (this->getWidth()>width));
    XResizeWindow(QX11Info::display(), this->clientID, newWidth,
            this->getHeight());
}

void Client::setHeight(int height) {
    int newHeight = this->icccm->roundHeight(height,(this->getHeight()>height));
    XResizeWindow(QX11Info::display(), this->clientID, this->getWidth(),
            newHeight);
}

void Client::setBorderWidth(int borderWitdh) {
    XSetWindowBorderWidth(QX11Info::display(), this->clientID, borderWitdh);
}

//------------------------------------------------------------------------------

QString Client::getTitle() const {
    if(this->ewmh->getVisibleTitle() != "")
        return this->ewmh->getVisibleTitle();
    else if(this->ewmh->getTitle() != "")
        return this->ewmh->getTitle();
    else {
        return this->icccm->getTitle();
    }
}

//------------------------------------------------------------------------------

int Client::getMinWidth() const {
    return this->icccm->getMinWidth();
}

int Client::getMinHeight() const {
    return this->icccm->getMinHeight();
}

int Client::getMaxWidth() const {
    return this->icccm->getMaxWidth();
}

int Client::getMaxHeight() const {
    return this->icccm->getMaxHeight();
}

bool Client::overridePositionHints() const {
    return this->icccm->overridePositionHints();
}

int Client::getInitialPosition() const {
    return this->icccm->getInitialPosition();
}

//------------------------------------------------------------------------------

int Client::getInitialState() const {
    return this->icccm->getInitialState();
}

XID Client::getWindowGroup() const {
    return this->icccm->getWindowGroup();
}

QPixmap Client::getIconPixmap() const {
    if(!this->ewmh->getIconPixmap().isNull())
        return this->ewmh->getIconPixmap();
    else
        return this->icccm->getIconPixmap();
}

void Client::setFocus() const {
    this->icccm->setFocus();
}

//------------------------------------------------------------------------------

void Client::killClient() const {
    this->icccm->killClient();
}

//------------------------------------------------------------------------------

void Client::changeWmState(int state) {
    this->icccm->changeWmState(state);
}

//------------------------------------------------------------------------------

Atom Client::getWindowType() const {
    return this->ewmh->getWindowType();
}
