/**
 * @file /src/eggwm/events/handlers/CreateNotifyHandler.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Egg Window Manager, usted puede
 * redistribuirlo y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Egg Window Manager project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  CreateNotifyHandler
 * @author José Expósito
 */
#include "CreateNotifyHandler.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

CreateNotifyHandler::CreateNotifyHandler(XWindowList* wl)
        : EventHandler(wl) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool CreateNotifyHandler::processEvent(XEvent* event) {
    Window windowID = event->xcreatewindow.window;
    qDebug() << "[+] CreateNotify event 0x" << hex << windowID;

    // Si la ventana no es un marco
    if(!this->wl->existFrame(windowID)) {
        qDebug() << "\tLa ventana es un cliente";
        XWindow* xwindow = new XWindow(windowID);

        qDebug() << "\tAñadiendo el cliente a la lista";
        this->wl->addClient(windowID, xwindow);

        return false;

    // Si la ventana es un marco
    } else {
        // Podemos saber que la ventana es un marco en el momento de crearla
        // porque el marco se añade en MapRequestHandler, guardando su ID en la
        // lista
        qDebug() << "\tLa ventana es un marco";
        return false;
    }
}
