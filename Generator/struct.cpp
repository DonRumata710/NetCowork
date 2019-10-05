#include "struct.h"


Struct::Struct(const std::string& name) :
    CodeElement (Type_enum::STRUCT, name)
{}

Struct::Struct(const Struct& other) :
    CodeElement (other),
    members(other.members)
{}

Struct::Struct(Struct&& other) :
    CodeElement (std::move(other)),
    members(std::move(other.members))
{}

void Struct::add_member(const Parameter& param)
{
    members.push_back(param);
}
