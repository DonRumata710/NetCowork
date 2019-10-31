#ifndef TYPES_H
#define TYPES_H

#include "enumutil.h"


#define Token(DO) \
    DO(TOKEN_CLASS, "class") \
    DO(TOKEN_STRUCT, "struct") \
    DO(TOKEN_ENUM, "enum") \
    DO(TOKEN_FUNCTION, "function") \
    DO(TOKEN_GETTER, "get") \
    DO(TOKEN_SETTER, "set") \
    DO(TOKEN_OPENING_BRACE, "{") \
    DO(TOKEN_CLOSING_BRACE, "}") \
    DO(TOKEN_OPENING_PARENTHESIS, "(") \
    DO(TOKEN_CLOSING_PARENTHESIS, ")") \
    DO(TOKEN_COMMA, ",") \
    DO(TOKEN_ASSIGNMENT, "=") \
    DO(TOKEN_SEMICOLON, ";") \
    DO(TOKEN_COLON, ":") \
    DO(TOKEN_NONE, "")


ENUM_WITH_NAMES(Token)
STR_TO_ENUM_DELC(Token)


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
