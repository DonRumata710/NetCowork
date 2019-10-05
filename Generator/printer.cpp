#include "printer.h"

#include "codeelement.h"
#include "parameter.h"

#include <iostream>


static uint16_t offset_unit = 2;
static std::string eol = ";\n";


Printer::Printer(const std::string& folder_path) :
    path(folder_path)
{
    if (*path.rbegin() != '/' && *path.rbegin() != '\\')
        path.push_back('/');
}

bool Printer::print_class(const Class& c)
{
    current_file = std::ofstream(path + c.get_name() + ".h");
    if (!current_file.is_open())
    {
        std::cerr << "file opening failure";
        return false;
    }

    std::string header_block = c.get_name() + "_h";
    print_line("#ifndef " + header_block);
    print_line("#define " + header_block);

    for (const auto& dependency : c.get_dependencies())
    {
        switch (dependency->get_type())
        {
        case Type_enum::UI64:
        case Type_enum::UI32:
        case Type_enum::UI16:
        case Type_enum::UI8:
        case Type_enum::I64:
        case Type_enum::I32:
        case Type_enum::I16:
        case Type_enum::I8:
        case Type_enum::CHAR:
            break;
        case Type_enum::STRING:
            print_dependency("string");
            break;
        case Type_enum::FUNCTION:
        case Type_enum::STRUCT:
        case Type_enum::CLASS:
        case Type_enum::ENUM:
            print_dependency(dependency->get_name() + ".h");
            break;
        default:
            std::logic_error("unknown type in printer");
        }
    }

    print_line("");

    print_line("class " + c.get_name() + '\n');
    print_line("{");
    increase_offset();
    print_line("virtual ~" + c.get_name() + "() = default");

    for (const Function& func : c.get_functions())
    {
        std::string line = "virtual void " + func.get_name() + "(";
        for (const Parameter& param : func.get_parameters())
        {
            const CodeElement* element = param.element;
            bool as_ref = element->get_type() == Type_enum::STRING || element->get_type() == Type_enum::STRUCT;
            if (as_ref)
                line += "const ";
            line += get_type_name(element);
            if (as_ref)
                line += "& ";
            else
                line += " ";
            line += param.value_name;
            line += ",";
        }

        line.pop_back();
        line += ") = 0;";
        print_line(line);
    }

    for (const Parameter& param : c.get_members())
    {
        const CodeElement* element = param.element;
        bool as_ref = element->get_type() == Type_enum::STRING || element->get_type() == Type_enum::STRUCT;
        {
            std::string line = "virtual void set_" + param.value_name + "(";

            if (as_ref)
                line += "const ";
            line += get_type_name(element);
            if (as_ref)
                line += "& new_";
            else
                line += " new_";

            line += param.value_name + ") = 0;";

            print_line(line);
        }
        {
            std::string line = "virtual ";

            if (as_ref)
                line += "const ";
            line += get_type_name(element) + "get_" + param.value_name + "() const = 0;";
            print_line(line);
        }
    }

    decrease_offset();
    print_line("};");

    print_line("#endif");

    current_file = std::ofstream(path + c.get_name() + "processor.h");

    header_block = c.get_name() + "processor_h";
    print_line("#ifndef " + header_block);
    print_line("#define " + header_block);

    return true;
}

void Printer::print_line(const std::string& line)
{
    current_file << line << std::endl;
}

void Printer::print_dependency(const std::string& type)
{
    print_line("#include <"  + type  + ">");
}

void Printer::increase_offset()
{
    offset += "  ";
}

void Printer::decrease_offset()
{
    offset.erase(offset.end() - 2, offset.end());
}

std::string Printer::get_type_name(const CodeElement* element)
{
    switch(element->get_type())
    {
    case Type_enum::UI64:
        return "uint64_t";
    case Type_enum::UI32:
        return "uint32_t";
    case Type_enum::UI16:
        return "uint16_t";
    case Type_enum::UI8:
        return "uint8_t";
    case Type_enum::I64:
        return "int64_t";
    case Type_enum::I32:
        return "int32_t";
    case Type_enum::I16:
        return "int16_t";
    case Type_enum::I8:
        return "int8_t";
    case Type_enum::CHAR:
        return "char";
    case Type_enum::STRING:
        return "std::string";
    case Type_enum::FUNCTION:
        std::cout << "function as argument is unsupported";
        throw std::logic_error("unsupported");
    case Type_enum::STRUCT:
    case Type_enum::CLASS:
    case Type_enum::ENUM:
        return element->get_name();
    default:
        std::logic_error("unknown type in printer");
    }
}
