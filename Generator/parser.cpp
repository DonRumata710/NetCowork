#include "parser.h"

#include "types.h"

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <sstream>


//static std::unordered_map<std::string, Token_enum> tokens = {
//    { "class", Token_enum::CLASS },
//    { "struct", Token_enum::STRUCT },
//    { "enum", Token_enum::ENUM },
//    { "function", Token_enum::FUNCTION },
//    { "{", Token_enum::OPENING_BRACE },
//    { "}", Token_enum::CLOSING_BRACE },
//    { "(", Token_enum::OPENING_PARENTHESIS },
//    { ")", Token_enum::CLOSING_PARENTHESIS }
//};


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
            std::cout << " line " << file.get_line_num() << " in file " << filename << " \n";
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
            current_class->add_member({ type, handler->next_word() });

            it_token = Token_from_str.find(handler->next_word());
            if (it_token == Token_from_str.end() || it_token->second != TOKEN_SEMICOLON)
            {
                std::cout << "unexpected symbol after parameter of class '" << current_class->get_name() << "', ';' expected";
            }
        }
    }

    it_token = Token_from_str.find(handler->next_word());
    if (it_token == Token_from_str.end() || it_token->second != TOKEN_SEMICOLON)
    {
        std::cout << "unexpected symbol after delaration of class '" << current_class->get_name() << "', ';' expected";
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
        std::cout << "unexpected symbol after delaration of function '" << current_function->get_name() << "', ';' expected";
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
