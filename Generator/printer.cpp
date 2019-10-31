#include "printer.h"

#include "codeelement.h"
#include "parameter.h"

#include <iostream>
#include <filesystem>


static std::string eol = ";\n";


Printer::Printer(const std::string& folder_path) :
    path(folder_path)
{
    if (!std::filesystem::exists(folder_path) && !std::filesystem::create_directory(folder_path))
        std::cerr << "failed creation directory '" << folder_path << "'\n";
    if (*path.rbegin() != '/' && *path.rbegin() != '\\')
        path.push_back('/');
}

bool Printer::print_class(const Class& c)
{
    std::string processor_class = c.get_name() + "Processor";
    std::string sync_class = c.get_name() + "Sync";
    std::string sync_function = sync_class + "::";


    current_file = std::ofstream(path + c.get_name() + ".h");
    if (!current_file.is_open())
    {
        std::cerr << "file opening failure";
        return false;
    }
    print_line("// This file is auto generated");

    std::string header_block = c.get_name() + "_h";
    print_line("#ifndef " + header_block);
    print_line("#define " + header_block);
    print_line("");

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
            print_dependency("cstdint");
            break;
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

    print_line("#include \"netcoworker.h\"");
    print_line("#include \"netcoworkfactory.h\"");

    print_line("");
    print_line("");

    print_line("template<class " + c.get_name() + "> class " + processor_class + ";");

    print_line("");

    start_class(sync_class, "NetCoworker", "i" + c.get_name());

    print_line(sync_class + "(const " + processor_class + "<" + c.get_name() + ">* _proc, uint32_t object_id, " + c.get_name() + "* obj);");

    size_t counter = 1;

    for (size_t i = 0; i < c.get_functions().size(); ++i)
    {
        const Function* func = &c.get_functions()[i];
        print_function("void", func->get_name(), func->get_parameters(), false);
        print_line("{");
        increase_offset();

        std::string args;
        for (const auto& param : c.get_functions()[i].get_parameters())
            args += param.value_name + ", ";
        args.pop_back();
        args.pop_back();

        print_line("impl->" + c.get_functions()[i].get_name() + "(" + args + ");");

        print_line("Message msg;");
        print_line("msg.add_value(uint32_t(" + std::to_string(counter++) + "));");

        for (const auto& param : c.get_functions()[i].get_parameters())
            print_line("msg.add_value(" + param.value_name + ");");

        print_line("send_func_call(msg);");

        decrease_offset();
        print_line("}");
        print_line("");
    }

    for (size_t i = 0; i < c.get_properties().size(); ++i)
    {
        const Property& property = c.get_properties()[i];
        std::string parameter = c.get_properties()[i].parameter.value_name;

        print_function("void", property.setter, { property.parameter }, false, sync_class);
        print_line("{");
        increase_offset();
        print_line("impl->" + property.setter + "(" + parameter + ");");
        print_line("Message msg;");
        print_line("msg.add_value(uint32_t(" + std::to_string(counter++) + "));");
        print_line("msg.add_value(" + parameter + ");");
        print_line("send_func_call(msg);");
        decrease_offset();
        print_line("}");
        print_line("");

        print_function(property.parameter.element, property.getter, {}, true, sync_class);
        print_line("{");
        increase_offset();
        print_line("return impl->" + property.getter + "();");
        decrease_offset();
        print_line("}");
        print_line("");
    }

    print_line("void handle_call(Message& data)");
    print_line("{");
    increase_offset();
    print_line("uint32_t func_id = data.get_value<uint32_t>();");
    print_line("switch (func_id)");
    print_line("{");
    print_line("case 0:");
    increase_offset();
    print_line("throw std::logic_error(\"Unexpected sync signal\");");
    decrease_offset();

    counter = 1;

    for (size_t i = 0; i < c.get_functions().size(); ++i)
    {
        print_line("case " + std::to_string(counter++) + ":");
        print_line("{");
        increase_offset();

        std::string line = "impl->" + c.get_functions()[i].get_name() + "(";
        for (const Parameter& param : c.get_functions()[i].get_parameters())
        {
            std::string type = get_type_name(param.element);
            print_line(type + " " + param.value_name + " = data.get_value<" + type + ">();");

            line += param.value_name + ", ";
        }

        line.pop_back();
        line.pop_back();

        print_line(line + ");");

        print_line("break;");
        decrease_offset();
        print_line("}");
    }

    for (size_t i = 0; i < c.get_properties().size(); ++i)
    {
        print_line("case " + std::to_string(counter++) + ":");
        print_line("{");
        increase_offset();

        const Property* property = &c.get_properties()[i];

        std::string get_value_line = get_type_name(property->parameter.element) + " val = data.get_";
        switch(property->parameter.element->get_type())
        {
        case Type_enum::STRING:
            get_value_line += "string";
            break;
        case Type_enum::CLASS:
        case Type_enum::STRUCT:
        case Type_enum::FUNCTION:
            throw std::logic_error("Not implemented yet");
        default:
            get_value_line += "value<" + get_type_name(property->parameter.element) + ">";
        }
        get_value_line += "();";
        print_line(get_value_line);

        print_line("impl->" + property->setter + "(val);");

        print_line("break;");
        decrease_offset();
        print_line("}");
    }

    print_line("default:");
    increase_offset();
    print_line("throw std::runtime_error(\"Unknown function call\");");
    decrease_offset();
    print_line("}");
    decrease_offset();
    print_line("}");

    decrease_offset();
    print_line("");
    print_line("private:");
    increase_offset();

    print_line("Interface* impl = nullptr;");

    finish_class();


    start_class(c.get_name() + "Processor", "NetCoworkFactory");

    print_line("typedef " + sync_class + " SyncObj;");

    print_line(current_class + "(NetCoworkProvider* _provider) :");
    increase_offset();
    print_line("NetCoworkFactory(_provider)");
    decrease_offset();
    print_line("{}");
    print_line("");

    print_line("SyncObj* get_object()");
    print_line("{");
    increase_offset();
    print_line("uint32_t cnt = counter++;");
    print_line("Message m;");
    print_line("m.add_value(cnt);");
    print_line("send_func_call(m);");
    print_line("auto* obj = new " + c.get_name() + "Sync(this, cnt, generate_object());");
    print_line("add_object(obj);");
    print_line("return obj;");
    decrease_offset();
    print_line("}");
    print_line("");
    print_line("NetCoworker* create_object(uint32_t object_id) const");
    print_line("{");
    increase_offset();
    print_line("counter = object_id + 1;");
    print_line("auto* obj = new " + sync_class + "(this, object_id, generate_object());");
    print_line("return obj;");
    decrease_offset();
    print_line("}");
    print_line("");
    print_line("std::string get_name() const");
    print_line("{");
    increase_offset();
    print_line("return \"" + c.get_name() + "\";");
    decrease_offset();
    print_line("}");
    print_line("");
    print_line("Message get_sync_message(NetCoworker* obj) const");
    print_line("{");
    increase_offset();
    print_line("SyncObj* sync_obj = dynamic_cast<SyncObj*>(obj);");
    print_line("if (!sync_obj)");
    increase_offset();
    print_line("return Message();");
    decrease_offset();
    print_line("Message msg;");
    print_line("msg.set_metadata(get_class_id(), obj->get_object_id());");
    print_line("msg.add_value<uint32_t>(0);");

    for (const Property& property : c.get_properties())
    {
        print_line("msg.add_value(sync_obj->" + property.getter + "());");
    }

    print_line("return msg;");
    decrease_offset();
    print_line("}");
    print_line("");
    print_line("void sync(NetCoworker* obj, Message& msg) const");
    print_line("{");
    increase_offset();
    print_line("SyncObj* sync_obj = dynamic_cast<SyncObj*>(obj);");
    print_line("if (!sync_obj)");
    increase_offset();
    print_line("std::logic_error(\"Wrong object type in NetObjectProcessor\");");
    decrease_offset();

    for (const Property& property : c.get_properties())
    {
        switch (property.parameter.element->get_type())
        {
        case Type_enum::STRING:
            print_line("sync_obj->get_impl()->" + property.setter + "(msg.get_string());");
            break;
        default:
            print_line("sync_obj->get_impl()->" + property.setter + "(msg.get_value<" + get_type_name(property.parameter.element) + ">());");
            break;
        }
    }

    decrease_offset();
    print_line("}");

    decrease_offset();
    print_line("");
    print_line("private:");
    increase_offset();

    print_line("static uint32_t counter;");

    finish_class();


    print_line(sync_function + sync_class + "(const " + processor_class + "<" + c.get_name() + ">* _proc, uint32_t object_id, " + c.get_name() + "* obj) :");
    increase_offset();
    print_line("NetCoworker(_proc, object_id),");
    print_line("impl(obj)");
    decrease_offset();
    print_line("{}");
    print_line("");
    print_line("");
    print_line("#endif");

    return true;
}

void Printer::print_line(const std::string& line)
{
    current_file << offset << line << std::endl;
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
        throw std::logic_error("unknown type in printer");
    }
}

void Printer::start_class(const std::string& name, const std::string& parent, const std::string& parent2)
{
    print_line("");
    print_line("template<class NetObject>");
    print_line("class " + name + (parent.empty() ? "" : (" : public " + parent + (parent2.empty() ? "" : (", public " + parent2)))));
    print_line("{");
    print_line("public:");
    increase_offset();

    current_class = name;
}

void Printer::print_function(const CodeElement* ret_type, const std::string& func_name,
                             const std::vector<Parameter>& parameters, bool is_const, const std::string& class_name)
{
    print_function(get_type_name(ret_type), func_name, parameters, is_const, class_name);
}

void Printer::print_function(const std::string& ret_type, const std::string& func_name,
                             const std::vector<Parameter>& parameters, bool is_const,  const std::string& class_name)
{
    std::string line;
    line += ret_type + " ";
    if (class_name.length() > 0)
        line += class_name + "::";
    line += func_name + "(";
    for (const Parameter& param : parameters)
        line += get_parameter_str(param);

    if (!parameters.empty())
    {
        line.pop_back();
        line.pop_back();
    }

    line += ")";

    if (is_const)
        line += " const";

    print_line(line);
}

std::string Printer::get_parameter_str(const Parameter& param)
{
    std::string res;

    const CodeElement* element = param.element;
    bool as_ref = element->get_type() == Type_enum::STRING || element->get_type() == Type_enum::STRUCT;
    if (as_ref)
        res += "const ";
    res += get_type_name(element);
    if (as_ref)
        res += "& ";
    else
        res += " ";
    res += param.value_name;
    res += " ,";

    return res;
}

void Printer::finish_class()
{
    decrease_offset();
    print_line("};");
}
