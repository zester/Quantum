/**
 * @file /src/eggwm/EggWM.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Egg Window Manager, usted puede
 * redistribuirlo y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Egg Window Manager project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  EggWM
 * @author José Expósito
 */
#include "EggWM.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

EggWM::EggWM(int argc, char** argv) : QApplication(argc, argv) {
    // Inicializamos los atributos
    this->wmCheckWindow = new WMCheckWindow;
    this->windowList    = new XWindowList;
    this->eventFactory  = EventFactory::getInstance();
    this->eventFactory->initialize(this->windowList);

    // cargamos la configuración
    Config* cfg = Config::getInstance();
    cfg->loadConfig();

    // TODO Añadir a la lista de ventanas las ventanas que ya existan


    // Establecemos diversas propiedades requeridas por el estándar EWMH
    this->sendHints();

    // Establecemos que eventos queremos recibir
    XSelectInput(QX11Info::display(),
            QX11Info::appRootWindow(QX11Info::appScreen()),
              SubstructureRedirectMask /* MapRequest, ConfigureRequest,
                                          CirculateRequest */
            | SubstructureNotifyMask   /* CreateNotify, DestroyNotify,
                                          MapNotify, UnmapNotify,
                                          ReparentNotify, GravityNotify,
                                          ConfigureNotify, CirculateNotify */
            | ButtonPressMask);        /* ButtonPress */
    XFlush(QX11Info::display());
}

EggWM::~EggWM() {
    delete this->wmCheckWindow;
    delete this->windowList;
}


// ************************************************************************** //
// **********                    PRIVATE METHODS                   ********** //
// ************************************************************************** //

void EggWM::sendHints() {
    EWMHRoot ewmhRoot;

    ewmhRoot.sendSupportedHints();
    ewmhRoot.sendActiveWindow(None);
    ewmhRoot.sendSupportingWmCheck(this->wmCheckWindow->winId());

    ewmhRoot.sendNumberOfDesktops(1.0);
    ewmhRoot.sendDesktopNames("Egg Desktop");
    ewmhRoot.sendDesktopGeometry((long)QApplication::desktop()->width(),
            (long)QApplication::desktop()->height());
    ewmhRoot.sendDesktopViewport(0.0, 0.0);
    ewmhRoot.sendWorkarea(0.0, 0.0, (long)QApplication::desktop()->width(),
            (long)QApplication::desktop()->height());
    ewmhRoot.sendCurrentDesktop(0.0);
    ewmhRoot.sendSupportShowingdesktop(0.0);
}


// ************************************************************************** //
// **********                   PROTECTED METHODS                  ********** //
// ************************************************************************** //

bool EggWM::x11EventFilter(XEvent* event) {
    EventHandler* handler = this->eventFactory->getEventHandler(event->type);

    if(handler != NULL)
        return handler->processEvent(event);
    else
        return false;
}
