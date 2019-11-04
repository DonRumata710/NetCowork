#ifndef PLATFORM_H
#define PLATFORM_H

#include <cstdint>


class Platform
{
public:
    Platform(uint16_t pos = 0);

    void set_pos(uint16_t new_pos);
    uint16_t get_pos() const;

private:
    uint16_t pos;
};

#endif // PLATFORM_H
