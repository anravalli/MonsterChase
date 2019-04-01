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
        tst_collisions.h \
        tst_arena.h \
        ../src/arena.h

SOURCES += \
        main.cpp \
        ../src/playersm.cc \
        ../src/arena.cpp

INCLUDEPATH += ../src
