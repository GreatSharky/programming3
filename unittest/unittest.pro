QT += testlib
QT -= gui

TARGET = tst_unittest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_unittest.cpp \
    ../Game/statistics.cpp

HEADERS += \
    ../Game/statistics.hh \
    ../Course/CourseLib/interfaces/istatistics.hh \

DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += \
    ../Game/ \
    ../Course/CourseLib/interfaces/ \
DEPENDPATH += \
    ../Course/CourseLib/interfaces/ \
