#include "game.h"

#include "netcoworkserver.h"
#include "netcoworkclient.h"


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

void Game::start(uint16_t port, const QString& addr)
{
    if (addr.isNull())
        create_server(port);
    else
        create_client(addr, port);

    ball_processor = provider->register_new_class<BallProcessor<Ball>>();
    platform_processor = provider->register_new_class<PlatformProcessor<Platform>>();


    provider->set_add_object_callback([this](NetCoworker* p_obj, uint32_t class_id, uint32_t obj_id){
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
    provider.reset(server);
}

void Game::create_client(const QString& addr, uint16_t port)
{
    NetCoworkClient* client = new NetCoworkClient;
    client->start(addr.toStdString(), port);
    provider.reset(client);
}
