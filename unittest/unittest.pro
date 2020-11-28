QT += testlib
QT -= gui

TARGET = tst_unittest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_unittest.cpp \
    ../Game/statistics.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../Game/statistics.hh \
    ../

INCLUDEPATH += \
    ../Game/ \
    ../Course/CourseLib \
    ../

DEPENDPATH += \
    ../Course/CourseLib \
    ../
