#include "ball.h"

#include <QPainter>


Ball::Ball(QPointF _pos) : QGraphicsEllipseItem(-get_radius(), -get_radius(), get_radius() * 2, get_radius() * 2)
{
    setPos(_pos);
    setPen(QPen(Qt::black, 2));
    setBrush(Qt::red);
}

void Ball::set_pos(QPointF new_pos)
{
    setPos(new_pos);
    update(boundingRect());
}

QPointF Ball::get_pos() const
{
    return pos();
}

void Ball::set_direction(float new_direction)
{
    setRotation(static_cast<double>(new_direction));
}

float Ball::get_direction() const
{
    return static_cast<float>(rotation());
}

void Ball::set_speed(float new_speed)
{
    speed = new_speed;
}

float Ball::get_speed() const
{
    return speed;
}

float Ball::get_radius()
{
    return 10.0f;
}
