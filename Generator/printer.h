#ifndef PRINTER_H
#define PRINTER_H

#include "class.h"
#include "struct.h"
#include "function.h"
#include "enum.h"

#include <string>
#include <fstream>


class Printer
{
public:
    explicit Printer(const std::string& folder_path = std::string());

    bool print_class(const Class& c);

private:
    void print_line(const std::string& line);
    void print_dependency(const std::string& type);

    void increase_offset();
    void decrease_offset();

    std::string get_type_name(const CodeElement* element);

    void start_class(const std::string& name, const std::string& parent = std::string(), const std::string& parent2 = std::string());
    void print_function(bool is_decl, const CodeElement* ret_type, const std::string& func_name,
                        const std::vector<Parameter>& parameters, bool is_const, const std::string& class_name = std::string());
    void print_function(bool is_decl, const std::string& ret_type, const std::string& func_name,
                        const std::vector<Parameter>& parameters, bool is_const, const std::string& class_name = std::string());
    std::string get_parameter_str(const Parameter& param);
    void finish_class();

private:
    std::string path;
    std::ofstream current_file;
    std::string offset;

    std::string current_class;
};

#endif // PRINTER_H
