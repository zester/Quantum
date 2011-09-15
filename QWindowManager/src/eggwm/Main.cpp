/**
 * @file /src/eggwm/Main.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Egg Window Manager, usted puede
 * redistribuirlo y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Egg Window Manager project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @author José Expósito
 */
#include "src/eggwm/EggWM.h"

/**
 * @~spanish
 * Función de inicio de Egg Window Manager.
 * @param argc Número de argumentos recibidos por consola.
 * @param argv Lista de argumentos.
 *
 * @~english
 * Start function for Egg Window Manager.
 * @param argc Number of arguments received by console.
 * @param argv Argument list.
 */
int main(int argc, char** argv) {
    EggWM eggWM(argc, argv);
    return eggWM.exec();
}

/*
 * Para debuggear:
 *
 * $ Xephyr :1 -ac -screen 900x700 &
 * En "Proyectos -> Entorno de construcción -> DISPLAY" poner ":1" o lanzar con
 * la opción "-display :1".
 *
 * Para ver el árbol de ventanas:
 * $ xwininfo -display :1 -tree -root
 *
 * Ver propiedades de una ventana:
 * $ xwininfo -display :1
 *
 * Se le puede añadir una composición muy simple con xcompmg:
 * $ xcompmgr -cf -d :1
 *
 * Para debugear el estándar EWMH/NetWM:
 * La herramienta wmctrl nos proporciona diversa información:
 * $ man wmctrl
 * Para ver las propiedades que va estableciendo el WM sobre la root window:
 * $ xprop -root -display :1
 *
 * NOTA -> Mirar QStyle para ver como crear un estilo para los widgets
 */
