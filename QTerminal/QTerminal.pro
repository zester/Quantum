#-------------------------------------------------
#
# Project created by QtCreator 2011-09-19T09:28:23
#
#-------------------------------------------------

QT       += core gui

TARGET = QTerminal
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

LIBS += -L/usr/lib -lqtermwidget
