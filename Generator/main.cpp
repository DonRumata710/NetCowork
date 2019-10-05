#include <iostream>

#include "parser.h"


int main(int argc, char** argv)
{
    std::vector<std::string> input;
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

    Parser g(input, output_folder);

    return 0;
}
