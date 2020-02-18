#include "interfacemodel.h"

#include <unordered_map>


InterfaceModel::InterfaceModel()
{
    types = {
        { "ui64",   SimpleType(Type_enum::UI64  ) },
        { "ui32",   SimpleType(Type_enum::UI32  ) },
        { "ui16",   SimpleType(Type_enum::UI16  ) },
        { "ui8",    SimpleType(Type_enum::UI8   ) },
        { "i64",    SimpleType(Type_enum::I64   ) },
        { "i32",    SimpleType(Type_enum::I32   ) },
        { "i16",    SimpleType(Type_enum::I16   ) },
        { "i8",     SimpleType(Type_enum::I8    ) },
        { "float",  SimpleType(Type_enum::FLOAT ) },
        { "double", SimpleType(Type_enum::DFLOAT) },
        { "char",   SimpleType(Type_enum::CHAR  ) },
        { "string", SimpleType(Type_enum::STRING) }
    };
}

void InterfaceModel::print(Printer& printer)
{
    for (const auto& c : classes)
        printer.print_class(c);
}


template<typename T, typename Alloc, template <typename, typename> class Container>
const T* find_type(const Container<T, Alloc>& cont, const std::string& name)
{
    for (const auto& obj : cont)
    {
        if (obj.get_name() == name)
            return &obj;
    }

    return nullptr;
}


const CodeElement* InterfaceModel::get_type(const std::string& type_name) const
{
    auto it = types.find(type_name);
    if (it != types.end())
    {
        return &it->second;
    }

    const CodeElement* type;
    type = find_type(dependencies, type_name);
    if (type)
        return type;

    type = find_type(classes, type_name);
    if (type)
        return type;

    type = find_type(structs, type_name);
    if (type)
        return type;

    type = find_type(enums, type_name);
    if (type)
        return type;

    return nullptr;
}

Dependency* InterfaceModel::add_dependency(const Dependency& dependency)
{
    dependencies.push_back(dependency);
    return &*dependencies.rbegin();
}

Class* InterfaceModel::add_class(const Class& new_class)
{
    classes.emplace_back(new_class);
    return &*classes.rbegin();
}

Class* InterfaceModel::add_class(Class&& new_class)
{
    classes.emplace_back(std::move(new_class));
    return &*classes.rbegin();
}

Struct* InterfaceModel::add_struct(const Struct& new_struct)
{
    structs.emplace_back(new_struct);
    return &*structs.rbegin();
}

Struct* InterfaceModel::add_struct(Struct&& new_struct)
{
    structs.emplace_back(std::move(new_struct));
    return &*structs.rbegin();
}

Enum* InterfaceModel::add_enumeration(const Enum& new_enum)
{
    enums.emplace_back(new_enum);
    return &*enums.rbegin();
}

Enum* InterfaceModel::add_enumeration(Enum&& new_enum)
{
    enums.emplace_back(std::move(new_enum));
    return &*enums.rbegin();
}

Function* InterfaceModel::add_function(const Function& new_enum)
{
    functions.emplace_back(new_enum);
    return &*functions.rbegin();
}

Function* InterfaceModel::add_function(Function&& new_enum)
{
    functions.emplace_back(std::move(new_enum));
    return &*functions.rbegin();
}
