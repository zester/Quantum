/**
 * @file /src/eggwm/standards/WMCheckWindow.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Egg Window Manager, usted puede
 * redistribuirlo y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Egg Window Manager project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  WMCheckWindow
 * @author José Expósito
 */
#include "WMCheckWindow.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

WMCheckWindow::WMCheckWindow() {
    AtomList* al = AtomList::getInstance();

    this->setWindowTitle("Egg Window Manager");

    int id = this->winId();
    XChangeProperty(QX11Info::display(), id,
            al->getAtom("_NET_SUPPORTING_WM_CHECK"),
            al->getAtom("WINDOW"), 32, PropModeReplace,
            (unsigned char*)&id, 1);
}
