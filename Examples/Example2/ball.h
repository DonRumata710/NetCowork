#ifndef BALL_H
#define BALL_H

#include <QPoint>


class Ball
{
public:
    Ball(QPoint pos = QPoint());

    void set_pos(QPoint new_pos);
    QPoint get_pos() const;

private:
    QPoint pos;
};

#endif // BALL_H
