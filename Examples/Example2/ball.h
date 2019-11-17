#ifndef BALL_H
#define BALL_H

#include <QPoint>
#include <QObject>
#include <QGraphicsItem>


class Ball : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    Ball(QPoint pos = QPoint());

    void set_pos(QPoint new_pos);
    QPoint get_pos() const;

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QPoint pos;
};

#endif // BALL_H
