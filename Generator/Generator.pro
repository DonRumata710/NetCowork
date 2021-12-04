TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += \
    $$OUT_PWD/generated \
    $$PWD/../../RE-flex/include

SOURCES += \
        class.cpp \
        codeelement.cpp \
        dependency.cpp \
        enum.cpp \
        enumtest.cpp \
        filehandler.cpp \
        function.cpp \
        interfacemodel.cpp \
        main.cpp \
        printer.cpp \
        property.cpp \
        simpletypeelement.cpp \
        struct.cpp \
        types.cpp \
        $$OUT_PWD/generated/interface.lexer.cpp \
        $$OUT_PWD/generated/interface.parser.cpp

HEADERS += \
    class.h \
    codeelement.h \
    dependency.h \
    enum.h \
    enumutil.h \
    filehandler.h \
    function.h \
    interfacemodel.h \
    parameter.h \
    printer.h \
    property.h \
    simpletypeelement.h \
    struct.h \
    types.h \
    $$OUT_PWD/generated/interface.lexer.hpp \
    $$OUT_PWD/generated/interface.parser.hpp

DISTFILES += \
    interface.lxx \
    interface.yxx

folder.target = $$OUT_PWD/generated
win32:folder.commands = $(CHK_DIR_EXISTS) $$shell_path($$OUT_PWD/generated) $(MKDIR) $$shell_path($$OUT_PWD/generated)
linux:folder.commands = $$shell_path($$OUT_PWD/generated) & $(MKDIR) $$shell_path($$OUT_PWD/generated)
QMAKE_EXTRA_TARGETS += folder

flex.target = $$OUT_PWD/generated/interface.lexer.cpp
flex.depends = $$PWD/interface.lxx
flex.commands = $$PWD/../../RE-flex/bin/win64/reflex.exe $$PWD/interface.lxx --outfile=$$OUT_PWD/generated/interface.lexer.cpp --header-file=$$OUT_PWD/generated/interface.lexer.hpp
QMAKE_EXTRA_TARGETS += flex

flex_header.target = $$OUT_PWD/generated/interface.lexer.hpp
flex_header.depends = $$PWD/interface.lxx
flex_header.commands = $$PWD/../../RE-flex/bin/win64/reflex.exe $$PWD/interface.lxx --outfile=$$OUT_PWD/generated/interface.lexer.cpp --header-file=$$OUT_PWD/generated/interface.lexer.hpp
QMAKE_EXTRA_TARGETS += flex_header

bison.target = $$OUT_PWD/generated/interface.parser.cpp
bison.depends = $$PWD/interface.yxx
bison.commands = $$PWD/../../bison/bin/win_bison.exe -d $$PWD/interface.yxx --output=$$OUT_PWD/generated/interface.parser.cpp
QMAKE_EXTRA_TARGETS += bison

bison_header.target = $$OUT_PWD/generated/interface.parser.hpp
bison_header.depends = $$PWD/interface.yxx
bison_header.commands = $$PWD/../../bison/bin/win_bison.exe -d $$PWD/interface.yxx --output=$$OUT_PWD/generated/interface.parser.cpp
QMAKE_EXTRA_TARGETS += bison_header

PRE_TARGETDEPS += \
    $$OUT_PWD/generated \
    $$OUT_PWD/generated/interface.lexer.hpp \
    $$OUT_PWD/generated/interface.lexer.cpp \
    $$OUT_PWD/generated/interface.parser.hpp \
    $$OUT_PWD/generated/interface.parser.cpp

win32: LIBS += -L$$PWD/../../RE-flex/vs/ -lreflex
win32: PRE_TARGETDEPS += $$PWD/../../RE-flex/vs/reflex.lib
unix:!macx: LIBS += -L$$PWD/../../RE-flex/ -lreflex
unix: PRE_TARGETDEPS += $$PWD/../../RE-flex/libreflex.a

MOC_DIR = $$OUT_PWD/moc
OBJECTS_DIR = $$OUT_PWD/obj
UI_DIR = $$OUT_PWD/ui
