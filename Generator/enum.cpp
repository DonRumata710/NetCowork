#include "enum.h"


Enum::Enum(const std::string& name) :
    CodeElement (Type_enum::ENUM, name)
{}

void Enum::add_value(const std::string& name, int64_t val)
{
    values.insert(decltype (values)::value_type(name, val));
}

void Enum::add_value(std::string&& name, int64_t val)
{
    values.insert(decltype (values)::value_type(std::move(name), val));
}

void Enum::add_value(const std::pair<std::string, int64_t>& val)
{
    values.insert(val);
}

void Enum::add_value(std::pair<std::string, int64_t>&& val)
{
    values.insert(std::move(val));
}

bool Enum::check_value(const std::string& name) const
{
    return values.find(name) != values.end();
}

int64_t Enum::get_value(const std::string& name) const
{
    auto it = values.find(name);
    if (it == values.end())
        return INT64_MIN;
    return it->second;
}
