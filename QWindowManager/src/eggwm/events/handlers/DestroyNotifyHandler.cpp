/**
 * @file /src/eggwm/events/handlers/DestroyNotifyHandler.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Egg Window Manager, usted puede
 * redistribuirlo y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Egg Window Manager project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  DestroyNotifyHandler
 * @author José Expósito
 */
#include "DestroyNotifyHandler.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

DestroyNotifyHandler::DestroyNotifyHandler(XWindowList* wl)
        : EventHandler(wl) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool DestroyNotifyHandler::processEvent(XEvent* event) {
    Window windowID = event->xdestroywindow.window;
    qDebug() << "[+] DestroyNotify event 0x" << hex << windowID;

    // Si la ventana es un cliente
    if(this->wl->existClient(windowID)) {
        qDebug() << "\tLa ventana es un cliente";
        XWindow* xwindow = this->wl->getXWindowByClientID(windowID);

        qDebug() << "\tEliminando la ventana de la lista";
        wl->removeClient(xwindow->getClientID());

        qDebug() << "\tEliminando la ventana de la lista del EWMH";
        this->wl->removeFromManagedWindow(xwindow);

        // Si la ventana no tiene marco la destruimos tal cual
        if(!xwindow->haveFrame()) {
            qDebug() << "\tLa ventana no tiene marco";

            qDebug() << "\tLiberando memoria";
            delete xwindow;

        // Si la ventana si tiene marco lo destruimos
        } else {
            qDebug() << "\tLa ventana tiene marco, destruyéndolo";
            xwindow->removeFrame();

            // Liberamos memoria y quitamos el marco de la lista cuando se
            // destruya el marco
        }

        return true;

    // Si la ventana es un marco
    } else if(wl->existFrame(windowID)) {
        qDebug() << "\tLa ventana es un marco";
        XWindow* xwindow = this->wl->getXWindowByFrameID(windowID);

        if(event->xdestroywindow.event == event->xdestroywindow.window) {
            qDebug() << "\tevent != window";
            return true;
        }

        qDebug() << "\tEliminando el marco de la lista";
        this->wl->removeFrame(xwindow->getFrameID());

        qDebug() << "\tLiberando memoria";
        delete xwindow;

        return true;

    // Si no es ni un marco ni un cliente
    } else {
        qDebug() << "\tLa ventana no es ni un cliente ni un marco";
        return false;
    }
}
