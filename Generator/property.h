#ifndef PROPERTY_H
#define PROPERTY_H

#include "parameter.h"


struct Property
{
    Parameter parameter;
    std::string getter;
    std::string setter;
};

#endif // PROPERTY_H
