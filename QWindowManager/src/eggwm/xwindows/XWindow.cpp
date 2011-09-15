/**
 * @file /src/eggwm/xwindows/XWindow.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Egg Window Manager, usted puede
 * redistribuirlo y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Egg Window Manager project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  XWindow
 * @author José Expósito
 */
#include "XWindow.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

XWindow::XWindow(const Window& clientID) {
    this->client   = new Client(clientID);
    this->frame    = NULL;
    this->clientID = clientID;
    this->frameID  = 0;
    this->state    = WithdrawnState;

    this->client->setBorderWidth(0);
}

XWindow::~XWindow() {
    delete this->client;

    if(this->haveFrame())
        delete this->frame;
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool XWindow::bypassWM() const {
    XWindowAttributes xwa;
    XGetWindowAttributes(QX11Info::display(), this->clientID, &xwa);
    return xwa.override_redirect;
}

//------------------------------------------------------------------------------

void XWindow::addFrame() {
    if(!this->haveFrame() && this->needFrame()) {
        Config* cfg = Config::getInstance();

        // Creamos el marco con la posición y tamaño necesarios
        this->frame = new ClientFrame(cfg->isIconVisible(), true);
        this->setX(this->client->getX());
        this->setY(this->client->getY());
        this->setWidth(this->client->getWidth() + cfg->getLeftBorderWidth()
                + cfg->getRightBorderWidth());
        this->setHeight(this->client->getHeight() + cfg->getTitlebarWidth()
                + cfg->getTopBorderWidth() + cfg->getBottomBorderWidth());

        // Guardamos el ID del frame
        this->frameID = this->frame->winId();

        // Hacemos al marco padre de la ventana a decorar
        XReparentWindow(QX11Info::display(), this->clientID,
                this->frameID,
                cfg->getLeftBorderWidth(),
                cfg->getTitlebarWidth() + cfg->getTopBorderWidth());

        // Como ahora la ventana no es hija de la root window ya no recibimos
        // sus eventos. Hacemos que se sigan recibiendo.
        XSelectInput(QX11Info::display(), this->frameID,
                  ButtonPressMask | ButtonReleaseMask | ButtonMotionMask
                | PointerMotionMask
                | KeyPressMask | KeyReleaseMask | KeymapStateMask
                | EnterWindowMask | LeaveWindowMask | FocusChangeMask
                | ExposureMask | SubstructureRedirectMask
                | StructureNotifyMask | SubstructureNotifyMask
                | PropertyChangeMask);

        // Conectamos signals y slots
        connect(this->frame, SIGNAL(resizedFrame(int, int)),
                this, SLOT(resizedFrame(int, int)));
        connect(this->frame, SIGNAL(minimizedFrame()),
                this, SLOT(minimizedFrame()));
        connect(this->frame, SIGNAL(maximizedFrame()),
                this, SLOT(maximizedFrame()));
        connect(this->frame, SIGNAL(closedFrame()), this, SLOT(closedFrame()));

        // Añadimos el cliente al save-set para que si el WM se cierra
        // inesperadamente no desaparezcan los clientes
        XAddToSaveSet(QX11Info::display(), this->clientID);
    }
}

void XWindow::removeFrame() {
    if(this->haveFrame()) {
        delete this->frame;
        this->frame = NULL;
    }
}

bool XWindow::haveFrame() const {
    return (this->frame != NULL);
}

bool XWindow::needFrame() const {
    AtomList* al = AtomList::getInstance();
    Atom clientType = this->client->getWindowType();
    return !(clientType == al->getAtom("_NET_WM_WINDOW_TYPE_DESKTOP")
          || clientType == al->getAtom("_NET_WM_WINDOW_TYPE_DOCK")
          || clientType == al->getAtom("_NET_WM_WINDOW_TYPE_SPLASH"));
}


// ************************************************************************** //
// **********                      GET/SET/IS                      ********** //
// ************************************************************************** //

void XWindow::setState(int state) {
    // WithdrawnState -> NormalState o IconicState
    if((this->state == WithdrawnState && state == NormalState)
            || (this->state == WithdrawnState && state == IconicState)) {

        // Mapeamos el marco y le añadimos algunas propiedades si corresponde
        if(this->haveFrame()) {
            this->frame->setVisible(true);
            this->frame->setTitle(this->client->getTitle());
            this->frame->setIconPixmap(this->client->getIconPixmap());
        }

        // Mapeamos el cliente
        this->client->setVisible(true);

        // La ponemos en su posición por defecto
        if(!this->client->overridePositionHints()) {
            // TODO Tener en cuenta que los paneles ocupan un tamaño en el
            //      escritorio en el que no se deberían situar ventanas.
            switch (this->client->getInitialPosition()) {
            case NorthWestGravity:
                this->setX(0);
                this->setY(0);
                break;
            case NorthGravity:
                this->setX(QApplication::desktop()->width()/2 - this->getWidth()/2);
                this->setY(0);
                break;
            case NorthEastGravity:
                this->setX(QApplication::desktop()->width() - this->getWidth());
                this->setY(0);
                break;
            case WestGravity:
                this->setX(0);
                this->setY(QApplication::desktop()->height()/2-this->getHeight()/2);
                break;
            case CenterGravity:
                this->setX(QApplication::desktop()->width()/2 - this->getWidth()/2);
                this->setY(QApplication::desktop()->height()/2-this->getHeight()/2);
                break;
            case EastGravity:
                this->setX(QApplication::desktop()->width() - this->getWidth());
                this->setY(QApplication::desktop()->height()/2-this->getHeight()/2);
                break;
            case SouthWestGravity:
                this->setX(0);
                this->setY(QApplication::desktop()->height() - this->getHeight());
                break;
            case SouthGravity:
                this->setX(QApplication::desktop()->width()/2 - this->getWidth()/2);
                this->setY(QApplication::desktop()->height() - this->getHeight());
                break;
            case SouthEastGravity:
                this->setX(QApplication::desktop()->width() - this->getWidth());
                this->setY(QApplication::desktop()->height() - this->getHeight());
                break;
            }
        }

        // Cambiamos la propiedad WM_STATE del cliente
        this->client->changeWmState(NormalState);
        this->state = state;

        // Inicialmente marcamos la ventana como NormalState y si hay que
        // minimizarla a continuación lo hacemos
        if(this->client->getInitialState() == IconicState)
            this->minimizedFrame();

    //--------------------------------------------------------------------------

    // NormalState o IconicState -> WithdrawnState
    } else if((this->state == NormalState && state == WithdrawnState)
            || (this->state == IconicState && state == WithdrawnState)) {
        // Si el cliente tiene marco lo desmapeamos
        if(this->haveFrame())
            this->frame->setVisible(false);

        // Cambiamos la propiedad WM_STATE del cliente
        this->client->changeWmState(state);
        this->state = state;

    //--------------------------------------------------------------------------

    // NormalState -> IconicState
    } else if(this->state == NormalState && state == IconicState) {
        // Desmapeamos la ventana y su marco si tiene
        this->client->setVisible(false);
        if(this->haveFrame())
            this->frame->setVisible(false);

        // Cambiamos la propiedad WM_STATE del cliente
        this->client->changeWmState(IconicState);
        this->state = IconicState;

    //--------------------------------------------------------------------------

    // IconicState -> NormalState
    } else if(this->state == IconicState && state == NormalState) {
        // Mapeamos la ventana y su marco si tiene
        if(this->haveFrame())
            this->frame->setVisible(true);
        this->client->setVisible(true);

        // Cambiamos la propiedad WM_STATE del cliente
        this->client->changeWmState(state);
        this->state = state;
    }
}

int XWindow::getState() const {
    return this->state;
}

//------------------------------------------------------------------------------

Window XWindow::getClientID() const {
    return this->clientID;
}

Window XWindow::getFrameID() const {
    return this->frameID;
}

XID XWindow::getWindowGroup() const {
    return this->client->getWindowGroup();
}

//------------------------------------------------------------------------------

void XWindow::setFocus() const {
    this->client->setFocus();
}

//------------------------------------------------------------------------------

Atom XWindow::getWindowType() const {
    return this->client->getWindowType();
}

bool XWindow::isTopWindow() const {
    AtomList* al = AtomList::getInstance();
    Atom type = this->client->getWindowType();
    return type == al->getAtom("_NET_WM_WINDOW_TYPE_DOCK")
        || type == al->getAtom("_NET_WM_WINDOW_TYPE_SPLASH");
}


bool XWindow::isBottomWindow() const {
    AtomList* al = AtomList::getInstance();
    Atom type = this->client->getWindowType();
    return type == al->getAtom("_NET_WM_WINDOW_TYPE_DESKTOP");
}

//------------------------------------------------------------------------------

void XWindow::setX(int x) {
    this->haveFrame() ? this->frame->setX(x) : this->client->setX(x);
}

void XWindow::setY(int y) {
    this->haveFrame() ? this->frame->setY(y) : this->client->setY(y);
}

void XWindow::setWidth(unsigned int width) {
    if(this->haveFrame()) {
        Config* cfg = Config::getInstance();
        this->client->setWidth(width - cfg->getLeftBorderWidth()
                - cfg->getRightBorderWidth());

        // Hay que redimensionar el frame así por si el cliente no acepta
        // cualquier tamaño
        this->frame->setWidth(this->client->getWidth()
                + cfg->getLeftBorderWidth() + cfg->getRightBorderWidth());
    } else {
        this->client->setWidth(width);
    }
}

void XWindow::setHeight(unsigned int height) {
    if(this->haveFrame()) {
        Config* cfg = Config::getInstance();
        this->client->setHeight(height - cfg->getTitlebarWidth()
                - cfg->getTopBorderWidth() - cfg->getBottomBorderWidth());
        // Hay que redimensionar el frame así por si el cliente no acepta
        // cualquier tamaño
        this->frame->setHeight(this->client->getHeight()
                + cfg->getTitlebarWidth() + cfg->getTopBorderWidth()
                + cfg->getBottomBorderWidth());
    } else {
        this->client->setHeight(height);
    }
}

unsigned int XWindow::getWidth() const {
    return this->haveFrame() ? this->frame->getWidth():this->client->getWidth();
}

unsigned int XWindow::getHeight() const {
    return this->haveFrame()?this->frame->getHeight():this->client->getHeight();
}


// ************************************************************************** //
// **********                     PUBLIC SLOTS                     ********** //
// ************************************************************************** //

bool XWindow::resizedFrame(int width, int height) {
    if(width != 0) {
        int newWidth = this->frame->getWidth() + width;
        int minWidht = this->client->getMinWidth();
        int maxWidth = this->client->getMaxWidth();

        if(newWidth >= minWidht && newWidth <= maxWidth) {
            this->setWidth(newWidth);
            return true;
        } else
            return false;
    }

    if(height != 0) {
        int newHeight = this->frame->getHeight() + height;
        int minHeight = this->client->getMinHeight();
        int maxHeight = this->client->getMaxHeight();

        if(newHeight >= minHeight && newHeight <= maxHeight) {
            this->setHeight(newHeight);
            return true;
        } else
            return false;
    }

    return false;
}

void XWindow::minimizedFrame() {
    this->setState(IconicState);
}

void XWindow::maximizedFrame() {
    // TODO Mirar si hay paneles y de más
    if(this->client->getMaxWidth() >= QApplication::desktop()->width()
            && this->client->getMaxHeight()>=QApplication::desktop()->height()){
        this->setX(0);
        this->setY(0);
        this->setWidth(QApplication::desktop()->width());
        this->setHeight(QApplication::desktop()->height());
    }
}

void XWindow::closedFrame() {
    this->client->killClient();
}
