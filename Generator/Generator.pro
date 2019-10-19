TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        class.cpp \
        codeelement.cpp \
        enum.cpp \
        enumtest.cpp \
        filehandler.cpp \
        function.cpp \
        interfacemodel.cpp \
        main.cpp \
        parser.cpp \
        printer.cpp \
        simpletypeelement.cpp \
        struct.cpp \
        types.cpp

HEADERS += \
    class.h \
    codeelement.h \
    enum.h \
    enumutil.h \
    filehandler.h \
    function.h \
    interfacemodel.h \
    parameter.h \
    parser.h \
    printer.h \
    simpletypeelement.h \
    struct.h \
    types.h

MOC_DIR = $$OUT_PWD/moc
OBJECTS_DIR = $$OUT_PWD/obj
UI_DIR = $$OUT_PWD/ui
