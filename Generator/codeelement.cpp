#include "codeelement.h"

#include <cctype>


CodeElement::CodeElement(Type_enum _type, const std::string& _name) :
    type(_type),
    name(_name)
{
    if (!isalpha(name[0]))
        throw std::runtime_error("syntax error in typename '" + name + "'");

    for (char ch : name)
    {
        if (!isalnum(ch))
            throw std::logic_error("wrong type name recognition");
    }
}

CodeElement::CodeElement(const CodeElement& other) :
    type(other.type),
    name(other.name)
{}

CodeElement::CodeElement(CodeElement&& other) :
    type(other.type),
    name(std::move(other.name))
{}

Type_enum CodeElement::get_type() const
{
    return type;
}

const std::string& CodeElement::get_name() const
{
    return name;
}
