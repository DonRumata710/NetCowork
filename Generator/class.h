#ifndef CLASS_H
#define CLASS_H

#include "function.h"
#include "property.h"
#include "dependency.h"

#include <vector>
#include <set>


class Class : public CodeElement
{
public:
    explicit Class(const std::string& name);
    Class(const Class& other);
    Class(Class&& other);

    void add_dependency(const Dependency* dependency);
    void add_property(const Property& type);
    void add_property(Property&& type);
    void add_function(const Function& func);
    void add_function(Function&& func);

    const std::set<const CodeElement*>& get_dependencies() const;

    const std::vector<Property>& get_properties() const;
    const std::vector<Function>& get_functions() const;

private:
    void add_dependencies(const Function& func);

private:
    std::vector<Property> properties;
    std::vector<Function> functions;
    std::set<const CodeElement*> dependencies;
};

#endif // CLASS_H
