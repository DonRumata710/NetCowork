#include "platform.h"

#include <QPainter>
#include <QGraphicsScene>


Platform::Platform(uint16_t _pos) : pos(_pos)
{}

void Platform::set_field_size(int size)
{
    field_size = size;
}

void Platform::set_h_pos(int p)
{
    h_pos = p;
    update();
}

void Platform::set_pos(uint16_t new_pos)
{
    pos = new_pos;
    update();
}

uint16_t Platform::get_pos() const
{
    return pos;
}

uint16_t Platform::get_width()
{
    return width;
}

QRectF Platform::boundingRect() const
{
    return { qreal(pos), qreal(h_pos), qreal(get_width()), 10 };
}

void Platform::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setPen(QPen(Qt::black, 2));
    QPainterPath path;
    path.addRect(boundingRect());
    painter->drawPath(path);
}
