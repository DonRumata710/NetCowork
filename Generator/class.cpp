#include "class.h"


Class::Class(const std::string& name) :
    CodeElement (Type_enum::CLASS, name)
{}

Class::Class(const Class& other) :
    CodeElement (other),
    properties(other.properties),
    functions(other.functions),
    dependencies(other.dependencies)
{}

Class::Class(Class&& other) :
    CodeElement (std::move(other)),
    properties(std::move(other.properties)),
    functions(std::move(other.functions)),
    dependencies(std::move(other.dependencies))
{}

void Class::add_dependency(const Dependency* dependency)
{
    dependencies.insert(dependency);
}

void Class::add_property(const Property &property)
{
    dependencies.insert(property.parameter.element);
    properties.push_back(property);
}

void Class::add_property(Property&& property)
{
    dependencies.insert(property.parameter.element);
    properties.emplace_back(std::move(property));
}

void Class::add_function(const Function& func)
{
    add_dependencies(func);
    functions.push_back(func);
}

void Class::add_function(Function&& func)
{
    add_dependencies(func);
    functions.push_back(std::move(func));
}

const std::set<const CodeElement*>& Class::get_dependencies() const
{
    return dependencies;
}

const std::vector<Property>& Class::get_properties() const
{
    return properties;
}

const std::vector<Function>& Class::get_functions() const
{
    return functions;
}

void Class::add_dependencies(const Function& func)
{
    for (size_t i = 0; i < func.get_params_count(); ++i)
        dependencies.insert(func.get_param(i)->element);
}
