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

private:
    std::string path;
    std::ofstream current_file;
    std::string offset;
};

#endif // PRINTER_H
