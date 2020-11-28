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
    ../CourseLib/interfaces/istatistics.hh \

INCLUDEPATH += \
    ../Game/ \
    ../CourseLib/interfaces/
DEPENDPATH += \
    ../CourseLib/interfaces/
