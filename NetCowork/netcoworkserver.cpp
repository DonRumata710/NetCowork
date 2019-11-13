#include "netcoworkserver.h"

#include "netcoworker.h"
#include "netcoworkfactory.h"

#include <QDataStream>
#include <QDebug>


ClassFilter::ClassFilter(std::set<uint32_t> _private_classes) :
    private_classes(_private_classes)
{}

bool ClassFilter::allow(QTcpSocket* socket, uint32_t class_id)
{
    return private_classes.find(class_id) == private_classes.end();
}


NetCoworkServer::NetCoworkServer()
{
    connect(this, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

void NetCoworkServer::start(const std::string& address, uint16_t port)
{
    if (!listen(QHostAddress(address.c_str()), port))
        qCritical() << "Listen failed";
}

void NetCoworkServer::stop()
{
    close();
}

void NetCoworkServer::set_creation_policy(NetCoworkServer::CreationPolicy new_policy)
{
    policy = new_policy;
}

bool NetCoworkServer::set_filter(std::unique_ptr<CreationFilter> new_filter)
{
    if (policy == CreationPolicy::CUSTOM)
    {
        filter.swap(new_filter);
        return true;
    }
    else
    {
        return false;
    }
}

void NetCoworkServer::onNewConnection()
{
    QTcpSocket* socket = nextPendingConnection();
    sockets.push_back(socket);
    connect(socket, &QTcpSocket::readyRead, this, &NetCoworkServer::onDataReady);

    for (uint32_t i = 0; i < factory_count(); ++i)
    {
        const NetCoworkFactory* factory = get_factory(i);

        Message msg;
        msg.add_value(factory->get_name());
        msg.set_metadata(UINT32_MAX, factory->get_class_id());
        socket->write(msg.get_data());
    }

    for (uint32_t i = 0; i < object_count(); ++i)
        socket->write(get_object(i)->get_factory()->get_sync_message(get_object(i)).get_data());

    qDebug() << "New connection";
}

void NetCoworkServer::onDataReady()
{
    qDebug() << "Data coming";

    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    Message msg(Message::get_message(socket));
    process_func(msg);

    send_data(msg);
}

void NetCoworkServer::send_data(Message& msg)
{
    send_data(msg.get_data());
}

void NetCoworkServer::send_data(Message&& msg)
{
    send_data(msg.get_data());
}

void NetCoworkServer::respond(Message& msg)
{
    respond(msg.get_data());
}

void NetCoworkServer::respond(Message&& msg)
{
    respond(msg.get_data());
}

bool NetCoworkServer::is_server()
{
    return true;
}

bool NetCoworkServer::creation_filter(uint32_t class_id)
{
    switch(policy)
    {
    case CreationPolicy::ALL:
        return true;
    case CreationPolicy::SERVER_ONLY:
        return false;
    case CreationPolicy::CUSTOM:
        return filter->allow(qobject_cast<QTcpSocket*>(sender()), class_id);
    }
}

void NetCoworkServer::send_data(const QByteArray& data)
{
    for (auto socket : sockets)
    {
        if (socket != sender())
        {
            if (socket->write(data) != data.size())
                qCritical() << "Failure sending data";
            socket->flush();
        }
    }

    qDebug() << "Data is sended";
}

void NetCoworkServer::respond(const QByteArray& data)
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (socket)
    {
        if (socket->write(data) != data.size())
            qCritical() << "Failure sending data";
        socket->flush();
    }
}
