#include "filehandler.h"

#include <iostream>


FileHandler::FileHandler(const std::string& file) :
    file_stream(file),
    filename(file)
{}

bool FileHandler::is_open() const
{
    return file_stream.is_open();
}

std::string FileHandler::next_word()
{
    if (word.empty())
    {
        if (!line_stream.good())
        {
            ++line_num;
            std::getline(file_stream, line);
            line_stream = std::istringstream(line);
        }

        line_stream >> word;
    }

    char letter = word[0];
    if (!isalpha(letter))
    {
        if (isdigit(letter))
        {
            std::string num;
            size_t i = 0;
            do
            {
                num.push_back(word[i]);
                ++i;
            }
            while(isdigit(word[i]));
            word.erase(0, i);
            return num;
        }

        word.erase(word.begin());
        return std::string(1, letter);
    }
    else
    {
        std::string res;
        size_t i = 0;
        do
        {
            res.push_back(word[i]);
        }
        while (isalnum(word[i]));

        word.erase(0, i);
        return res;
    }
}

const std::string& FileHandler::get_filename() const
{
    return filename;
}

size_t FileHandler::get_line_num() const
{
    return line_num;
}
