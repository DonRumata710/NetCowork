#include "game.h"

#include "netcoworkserver.h"
#include "netcoworkclient.h"

#include <QPainter>
#include <QGraphicsScene>
#include <QKeyEvent>


Game* Game::instance(nullptr);


template<>
Ball* BallProcessor<Ball>::generate_object() const
{
    Ball* ball = new Ball;
    Game::get_instance()->add_item(ball);
    ball->set_pos({ int(Game::get_instance()->sceneRect().width() / 2), int(Game::get_instance()->sceneRect().height() / 2) });
    return ball;
}


template<>
Platform* PlatformProcessor<Platform>::generate_object() const
{
    Platform* platform = new Platform;
    Game::get_instance()->add_item(platform);
    platform->set_h_pos(480);
    return platform;
}


Game::Game(QWidget* parent) :
    QGraphicsView(parent)
{
    if (instance)
        throw std::logic_error("Several instances of Game");

    instance = this;

    setScene(new QGraphicsScene);  /// Устанавливаем графическую сцену в graphicsView
    setRenderHint(QPainter::Antialiasing);    /// Устанавливаем сглаживание
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по горизонтали

    scene()->setSceneRect(0, 0, 500, 500);
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
            platform->get_impl()->set_h_pos(480);
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
                bs->get_impl()->update();
            }
        }
        else if (class_id == platform_processor->get_class_id())
        {
            PlatformSync<Platform>* ps = dynamic_cast<PlatformSync<Platform>*>(p_obj);
            if (ps)
            {
                enemy_platform = ps;
                enemy_platform->get_impl()->set_h_pos(10);
                ps->get_impl()->update();
            }
        }
    });

    connect(&timer, &QTimer::timeout, this, &Game::step);
    timer.start(100);
}

void Game::step()
{
    if (!platform)
        return;

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
        qDebug() << "right button is on";
    }
    if (event->key() == Qt::Key::Key_Left || event->key() == Qt::Key::Key_A)
    {
        left_button = true;
        qDebug() << "left button is on";
    }
}

void Game::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key::Key_Right || event->key() == Qt::Key::Key_D)
    {
        right_button = false;
        qDebug() << "right button is off";
    }
    if (event->key() == Qt::Key::Key_Left || event->key() == Qt::Key::Key_A)
    {
        left_button = false;
        qDebug() << "left button is off";
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
