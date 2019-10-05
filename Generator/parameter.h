#ifndef PARAMETER_H
#define PARAMETER_H

#include "types.h"
#include "codeelement.h"


struct Parameter
{
    const CodeElement* element;
    std::string value_name;
};


#endif // PARAMETERS_H
