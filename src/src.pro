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

QMAKE_CXXFLAGS += -O0 -std=c++11 -g

INCLUDEPATH += .
#	options_panel \
#	level_editor

SOURCES += main.cpp\
    algorithms.cpp \
#    level_editor/*.cpp \
    editor/level_editor.cpp \
    editor/editor_ui.cpp \
    editor/level_models.cpp \
    options_panel/optionpage_controller.cpp \
    options_panel/optionpage_view.cpp \
    options_panel/optionsmenu.cpp \
    hiscore_panel/hiscorepage_controller.cpp \
    hiscore_panel/hiscorepage_view.cpp \
    matchmenu.cpp \
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
    match.cpp \
    match_sm.cpp \
    ui_framework/uipagecontroller.cpp \
    ui_framework/uipagemenu.cpp \
    ui_framework/uipagemenuwidgets_qt.cpp \
    ui_framework/uipageview_qt.cpp \
    ui_framework/uiviewitems_qt.cpp \
    animations.cpp

HEADERS  += monsterchase.h \
	monsterchase_mainpage.h \
    algorithms.h \
    editor/level_editor.h \
    editor/editor_ui.h \
    editor/level_models.h \
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
    matchmenu.h \
    match.h \
    match_sm.h \
    matchendmenu.h \
    ui_framework/uipagecontroller.h \
    ui_framework/uipagemenu.h \
    ui_framework/uipagemenuwidgets_qt.h \
    ui_framework/uipageview_qt.h \
    ui_framework/uiviewitems_qt.h \
    animations.h

RESOURCES += \
    ../monsterchase.qrc 

FORMS += \
    editor/editor.ui

DISTFILES += \
    ../models/monsterchase_ui.qmodel \
    ../models/monsters.qmodel
