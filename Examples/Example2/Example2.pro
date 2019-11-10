#-------------------------------------------------
#
# Project created by QtCreator 2019-09-08T11:08:14
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NetCoworkExample
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

SOURCES += \
        ball.cpp \
        game.cpp \
        main.cpp \
        mainwindow.cpp \
        platform.cpp

HEADERS += \
        ball.h \
        game.h \
        mainwindow.h \
        $$OUT_PWD/generated/Ball_net.h \
        $$OUT_PWD/generated/Platform_net.h \
        platform.h

INCLUDEPATH += \
    $$PWD/../include \
    $$OUT_PWD

FORMS += \
        mainwindow.ui

netcowork.target = $$OUT_PWD/generated/Ball_net.h $$OUT_PWD/generated/Platform_net.h
netcowork.depends = $$PWD/netobjects.nc
CONFIG(release, debug|release): netcowork.commands = $$OUT_PWD/../../Generator/release/Generator -i $$PWD/netobjects.nc -o $$OUT_PWD/generated
CONFIG(debug, debug|release): netcowork.commands = $$OUT_PWD/../../Generator/debug/Generator -i $$PWD/netobjects.nc -o $$OUT_PWD/generated
QMAKE_EXTRA_TARGETS += netcowork
PRE_TARGETDEPS += $$netcowork.target

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../NetCowork/release/ -lNetCowork
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../NetCowork/debug/ -lNetCowork
else:unix:!macx: LIBS += -L$$OUT_PWD/../../NetCowork/ -lNetCowork

INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../NetCowork/release/libNetCowork.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../NetCowork/debug/libNetCowork.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../NetCowork/release/NetCowork.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../NetCowork/debug/NetCowork.lib
else:unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../../NetCowork/libNetCowork.a

MOC_DIR = $$OUT_PWD/moc
OBJECTS_DIR = $$OUT_PWD/obj
UI_DIR = $$OUT_PWD/ui
