#include "netcoworkserver.h"

#include "netcoworker.h"
#include "netcoworkfactory.h"

#include <QDataStream>
#include <QDebug>


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
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_2);
    quint16 block_size = 0;
    while(true)
    {
        if (!block_size)
        {
            if (socket->bytesAvailable() < sizeof(quint16))
                break;
            in >> block_size;
        }

        if (socket->bytesAvailable() < block_size)
            break;
    }

    QByteArray data(block_size, 0);
    in.readRawData(data.data(), block_size);

    parse_message(data);

    send_data(data);
}

void NetCoworkServer::send_data(Message& msg)
{
    send_data(msg.get_data());
}

bool NetCoworkServer::is_server()
{
    return true;
}

void NetCoworkServer::send_data(const QByteArray& data)
{
    for (auto socket : sockets)
    {
        if (socket != sender())
        {
            socket->write(data);
        }
    }

    qDebug() << "Data is sended";
}