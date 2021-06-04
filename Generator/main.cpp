#include <iostream>
#include <filesystem>

#include "interface.lexer.hpp"
#include "interface.parser.hpp"
#include "printer.h"


int main(int argc, char** argv)
{
    std::vector<std::filesystem::path> input;
    std::string output_folder;

    for(int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-i") == 0)
        {
            for(; i < argc && argv[i + 1][0] != '-'; ++i)
                input.push_back(argv[i + 1]);
            --i;
        }
        else if (strcmp(argv[i], "-o") == 0)
        {
            output_folder = argv[i + 1];
            ++i;
        }
    }

    if (input.empty())
    {
        std::cout << "There is nothing to parse\n";
        return -1;
    }

    if (output_folder.empty())
        output_folder = ".";

    try
    {
        for (const auto& filename : input)
        {
            InterfaceModel model;
            std::vector<std::string> errors;

            if (!std::filesystem::exists(filename))
            {
                std::cerr << "File \"" << filename.string() << "\" does not exists";
                return -2;
            }

            std::ifstream file(filename);
            yy::scanner scanner(file, &std::cout);
            yy::parser parser(filename.parent_path().string(), scanner, model, errors);
            int res = parser.parse();
            if (res)
            {
                throw std::runtime_error("Parsing was failed with code " + std::to_string(res) + "\n");
            }

            Printer p(output_folder);
            model.print(p);
        }
    }
    catch (const std::exception& err)
    {
        std::cerr << err.what() << '\n';
        return -3;
    }

    return 0;
}
