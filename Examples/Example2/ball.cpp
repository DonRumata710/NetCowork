#include "ball.h"

#include <QPainter>

#define _USE_MATH_DEFINES
#include <math.h>


bool Ball::y_inversion(false);


Ball::Ball(QPointF _pos) : QGraphicsEllipseItem(-get_radius(), -get_radius(), get_radius() * 2, get_radius() * 2)
{
    setPos(_pos);
    setPen(QPen(Qt::black, 2));
    setBrush(Qt::red);
}

void Ball::set_pos(QPointF new_pos)
{
    if (y_inversion)
        new_pos.setY(-new_pos.ry());
    setPos(new_pos);
    update(boundingRect());
}

QPointF Ball::get_pos() const
{
    if (y_inversion)
    {
        QPointF realPos = pos();
        realPos.setY(-realPos.ry());
        return realPos;
    }
    return pos();
}

void Ball::set_direction(float new_direction)
{
    if (y_inversion)
    {
        double dir = (new_direction - 90) / 180 * M_PI;
        QPointF move_vector = QPointF(cos(dir), sin(dir));
        move_vector.setY(-move_vector.ry());
        setRotation(atan2(move_vector.ry(), move_vector.rx()) / M_PI * 180 + 90);
    }
    else
    {
        setRotation(static_cast<double>(new_direction));
    }
}

float Ball::get_direction() const
{
    if (y_inversion)
    {
        double dir = (rotation() - 90) / 180 * M_PI;
        QPointF move_vector = QPointF(cos(dir), sin(dir));
        move_vector.setY(-move_vector.ry());
        return static_cast<float>(atan2(move_vector.ry(), move_vector.rx()) / M_PI * 180 + 90);
    }
    else
    {
        return static_cast<float>(rotation());
    }
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

void Ball::set_y_inversion(bool state)
{
    y_inversion = state;
}
