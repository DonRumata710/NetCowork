#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QHostAddress>
#include <QPaintEvent>
#include <QTimer>

#include "generated/Ball_net.h"
#include "generated/Platform_net.h"


#include "ball.h"
#include "platform.h"


class Game : public QGraphicsView
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game() override;

    void add_item(QGraphicsItem* item);

    static Game* get_instance();

signals:

public slots:
    void start(uint16_t port, const QString& addr);

    void step();

private:
    void create_server(uint16_t port);
    void create_client(const QString& addr, uint16_t port);

    void drawPlatform(int16_t pos, QPainter& painter, int step, bool on_top);

    virtual void keyPressEvent(QKeyEvent* event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;

    void set_plarform_pos(int16_t pos);

    void game_inner_logic();

private:
    std::unique_ptr<NetCoworkProvider> provider;
    std::vector<BallSync<Ball>*> balls;
    BallProcessor<Ball>* ball_processor = nullptr;
    PlatformSync<Platform>* platform = nullptr;
    PlatformSync<Platform>* enemy_platform = nullptr;
    PlatformProcessor<Platform>* platform_processor = nullptr;
    QTimer timer;
    bool right_button = false;
    bool left_button = false;

    const static size_t TIME_STEP = 50;

    static Game* instance;
};

#endif // GAME_H
