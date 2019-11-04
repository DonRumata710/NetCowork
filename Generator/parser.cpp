#include "parser.h"

#include "types.h"

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <sstream>


Parser::Parser(const std::vector<std::string>& _start_files, const std::string& _output_folder) :
    start_files(_start_files),
    output_folder(_output_folder)
{}

InterfaceModel Parser::parse()
{
    for (const std::string& filename : start_files)
    {
        FileHandler file(filename);
        if (!file.is_open())
        {
            std::cout << "Cannot open file " << filename << std::endl;
            continue;
        }

        if (!parse_file(file))
        {
            std::cout << " - line " << file.get_line_num() << " in file " << filename << " \n";
            return model;
        }
    }

    return model;
}

bool Parser::parse_file(FileHandler& current_handler)
{
    handler = &current_handler;
    while(true)
    {
        std::string word = handler->next_word();
        if (word.empty())
            break;

        auto it_token = Token_from_str.find(word);
        if (it_token == Token_from_str.end())
        {
            std::cout << "unknown symbol";
            return false;
        }

        switch(it_token->second)
        {
        case TOKEN_IMPORT:
            if (!parse_dependency())
                return false;
            break;
        case TOKEN_CLASS:
            if (!parse_class(model.add_class(Class(handler->next_word()))))
                return false;
            break;
        case TOKEN_STRUCT:
            if (!parse_struct(model.add_struct(Struct(handler->next_word()))))
                return false;
            break;
        case TOKEN_ENUM:
            if (!parse_enum(model.add_enumeration(Enum(handler->next_word()))))
                return false;
            break;
        case TOKEN_FUNCTION:
            if (!parse_function(model.add_function(Function(handler->next_word()))))
                return false;
            break;
        default:
            std::cout << "unexpected symbol";
            return false;
        }
    }

    return true;
}

bool Parser::parse_dependency()
{
    auto it_token = Token_from_str.find(handler->next_word());
    if (it_token == Token_from_str.end())
    {
        std::cout << "unexpected symbol after import";
        return false;
    }

    Type_enum type;

    switch(it_token->second)
    {
    case TOKEN_CLASS:
        type = Type_enum::CLASS;
        break;
    case TOKEN_STRUCT:
        type = Type_enum::STRUCT;
        break;
    case TOKEN_ENUM:
        type = Type_enum::ENUM;
        break;
    default:
        std::cout << "unexpected import type";
    }

    std::string file_name = handler->next_word();
    std::string type_name = file_name;

    it_token = Token_from_str.find(handler->next_word());
    if (it_token == Token_from_str.end())
    {
        std::cout << "unexpected symbol after import";
        return false;
    }

    if (it_token->second == TOKEN_DOT)
    {
        type_name = handler->next_word();

        it_token = Token_from_str.find(handler->next_word());
        if (it_token == Token_from_str.end() || it_token->second != TOKEN_SEMICOLON)
        {
            std::cout << "unexpected symbol after import '" << type_name << "', ';' expected";
            return false;
        }
    }
    else if (it_token->second != TOKEN_SEMICOLON)
    {
        std::cout << "unexpected symbol after import '" << type_name << "', ';' or '.' expected";
        return false;
    }

    model.add_dependency(Dependency(file_name, type_name, type));

    return true;
}

bool Parser::parse_class(Class* current_class)
{
    auto it_token = Token_from_str.find(handler->next_word());
    if (it_token->second != TOKEN_OPENING_BRACE)
    {
        std::cout << "wrong syntax after class declaration '" << current_class->get_name() << "'";
        return false;
    }

    while(true)
    {
        std::string word = handler->next_word();

        it_token = Token_from_str.find(word);
        if (it_token != Token_from_str.end())
        {
            if (it_token->second == TOKEN_CLOSING_BRACE)
            {
                break;
            }
            else if (it_token->second == TOKEN_FUNCTION)
            {
                Function func(handler->next_word());
                if (!parse_function(&func))
                {
                    std::cout << " in class '" << current_class->get_name() << "'";
                    return false;
                }
                current_class->add_function(func);
            }
        }
        else
        {
            const CodeElement* type = model.get_type(word);
            if (type == nullptr)
            {
                std::cout << "unknown parameter type in class '" << current_class->get_name() << "'";
                return false;
            }

            Property prop;
            prop.parameter = { type, handler->next_word() };

            if (!parse_property(prop))
                return false;

            current_class->add_property(prop);
        }
    }

    it_token = Token_from_str.find(handler->next_word());
    if (it_token == Token_from_str.end() || it_token->second != TOKEN_SEMICOLON)
    {
        std::cout << "unexpected symbol after delaration of class '" << current_class->get_name() << "', ';' expected";
        return false;
    }

    return true;
}

bool Parser::parse_function(Function* current_function)
{
    auto it_token = Token_from_str.find(handler->next_word());
    if (it_token->second != TOKEN_OPENING_PARENTHESIS)
    {
        std::cout << "wrong syntax after function declaration '" << current_function->get_name() << "'";
        return false;
    }

    while(true)
    {
        std::string word = handler->next_word();

        it_token = Token_from_str.find(word);
        if (it_token != Token_from_str.end() && it_token->second == TOKEN_CLOSING_PARENTHESIS)
        {
            break;
        }
        else
        {
            const CodeElement* type = model.get_type(word);
            if (type == nullptr)
            {
                std::cout << "unknown type of " << current_function->get_params_count() + 1 << " argument of function '" << current_function->get_name() << "'";
                return false;
            }
            current_function->add_param({ type, handler->next_word() });

            it_token = Token_from_str.find(handler->next_word());
            if (it_token == Token_from_str.end())
            {
                std::cout << "unknown symbol after " << current_function->get_params_count() << " argument of function '" << current_function->get_name() << "'";
                return false;
            }

            if (it_token->second == TOKEN_CLOSING_PARENTHESIS)
            {
                break;
            }

            if (it_token->second != TOKEN_COMMA)
            {
                std::cout << "unexpected symbol after " << current_function->get_params_count() << " argument of function '" << current_function->get_name() << "'";
                return false;
            }
        }
    }

    it_token = Token_from_str.find(handler->next_word());
    if (it_token == Token_from_str.end() || it_token->second != TOKEN_SEMICOLON)
    {
        std::cout << "unexpected symbol after delaration of function '" << current_function->get_name() << "', expected ';'";
    }

    return true;
}

bool Parser::parse_struct(Struct* current_struct)
{
    auto it_token = Token_from_str.find(handler->next_word());
    if (it_token->second != TOKEN_OPENING_BRACE)
    {
        std::cout << "wrong syntax after struct declaration '" << current_struct->get_name() << "'";
        return false;
    }

    while(true)
    {
        std::string word = handler->next_word();

        it_token = Token_from_str.find(word);
        if (it_token->second == TOKEN_CLOSING_BRACE)
        {
            break;
        }
        else
        {
            const CodeElement* type = model.get_type(word);
            if (type == nullptr)
            {
                std::cout << "unknown type";
                return false;
            }
            current_struct->add_member({ type, handler->next_word() });
        }
    }

    it_token = Token_from_str.find(handler->next_word());
    if (it_token == Token_from_str.end() || it_token->second != TOKEN_SEMICOLON)
    {
        std::cout << "unexpected symbol after delaration of struct '" << current_struct->get_name() << "', ';' expected";
    }

    return true;
}

bool Parser::parse_enum(Enum* current_enum)
{
    auto it_token = Token_from_str.find(handler->next_word());
    if (it_token->second != TOKEN_OPENING_BRACE)
    {
        std::cout << "unexpected symbol after enum declaration '" << current_enum->get_name() << "'";
        return false;
    }

    int value = 0;
    while(true)
    {
        std::string word = handler->next_word();

        it_token = Token_from_str.find(word);
        if (it_token->second == TOKEN_CLOSING_BRACE)
        {
            break;
        }
        else
        {
            std::string name = handler->next_word();
            it_token = Token_from_str.find(handler->next_word());
            if (it_token->second == TOKEN_ASSIGNMENT)
            {
                value = atoi(handler->next_word().c_str());
                it_token = Token_from_str.find(handler->next_word());
            }
            if (it_token->second != TOKEN_COMMA)
            {
                std::cout << "unexpected symbol in enum definition '" << current_enum->get_name() << "'";
                return false;
            }
            current_enum->add_value(name, value++);
        }
    }

    it_token = Token_from_str.find(handler->next_word());
    if (it_token == Token_from_str.end() || it_token->second != TOKEN_SEMICOLON)
    {
        std::cout << "unexpected symbol after delaration of enumeration '" << current_enum->get_name() << "', ';' expected";
    }

    return true;
}

bool Parser::parse_property(Property& property)
{
    auto it_token = Token_from_str.find(handler->next_word());
    if (it_token == Token_from_str.end())
    {
        std::cout << "unknown symbol in declaration of property '" << property.parameter.value_name << "'";
        return false;
    }

    if (it_token->second == TOKEN_SEMICOLON)
    {
        property.setter = "set_" + property.parameter.value_name;
        property.getter = "get_" + property.parameter.value_name;
        return true;
    }

    if (it_token->second != TOKEN_OPENING_BRACE)
    {
        std::cout << "unexpected symbol in declaration of property '" << property.parameter.value_name << "'";
        return false;
    }

    it_token = Token_from_str.find(handler->next_word());
    if (it_token == Token_from_str.end())
    {
        std::cout << "wrong syntax of property declaration '" << property.parameter.value_name << "', expected 'get' or 'set', got '" << it_token->first << "'";
        return false;
    }

    while(true)
    {
        if (it_token->second == Token_enum::TOKEN_GETTER)
        {
            it_token = Token_from_str.find(handler->next_word());
            if (it_token == Token_from_str.end())
            {
                std::cout << "wrong syntax in declaration of getter '" << property.parameter.value_name << "', expected ':', got '" << it_token->first << "'";
                return false;
            }

            property.getter = handler->next_word();
        }
        else if (it_token->second == Token_enum::TOKEN_SETTER)
        {
            it_token = Token_from_str.find(handler->next_word());
            if (it_token == Token_from_str.end())
            {
                std::cout << "wrong syntax in declaration of setter '" << property.parameter.value_name << "', expected ':', got '" << it_token->first << "'";
                return false;
            }

            property.setter = handler->next_word();
        }
        else
        {
            std::cout << "unexpected symbol in declaration of property '" << property.parameter.value_name << "', expected 'get' or 'set', got '" << it_token->first << "'";
            return false;
        }

        it_token = Token_from_str.find(handler->next_word());
        if (it_token == Token_from_str.end())
        {
            std::cout << "wrong syntax in declaration of property '" << property.parameter.value_name << "'";
            return false;
        }

        if (it_token->second == TOKEN_CLOSING_BRACE)
            break;

        if (it_token->second == TOKEN_COMMA)
        {
            it_token = Token_from_str.find(handler->next_word());
            continue;
        }

        std::cout << "unexpected symbol in declaration of property '" << property.parameter.value_name << "'";
        return false;
    }

    it_token = Token_from_str.find(handler->next_word());
    if (it_token == Token_from_str.end() || it_token->second != TOKEN_SEMICOLON)
    {
        std::cout << "unexpected symbol after delaration of property '" << property.parameter.value_name << "', expected ';'";
    }

    return true;
}
