GOOGLETEST_DIR = /home/andrea/Playgrounds/CPlusPlus_playground/googletest

include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
#CONFIG += c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
        tst_collisions.h

SOURCES += \
        main.cpp
