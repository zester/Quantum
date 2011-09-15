/**
 * @file /src/eggwm/standards/EWMHRoot.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Egg Window Manager, usted puede
 * redistribuirlo y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Egg Window Manager project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  EWMHRoot
 * @author José Expósito
 */
#ifndef EWMHROOT_H
#define EWMHROOT_H

#include "src/eggwm/util/Include.h"
#include "src/eggwm/atoms/AtomList.h"
#include "src/eggwm/xwindows/XWindow.h"
#include "src/eggwm/xwindows/XWindowList.h"

class XWindowList;

/**
 * @~spanish
 * El estándar EWMH o NetWM podría ser dividido en dos para facilitar su
 * implementación; esta clase se encarga de gestionar la parte del estándar
 * enfocada a enviar diversos mensajes a la ventana raíz (root window) para
 * indicar diversas propiedades, como el número de escritorios que soporta el
 * gestor de ventanas, la lista de ventanas, etc.
 *
 * @~english
 * TO TRANSLATE
 */
class EWMHRoot {

    private:

        /**
         * @~spanish
         * Instancia de la lista de atoms.
         *
         * @~english
         * TO TRANSLATE
         */
        AtomList* al;

        /**
         * @~spanish
         * Cambia la propiedad indicada en la ventana raíz.
         * @param property Atom de la propiedad a cambiar.
         * @param propertyType Tipo de la propiedad a cambiar: WINDOW,
         *        CARDINAL...
         * @param data Datos a modificar.
         * @param numProps Número de propiedades que se modificarán.
         *
         * @~english
         * TO TRANSLATE
         */
        void changeProperty(Atom property, Atom propertyType,
                const unsigned char* data, int numProps) const;

    public:

        /**
         * @~spanish
         * Constructora.
         *
         * @~english
         * TO TRANSLATE
         */
        EWMHRoot();

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Envía a la ventana raíz los hints que soporta EggWM.
         *
         * @~english
         * TO TRANSLATE
         */
        void sendSupportedHints() const;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Envía a la ventana raíz una lista con las ventanas GESTIONADAS por el
         * WM ordenadas por orden de mapeo.
         * @param mappingList Lista cuya primera ventana es la primera que se
         *        mapeó.
         *
         * @~english
         * TO TRANSLATE
         */
        void sendMappingClientList(const QList<const XWindow*>* mappingList)
                const;

        /**
         * @~spanish
         * Envía a la ventana raíz una lista con las ventanas GESTIONADAS por el
         * WM ordenadas por orden en la pila.
         * @param stackingList Lista cuya primera ventana es la que se encuentra
         *        más abajo.
         *
         * @~english
         * TO TRANSLATE
         */
        void sendStackingClientList(const QList<const XWindow*>* stackingList)
                const;

        /**
         * @~spanish
         * Envía a la ventana raíz el ID de la ventana activa o None si no hay
         * niguna activa.
         * @param id ID de la ventana activa.
         *
         * @~english
         * TO TRANSLATE
         */
        void sendActiveWindow(Window id) const;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Para que los clientes sepan que hay un gestor de ventanas
         * ejecutándose, EggWM envía a la ventana raíz el ID de una ventana
         * creada por él (clase WMCheckWindow).
         * Dicha ventana tiene que tener como _NET_WM_NAME "Egg Window Manager"
         * y _NET_SUPPORTING_WM_CHECK con dicho ID.
         * @param id El Id de la ventana de escritorio.
         *
         * @~english
         * TO TRANSLATE
         */
        void sendSupportingWmCheck(Window id) const;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Envía a la ventana raíz el número de escritorios disponibles.
         * @param num Número de escritorios.
         *
         * @~english
         * TO TRANSLATE
         */
        void sendNumberOfDesktops(long num) const;

        /**
         * @~spanish
         * Envía a la ventana raíz una lista con los nombres de todos los
         * escritorios.
         * @param list La lista.
         *
         * @~english
         * TO TRANSLATE
         */
        void sendDesktopNames(const QString& list) const;

        /**
         * @~spanish
         * Envía a la ventana raíz el tamaño total de todos los escritorios.
         * @param width  Ancho.
         * @param height Alto.
         *
         * @~english
         * TO TRANSLATE
         */
        void sendDesktopGeometry(long width, long height) const;

        /**
         * @~spanish
         * En caso de que se utilicen varios escritorios, este método envía a la
         * ventana raíz la coordenada de la esquina superior izquierda del
         * escritorio que se esté utilizando.
         * Si solo se usa un escritorio se debe usar la coordenada 0,0.
         * @param x Coordenada X de la esquina superior izquierda del viewport.
         * @param y Coordenada Y de la esquina superior izquierda del viewport.
         *
         * @~english
         * TO TRANSLATE
         */
        void sendDesktopViewport(long x, long y) const;

        /**
         * @~spanish
         * Envía a la ventana raíz el tamaño del área "usable" del escritorio.
         * Se calcula teniendo en cuenta el desktop viewport y el tamaño de los
         * posibles paneles.
         * Este tamaño se utiliza, por ejemplo, para colocar correctamente los
         * iconos en el escritorio.
         * @param x Coordenada X de la esquina superior izquierda del área útil.
         * @param y Coordenada Y de la esquina superior izquierda del área útil.
         * @param width  Ancho del área útil.
         * @param height Alto del área útil.
         *
         * @~english
         * TO TRANSLATE
         */
        void sendWorkarea(long x, long y, long width, long height);

        /**
         * @~spanish
         * Envía a la ventana raíz el índice del escritorio actual. El índice
         * debe estar entre 0 y número de escritorios - 1.
         * @param index El índice.
         *
         * @~english
         * TO TRANSLATE
         */
        void sendCurrentDesktop(long index) const;

        /**
         * @~spanish
         * Indica a la ventana raíz si el WM soporta el modo "mostrar el
         * escritorio". En este modo todas las ventanas se ocultan y solo el
         * escritorio es visible.
         * @param support A 1 si se soporta este modo, a 0 si no.
         *
         * @~english
         * TO TRANSLATE
         */
        void sendSupportShowingdesktop(long support) const;


        //----------------------------------------------------------------------
        //----------------------------------------------------------------------


        /**
         * @~spanish
         * Se llama cuando se recibe el mensaje _NET_ACTIVE_WINDOW,
         * desiconificando la ventana si estaba iconificada o colocándola en la
         * cima de la pila y poniendola activa si no.
         * @param wl Lista con todas las ventanas gestionadas o no por EggWM.
         * @param xwindow Ventana a tratar.
         *
         * @~english
         * TO TRANSLATE
         */
        void receivedActiveWindow(XWindowList* wl, XWindow* xwindow) const;

        /**
         * @~spanish
         * Se llama cuando se recibe el mensaje _NET_CLOSE_WINDOW, cerrando la
         * ventana indicada.
         * @param xwindow Ventana a tratar.
         *
         * @~english
         * TO TRANSLATE
         */
        void receivedCloseWindow(XWindow* xwindow) const;

};

#endif // EWMHROOT_H
