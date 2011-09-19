#-------------------------------------------------
#
# Project created by QtCreator 2011-09-19T04:38:10
#
#-------------------------------------------------

QT       += core gui

TARGET = QMediaPlayer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
LIBS += -L/usr/lib -lvlc-qt

RESOURCES += \
    resource.qrc
