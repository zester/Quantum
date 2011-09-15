/**
 * @file /src/eggwm/events/handlers/MapRequestHandler.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Egg Window Manager, usted puede
 * redistribuirlo y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Egg Window Manager project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  MapRequestHandler
 * @author José Expósito
 */
#ifndef MAPREQUESTHANDLER_H
#define MAPREQUESTHANDLER_H

#include "src/eggwm/events/handlers/EventHandler.h"


/**
 * @~spanihs
 * Evento que se llamará cuando una ventana intente mapearse. El WM se encargará
 * de mapearla poniendola un marco si es necesario.
 *
 * @~english
 * Event to be called when a window tries mapped. The WM is responsible for
 * putting it a frame if necessary.
 */
class MapRequestHandler : public EventHandler {

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
        MapRequestHandler(XWindowList* wl);

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

#endif // MAPREQUESTHANDLER_H
