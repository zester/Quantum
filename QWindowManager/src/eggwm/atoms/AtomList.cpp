/**
 * @file /src/eggwm/atoms/AtomList.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Egg Window Manager, usted puede
 * redistribuirlo y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Egg Window Manager project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  AtomList
 * @author José Expósito
 */
#include "AtomList.h"

// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //

AtomList* AtomList::instance = NULL;

AtomList* AtomList::getInstance() {
    if(AtomList::instance == NULL)
        AtomList::instance = new AtomList();
    return AtomList::instance;
}


// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

AtomList::AtomList() {
    const char* atomsNames[] = {
        // Tipos de datos
        "WINDOW",
        "UTF8_STRING",
        "CARDINAL",
        "ATOM",

        // ICCCM
        "WM_CHANGE_STATE",

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
        "_NET_VIRTUAL_ROOTS",
        "_NET_DESKTOP_LAYOUT",

        "_NET_CLOSE_WINDOW",
        "_NET_MOVERESIZE_WINDOW",
        "_NET_WM_MOVERESIZE",
        "_NET_RESTACK_WINDOW",
        "_NET_REQUEST_FRAME_EXTENTS",

        //----------------------------------------------------------------------

        // EWMH - Client
        "_NET_WM_NAME",
        "_NET_WM_VISIBLE_NAME",
        "_NET_WM_ICON_NAME",
        "_NET_WM_VISIBLE_ICON_NAME",
        "_NET_WM_DESKTOP",

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
        "_NET_WM_ICON",
        "_NET_WM_PID",
        "_NET_WM_HANDLED_ICONS",
        "_NET_WM_USER_TIME",
        "_NET_WM_USER_TIME_WINDOW",
        "_NET_FRAME_EXTENTS"

    };
    int numAtoms = sizeof(atomsNames)/sizeof(char*);
    Atom atomsReturn[numAtoms];

    XInternAtoms(QX11Info::display(), (char**)atomsNames, numAtoms, false, atomsReturn);

    this->atomHash = new QHash<const char*, Atom>();
    for(int n=0; n<numAtoms; n++)
        this->atomHash->insert(atomsNames[n], atomsReturn[n]);
}


// ************************************************************************** //
// **********                      GET/SET/IS                      ********** //
// ************************************************************************** //

Atom AtomList::getAtom(const char* atomName) {
    return this->atomHash->value(atomName, NULL);
}
