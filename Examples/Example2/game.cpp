#include "game.h"

#include "netcoworkserver.h"
#include "netcoworkclient.h"

#include <QPainter>
#include <QGraphicsScene>
#include <QKeyEvent>

#define _USE_MATH_DEFINES
#include <math.h>


Game* Game::instance(nullptr);


template<>
Ball* BallProcessor<Ball>::generate_object() const
{
    Ball* ball = new Ball;
    Game::get_instance()->add_item(ball);
    QPointF sceneCenter = Game::get_instance()->sceneRect().center();
    ball->set_pos({ sceneCenter.rx(), sceneCenter.ry() });
    ball->set_direction(rand() % 360);
    ball->set_speed(2.5);
    return ball;
}


template<>
Platform* PlatformProcessor<Platform>::generate_object() const
{
    Platform* platform = new Platform;
    Game::get_instance()->add_item(platform);
    platform->set_h_pos(230);
    return platform;
}


Game::Game(QWidget* parent) :
    QGraphicsView(parent)
{
    if (instance)
        throw std::logic_error("Several instances of Game");

    instance = this;

    setScene(new QGraphicsScene);
    setRenderHint(QPainter::Antialiasing);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene()->setSceneRect(0, -250, 500, 500);
}

Game::~Game()
{
    if (provider)
        provider->stop();
}

void Game::add_item(QGraphicsItem* item)
{
    scene()->addItem(item);
}

Game* Game::get_instance()
{
    return instance;
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
            platform->set_pos(sceneRect().width() / 2);
            platform->get_impl()->set_h_pos(230);
        }
    });

    provider->set_add_object_callback([this](NetCoworker* p_obj, uint32_t class_id, uint32_t obj_id) {
        qDebug() << "Object created id:" << obj_id << ", class:" << class_id;
        if (class_id == ball_processor->get_class_id())
        {
            BallSync<Ball>* bs = dynamic_cast<BallSync<Ball>*>(p_obj);
            if (bs)
            {
                Game::get_instance()->add_item(bs->get_impl());
                balls.push_back(bs);
                bs->get_impl()->update();
            }
        }
        else if (class_id == platform_processor->get_class_id())
        {
            PlatformSync<Platform>* ps = dynamic_cast<PlatformSync<Platform>*>(p_obj);
            if (ps)
            {
                enemy_platform = ps;
                enemy_platform->get_impl()->set_h_pos(-230);
                ps->get_impl()->update();
            }
        }
    });

    connect(&timer, &QTimer::timeout, this, &Game::step);
    timer.start(TIME_STEP);
}

void Game::step()
{
    if (!platform)
        return;

    game_inner_logic();

    int16_t pos = platform->get_pos();
    if (right_button && !left_button)
    {
        pos += 2;
        set_plarform_pos(pos);
    }
    else if (left_button && !right_button)
    {
        pos -= 2;
        set_plarform_pos(pos);
    }
}

void Game::create_server(uint16_t port)
{
    Ball::set_y_inversion(false);

    NetCoworkServer* server = new NetCoworkServer;
    server->start("*", port);
    server->set_creation_policy(NetCoworkServer::CreationPolicy::ALL);
    provider.reset(server);

    ball_processor = provider->register_new_class<BallProcessor<Ball>>();
    balls.push_back(ball_processor->get_object());

    platform_processor = provider->register_new_class<PlatformProcessor<Platform>>();
    platform = platform_processor->get_object();
    platform->set_pos(sceneRect().width() / 2);
}

void Game::create_client(const QString& addr, uint16_t port)
{
    Ball::set_y_inversion(true);

    NetCoworkClient* client = new NetCoworkClient;
    client->start(addr.toStdString(), port);
    provider.reset(client);

    ball_processor = provider->register_new_class<BallProcessor<Ball>>();
    platform_processor = provider->register_new_class<PlatformProcessor<Platform>>();
}

void Game::drawPlatform(int16_t pos, QPainter& painter, int step, bool on_top)
{
    QPainterPath path;
    path.addRect(QRect(pos * width() / 100, on_top ? 20 : height() - 20, step * 4, 20));
    painter.drawPath(path);
}

void Game::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key::Key_Right || event->key() == Qt::Key::Key_D)
    {
        right_button = true;
    }
    if (event->key() == Qt::Key::Key_Left || event->key() == Qt::Key::Key_A)
    {
        left_button = true;
    }
}

void Game::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key::Key_Right || event->key() == Qt::Key::Key_D)
    {
        right_button = false;
    }
    if (event->key() == Qt::Key::Key_Left || event->key() == Qt::Key::Key_A)
    {
        left_button = false;
    }
}

void Game::set_plarform_pos(int16_t pos)
{
    if (pos < 0)
        pos = 0;
    if (pos > sceneRect().width() - Platform::get_width())
        pos = sceneRect().width() - Platform::get_width();
    platform->set_pos(pos);
}

void Game::game_inner_logic()
{
    for (const auto& net_ball : balls)
    {
        auto ball = net_ball->get_impl();

        auto distance = ball->get_speed();
        auto new_pos = ball->mapToScene(0, -distance);
        float dir = (ball->get_direction() - 90) / 180 * M_PI;
        QPointF move_vector = QPointF(distance * cos(dir), distance * sin(dir));

        QRectF rect = scene()->sceneRect();

        bool right_collision = new_pos.rx() + Ball::get_radius() > rect.right();
        bool left_collision = new_pos.rx() - Ball::get_radius() < rect.left();
        bool top_collision = new_pos.ry() - Ball::get_radius() < rect.top();
        bool botton_collision = new_pos.ry() + Ball::get_radius() > rect.bottom();

        if (right_collision || left_collision)
        {
            move_vector.setX(-move_vector.rx());

            if (right_collision)
                new_pos.setX(rect.right() + rect.right() - new_pos.rx() - Ball::get_radius() - Ball::get_radius());
            else if (left_collision)
                new_pos.setX(rect.left() + rect.left() - new_pos.rx() + Ball::get_radius() + Ball::get_radius());
        }

        if (top_collision || botton_collision)
        {
            move_vector.setY(-move_vector.ry());

            if (top_collision)
                new_pos.setY(rect.top() + rect.top() - new_pos.ry() + Ball::get_radius() + Ball::get_radius());
            else if (botton_collision)
                new_pos.setY(rect.bottom() + rect.bottom() - new_pos.ry() - Ball::get_radius() - Ball::get_radius());
        }

        if (right_collision || left_collision || top_collision || botton_collision)
            ball->set_direction(atan2(move_vector.ry() / distance, move_vector.rx() / distance) / M_PI * 180 + 90);

        ball->setPos(new_pos);
    }
}
