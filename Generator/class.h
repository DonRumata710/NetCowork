#ifndef CLASS_H
#define CLASS_H

#include "function.h"

#include <vector>
#include <set>


class Class : public CodeElement
{
public:
    explicit Class(const std::string& name);
    Class(const Class& other);
    Class(Class&& other);

    void add_member(const Parameter& type);
    void add_member(Parameter&& type);
    void add_function(const Function& func);
    void add_function(Function&& func);

    const std::set<const CodeElement*>& get_dependencies() const;

    const std::vector<Function>& get_functions() const;
    const std::vector<Parameter>& get_members() const;

private:
    void add_dependencies(const Function& func);

private:
    std::vector<Parameter> members;
    std::vector<Function> functions;
    std::set<const CodeElement*> dependencies;
};

#endif // CLASS_H
