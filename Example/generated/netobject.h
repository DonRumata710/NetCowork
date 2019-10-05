#ifndef NETOBJECT_H
#define NETOBJECT_H


#include <stdint.h>
#include <string>


class iNetObject
{
public:
    virtual ~iNetObject() = default;

    virtual void setPos(int32_t x, int32_t y) = 0;

    virtual void set_x(int32_t new_x) = 0;

    virtual void set_y(int32_t new_y) = 0;

    virtual void set_button_name(const std::string& new_button_name) = 0;

    virtual int32_t get_x() const = 0;

    virtual int32_t get_y() const = 0;

    virtual std::string get_button_name() const = 0;
};


#endif // NETOBJECT_H
