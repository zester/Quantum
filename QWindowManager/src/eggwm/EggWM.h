/**
 * @file /src/eggwm/EggWM.h
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
#ifndef EGGWM_H
#define EGGWM_H

#include "src/eggwm/util/Include.h"
#include "src/eggwm/standards/EWMHRoot.h"
//#include "src/eggwm/xwindows/XWindowList.h"
#include "src/eggwm/standards/WMCheckWindow.h"
#include "src/eggwm/events/factory/EventFactory.h"


/**
 * @~spanish
 * Corazón del gestor de ventanas. Se encarga de procesar los distintos eventos
 * con ayuda de sus correspondientes handlers.
 *
 * @~english
 * Heart of the window manager. Is responsible for process the various events
 * using their associated handlers.
 */
class EggWM : public QApplication {

    private:

        /**
         * @~spanish
         * Véntana para que los clientes sepan que hay un WM ejecutándose.
         *
         * @~english
         * Window used to indicate to the clients that a WM is running.
         */
        WMCheckWindow* wmCheckWindow;

        /**
         * @~spanish
         * Lista con las ventanas gestionadas por el WM.
         *
         * @~english
         * List of windows managed by the WM.
         */
        XWindowList* windowList;

        /**
         * @~spanish
         * Factoría de eventos.
         *
         * @~english
         * Event factory.
         */
        EventFactory* eventFactory;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Envía diversos hints requeridos por el estándar EWMH a la ventana
         * raíz.
         *
         * @~english
         * Send various hints required by the EWMH standard to the root window.
         */
        void sendHints();

        /**
         * @~spanish
         * Asocia cada tipo de evento a su correspondiente handler. Es decir,
         * inicializa eventHandlerHash.
         *
         * @~english
         * Associate each event type with his handler. That is, initialized
         * eventHandlerHash.
         */
        void attachEventHandler();

    protected:

        /**
         * @~spanish
         * Reimplementa el método QApplication::x11EventFilter. En este método
         * se recibirán todos los eventos que deberá gestionar el WM (previa
         * llamada a XSelectInput en el constructor) y se gestionarán como
         * corresponda, sirviendose de los distintos "handlers" de eventos.
         * @param event El evento que se ha producido.
         * @return true para evitar que el evento sea tratado con normalidad, es
         *         decir, cuando ya lo tratamos nosotros, false para que el
         *         evento se trate connormalidad.
         *
         * @~english
         * Reimplement the method QApplication::x11EventFilter. In this method
         * recives all events that will be managed by the WM (previously calling
         * XSelectInput function in the constructor) and manage it as appropiate
         * using the correct event handler.
         * @param event The event that occurred.
         * @return true if you want to stop the event from being processed, ie
         *         when we treat ourselves, false for normal event dispatching.
         */
        virtual bool x11EventFilter(XEvent* event);

    public:

        /**
         * @~spanish
         * Constructor.
         * @param argc Número de argumentos recibidos por consola.
         * @param argv Lista de argumentos.
         *
         * @~english
         * Constructor.
         * @param argc Number of arguments received by console.
         * @param argv Argument list.
         */
        EggWM(int argc, char** argv);

        /**
         * @~spanish
         * Destructor.
         *
         * @~english
         * Destructor.
         */
        virtual ~EggWM();
};

#endif // EGGWM_H
