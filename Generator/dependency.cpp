#include "dependency.h"


Dependency::Dependency(const std::string& _filename, const std::string& _type_name, Type_enum _type) :
    CodeElement(_type, _type_name),
    filename(_filename)
{}

std::string Dependency::get_module() const
{
    return filename;
}
