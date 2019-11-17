#include "ball.h"

#include <QPainter>


Ball::Ball(QPoint _pos) : pos(_pos)
{}

void Ball::set_pos(QPoint new_pos)
{
    pos = new_pos;
    update(boundingRect());
}

QPoint Ball::get_pos() const
{
    return pos;
}

QRectF Ball::boundingRect() const
{
    return QRectF(pos + QPoint(10, 10) , QSize(20, 20));
}

void Ball::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setPen(QPen(Qt::red, 2));
    QPainterPath path;
    path.addEllipse(boundingRect());
    painter->drawPath(path);
}
