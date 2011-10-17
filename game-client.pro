#-------------------------------------------------
#
# Project created by QtCreator 2011-06-13T20:35:58
#
#-------------------------------------------------

QT       += core gui network testlib

TARGET   = game-client
TEMPLATE = app


SOURCES  += main.cpp\
    gui/Enter.cpp \
    gui/Game.cpp \
    lib/GameClient.cpp \
    lib/Npc.cpp \
    gui/Talk.cpp \
    lib/Quest.cpp \
    lib/Mob.cpp \
    gui/Character.cpp \
    lib/Item.cpp \
    gui/Trade.cpp

HEADERS  += \
    gui/Enter.h \
    gui/Game.h \
    lib/GameClient.h \
    lib/Npc.h \
    gui/Talk.h \
    lib/Quest.h \
    lib/Mob.h \
    gui/Character.h \
    lib/Item.h \
    gui/Trade.h

FORMS    += \
    ui/Game.ui \
    ui/Enter.ui \
    ui/Talk.ui \
    ui/Character.ui \
    ui/Trade.ui

RESOURCES += \
    images.qrc
