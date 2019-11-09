#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QHostAddress>
#include <QPaintEvent>

#include "generated/Ball_net.h"
#include "generated/Platform_net.h"


#include "ball.h"
#include "platform.h"


class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();

signals:

public slots:
    void start(uint16_t port, const QString& addr);

private:
    void create_server(uint16_t port);
    void create_client(const QString& addr, uint16_t port);

    virtual void paintEvent(QPaintEvent *event) override;

    void drawPlatform(int16_t pos, QPainter& painter, int step, bool on_top);

private:
    std::unique_ptr<NetCoworkProvider> provider;
    std::vector<BallSync<Ball>*> balls;
    BallProcessor<Ball>* ball_processor = nullptr;
    PlatformSync<Platform>* platform = nullptr;
    PlatformSync<Platform>* enemy_platform = nullptr;
    PlatformProcessor<Platform>* platform_processor = nullptr;
};

#endif // GAME_H
