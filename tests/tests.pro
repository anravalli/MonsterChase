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
    ../src/ui/uiviewitems_qt.h \
    ../src/ui/uipagecontroller.h \
    ../src/ui/uipageview_qt.h \
    ../src/ui/uipagemenu.h \
    ../src/ui/uipagemenuwidgets_qt.h \
    ../src/editor/level_editor.h \
    ../src/editor/editor_ui.h

SOURCES += \
        main.cpp \
        ../src/editor/level_editor.cpp \
        ../src/editor/editor_ui.cpp \
        ../src/editor/level_models.cpp \
        ../src/ui/uipagemenu.cpp \
        ../src/ui/uipagemenuwidgets_qt.cpp \
        ../src/ui/uiviewitems_qt.cpp \
        ../src/ui/uipageview_qt.cpp \
        ../src/ui/uipagecontroller.cpp \
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
