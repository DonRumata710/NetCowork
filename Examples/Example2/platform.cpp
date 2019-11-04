#include "platform.h"

Platform::Platform(uint16_t _pos) : pos(_pos)
{}

void Platform::set_pos(uint16_t new_pos)
{
    pos = new_pos;
}

uint16_t Platform::get_pos() const
{
    return pos;
}
