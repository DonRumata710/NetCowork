#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>
#include <sstream>


class FileHandler
{
public:
    FileHandler(const std::string& file);

    bool is_open() const;

    std::string next_word();

    const std::string& get_filename() const;
    size_t get_line_num() const;

private:
    std::ifstream file_stream;
    std::istringstream line_stream;
    std::string word;

    std::string filename;

    size_t line_num = 0;
    std::string line;
};

#endif
