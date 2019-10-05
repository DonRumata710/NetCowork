#ifndef TYPES_H
#define TYPES_H

#include "enumutil.h"


#define Token(DO) \
    DO(CLASS) \
    DO(STRUCT) \
    DO(ENUM) \
    DO(FUNCTION) \
    DO(OPENING_BRACE) \
    DO(CLOSING_BRACE) \
    DO(OPENING_PARENTHESIS) \
    DO(CLOSING_PARENTHESIS) \
    DO(COMMA) \
    DO(ASSIGNMENT) \
    DO(NONE)


ENUM_C(Token)


//enum class Token
//{
//    CLASS,
//    STRUCT,
//    ENUM,
//    FUNCTION,
//    PROPERTY,
//    OPENING_BRACE,
//    CLOSING_BRACE,
//    OPENING_PARENTHESIS,
//    CLOSING_PARENTHESIS,
//    NONE
//};


#define Type(DO) \
    DO(UI64) \
    DO(UI32) \
    DO(UI16) \
    DO(UI8) \
    DO(I64) \
    DO(I32) \
    DO(I16) \
    DO(I8) \
    DO(CHAR) \
    DO(STRING) \
    DO(FUNCTION) \
    DO(STRUCT) \
    DO(CLASS) \
    DO(ENUM) \
    DO(NONE)


ENUM_C(Type)


//enum class Type
//{
//    UI64,
//    UI32,
//    UI16,
//    UI8,
//    I64,
//    I32,
//    I16,
//    I8,
//    CHAR,
//    STRING,
//    FUNCTION,
//    STRUCT,
//    CLASS,
//    NONE
//};


#endif // TYPES_H
