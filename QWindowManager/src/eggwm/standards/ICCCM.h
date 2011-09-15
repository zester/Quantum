/**
 * @file /src/eggwm/standards/ICCCM.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Egg Window Manager, usted puede
 * redistribuirlo y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Egg Window Manager project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  ICCCM
 * @author José Expósito
 */
#ifndef ICCCM_H
#define ICCCM_H

#include "src/eggwm/util/Include.h"
#include "src/eggwm/config/Config.h"

/**
 * @~spanish
 * Clase encargada de implementar los estandares referidos a las propiedades de
 * los clientes definidos por el ICCCM.
 *
 * @~english
 * TO TRANSLATE
 *
 * @~english
 * TO TRANSLATE
 */
class ICCCM {

    private:

        /**
         * @~spanish
         * ID del cliente del cual obtendremos los distintos estandares.
         *
         * @~english
         * TO TRANSLATE
         *
         * @~english
         * TO TRANSLATE
         */
        Window clientID;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * En caso de que el cliente no defina un tamaño mínimo se usará este.
         *
         * @~english
         * TO TRANSLATE
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
         *
         * @~english
         * TO TRANSLATE
         */
        static const unsigned int DEFAULT_MAX_SIZE;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Transforma el XTextProperty indicado en un QString.
         * @param textProperty El XTextProperty.
         * @return El QString.
         *
         * @~english
         * TO TRANSLATE
         *
         * @~english
         * TO TRANSLATE
         */
        QString textPropertyToQString(XTextProperty textProperty) const;

        /**
         * @~spanish
         * Devuelve los la estructura con las preferencias de tamaño iniciales
         * del cliente.
         * @return Dicha estructura.
         *
         * @~english
         * TO TRANSLATE
         *
         * @~english
         * TO TRANSLATE
         */
        XSizeHints getSizeHints() const;

        /**
         * @~spanish
         * Indica si el cliente soporta el protocolo establecido.
         * @param protocol El protocolo.
         * @return Si lo soporta o no.
         *
         * @~english
         * TO TRANSLATE
         *
         * @~english
         * TO TRANSLATE
         */
        bool supportProtocol(const char* protocol) const;

        /**
         * @~spanish
         * Envía el mensaje de protocolo establecido.
         * @param protocol El protocolo.
         *
         * @~english
         * TO TRANSLATE
         *
         * @~english
         * TO TRANSLATE
         */
        void sendProtocol(const char* protocol) const;

    public:

        /**
         * @~spanish
         * Constructora.
         * @param clientID ID del cliente a gestionar.
         *
         * @~english
         * TO TRANSLATE
         *
         * @~english
         * TO TRANSLATE
         */
        ICCCM(const Window& clientID);

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Devuelve el título de la ventana.
         * @return El título.
         *
         * @~english
         * TO TRANSLATE
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
         *
         * @~english
         * TO TRANSLATE
         */
        int getInitialPosition() const;

        /**
         * @~spanish
         * Redondea el ancho indicado al ancho mayor o menor válido más próximo.
         * Por ejemplo xterm no acepta cualquier tamaño, solo acepta múltiplos
         * de el tamño de letra. Si el tamaño de la letra es por ejemplo 5px:
         * roundWidth(7, true) = 10
         * @param width El ancho a redondear
         * @param roundingUp true si se quiere redondear hacía arriba, false
         *        para redondear hacia abajo.
         * @return El ancho válido más próximo al indicado. Si el indicado es
         *        válido se devuelve el mismo.
         *
         * @~english
         * TO TRANSLATE
         *
         * @~english
         * TO TRANSLATE
         */
        int roundWidth(int width, bool roundingUp) const;

        /**
         * @~spanish
         * Redondea el alto indicado al ancho mayor o menor válido más próximo.
         * Por ejemplo xterm no acepta cualquier tamaño, solo acepta múltiplos
         * de el tamño de letra. Si el tamaño de la letra es por ejemplo 5px:
         * roundHeight(7, true) = 10
         * @param height El alto a redondear
         * @param roundingUp true si se quiere redondear hacía arriba, false
         *        para redondear hacia abajo.
         * @return El alto válido más próximo al indicado. Si el indicado es
         *        válido se devuelve el mismo.
         *
         * @~english
         * TO TRANSLATE
         *
         * @~english
         * TO TRANSLATE
         */
        int roundHeight(int height, bool roundingUp) const;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Devuelve el estado inicial del cliente.
         * @return El estado inicial: WithdrawnState, NormalState o IconicState.
         *
         * @~english
         * TO TRANSLATE
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
         *
         * @~english
         * TO TRANSLATE
         */
        XID getWindowGroup() const;

        /**
         * @~spanish
         * Devuelve un QPixmap con el icono del cliente.
         * @return El pixmap, devuelve NULL si no se ha podido obtener.
         *
         * @~english
         * TO TRANSLATE
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
         *
         * @~english
         * TO TRANSLATE
         */
        void changeWmState(int state);

        /**
         * @~spanish
         * Establece los tamaños de icono que acepta el WM.
         *
         * @~english
         * TO TRANSLATE
         *
         * @~english
         * TO TRANSLATE
         */
        void setIconSizes();
};

#endif // ICCCM_H
