/**
 * @file /src/eggwm/xwindows/ClientFrame.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Egg Window Manager, usted puede
 * redistribuirlo y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Egg Window Manager project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  ClientFrame
 * @author José Expósito
 */
#ifndef CLIENTFRAME_H
#define CLIENTFRAME_H

#include "src/eggwm/util/Include.h"
#include "src/eggwm/config/Config.h"


/**
 * @~spanish
 * Marco o frame usado para decorar, mostrar información y gestionar fácilmente
 * los distintos clientes.
 *
 * @~english
 * TO TRANSLATE
 */
class ClientFrame : public QWidget {

    Q_OBJECT

    private:

        /**
         * @~spanish
         * Posición de la barra de título en la que se "clika" para desplazar la
         * ventana.
         *
         * @~english
         * TO TRANSLATE
         */
        QPoint clickPosition;

        /**
         * @~spanish
         * Máscara de bits que indica, al desplazarse o redimensionarse la
         * ventana la acción que se está llevando a cabo. Se utiliza para poder
         * mover o redimensionar la ventana en el evento mouseMoveEvent() hasta
         * que se genere el evento mouseReleaseEvent().
         *
         * @~english
         * TO TRANSLATE
         */
        int mouseMask;

        /**
         * @~spanish
         * Bit de la mouseMask que indica que se está desplazando la ventana.
         *
         * @~english
         * TO TRANSLATE
         */
        static const int MOVE;

        /**
         * @~spanish
         * Bit de la mouseMask que indica que se estira por el borde superior.
         *
         * @~english
         * TO TRANSLATE
         */
        static const int TOP_BORDER;

        /**
         * @~spanish
         * Bit de la mouseMask que indica que se estira por el borde inferior.
         *
         * @~english
         * TO TRANSLATE
         */
        static const int BOTTOM_BORDER;

        /**
         * @~spanish
         * Bit de la mouseMask que indica que se estira por el borde izquierdo.
         *
         * @~english
         * TO TRANSLATE
         */
        static const int LEFT_BORDER;

        /**
         * @~spanish
         * Bit de la mouseMask que indica que se estira por el borde derecho.
         *
         * @~english
         * TO TRANSLATE
         */
        static const int RIGHT_BORDER;

        //----------------------------------------------------------------------

        // Label con la imagen de fondo de la barra de título.
        QLabel* titlebar;

        // Label con el título de la ventana.
        QLabel* title;

        // Borde superior de la ventana.
        QLabel* topBorder;
        QLabel* topLeftBorder;
        QLabel* topRightBorder;

        // Borde inferior de la ventana.
        QLabel* bottomBorder;
        QLabel* bottomLeftBorder;
        QLabel* bottomRightBorder;

        // Borde izquierdo de la ventana.
        QLabel* leftBorder;
        QLabel* leftTopBorder;
        QLabel* leftBottomBorder;

        // Borde derecho de la ventana.
        QLabel* rightBorder;
        QLabel* rightTopBorder;
        QLabel* rightBottomBorder;

        // Botón "minimizar".
        QPushButton* minimizeButton;

        // Botón "maximizar".
        QPushButton* maximizeButton;

        // Botón "cerrar".
        QPushButton* exitButton;

        // Label con el icono de la ventana.
        QLabel* icon;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Establece la alineación vertical de los distintos elementos de la
         * barra de título.
         * @param widget Elemento a posicionar.
         * @param aling  El alineamiento.
         *
         * @~english
         * TO TRANSLATE
         */
        void setVerticalAling(QWidget* widget, Config::Aling aling);

        /**
         * @~spanish
         * Coloca los adornos/botones del frame en su lugar. Para ello se sirve
         * de las funciones auxiliares placeInHash() y placeItemsInTitlebar().
         *
         * @~english
         * TO TRANSLATE
         */
        void reorganizeFrame();

        /**
         * @~spanish
         * Coloca el elemento indicado en el QHash correcto según se indique.
         * @param pair   Posición del elemento dentro de la barra de título.
         * @param widget Elemento a introducir en el QHash correspondiente.
         * @param left   QHash con los elementos del lado izquierdo de la barra
         *               de título, la clave es ip.index.
         * @param center QHash con los elementos del lado izquierdo de la barra
         *               título, la clave es ip.index.
         * @param right  QHash con los elementos del lado izquierdo de la barra
         *               de título, la clave es ip.index.
         *
         * @~english
         * TO TRANSLATE
         */
        void placeInHash(const QPair<Config::Aling, int>& pair, QWidget* widget,
                QHash<int, QWidget*>* left,
                QHash<int, QWidget*>* center,
                QHash<int, QWidget*>* right) const;

        /**
         * @~spanish
         * Coloca los elementos contenidos en el QHash indicado en orden detro
         * de la barra de título. La clave del QHash indica que elemento va
         * antes.
         * @param left   Elementos de la parte izquierda de la barra de título.
         * @param center Elementos de la parte central de la barra de título.
         * @param right  Elementos de la parte derecha de la barra de título.
         *
         * @~english
         * TO TRANSLATE
         */
        void placeItemsInTitlebar(QHash<int, QWidget*>* left,
                QHash<int, QWidget*>* center, QHash<int, QWidget*>* right);

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Indica si la posición indicada está dentro de los márgenes de un
         * QLabel. Se utiliza para saber sobre que botón o borde se hace click.
         * @param clickPosition Posición en la que se ha hecho click.
         * @param label Label sobre el que se quiere saber si se ha hecho click.
         * @return true si se ha hecho click sobre el label indicado, false en
         *         caso contrario.
         *
         * @~english
         * TO TRANSLATE
         */
        bool isClicked(QPoint clickPosition, const QLabel* label) const;

    protected:

        /**
         * @~spanish
         * Evento que se lanza al hacer click sobre el marco.
         * @param event Evento producido.
         *
         * @~english
         * TO TRANSLATE
         */
        void mousePressEvent(QMouseEvent* event);

        /**
         * @~spanish
         * Evento que se lanza al clickar la ventana y mover el ratón. Por
         * ejemplo cuando se desplaza o se redimensiona la ventana.
         * @param event Evento producido.
         *
         * @~english
         * TO TRANSLATE
         */
        void mouseMoveEvent(QMouseEvent* event);

        /**
         * @~spanish
         * Evento que se lanzará al soltar el botón del ratón.
         * @param event Evento producido.
         *
         * @~english
         * TO TRANSLATE
         */
        void mouseReleaseEvent(QMouseEvent* event);

    public:

        /**
         * @~spanish
         * Crea un marco con las propiedades especificadas.
         * @param showIcon      Si el icono es visible o no.
         * @param showMaxButton Si el botón maximizar es visible o no.
         * @param parent        Ventana padre.
         *
         * @~english
         * TO TRANSLATE
         */
        ClientFrame(bool showIcon, bool showMaxButton, QWidget* parent = 0);

        /**
         * @~spanish
         * Destructor.
         *
         * @~english
         * TO TRANSLATE
         */
        virtual ~ClientFrame();

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Sobreescribimos el método setVisible() para reorganizar el marco
         * al hacerlo visible.
         * @param visible Si se hace visible o invisible.
         *
         * @~english
         * TO TRANSLATE
         */
        void setVisible(bool visible);

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Establece la coordenada X del marco.
         * @param x La coordenada X respecto a la ventana madre.
         *
         * @~english
         * TO TRANSLATE
         */
        void setX(int x);

        /**
         * @~spanish
         * Establece la coordenada Y del marco.
         * @param y La coordenada Y respecto a la ventana madre.
         *
         * @~english
         * TO TRANSLATE
         */
        void setY(int y);

        /**
         * @~spanish
         * Establece el ancho del marco.
         * @param width El ancho del marco.
         *
         * @~english
         * TO TRANSLATE
         */
        void setWidth(unsigned int width);

        /**
         * @~spanish
         * Establece el alto del marco.
         * @param height El alto del marco.
         *
         * @~english
         * TO TRANSLATE
         */
        void setHeight(unsigned int height);

        /**
         * @~spanish
         * Devuelve el ancho del marco.
         * @return El ancho del marco.
         *
         * @~english
         * TO TRANSLATE
         */
        unsigned int getWidth() const;

        /**
         * @~spanish
         * Devuelve el alto del marco.
         * @return El alto del marco.
         *
         * @~english
         * TO TRANSLATE
         */
        unsigned int getHeight() const;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Muestra en el marco el título indicado para ayudar al usuario a
         * identificar las ventanas.
         * @param title El título.
         *
         * @~english
         * TO TRANSLATE
         */
        void setTitle(const QString& title);

        /**
         * @~spanish
         * Establece el pixmap que se usará como icono.
         * @param pixmap El pixmap a utilizar.
         *
         * @~english
         * TO TRANSLATE
         */
        void setIconPixmap(const QPixmap& pixmap);

    signals:

        /**
         * @~spanish
         * Señal que se lanza al redimensionar el marco al ampliarlo estirandolo
         * por los bordes. La deberá recoger la XWindow que contiene este marco
         * para redimensionar el cliente si corresponde (respetando el tamaño
         * mínimo, etc).
         * @param width  Ancho a ampliar o disminuir.
         * @param height Alto a ampliar o disminuir.
         * @return true si se ha podido redimensionar la ventana, false si no.
         *
         * @~english
         * TO TRANSLATE
         */
        bool resizedFrame(int width, int height);

        /**
         * @~spanish
         * Señal que se lanza cuando el usuario hace click en el botón de
         * minimizar.
         *
         * @~english
         * TO TRANSLATE
         */
        void minimizedFrame();

        /**
         * @~spanish
         * Señal que se lanza cuando el usuario hace click en el botón  de
         * maximizar.
         *
         * @~english
         * TO TRANSLATE
         */
        void maximizedFrame();

        /**
         * @~spanish
         * Señal que se lanza cuando el usuario hace click en el botón salir.
         *
         * @~english
         * TO TRANSLATE
         */
        void closedFrame();

};

#endif // CLIENTFRAME_H
