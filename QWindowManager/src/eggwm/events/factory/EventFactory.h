/**
 * @file /src/eggwm/events/factory/EventFactory.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Egg Window Manager, usted puede
 * redistribuirlo y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Egg Window Manager project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  EventFactory
 * @author José Expósito
 */
#ifndef EVENTFACTORY_H
#define EVENTFACTORY_H

#include "src/eggwm/util/Include.h"
#include "src/eggwm/events/handlers/EventHandler.h"
#include "src/eggwm/events/handlers/MapRequestHandler.h"
#include "src/eggwm/events/handlers/ConfigureRequestHandler.h"
#include "src/eggwm/events/handlers/CreateNotifyHandler.h"
#include "src/eggwm/events/handlers/DestroyNotifyHandler.h"
#include "src/eggwm/events/handlers/UnmapNotifyHandler.h"
#include "src/eggwm/events/handlers/ButtonPressHandler.h"
#include "src/eggwm/events/handlers/ClientMessageHandler.h"

/**
 * @~spanish
 * Factoría para obtener los distintos manejadores de eventos.
 *
 * @~english
 * Factory for get the differents event handlers.
 */
class EventFactory {

    private:

        /**
         * @~spanish
         * Tabla hash que asocia a cada evento la clase que lo tratará, siendo
         * event->type la clave y el handler del evento el valor.
         *
         * @~english
         * Hash table that associates each event with the class that will treat
         * it, being event->type the key and the event handler the value.
         */
        QHash<int, EventHandler*> eventHandlerHash;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Única instancia de la clase.
         *
         * @~english
         * Single instance of the class.
         */
        static EventFactory* instance;

        // Ocultamos las constructoras
        EventFactory(){}
        EventFactory(const EventFactory&){}
        const EventFactory& operator = (const EventFactory& ef){return ef;}

    public:

        /**
         * @~spanish
         * Único método para obtener una instancia de la clase.
         * @return La única instancia de la clase.
         * @see EventFactory::initialize().
         *
         * @~english
         * Only method to get an instance of the class.
         * @return The single instance of the class.
         * @see EventFactory::initialize().
         */
        static EventFactory* getInstance();

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Inicializa la factoría de eventos.
         * @param windowList Lista de ventanas que usarán los handlers.
         *
         * @~english
         * Initializes the event factory.
         * @param windowList Window list that will use the event handlers.
         */
        void initialize(XWindowList* windowList);

        /**
         * @~spanish
         * Devuelve el manejador de eventos especificado, NULL si EggWM no trata
         * el tipo de evento especificado.
         * @return Dicho evento o NULL.
         *
         * @~english
         * Returns the specified event handler, NULL if EggWM not treated the
         * event.
         * @return The event handler or NULL.
         */
        EventHandler* getEventHandler(int eventType) const;

};

#endif // EVENTFACTORY_H
