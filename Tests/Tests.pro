QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_netcowork.cpp

INCLUDEPATH += \
    $$PWD/../include \

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../NetCowork/release/ -lNetCowork
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../NetCowork/debug/ -lNetCowork
else:unix:!macx: LIBS += -L$$OUT_PWD/../../NetCowork/ -lNetCowork

DEPENDPATH += $$PWD/../include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../NetCowork/release/libNetCowork.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../NetCowork/debug/libNetCowork.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../NetCowork/release/NetCowork.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../NetCowork/debug/NetCowork.lib
else:unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../NetCowork/libNetCowork.a

MOC_DIR = $$OUT_PWD/moc
OBJECTS_DIR = $$OUT_PWD/obj
UI_DIR = $$OUT_PWD/ui
