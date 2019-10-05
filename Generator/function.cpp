#include "function.h"

Function::Function(const std::string& name) :
    CodeElement (Type_enum::FUNCTION, name)
{}

void Function::add_param(const Parameter& param)
{
    params.push_back(param);
}

const Parameter* Function::get_param(size_t i) const
{
    return &params[i];
}

size_t Function::get_params_count() const
{
    return params.size();
}

const std::vector<Parameter>& Function::get_parameters() const
{
    return params;
}
