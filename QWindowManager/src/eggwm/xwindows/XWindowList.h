/**
 * @file /src/eggwm/xwindows/XWindowList.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Egg Window Manager, usted puede
 * redistribuirlo y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Egg Window Manager project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  XWindowList
 * @author José Expósito
 */
#ifndef XWINDOWLIST_H
#define XWINDOWLIST_H

#include "src/eggwm/util/Include.h"
#include "src/eggwm/xwindows/XWindow.h"
#include "src/eggwm/standards/EWMHRoot.h"


/**
 * @~spanish
 * Clase encargada de mantener una lista con todas las ventanas, estén o no
 * gestionadas por EggWM.
 *
 * Todas las ventanas serán accesibles mediante el ID del cliente o el de su
 * marco.
 *
 * Así mismo de entre todas esas ventanas, habrá un subgrupo de ventanas
 * gestionadas por el WM, que son ventanas, con o sin marco, que no bypessean el
 * WM y que tienen que gestionarse según indica el estándar EWMH (mantener su
 * orden dentro de la pila, mantener listas en la ventana raíz de su orden de
 * mapeo o en la pila, etc).
 *
 * @~english
 * TO TRANSLATE
 */
class XWindowList {

    private:

        /**
         * @~spanish
         * Tabla hash que asocia a un ID de ventana cliente con la clase
         * "XWindow" que la representa.
         * Contiene todas lasventanas, ya estén gestionadas o no por el WM.
         *
         * @~english
         * TO TRANSLATE
         */
        QHash<Window, const XWindow*>* clientHash;

        /**
         * @~spanish
         * Tabla hash que asocia el ID de un marco con la clase "XWindow" que la
         * representa.
         * Contiene todas lasventanas, ya estén gestionadas o no por el WM.
         *
         * @~english
         * TO TRANSLATE
         */
        QHash<Window, const XWindow*>* frameHash;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * @~spanish
         * Lista que guarda las ventanas gestioadas por el WM en el orden en el
         * que se van mapeando. Requerido por el EWMH.
         *
         * @~english
         * TO TRANSLATE
         */
        QList<const XWindow*>* mappingList;

        /**
         * @~spanish
         * @~spanish
         * Lista que guarda las ventanas gestioadas por el WM en el orden en el
         * que se encuentran en la pila (la primera es la que se encuentra más
         * abajo). Requerido por el EWMH.
         *
         * @~english
         * TO TRANSLATE
         */
        QList<const XWindow*>* stackingList;

        /**
         * @~spanish
         * @~spanish
         * Ventana activa, debe ser una ventana gestionada por el WM.
         * Requerido por el EWMH.
         *
         * @~english
         *
         * @~english
         * TO TRANSLATE
         */
        const XWindow* activeWindow;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Ordena las ventanas en la pila según se encuentren en la lista de
         * apiladas.
         *
         * @~english
         * TO TRANSLATE
         */
        void restackWindows() const;

    public:

        /**
         * @~spanish
         * Crea una lista de ventanas vacía.
         *
         * @~english
         * TO TRANSLATE
         */
        XWindowList();

        /**
         * @~spanish
         * Destructor.
         *
         * @~english
         * TO TRANSLATE
         */
        ~XWindowList();

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Indica si el cliente identificado por la clave establecida está en la
         * lista.
         * @param clientID ID del cliente a buscar.
         * @return true si está, false en caso contrario.
         *
         * @~english
         * TO TRANSLATE
         */
        bool existClient(Window clientID) const;

        /**
         * @~spanish
         * Añade un cliente identificado por su ID.
         * @param clientID ID de la ventana en cuestión.
         * @param xwindow Clase que encapsula al cliente.
         *
         * @~english
         * TO TRANSLATE
         */
        void addClient(Window clientID, const XWindow* xwindow);

        /**
         * @~spanish
         * Borra un cliente de la lista identificado por su ID.
         * @param clientID ID del cliente a borrar.
         *
         * @~english
         * TO TRANSLATE
         */
        void removeClient(Window clientID);

        /**
         * @~spanish
         * Obtiene la ventana asociada al ID indicado.
         * @param clientID ID del cliente asociado a la ventana.
         * @return La ventana. Si el cliente no exite devuelve NULL.
         *
         * @~english
         * TO TRANSLATE
         */
        XWindow* getXWindowByClientID(Window clientID) const;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Indica si el marco identificado por la clave establecida está en la
         * lista.
         * @param frameID ID del marco a buscar.
         * @return true si está, false en caso contrario.
         *
         * @~english
         * TO TRANSLATE
         */
        bool existFrame(Window frameID) const;

        /**
         * @~spanish
         * Añade un marco identificado por su ID.
         * @param frameID ID del marco a añadir.
         * @param xwindow Clase que encapsula al marco.
         *
         * @~english
         * TO TRANSLATE
         */
        void addFrame(Window frameID, const XWindow* xwindow);

        /**
         * @~spanish
         * Borra un marco de la lista identificado por su ID.
         * @param frameID ID del marco a borrar.
         *
         * @~english
         * TO TRANSLATE
         */
        void removeFrame(Window frameID);

        /**
         * @~spanish
         * Obtiene la ventana asociada al ID indicado.
         * @param frameID ID del frame asociado a la ventana.
         * @return La ventana. Si el frame no exite devuelve NULL.
         *
         * @~english
         * TO TRANSLATE
         */
        XWindow* getXWindowByFrameID(Window frameID) const;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * @~spanish
         * Añade la ventana a la lista de mapeadas y de la de apiladas,
         * actualiza las listas de la ventana raíz y coloca la ventana en la
         * posición de la pila que le corresponde.
         * @param xwindow La ventana a añadir.
         *
         * @~english
         * TO TRANSLATE
         */
        void addToManagedWindows(const XWindow* xwindow);

        /**
         * @~spanish
         * @~spanish
         * Borra la ventana de la lista de mapeadas y de la de apiladas y
         * actualiza las listas de la ventana raíz.
         * @param xwindow La ventana a eliminar.
         *
         * @~english
         * TO TRANSLATE
         */
        void removeFromManagedWindow(const XWindow* xwindow);

        /**
         * @~spanish
         * @~spanish
         * Coloca la ventana en la parte más alta de la pila en la que puede
         * estar (vease debajo de los docks, si es el escritorio en el fondo...)
         * y actualiza las listas que guarda la ventana raíz.
         * @param xwindow La ventana a recolocar.
         *
         * @~english
         * TO TRANSLATE
         */
        void restackManagedWindow(const XWindow* xwindow);

        /**
         * @~spanish
         * @~spanish
         * Establece la ventana activa y le asigna el foco.
         * @param activeWindow La que será la nueva ventana activa, NULL si no
         *        se quiere establecer ninguna.
         *
         * @~english
         * TO TRANSLATE
         */
        void setActiveWindow(const XWindow* activeWindow);

        /**
         * @~spanish
         * @~spanish
         * Indica cual es la ventana que se encuentra en a cima de la pila,
         * siempre que no sea una ventana que siempre deba estar en la cima o en
         * el fondo de la pila o esté minimizada.
         * Por ejemplos, si tenemos un dock, un escritorio y tres ventanas
         * normales devolverá la ventana normal que esté en la parte más alta de
         * la pila.
         * @return La ventana de la cima de la pila o NULL si no hay ninguna.
         *
         * @~english
         * TO TRANSLATE
         */
        const XWindow* getTopWindow() const;

};

#endif // XWINDOWLIST_H
