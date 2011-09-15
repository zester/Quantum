/**
 * @file /src/eggwm/standards/EWMHRoot.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Egg Window Manager, usted puede
 * redistribuirlo y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Egg Window Manager project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  EWMHRoot
 * @author José Expósito
 */
#include "EWMHRoot.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

EWMHRoot::EWMHRoot() {
    this->al = AtomList::getInstance();
}


// ************************************************************************** //
// **********                    PRIVATE METHODS                   ********** //
// ************************************************************************** //

void EWMHRoot::changeProperty(Atom property, Atom propertyType,
        const unsigned char* data, int numProps) const {
    XChangeProperty(QX11Info::display(),
            QX11Info::appRootWindow(QX11Info::appScreen()),
            property, propertyType, 32, PropModeReplace, data, numProps);
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void EWMHRoot::sendSupportedHints() const {

    const char* supportedHints[] = {
        // EWMH - Root
        "_NET_SUPPORTED",
        "_NET_CLIENT_LIST",
        "_NET_CLIENT_LIST_STACKING",
        "_NET_ACTIVE_WINDOW",
        "_NET_SUPPORTING_WM_CHECK",
        "_NET_NUMBER_OF_DESKTOPS",
        "_NET_DESKTOP_NAMES",
        "_NET_DESKTOP_GEOMETRY",
        "_NET_DESKTOP_VIEWPORT",
        "_NET_WORKAREA",
        "_NET_CURRENT_DESKTOP",
        "_NET_SHOWING_DESKTOP",
        // "_NET_VIRTUAL_ROOTS",
        // "_NET_DESKTOP_LAYOUT",

        "_NET_CLOSE_WINDOW",
        "_NET_MOVERESIZE_WINDOW",
        "_NET_WM_MOVERESIZE",
        "_NET_RESTACK_WINDOW",
        // "_NET_REQUEST_FRAME_EXTENTS",

        //----------------------------------------------------------------------

        // EWMH - Client
        "_NET_WM_NAME",
        "_NET_WM_VISIBLE_NAME",
        "_NET_WM_ICON_NAME",
        "_NET_WM_VISIBLE_ICON_NAME",
        "_NET_WM_ICON",
        //"_NET_WM_DESKTOP",

        "_NET_WM_WINDOW_TYPE",
        "_NET_WM_WINDOW_TYPE_DESKTOP",
        "_NET_WM_WINDOW_TYPE_DOCK",
        "_NET_WM_WINDOW_TYPE_TOOLBAR",
        "_NET_WM_WINDOW_TYPE_MENU",
        "_NET_WM_WINDOW_TYPE_UTILITY",
        "_NET_WM_WINDOW_TYPE_SPLASH",
        "_NET_WM_WINDOW_TYPE_DIALOG",
        "_NET_WM_WINDOW_TYPE_DROPDOWN_MENU",
        "_NET_WM_WINDOW_TYPE_POPUP_MENU",
        "_NET_WM_WINDOW_TYPE_TOOLTIP",
        "_NET_WM_WINDOW_TYPE_NOTIFICATION",
        "_NET_WM_WINDOW_TYPE_COMBO",
        "_NET_WM_WINDOW_TYPE_DND",
        "_NET_WM_WINDOW_TYPE_NORMAL",

        /*
        "_NET_WM_STATE",
        "_NET_WM_STATE_MODAL",
        "_NET_WM_STATE_STICKY",
        "_NET_WM_STATE_MAXIMIZED_VERT",
        "_NET_WM_STATE_MAXIMIZED_HORZ",
        "_NET_WM_STATE_SHADED",
        "_NET_WM_STATE_SKIP_TASKBAR",
        "_NET_WM_STATE_SKIP_PAGER",
        "_NET_WM_STATE_HIDDEN",
        "_NET_WM_STATE_FULLSCREEN",
        "_NET_WM_STATE_ABOVE",
        "_NET_WM_STATE_BELOW",
        "_NET_WM_STATE_DEMANDS_ATTENTION",

        "_NET_WM_ALLOWED_ACTIONS",
        "_NET_WM_ACTION_MOVE",
        "_NET_WM_ACTION_RESIZE",
        "_NET_WM_ACTION_MINIMIZE",
        "_NET_WM_ACTION_SHADE",
        "_NET_WM_ACTION_STICK",
        "_NET_WM_ACTION_MAXIMIZE_HORZ",
        "_NET_WM_ACTION_MAXIMIZE_VERT",
        "_NET_WM_ACTION_FULLSCREEN",
        "_NET_WM_ACTION_CHANGE_DESKTOP",
        "_NET_WM_ACTION_CLOSE",
        "_NET_WM_ACTION_ABOVE",
        "_NET_WM_ACTION_BELOW",

        "_NET_WM_STRUT",
        "_NET_WM_STRUT_PARTIAL",
        "_NET_WM_ICON_GEOMETRY",
        "_NET_WM_PID",
        "_NET_WM_HANDLED_ICONS",
        "_NET_WM_USER_TIME_WINDOW",
        "_NET_FRAME_EXTENTS",
        */

        "_NET_WM_USER_TIME"
    };
    int numAtoms = sizeof(supportedHints)/sizeof(char*);
    Atom supportedAtoms[numAtoms];

    for(int n=0; n<numAtoms; n++)
        supportedAtoms[n] = al->getAtom(supportedHints[n]);

    this->changeProperty(al->getAtom("_NET_SUPPORTED"), XA_ATOM,
            (const unsigned char*)&supportedAtoms, numAtoms);
}

//------------------------------------------------------------------------------

void EWMHRoot::sendMappingClientList(const QList<const XWindow*>* mappingList)
        const {
    int numWindows = mappingList->size();
    Window array[numWindows];

    for(int n=0; n<numWindows; n++) {
        array[n] = mappingList->at(n)->getClientID();
    }

    this->changeProperty(al->getAtom("_NET_CLIENT_LIST"), XA_WINDOW,
            (const unsigned char*)&array, numWindows);
}

void EWMHRoot::sendStackingClientList(const QList<const XWindow*>* stackingList)
        const {
    int numWindows = stackingList->size();
    Window array[numWindows];

    for(int n=0; n<numWindows; n++) {
        array[n] = stackingList->at(n)->getClientID();
    }

    this->changeProperty(al->getAtom("_NET_CLIENT_LIST_STACKING"), XA_WINDOW,
            (const unsigned char*)&array, numWindows);
}

void EWMHRoot::sendActiveWindow(Window id) const {
    this->changeProperty(al->getAtom("_NET_ACTIVE_WINDOW"), XA_WINDOW,
            (const unsigned char*)&id, 1);
}

//------------------------------------------------------------------------------

void EWMHRoot::sendSupportingWmCheck(Window id) const {
    this->changeProperty(al->getAtom("_NET_SUPPORTING_WM_CHECK"), XA_WINDOW,
            (const unsigned char*)&id, 1);
}

//------------------------------------------------------------------------------

void EWMHRoot::sendNumberOfDesktops(long num) const {
    this->changeProperty(al->getAtom("_NET_NUMBER_OF_DESKTOPS"), XA_CARDINAL,
            (const unsigned char*)&num, 1);
}

void EWMHRoot::sendDesktopNames(const QString& name) const {
    QWidget w;
    w.setWindowTitle(name);
    QByteArray desktopName = w.windowTitle().toUtf8();

    XChangeProperty(QX11Info::display(),
            QX11Info::appRootWindow(QX11Info::appScreen()),
            al->getAtom("_NET_DESKTOP_NAMES"),
            al->getAtom("UTF8_STRING"),
            8, PropModeReplace,
            (const unsigned char*)desktopName.data(),
            desktopName.size());
}

void EWMHRoot::sendDesktopGeometry(long width, long height) const {
    long geometry[2];
    geometry[0] = width;
    geometry[1] = height;

    this->changeProperty(al->getAtom("_NET_DESKTOP_GEOMETRY"), XA_CARDINAL,
            (const unsigned char*)&geometry, 2);
}

void EWMHRoot::sendDesktopViewport(long x, long y) const {
    long viewport[2];
    viewport[0] = x;
    viewport[1] = y;

    this->changeProperty(al->getAtom("_NET_DESKTOP_VIEWPORT"), XA_CARDINAL,
            (const unsigned char*)&viewport, 2);
}

void EWMHRoot::sendWorkarea(long x, long y, long width, long height) {
    long workarea[4];
    workarea[0] = x;
    workarea[1] = y;
    workarea[2] = width;
    workarea[3] = height;

    this->changeProperty(al->getAtom("_NET_WORKAREA"), XA_CARDINAL,
            (const unsigned char*)&workarea, 4);
}

void EWMHRoot::sendCurrentDesktop(long index) const {
    this->changeProperty(al->getAtom("_NET_CURRENT_DESKTOP"), XA_CARDINAL,
            (const unsigned char*)&index, 1);
}

void EWMHRoot::sendSupportShowingdesktop(long support) const {
    this->changeProperty(al->getAtom("_NET_SHOWING_DESKTOP"), XA_CARDINAL,
            (const unsigned char*)&support, 1);
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


void EWMHRoot::receivedActiveWindow(XWindowList* wl, XWindow* xwindow) const {
    if(xwindow->getState() == IconicState) {
        // Si la ventana estaba minimizada la restauramos
        xwindow->setState(NormalState);

        // TODO Si la ventana tiene una ventana modal asociada (vease un
        //      diálogo) no se restaura. Hay que minimizar las ventanas
        //      modales junto con su ventana madre.
    }

    // Modificando la lista del EWMH
    wl->restackManagedWindow(xwindow);

    // Actualizando la ventana activa
    wl->setActiveWindow(xwindow);
}

void EWMHRoot::receivedCloseWindow(XWindow* xwindow) const {
    xwindow->closedFrame();
}







