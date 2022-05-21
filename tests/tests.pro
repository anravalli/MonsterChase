GOOGLETEST_DIR = ../googletest

include(gtest_dependency.pri)

TEMPLATE = app
#CONFIG += console c++11
CONFIG += c++11
CONFIG -= app_bundle
CONFIG += thread
#CONFIG -= qt
QT += widgets
CONFIG += qt

QMAKE_CXXFLAGS += -O0 -std=c++11

HEADERS += \
    ../src/arena.h \
    ../src/monster.h \
    ../src/player.h \
    ../src/monsterchase.h \
    ../src/monsterchase_mainpage.h \
    ../src/gamecontroller.h \
    ../src/gameworld.h \
    ../src/ui_framework/uiviewitems_qt.h \
    ../src/ui_framework/uipagecontroller.h \
    ../src/ui_framework/uipageview_qt.h \
    ../src/ui_framework/uipagemenu.h \
    ../src/ui_framework/uipagemenuwidgets_qt.h \
    ../src/editor/level_editor.h \
    ../src/editor/editor_ui.h

SOURCES += \
        main.cpp \
        ../src/editor/level_editor.cpp \
        ../src/editor/editor_ui.cpp \
        ../src/editor/level_models.cpp \
        ../src/options_panel/optionpage_controller.cpp \
        ../src/options_panel/optionpage_view.cpp \
        ../src/ui_framework/uipagemenu.cpp \
        ../src/ui_framework/uipagemenuwidgets_qt.cpp \
        ../src/ui_framework/uiviewitems_qt.cpp \
        ../src/ui_framework/uipageview_qt.cpp \
        ../src/ui_framework/uipagecontroller.cpp \
        ../src/algorithms.cpp \
        ../src/player.cpp \
        ../src/playersm.cc \
        ../src/playerqtviews.cpp \
        ../src/arena.cpp \
        ../src/behaviors.cpp \
        ../src/monster.cpp \
        ../src/monsterchase.cpp \
        ../src/monsterviews.cpp \
        ../src/monstersm.cpp \
        ../src/gameworld.cpp \
        ../src/gamecontroller.cpp \
        ../src/gameconfig.cpp \
        ../src/gameviews.cpp

FORMS += \
    ../src/editor/editor.ui

INCLUDEPATH += ../src ./
