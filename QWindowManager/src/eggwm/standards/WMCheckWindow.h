/**
 * @file /src/eggwm/standards/WMCheckWindow.h
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
#ifndef WMCHECKWINDOW_H
#define WMCHECKWINDOW_H

#include "src/eggwm/util/Include.h"
#include "src/eggwm/atoms/AtomList.h"

/**
 * @~spanish
 * Ventana que se usa para implementar el hint _NET_SUPPORTING_WM_CHECK.
 * La propiedad _NET_SUPPORTING_WM_CHECK debe llevar el valor de winId() y la
 * propiedad _NET_WM_NAME el valor "Egg Window Manager".
 *
 * @~english
 * Window used to implement the  _NET_SUPPORTING_WM_CHECK hint.
 * The _NET_SUPPORTING_WM_CHECK must be set to winId() and _NET_WM_NAME must be
 * set to "Egg window Manager".
 */
class WMCheckWindow : public QWidget {

    public:

        /**
         * @~spanish
         * Crea la ventana.
         *
         * @~english
         * Create the window.
         */
        WMCheckWindow();
};

#endif // WMCHECKWINDOW_H
