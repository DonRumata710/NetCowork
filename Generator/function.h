#ifndef FUNCTION_H
#define FUNCTION_H

#include "types.h"
#include "codeelement.h"
#include "parameter.h"

#include <vector>


class Function : public CodeElement
{
public:
    explicit Function(const std::string& name);

    void add_param(const Parameter& type);

    const Parameter* get_param(size_t i) const;

    size_t get_params_count() const;

    const std::vector<Parameter>& get_parameters() const;

private:
    std::vector<Parameter> params;
};

#endif // FUNCTION_H
