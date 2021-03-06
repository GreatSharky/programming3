TEMPLATE = app
TARGET = NYSSE

QT += core gui widgets network multimedia

CONFIG += c++14

win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/ -lCourseLib

INCLUDEPATH += \
    $$PWD/../Course/CourseLib

DEPENDPATH += \
    $$PWD/../Course/CourseLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/libCourseLib.a

HEADERS += \
    airplane.hh \
    busgraphic.h \
    character.hh \
    city.h \
    dialog.h \
    graphicitem.h \
    mainwindow.h \
    statistics.hh \
    stopgraphic.h

SOURCES += \
    airplane.cpp \
    busgraphic.cpp \
    character.cpp \
    city.cpp \
    creategame.cpp \
    dialog.cpp \
    graphicitem.cpp \
    main.cc \
    mainwindow.cpp \
    statistics.cpp \
    stopgraphic.cpp

FORMS += \
    dialog.ui \
    mainwindow.ui

RESOURCES += \
    bus-stop-icon.png \
    bus-icon.png

DISTFILES +=
