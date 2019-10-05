#ifndef STRUCT_H
#define STRUCT_H

#include "codeelement.h"
#include "parameter.h"

#include <string>
#include <vector>


class Struct : public CodeElement
{
public:
    explicit Struct(const std::string& name);
    Struct(const Struct& other);
    Struct(Struct&& other);

    void add_member(const Parameter& param);

private:
    std::vector<Parameter> members;
};


#endif // TYPES_H
