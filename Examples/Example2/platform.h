#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>
#include <QGraphicsItem>

#include <cstdint>


class Platform : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    Platform(uint16_t pos = 0);

    void set_field_size(int size);
    void set_h_pos(int p);

    void set_field(QWidget* f);

    void set_pos(uint16_t new_pos);
    uint16_t get_pos() const;

    static uint16_t get_width();

protected:
    QRectF realRect() const;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    uint16_t pos = 0;
    int field_size = 0;
    int h_pos = 0;

    static const uint16_t width = 60;
};

#endif // PLATFORM_H
