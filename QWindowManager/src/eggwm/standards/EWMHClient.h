/**
 * @file /src/eggwm/standards/EWMHClient.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Egg Window Manager, usted puede
 * redistribuirlo y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Egg Window Manager project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  EWMHClient
 * @author José Expósito
 */
#ifndef EWMHCLIENT_H
#define EWMHCLIENT_H

#include "src/eggwm/util/Include.h"
#include "src/eggwm/atoms/AtomList.h"


/**
 * @~spanish
 * El estándar EWMH o NetWM podría ser dividido en dos para facilitar su
 * implementación; esta clase se encarga de gestionar la parte del estándar
 * enfocada a obtener diversos datos de los clientes, como el nombre, el icono,
 * el tipo de ventana, etc.
 *
 * @~english
 * The NetWM or  EWMH standard could be divided into two to facilitate its
 * implementation; this class is responsible for managing the standard focused
 * on obtaining various customer data such as name, icon, window type, etc.
 */
class EWMHClient {

    private:

        /**
         * @~spanish
         * Instancia de la lista de atoms.
         *
         * @~english
         * Instance of the atom list.
         */
        AtomList* al;

        /**
         * @~spanish
         * ID del cliente a gestionar.
         *
         * @~english
         * ID of the client to be manage.
         */
        Window clientID;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Devuelve la propiedad indicada del cliente.
         * @param property Propiedad a obtener.
         * @param propertyType Tipo de la propiedad a obtener.
         * @param propRet Propiedad del cliente, hacer caso a este valor SOLO si
         *        se devuelve true.
         * @return Si se ha podido obtener o no la propiedad. IMPORTANTE: si se
         *        devuelve true hacer un XFree() sobre la propiedad para liberar
         *        memoria.
         *
         * @~english
         * Returns the indicated property of the client.
         * @param property Property to get.
         * @param propertyType The type of the property to get.
         * @param propRet Client property, paying attention to this value ONLY
         *        if the method returns true.
         * @return If it has been able to obtain property or not.
         *        IMPORTANT: If returns true make XFree() to free memory.
         */
        bool getProperty(Atom property, Atom propertyType,
                unsigned char** propRet) const;

        /**
         * @~spanish
         * Devuelve la propiedad indicada del cliente.
         * @param property Propiedad a obtener.
         * @param propertyType Tipo de la propiedad a obtener.
         * @param propRet Propiedad del cliente, hacer caso a este valor SOLO si
         *        se devuelve true.
         * @param numItems número de elementos devueltos en caso de que la
         *        propiedad a devolver sea una lista.
         * @return Si se ha podido obtener o no la propiedad. IMPORTANTE: si se
         *        devuelve true hacer un XFree() sobre la propiedad para liberar
         *        memoria.
         *
         * @~english
         * Returns the indicated property of the client.
         * @param property Property to get.
         * @param propertyType The type of the property to get.
         * @param propRet Client property, paying attention to this value ONLY
         *        if the method returns true.
         * @param numItems Number of items returned if the property is returning
         *        a list.
         * @return If it has been able to obtain property or not.
         *        IMPORTANT: If returns true make XFree() to free memory.
         */
        bool getProperty(Atom property, Atom propertyType,
                unsigned char** propRet, unsigned long* numItems) const;

        /**
         * @~spanish
         * Devuelve la propiedad indicada del cliente.
         * @param property Propiedad a obtener.
         * @param propertyType Tipo de la propiedad a obtener.
         * @param propRet Propiedad del cliente, hacer caso a este valor SOLO si
         *        se devuelve true.
         * @param numItems Número de elementos devueltos en caso de que la
         *        propiedad a devolver sea una lista.
         * @param offset Punto desde el que empezar a leer la propiedad.
         * @param lenght Tamaño de los datos a leer.
         * @return Si se ha podido obtener o no la propiedad. IMPORTANTE: si se
         *        devuelve true hacer un XFree() sobre la propiedad para liberar
         *        memoria.
         *
         * @~english
         * Returns the indicated property of the client.
         * @param property Property to get.
         * @param propertyType The type of the property to get.
         * @param propRet Client property, paying attention to this value ONLY
         *        if the method returns true.
         * @param numItems Number of items returned if the property is returning
         *        a list.
         * @param offset Point from which to start reading the property.
         * @param lenght Data size to read.
         * @return If it has been able to obtain property or not.
         *        IMPORTANT: If returns true make XFree() to free memory.
         */
        bool getProperty(Atom property, Atom propertyType,
                unsigned char** propRet, unsigned long* numItems, long offset,
                long lenght) const;
    public:

        /**
         * @~spanish
         * Constructora.
         * @param clientID ID del cliente a gestionar.
         *
         * @~english
         * Constructor.
         * @param clientID ID of the client to be managed.
         */
        EWMHClient(const Window& clientID);

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Devuelve el título de la ventana, si está establecido se usará este
         * título en vez de WM_NAME.
         * @return El título, si no está especificado devuelve "".
         *
         * @~english
         * Returns the window title,  if defined will use this title instead of
         * WM_NAME.
         * @return The title, if not specified return "".
         */
        QString getTitle() const;

        /**
         * @~spanish
         * Devuelve el título visible de la ventana, si está establecido se
         * usará en vez de _NET_WM_NAME y WM_NAME.
         * @return El título, si no está especificado devuelve "".
         *
         * @~english
         * Returns the visible window title, if defined will use this title
         * instead of _NET_WM_NAME and WM_NAME.
         */
        QString getVisibleTitle() const;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Devuelve el tipo del cliente.
         * @return El tipo de ventana.
         *
         * @~english
         * Returns the window type.
         * @return The window type.
         */
        Atom getWindowType() const;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Devuelve un QPixmap con el icono del cliente.
         * @return El pixmap, devuelve NULL si no se ha podido obtener.
         *
         * @~english
         * Returns a QPixmap with the window icon.
         * @return The pixmap, returns NULL if it has not been obtained.
         */
        QPixmap getIconPixmap() const;

};

#endif // EWMHCLIENT_H
