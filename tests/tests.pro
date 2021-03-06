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

HEADERS += \
    tst_arena.h \
    ../src/arena.h \
    ../src/monster.h \
    ../src/player.h \
    ../src/monsterchase.h \
    ../src/gameworld.h \
    tst_linear_rotation.h \
    tst_player_collisions.h \
    tst_monsters_collisions.h \
    tst_monster_player_detection.h\
    tst_perpendicular_direction.h

SOURCES += \
        main.cpp \
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
        ../src/gameconfig.cpp \
        ../src/gameviews.cpp


INCLUDEPATH += ../src
