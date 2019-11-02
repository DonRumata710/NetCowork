#ifndef DEPENDENCY_H
#define DEPENDENCY_H

#include <string>

#include "codeelement.h"


class Dependency : public CodeElement
{
public:
    Dependency(const std::string& _filename, const std::string& _type_name, Type_enum _type);

    virtual std::string get_module() const override;

private:
    std::string filename;
};


#endif // DEPENDENCY_H
