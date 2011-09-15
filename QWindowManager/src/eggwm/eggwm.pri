SOURCES += src/eggwm/Main.cpp \
    src/eggwm/EggWM.cpp
HEADERS += src/eggwm/EggWM.h

include(util/util.pri)
include(events/handlers/handlers.pri)
include(events/factory/factory.pri)
include(xwindows/xwindows.pri)
include(config/config.pri)
include(standards/standards.pri)
include(atoms/atoms.pri)
