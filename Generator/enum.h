#ifndef ENUM_H
#define ENUM_H

#include "codeelement.h"

#include <map>


class Enum : public CodeElement
{
public:
    explicit Enum(const std::string& name);

    void add_value(const std::string& name, int64_t val);
    void add_value(std::string&& name, int64_t val);

    void add_value(const std::pair<std::string, int64_t>& val);
    void add_value(std::pair<std::string, int64_t>&& val);

    bool check_value(const std::string& name) const;
    int64_t get_value(const std::string& name) const;

private:
    std::map<std::string, int64_t> values;
};

#endif // ENUM_H
