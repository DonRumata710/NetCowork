#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <stack>

#include "interfacemodel.h"
#include "filehandler.h"


class ParseError : public std::runtime_error
{
public:
    ParseError(const std::string& msg) :
        std::runtime_error(msg)
    {}
};


class Parser
{
public:
    Parser(const std::vector<std::string>& start_files, const std::string& output_folder);

    InterfaceModel parse();

private:
    bool parse_file(FileHandler& handler);
    bool parse_word(std::string& word);

    bool parse_class(Class* current_class);
    bool parse_function(Function* current_function);
    bool parse_struct(Struct* current_struct);
    bool parse_enum(Enum* current_enum);

    bool parse_property(Property& property);

private:
    std::vector<std::string> start_files;
    std::string output_folder;
    InterfaceModel model;

    enum class State
    {
        NONE,
        CLASS,
        CLASS_DEFINITION,
        STRUCT,
        STRUCT_DEFINITION,
        PROPERTY,
        FUNCTION,
        PARAMETER
    };

    State state;
    FileHandler* handler;
};

#endif // GENERATOR_H
