#include "game.h"

#include "netcoworkserver.h"
#include "netcoworkclient.h"

#include <QPainter>


template<>
Ball* BallProcessor<Ball>::generate_object() const
{
    return new Ball;
}


template<>
Platform* PlatformProcessor<Platform>::generate_object() const
{
    return new Platform;
}


Game::Game(QWidget* parent) :
    QWidget(parent)
{}

Game::~Game()
{
    if (provider)
        provider->stop();
}

void Game::start(uint16_t port, const QString& addr)
{
    if (addr.isNull())
        create_server(port);
    else
        create_client(addr, port);

    provider->set_add_class_callback([this](NetCoworkFactory* factory, uint32_t class_id) {
        if (platform_processor == factory)
        {
            platform = platform_processor->get_object();
            platform->set_pos(50);
        }
    });

    provider->set_add_object_callback([this](NetCoworker* p_obj, uint32_t class_id, uint32_t obj_id) {
        qDebug() << "Object created id:" << obj_id << ", class:" << class_id;
        if (class_id == ball_processor->get_class_id())
        {
            BallSync<Ball>* bs = dynamic_cast<BallSync<Ball>*>(p_obj);
            if (bs)
            {
                balls.push_back(bs);
            }
        }
        else if (class_id == platform_processor->get_class_id())
        {
            PlatformSync<Platform>* ps = dynamic_cast<PlatformSync<Platform>*>(p_obj);
            if (ps)
            {
                enemy_platform = ps;
            }
        }
    });
}

void Game::create_server(uint16_t port)
{
    NetCoworkServer* server = new NetCoworkServer;
    server->start("*", port);
    server->set_creation_policy(NetCoworkServer::CreationPolicy::ALL);
    provider.reset(server);

    ball_processor = provider->register_new_class<BallProcessor<Ball>>();
    balls.push_back(ball_processor->get_object());

    platform_processor = provider->register_new_class<PlatformProcessor<Platform>>();
    platform = platform_processor->get_object();
    platform->set_pos(50);
}

void Game::create_client(const QString& addr, uint16_t port)
{
    NetCoworkClient* client = new NetCoworkClient;
    client->start(addr.toStdString(), port);
    provider.reset(client);

    ball_processor = provider->register_new_class<BallProcessor<Ball>>();
    platform_processor = provider->register_new_class<PlatformProcessor<Platform>>();
}

void Game::paintEvent(QPaintEvent* event)
{
    int step = width() / 40;

    QPainter painter(this);
    painter.setPen(Qt::GlobalColor::green);

    for (auto ball : balls)
        painter.drawEllipse(ball->get_pos(), step, step);

    painter.setPen(Qt::GlobalColor::blue);
    painter.setBrush(Qt::BrushStyle::SolidPattern);

    if (platform)
        drawPlatform(platform->get_pos(), painter, step, false);
    if (enemy_platform)
        drawPlatform(enemy_platform->get_pos(), painter, step, true);
}

void Game::drawPlatform(int16_t pos, QPainter& painter, int step, bool on_top)
{
    QPainterPath path;
    path.addRect(QRect(pos * width() / 100, on_top ? 20 : height() - 20, step * 4, 20));
    painter.drawPath(path);
}
