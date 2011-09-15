/**
 * @file /src/eggwm/xwindows/Client.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Egg Window Manager, usted puede
 * redistribuirlo y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Egg Window Manager project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  Client
 * @author José Expósito
 */
#ifndef CLIENT_H
#define CLIENT_H

#include "src/eggwm/util/Include.h"
#include "src/eggwm/standards/ICCCM.h"
#include "src/eggwm/standards/EWMHClient.h"

/**
 * @~spanish
 * Clase que encapsula una ventana de Xlib (Window) y facilita el trabajo con la
 * misma.
 *
 * @~english
 * TO TRANSLATE
 */
class Client {

    private:

        /**
         * @~spanish
         * ID del cliente que encapsula esta clase.
         *
         * @~english
         * TO TRANSLATE
         */
        Window clientID;

        /**
         * @~spanish
         * Clase que implementa el estándar ICCCM.
         *
         * @~english
         * TO TRANSLATE
         */
        ICCCM* icccm;

        /**
         * @~spanish
         * Clase que implementa el estándar EWMH.
         *
         * @~english
         * TO TRANSLATE
         */
        EWMHClient* ewmh;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * En caso de que el cliente no defina un tamaño mínimo se usará este.
         *
         * @~english
         * TO TRANSLATE
         */
        static const unsigned int DEFAULT_MIN_SIZE;

        /**
         * @~spanish
         * En caso de que el cliente no defina un tamaño máximo se usará este.
         *
         * @~english
         * TO TRANSLATE
         */
        static const unsigned int DEFAULT_MAX_SIZE;

    public:

        /**
         * @~spanish
         * Crea un cliente a partir del ID especificado.
         * @param clientID ID del cliente.
         *
         * @~english
         * TO TRANSLATE
         */
        Client(const Window& clientID);

        /**
         * @~spanish
         * Destructora.
         *
         * @~english
         * TO TRANSLATE
         */
        ~Client();


        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Mapea o desmapea el cliente. Cuando se hace visible recarga todos los
         * hints.
         * @param visible true para mapearlo, false para desmapearlo.
         *
         * @~english
         * TO TRANSLATE
         */
        void setVisible(bool visible);

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Devuelve la coordenada X del cliente.
         * @return La coordenada X respecto a la ventana madre.
         *
         * @~english
         * TO TRANSLATE
         */
        int getX() const;

        /**
         * @~spanish
         * Devuelve la coordenada Y del cliente.
         * @return La coordenada Y respecto a la ventana madre.
         *
         * @~english
         * TO TRANSLATE
         */
        int getY() const;

        /**
         * @~spanish
         * Devuelve el ancho del cliente.
         * @return El ancho del cliente.
         *
         * @~english
         * TO TRANSLATE
         */
        int getWidth() const;

        /**
         * @~spanish
         * Devuelve el alto del cliente.
         * @return El alto del cliente.
         *
         * @~english
         * TO TRANSLATE
         */
        int getHeight() const;

        /**
         * @~spanish
         * Devuelve grosor del borde del cliente.
         * @return El grosor del borde.
         *
         * @~english
         * TO TRANSLATE
         */
        int getBorderWidth() const;

        /**
         * @~spanish
         * Establece la coordenada X del cliente.
         * @param x La coordenada X respecto a la ventana madre.
         *
         * @~english
         * TO TRANSLATE
         */
        void setX(int x);

        /**
         * @~spanish
         * Establece la coordenada Y del cliente.
         * @param y La coordenada Y respecto a la ventana madre.
         *
         * @~english
         * TO TRANSLATE
         */
        void setY(int y);

        /**
         * @~spanish
         * Establece el ancho del cliente.
         * @param width El ancho del cliente.
         *
         * @~english
         * TO TRANSLATE
         */
        void setWidth(int width);

        /**
         * @~spanish
         * Establece el alto del cliente.
         * @param height El alto del cliente.
         *
         * @~english
         * TO TRANSLATE
         */
        void setHeight(int height);

        /**
         * @~spanish
         * Establece el grosor del borde del cliente.
         * @param borderWitdh El grosor del borde.
         *
         * @~english
         * TO TRANSLATE
         */
        void setBorderWidth(int borderWitdh);

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Devuelve el título de la ventana.
         * @return El título.
         *
         * @~english
         * TO TRANSLATE
         */
        QString getTitle() const;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Devuelve el ancho mínimo que puede tener el cliente.
         * @return El ancho mínimo. De no estar especificado retorna
         *         DEFAULT_MIN_SIZE.
         *
         * @~english
         * TO TRANSLATE
         */
        int getMinWidth() const;

        /**
         * @~spanish
         * Devuelve el alto mínimo que puede tener el cliente.
         * @return El alto mínimo. De no estar especificado retorna
         *         DEFAULT_MIN_SIZE.
         *
         * @~english
         * TO TRANSLATE
         */
        int getMinHeight() const;

        /**
         * @~spanish
         * Devuelve el ancho máximo que puede tener el cliente.
         * @return El ancho máximo. De no estar especificado retorna
         *         DEFAULT_MAX_SIZE.
         *
         * @~english
         * TO TRANSLATE
         */
        int getMaxWidth() const;

        /**
         * @~spanish
         * Devuelve el alto máximo que puede tener el cliente.
         * @return El alto máximo. De no estar especificado retorna
         *         DEFAULT_MAX_SIZE.
         *
         * @~english
         * TO TRANSLATE
         */
        int getMaxHeight() const;

        /**
         * @~spanish
         * Indica si debe ignorarse o no la posición inicial de la ventana
         * obtenida en getInitialPosition() o por el contrario debe
         * aplicarse cuando la ventana pase de estado Withdrawn o Normal.
         * @return Si deben ignorarse (true) o no (false).
         *
         * @~english
         * TO TRANSLATE
         */
        bool overridePositionHints() const;

        /**
         * @~spanish
         * Devuelve la posición inicial del cliente.
         * @return La posición, que puede ser: CenterGravity, EastGravity,
         *         NorthEastGravity, NorthGravity, SouthEastGravity,
         *         SouthGravity, SouthWestGravity o WestGravity.
         *         Si no está especificada por defecto es NorthWestGravity.
         * @see overridePositionHints()
         *
         * @~english
         * TO TRANSLATE
         */
        int getInitialPosition() const;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Devuelve el estado inicial del cliente.
         * @return El estado inicial: WithdrawnState, NormalState o IconicState.
         *
         * @~english
         * TO TRANSLATE
         */
        int getInitialState() const;

        /**
         * @~spanish
         * Devuelve el grupo al que pertenece la ventana. De no pertenecer a
         * ninguno devuelve 0.
         * @return El grupo.
         *
         * @~english
         * TO TRANSLATE
         */
        XID getWindowGroup() const;

        /**
         * @~spanish
         * Devuelve un QPixmap con el icono del cliente.
         * @return El pixmap.
         *
         * @~english
         * TO TRANSLATE
         */
        QPixmap getIconPixmap() const;

        /**
         * @~spanish
         * Le asigna el foco al cliente.
         *
         * @~english
         * TO TRANSLATE
         */
        void setFocus() const;

        /**
         * @~spanish
         * Ciera el cliente cuando el usuario pulsa el botón "cerrar" del marco.
         *
         * @~english
         * TO TRANSLATE
         */
        void killClient() const;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Cambia la propiedad WM_STATE del cliente, marcandolo como
         * WithdrawnState, NormalState o IconicState.
         * @param state el nuevo estado del cliente.
         *
         * @~english
         * TO TRANSLATE
         */
        void changeWmState(int state);

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Devuelve el tipo del cliente.
         * @return El tipo de ventana.
         *
         * @~english
         * TO TRANSLATE
         */
        Atom getWindowType() const;

};

#endif // CLIENT_H
