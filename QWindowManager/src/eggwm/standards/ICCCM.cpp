/**
 * @file /src/eggwm/standards/ICCCM.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Egg Window Manager, usted puede
 * redistribuirlo y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Egg Window Manager project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  ICCCM
 * @author José Expósito
 */
#include "ICCCM.h"

// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //

const unsigned int ICCCM::DEFAULT_MIN_SIZE = 50;
const unsigned int ICCCM::DEFAULT_MAX_SIZE = 10000;


// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

ICCCM::ICCCM(const Window& clientID) {
    this->clientID = clientID;
}


// ************************************************************************** //
// **********                    PRIVATE METHODS                   ********** //
// ************************************************************************** //

QString ICCCM::textPropertyToQString(XTextProperty textProperty) const {
    char** list;
    int numElems;

    XTextPropertyToStringList(&textProperty, &list, &numElems);

    if(numElems > 0) {
        QString ret = list[0];
        XFreeStringList(list);
        return ret;
    } else
        return "";
}

XSizeHints ICCCM::getSizeHints() const {
    XSizeHints sizeHints;
    long supRet;
    XGetWMNormalHints(QX11Info::display(), this->clientID, &sizeHints, &supRet);
    return sizeHints;
}

bool ICCCM::supportProtocol(const char* protocol) const {
    bool support = false;
    Atom atom = XInternAtom(QX11Info::display(), protocol, false);

    Atom *protList;
    int num;

    if (XGetWMProtocols(QX11Info::display(), this->clientID, &protList, &num)) {
        int n = 0;
        while(n<num && !support) {
            if(protList[n] == atom)
                support = true;
            n++;
        }
        XFree(protList);
    }

    return support;
}

void ICCCM::sendProtocol(const char* protocol) const {
    XEvent event;
    event.xclient.type         = ClientMessage;
    event.xclient.window       = this->clientID;
    event.xclient.message_type = XInternAtom(QX11Info::display(),
            "WM_PROTOCOLS", false);
    event.xclient.format       = 32;
    event.xclient.data.l[0]    = XInternAtom(QX11Info::display(), protocol,
            false);
    event.xclient.data.l[1]    = CurrentTime;
    XSendEvent(QX11Info::display(), this->clientID, false, NULL, &event);
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

QString ICCCM::getTitle() const {
    XTextProperty textProperty;
    XGetWMName(QX11Info::display(), this->clientID, &textProperty);
    return this->textPropertyToQString(textProperty);
}

//------------------------------------------------------------------------------

int ICCCM::getMinWidth() const {
    XSizeHints sizeHints = this->getSizeHints();
    return (sizeHints.flags & PMinSize)
            ? sizeHints.min_width
            : DEFAULT_MIN_SIZE;
}

int ICCCM::getMinHeight() const {
    XSizeHints sizeHints = this->getSizeHints();
    return (sizeHints.flags & PMinSize)
            ? sizeHints.min_height
            : DEFAULT_MIN_SIZE;
}

int ICCCM::getMaxWidth() const {
    XSizeHints sizeHints = this->getSizeHints();
    return (sizeHints.flags & PMaxSize)
            ? sizeHints.max_width
            : DEFAULT_MAX_SIZE;
}

int ICCCM::getMaxHeight() const {
    XSizeHints sizeHints = this->getSizeHints();
    return (sizeHints.flags & PMaxSize)
            ? sizeHints.max_height
            : DEFAULT_MAX_SIZE;
}

bool ICCCM::overridePositionHints() const {
    XSizeHints sizeHints = this->getSizeHints();
    return  (sizeHints.flags & USPosition)
            || (sizeHints.flags & PPosition)
            || !(sizeHints.flags & PWinGravity);
}

int ICCCM::getInitialPosition() const {
    XSizeHints sizeHints = this->getSizeHints();
    return (sizeHints.flags & PWinGravity)
            ? sizeHints.win_gravity
            : NorthWestGravity;
}

int ICCCM::roundWidth(int width, bool roundingUp) const {
    XSizeHints sizeHints = this->getSizeHints();
    if(!(sizeHints.flags & PResizeInc))
        return width;

    int baseSize = (sizeHints.flags & PBaseSize)
            ? sizeHints.base_width
            : this->getMinWidth();
    int aux = (width - baseSize) / sizeHints.width_inc;
    return roundingUp ? baseSize + sizeHints.width_inc * (aux+1)
                      : baseSize + sizeHints.width_inc * aux;
}

int ICCCM::roundHeight(int height, bool roundingUp) const {
    XSizeHints sizeHints = this->getSizeHints();
    if(!(sizeHints.flags & PResizeInc))
        return height;

    int baseSize = (sizeHints.flags & PBaseSize)
            ? sizeHints.base_height
            : this->getMinHeight();
    int aux = (height - baseSize) / sizeHints.height_inc;
    return roundingUp ? baseSize + sizeHints.height_inc * (aux+1)
                      : baseSize + sizeHints.height_inc * aux;
}

//------------------------------------------------------------------------------

int ICCCM::getInitialState() const {
    XWMHints* wmHints = XGetWMHints(QX11Info::display(), this->clientID);

    int ret = (wmHints && (wmHints->flags & StateHint))
              ? wmHints->initial_state
              : NormalState;
    XFree(wmHints);
    return ret;
}

XID ICCCM::getWindowGroup() const {
    XWMHints* wmHints = XGetWMHints(QX11Info::display(), this->clientID);
    int ret = (wmHints && (wmHints->flags & WindowGroupHint))
            ? wmHints->window_group
            : 0;
    XFree(wmHints);
    return ret;
}

QPixmap ICCCM::getIconPixmap() const {
    XWMHints* wmHints = XGetWMHints(QX11Info::display(), this->clientID);
    QPixmap icon = NULL;

    if(wmHints && (wmHints->flags & IconPixmapHint)) {
        icon = QPixmap::fromX11Pixmap(wmHints->icon_pixmap);
        if(wmHints->flags & IconMaskHint)
            icon.setMask(QBitmap(QPixmap::fromX11Pixmap(wmHints->icon_mask)));
    }

    XFree(wmHints);
    return icon;
}

void ICCCM::setFocus() const {
    // Modelos Passive o Locally Active
    XWMHints* wmHints = XGetWMHints(QX11Info::display(), this->clientID);
    bool needWMToGetFocus = (wmHints && (wmHints->flags & InputHint))
            ? wmHints->input
            : false;

    if(needWMToGetFocus) {
        XSetInputFocus(QX11Info::display(), this->clientID, RevertToParent,
                CurrentTime);
    }

    // Modelos Locally Active o Globally Active
    if(this->supportProtocol("WM_TAKE_FOCUS")) {
        this->sendProtocol("WM_TAKE_FOCUS");
    }

    XFree(wmHints);
}

//------------------------------------------------------------------------------

void ICCCM::killClient() const {
    if(this->supportProtocol("WM_DELETE_WINDOW"))
        this->sendProtocol("WM_DELETE_WINDOW");
    else
        XKillClient(QX11Info::display(), this->clientID);
}

//------------------------------------------------------------------------------

void ICCCM::changeWmState(int state) {
    Atom wmStateAtom = XInternAtom(QX11Info::display(), "WM_STATE", false);
    ulong data[2];
    data[0] = (ulong)state;
    data[1] = (ulong)None;
    XChangeProperty(QX11Info::display(), this->clientID, wmStateAtom,
            wmStateAtom, 32, PropModeReplace, (uchar*)data, 2);
}

void ICCCM::setIconSizes() {
    Config* cfg = Config::getInstance();
    XIconSize sizes;
    sizes.max_width  = cfg->getIconSize();
    sizes.max_height = cfg->getIconSize();
    sizes.min_width  = cfg->getIconSize();
    sizes.min_height = cfg->getIconSize();
    sizes.width_inc  = 0;
    sizes.height_inc = 0;
    XSetIconSizes(QX11Info::display(), this->clientID, &sizes, 1);
}
