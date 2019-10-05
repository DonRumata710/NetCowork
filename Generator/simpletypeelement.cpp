#include "simpletypeelement.h"

#include <unordered_map>


std::unordered_map<Type_enum, std::string> type_names = {
    { Type_enum::UI64, "ui64" },
    { Type_enum::UI32, "ui32" },
    { Type_enum::UI16, "ui16" },
    { Type_enum::UI8, "ui8" },
    { Type_enum::I64, "i64" },
    { Type_enum::I32, "i32" },
    { Type_enum::I16, "i16" },
    { Type_enum::I8, "i8" },
    { Type_enum::CHAR, "char" },
    { Type_enum::STRING, "string" },
    { Type_enum::STRUCT, "struct" },
    { Type_enum::CLASS, "class" }
};


SimpleType::SimpleType(Type_enum type) :
    CodeElement(type, get_typename(type))
{}

std::string SimpleType::get_typename(Type_enum type) const
{
    return type_names[type];
}
