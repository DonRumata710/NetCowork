#include "class.h"


Class::Class(const std::string& name) :
    CodeElement (Type_enum::CLASS, name)
{}

Class::Class(const Class& other) :
    CodeElement (other),
    members(other.members),
    functions(other.functions)
{}

Class::Class(Class&& other) :
    CodeElement (std::move(other)),
    members(std::move(other.members)),
    functions(std::move(other.functions))
{}

void Class::add_member(const Parameter& new_member)
{
    dependencies.insert(new_member.element);
    members.push_back(new_member);
}

void Class::add_member(Parameter&& new_member)
{
    dependencies.insert(new_member.element);
    members.emplace_back(std::move(new_member));
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

const std::vector<Function>& Class::get_functions() const
{
    return functions;
}

const std::vector<Parameter>& Class::get_members() const
{
    return members;
}

void Class::add_dependencies(const Function& func)
{
    for (size_t i = 0; i < func.get_params_count(); ++i)
        dependencies.insert(func.get_param(i)->element);
}
