#-------------------------------------------------
#
# Project created by QtCreator 2019-09-08T11:08:14
#
#-------------------------------------------------

QT += core gui widgets network

TARGET = NetCowork
TEMPLATE = lib
CONFIG += staticlib c++17

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++17

SOURCES += \
        netcoworkclient.cpp \
        netcoworker.cpp \
        netcoworkfactory.cpp \
        netcoworkprovider.cpp \
        netcoworkserver.cpp \
        message.cpp

HEADERS += \
        $$PWD/../include/message.h \
        $$PWD/../include/netcoworkclient.h \
        $$PWD/../include/netcoworker.h \
        $$PWD/../include/netcoworkfactory.h \
        $$PWD/../include/netcoworkprovider.h \
        $$PWD/../include/netcoworkserver.h

INCLUDEPATH += $$PWD/../include

MOC_DIR = $$OUT_PWD/moc
OBJECTS_DIR = $$OUT_PWD/obj
UI_DIR = $$OUT_PWD/ui

unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
