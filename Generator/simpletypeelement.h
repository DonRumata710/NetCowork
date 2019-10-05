#ifndef SIMPLETYPEELEMENT_H
#define SIMPLETYPEELEMENT_H

#include "types.h"
#include "codeelement.h"


class SimpleType : public CodeElement
{
public:
    explicit SimpleType(Type_enum type);

private:
    std::string get_typename(Type_enum type) const;
};


#endif // SIMPLETYPEELEMENT_H
