#ifndef TYPES_H
#define TYPES_H

#include "enumutil.h"


#define Token(DO) \
    DO(TOKEN_IMPORT, "import") \
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
    DO(TOKEN_DOT, ".") \
    DO(TOKEN_NONE, "")


ENUM_WITH_NAMES(Token)
STR_TO_ENUM_DECL(Token)


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
    DO(Type, NONE,     "NONE") \
    DO(Type, UI64,     "ui64") \
    DO(Type, UI32,     "ui32") \
    DO(Type, UI16,     "ui16") \
    DO(Type, UI8,      "ui8") \
    DO(Type, I64,      "i64") \
    DO(Type, I32,      "i32") \
    DO(Type, I16,      "i16") \
    DO(Type, I8,       "i8") \
    DO(Type, FLOAT,    "float") \
    DO(Type, DFLOAT,   "double") \
    DO(Type, CHAR,     "char") \
    DO(Type, STRING,   "string") \
    DO(Type, FUNCTION, "FUNCTION") \
    DO(Type, STRUCT,   "STRUCT") \
    DO(Type, CLASS,    "CLASS") \
    DO(Type, ENUM,     "ENUM")


ENUM_C_WITH_NAMES(Type)
STR_TO_ENUM_DECL(Type)
ENUM_TO_STR_DECL(Type)


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
