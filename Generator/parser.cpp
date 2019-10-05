#include "parser.h"

#include "types.h"

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <sstream>


static std::unordered_map<std::string, Token_enum> tokens = {
    { "class", Token_enum::CLASS },
    { "struct", Token_enum::STRUCT },
    { "enum", Token_enum::ENUM },
    { "function", Token_enum::FUNCTION },
    { "{", Token_enum::OPENING_BRACE },
    { "}", Token_enum::CLOSING_BRACE },
    { "(", Token_enum::OPENING_PARENTHESIS },
    { ")", Token_enum::CLOSING_PARENTHESIS }
};


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

        auto it_token = tokens.find(word);
        if (it_token == tokens.end())
            return false;

        switch(it_token->second)
        {
        case Token_enum::CLASS:
            if (!parse_class(model.add_class(Class(handler->next_word()))))
                return false;
            break;
        case Token_enum::STRUCT:
            if (!parse_struct(model.add_struct(Struct(handler->next_word()))))
                return false;
            break;
        case Token_enum::ENUM:
            if (!parse_enum(model.add_enumeration(Enum(handler->next_word()))))
                return false;
            break;
        case Token_enum::FUNCTION:
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
    auto it_token = tokens.find(handler->next_word());
    if (it_token->second != Token_enum::OPENING_BRACE)
    {
        std::cout << "wrong syntax after class declaration '" << current_class->get_name() << "'";
        return false;
    }

    while(true)
    {
        std::string word = handler->next_word();

        it_token = tokens.find(word);
        if (it_token->second == Token_enum::CLOSING_BRACE)
        {
            break;
        }
        else if (it_token->second == Token_enum::FUNCTION)
        {
            Function func(handler->next_word());
            if (!parse_function(&func))
                return false;
            current_class->add_function(func);
        }
        else
        {
            const CodeElement* type = model.get_type(word);
            if (type == nullptr)
            {
                std::cout << "unknown type";
                return false;
            }
            current_class->add_member({ type, handler->next_word() });
        }
    }

    return true;
}

bool Parser::parse_function(Function* current_function)
{
    auto it_token = tokens.find(handler->next_word());
    if (it_token->second != Token_enum::OPENING_PARENTHESIS)
    {
        std::cout << "wrong syntax after function declaration '" << current_function->get_name() << "'";
        return false;
    }

    while(true)
    {
        std::string word = handler->next_word();

        it_token = tokens.find(word);
        if (it_token->second == Token_enum::CLOSING_PARENTHESIS)
        {
            break;
        }
        else
        {
            const CodeElement* type = model.get_type(word);
            if (type == nullptr)
            {
                std::cout << "unknown type of " << current_function->get_params_count() + 1 << " argument of function " << current_function->get_name();
                return false;
            }
            current_function->add_param({ type, handler->next_word() });

            it_token = tokens.find(handler->next_word());
            if (it_token->second != Token_enum::COMMA)
            {
                std::cout << "unexpected symbol after " << current_function->get_params_count() << " argument of function " << current_function->get_name();
            }
        }
    }

    return true;
}

bool Parser::parse_struct(Struct* current_struct)
{
    auto it_token = tokens.find(handler->next_word());
    if (it_token->second != Token_enum::OPENING_BRACE)
    {
        std::cout << "wrong syntax after struct declaration '" << current_struct->get_name() << "'";
        return false;
    }

    while(true)
    {
        std::string word = handler->next_word();

        it_token = tokens.find(word);
        if (it_token->second == Token_enum::CLOSING_BRACE)
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

    return true;
}

bool Parser::parse_enum(Enum* current_enum)
{
    auto it_token = tokens.find(handler->next_word());
    if (it_token->second != Token_enum::OPENING_BRACE)
    {
        std::cout << "unexpected symbol after enum declaration '" << current_enum->get_name() << "'";
        return false;
    }

    int value = 0;
    while(true)
    {
        std::string word = handler->next_word();

        it_token = tokens.find(word);
        if (it_token->second == Token_enum::CLOSING_BRACE)
        {
            break;
        }
        else
        {
            std::string name = handler->next_word();
            it_token = tokens.find(handler->next_word());
            if (it_token->second == Token_enum::ASSIGNMENT)
            {
                value = atoi(handler->next_word().c_str());
                it_token = tokens.find(handler->next_word());
            }
            if (it_token->second != Token_enum::COMMA)
            {
                std::cout << "unexpected symbol in enum definition '" << current_enum->get_name() << "'";
                return false;
            }
            current_enum->add_value(name, value++);
        }
    }

    return true;
}
