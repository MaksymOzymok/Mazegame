TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    mazegenerator.cpp \
    startscreen.cpp \
    gamelogic.cpp

HEADERS += \
    gameconstans.h \
    mazegenerator.h \
    startscreen.h \
    gamelogic.h