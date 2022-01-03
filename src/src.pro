#-------------------------------------------------
#
# Project created by QtCreator 2019-01-08T16:22:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = monsterchase
TEMPLATE = app

unix {
    INCLUDEPATH += /usr/lib/gcc/x86_64-linux-gnu/9/include
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x050000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += QT_MESSAGELOGCONTEXT

QMAKE_CXXFLAGS += -O0 -std=c++11

SOURCES += main.cpp\
    algorithms.cpp \
#    level_editor/*.cpp \
    editor/editor.cpp \
    gamecontroller.cpp \
    monsterchase.cpp \
    player.cpp \
    monster.cpp \
    arena.cpp \
    playersm.cc \
    playerqtviews.cpp \
    monstersm.cpp \
    monsterviews.cpp \
    behaviors.cpp \
    gameworld.cpp \
    gameviews.cpp \
    gameconfig.cpp \
    ui/uipagecontroller.cpp \
    ui/uipagemenu.cpp \
    ui/uipagemenuwidgets_qt.cpp \
    ui/uipageview_qt.cpp \
    ui/uiviewitems_qt.cpp

HEADERS  += monsterchase.h \
	monsterchase_mainpage.h \
    algorithms.h \
    editor/editor.h \
    game_entity.h \
    gamecontroller.h \
    player.h \
    monster.h \
    arena.h \
    playersm.h \
    playerqtviews.h \
    monstersm.h \
    monsterviews.h \
    behaviors.h \
    gameworld.h \
    gameviews.h \
    gameconfig.h \
    ui/uipagecontroller.h \
    ui/uipagemenu.h \
    ui/uipagemenuwidgets_qt.h \
    ui/uipageview_qt.h \
    ui/uiviewitems_qt.h

RESOURCES += \
    ../monsterchase.qrc 

FORMS += \
    editor/editor.ui

DISTFILES += \
    ../models/monsterchase_ui.qmodel \
    ../models/monsters.qmodel
