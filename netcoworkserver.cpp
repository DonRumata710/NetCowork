#include "netcoworkserver.h"

#include "netcoworker.h"

#include <QDataStream>
#include <QDebug>


NetCoworkServer::NetCoworkServer(const QHostAddress & address, uint16_t port)
{
    connect(this, &QTcpServer::newConnection, this, &NetCoworkServer::onNewConnection);

    if (!listen(address, port))
        qCritical() << "Listen failed";
}

void NetCoworkServer::send_data(Message& msg)
{
    QByteArray data = msg.get_data();
    send_data(msg.get_data());
}

void NetCoworkServer::send_data(const QByteArray &data)
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

void NetCoworkServer::onNewConnection()
{
    QTcpSocket* socket = nextPendingConnection();
    sockets.push_back(socket);
    connect(socket, &QTcpSocket::readyRead, this, &NetCoworkServer::onDataReady);

    for (auto& obj : get_coworkers())
    {
        obj->sync();
    }

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
