#include "ball.h"

Ball::Ball(QPoint _pos) : pos(_pos)
{}

void Ball::set_pos(QPoint new_pos)
{
    pos = new_pos;
}

QPoint Ball::get_pos() const
{
    return pos;
}
