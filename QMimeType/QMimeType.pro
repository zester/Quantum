#-------------------------------------------------
#
# Project created by QtCreator 2011-09-13T23:52:06
#
#-------------------------------------------------

QT       += xml

QT       -= core gui

TARGET = QMimeType
TEMPLATE = lib

DEFINES += QMIMETYPE_LIBRARY

SOURCES += qmimetype.cpp

HEADERS += qmimetype.h\
        QMimeType_global.h

headers.files += qmimetype.h QMimeType_global.h
headers.path = /usr/include

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE2FE7333
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = QMimeType.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target headers
}
