#-------------------------------------------------
#
# Project created by QtCreator 2011-09-20T21:28:51
#
#-------------------------------------------------



TARGET = QWindowScreen
TEMPLATE = lib

QT -= gui

DEFINES += QWINDOWSCREEN_LIBRARY

SOURCES += qwindowscreen.cpp

HEADERS += qwindowscreen.h\
        QWindowScreen_global.h

LIBS += -L/usr/lib -lX11 -lXext -lXrandr

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE399C426
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = QWindowScreen.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
