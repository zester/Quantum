QT      -= gui
QT      += xml
CONFIG  += console
CONFIG  -= app_bundle

HEADERS += src/stringhelp.h
SOURCES += src/stringhelp.cpp src/qconf.cpp

include($$OUT_PWD/conf.pri)

contains($$list($$[QT_VERSION]), 4.0.*|4.1.*) {
	DEFINES += DATADIR=\"$$DATADIR\"
} else {
	DEFINES += DATADIR=\\\"$$DATADIR\\\"
}

# install
#CONFIG += no_fixpath
target.path = $$BINDIR
INSTALLS += target
libfiles.path = $$DATADIR/qconf
libfiles.files = $$IN_PWD/conf $$IN_PWD/modules
INSTALLS += libfiles
