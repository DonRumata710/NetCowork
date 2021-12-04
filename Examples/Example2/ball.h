#ifndef BALL_H
#define BALL_H

#include <QPoint>
#include <QObject>
#include <QGraphicsEllipseItem>
#include <QDebug>


class Ball : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT

public:
    Ball(QPointF pos = QPointF());
    ~Ball() = default;

    void set_pos(QPointF new_pos);
    QPointF get_pos() const;

    void set_direction(float new_direction);

    float get_direction() const;

    void set_speed(float new_speed);

    float get_speed() const;

    static float get_radius();

private:
    float speed;
};

#endif // BALL_H
