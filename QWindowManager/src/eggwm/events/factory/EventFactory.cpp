/**
 * @file /src/eggwm/events/factory/EventFactory.cpp
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
#include "EventFactory.h"

// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //

EventFactory* EventFactory::instance = NULL;

EventFactory* EventFactory::getInstance() {
    if(EventFactory::instance == NULL)
        EventFactory::instance = new EventFactory();

    return EventFactory::instance;
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void EventFactory::initialize(XWindowList* windowList) {
    // MapRequest
    this->eventHandlerHash.insert(MapRequest, new MapRequestHandler(
            windowList));

    // ConfigureRequest
    this->eventHandlerHash.insert(ConfigureRequest,new ConfigureRequestHandler(
            windowList));

    //--------------------------------------------------------------------------

    // CreateNotify
    this->eventHandlerHash.insert(CreateNotify, new CreateNotifyHandler(
            windowList));

    // DestroyNotify
    this->eventHandlerHash.insert(DestroyNotify, new DestroyNotifyHandler(
            windowList));

    // UnmapNotify
    this->eventHandlerHash.insert(UnmapNotify, new UnmapNotifyHandler(
            windowList));

    //--------------------------------------------------------------------------

    // ButtonPress
    this->eventHandlerHash.insert(ButtonPress, new ButtonPressHandler(
            windowList));

    //--------------------------------------------------------------------------

    // ClientMessage
    this->eventHandlerHash.insert(ClientMessage, new ClientMessageHandler(
            windowList));
}

EventHandler* EventFactory::getEventHandler(int eventType) const {
    if(this->eventHandlerHash.contains(eventType))
        return this->eventHandlerHash.value(eventType);
    else
        return NULL;
}
