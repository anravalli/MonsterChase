#-------------------------------------------------
#
# Project created by QtCreator 2019-01-08T16:22:18
#
#-------------------------------------------------

QT       += core gui multimedia

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
LIBS += ../ext_libs/libQtMixer.so.2

INCLUDEPATH += . \
	../ext_libs/QtMixer/
#	options_panel \
#	level_editor

SOURCES += main.cpp\
    audio_server/AudioServer.cpp \
    base_game/gamecontroller.cpp \
    base_game/gameworld.cpp \
    base_game/gameviews.cpp \
    base_game/gameconfig.cpp \
    base_game/arena.cpp \
#    level_editor/*.cpp \
    editor/level_editor.cpp \
    editor/editor_ui.cpp \
    editor/level_models.cpp \
    highscores/hiscorepage_controller.cpp \
    highscores/hiscorepage_view.cpp \
    lib/algorithms.cpp \
    lib/behaviors.cpp \
    lib/ui_framework/uipagecontroller.cpp \
    lib/ui_framework/uipagemenu.cpp \
    lib/ui_framework/uipagemenuwidgets_qt.cpp \
    lib/ui_framework/uipageview_qt.cpp \
    lib/ui_framework/uiviewitems_qt.cpp \
    lib/animations.cpp \
    lib/persistence.cpp \
    match/matchmenu.cpp \
    match/match.cpp \
    match/match_sm.cpp \
    monsters/monster.cpp \
    monsters/monstersm.cpp \
    monsters/monsterviews.cpp \
    options/optionpage_controller.cpp \
    options/optionpage_view.cpp \
    options/optionsmenu.cpp \
    player/player.cpp \
    player/playersm.cc \
    player/playerqtviews.cpp \
    player_profile/playerprofile.cpp \
    player_profile/playerprofile_manager.cpp \
    monsterchase.cpp

HEADERS  += monsterchase.h \
    audio_server/AudioServer.h \
    base_game/game_entity.h \
    base_game/gamecontroller.h \
    base_game/arena.h \
    base_game/gameworld.h \
    base_game/gameviews.h \
    base_game/gameconfig.h \
    editor/level_editor.h \
    editor/editor_ui.h \
    editor/level_models.h \
    lib/algorithms.h \
    lib/persistence.h \
    lib/behaviors.h \
    lib/ui_framework/uipagecontroller.h \
    lib/ui_framework/uipagemenu.h \
    lib/ui_framework/uipagemenuwidgets_qt.h \
    lib/ui_framework/uipageview_qt.h \
    lib/ui_framework/uiviewitems_qt.h \
    lib/animations.h \
    match/matchmenu.h \
    match/match.h \
    match/match_sm.h \
    match/matchendmenu.h \
    monsters/monster.h \
    monsters/monstersm.h \
    monsters/monsterviews.h \
    player/player.h \
    player/playersm.h \
    player/playerqtviews.h \
    player_profile/playerprofile.h \
    player_profile/playerprofile_manager.h \
	monsterchase_mainpage.h

RESOURCES += \
    ../monsterchase.qrc 

FORMS += \
    editor/editor.ui

DISTFILES += \
    ../models/monsterchase_ui.qmodel \
    ../models/monsters.qmodel
