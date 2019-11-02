#ifndef INTERFACEMODEL_H
#define INTERFACEMODEL_H

#include "dependency.h"
#include "class.h"
#include "struct.h"
#include "enum.h"
#include "simpletypeelement.h"
#include "printer.h"

#include <set>


class InterfaceModel
{
public:
    InterfaceModel();

    void print(Printer& printer);

    const CodeElement* get_type(const std::string& type) const;

    Dependency* add_dependency(const Dependency&);

    Class* add_class(const Class& new_class);
    Class* add_class(Class&& new_class);

    Struct* add_struct(const Struct& new_struct);
    Struct* add_struct(Struct&& new_struct);

    Enum* add_enumeration(const Enum& new_enum);
    Enum* add_enumeration(Enum&& new_enum);

    Function* add_function(const Function& new_enum);
    Function* add_function(Function&& new_enum);

    std::vector<Class> get_classes() const;
    std::vector<Struct> get_sturctures() const;
    std::vector<Enum> get_enumerations() const;
    std::vector<Function> get_functions() const;

private:
    std::vector<Dependency> dependencies;

    std::vector<Class> classes;
    std::vector<Struct> structs;
    std::vector<Enum> enums;
    std::vector<Function> functions;

    std::unordered_map<std::string, SimpleType> types;
};

#endif // INTERFACEMODEL_H
