#ifndef CODEELEMENT_H
#define CODEELEMENT_H

#include "types.h"


class CodeElement
{
    friend std::hash<CodeElement>;

public:
    CodeElement(Type_enum _type, const std::string& _name);
    CodeElement(const CodeElement& ce);
    CodeElement(CodeElement&& other);
    virtual ~CodeElement() = default;

    Type_enum get_type() const;
    const std::string& get_name() const;

    virtual std::string get_module() const { return ""; }

private:
    const Type_enum type;
    const std::string name;
};


#endif // CODEELEMENT_H
