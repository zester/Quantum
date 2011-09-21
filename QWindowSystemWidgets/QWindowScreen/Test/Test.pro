#-------------------------------------------------
#
# Project created by QtCreator 2011-09-20T22:19:01
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -L/usr/lib -lX11 -lXext -lXrandr

SOURCES += main.cpp ../qwindowscreen.cpp
HEADERS += ../qwindowscreen.h\
        ../QWindowScreen_global.h
