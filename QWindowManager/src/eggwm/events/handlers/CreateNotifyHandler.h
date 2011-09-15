/**
 * @file /src/eggwm/events/handlers/CreateNotifyHandler.h
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
#ifndef CREATENOTIFYHANDLER_H
#define CREATENOTIFYHANDLER_H

#include "src/eggwm/events/handlers/EventHandler.h"

/**
 * @~spanish
 * Evento que se llamará cada vez que se cree una nueva ventana.
 *
 * @~english
 * Event is called each time you create a new window.
 */
class CreateNotifyHandler : public EventHandler {

    public:

        /**
         * @~spanish
         * Constructora por defecto.
         * @param wl La lista de ventanas.
         *
         * @~english
         * Default constructor.
         * @param wl The window list.
         */
        CreateNotifyHandler(XWindowList* wl);

        /**
         * @~spanish
         * Procesa el evento.
         * @param event El evento a procesar.
         * @return true para evitar que el evento sea tratado con normalidad, es
         *         decir, cuando ya lo tratamos nosotros, false para que el
         *         evento se trate con normalidad.
         *
         * @~english
         * Process the event.
         * @param event The event to be processed.
         * @return true if you want to stop the event from being processed, ie
         *         when we treat ourselves, false for normal event dispatching.
         */
        virtual bool processEvent(XEvent* event);
};

#endif // CREATENOTIFYHANDLER_H
