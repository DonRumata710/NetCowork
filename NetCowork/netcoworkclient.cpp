#include "netcoworkclient.h"


NetCoworkClient::NetCoworkClient() :
    socket(this)
{
    connect(&socket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(&socket, SIGNAL(readyRead()), this, SLOT(onDataReady()));
}

void NetCoworkClient::start(const std::string& address, uint16_t port)
{
    socket.connectToHost(address.c_str(), port);

    if (!socket.isOpen())
        throw std::runtime_error("Failed connetion");
}

void NetCoworkClient::stop()
{
    socket.close();
}

void NetCoworkClient::send_data(Message& msg)
{
    socket.write(msg.get_data());
}

bool NetCoworkClient::is_server()
{
    return false;
}

void NetCoworkClient::onConnected()
{
    connect(&socket, &QTcpSocket::readyRead, this, &NetCoworkClient::onDataReady);

    qDebug() << "Connection to server";
}

void NetCoworkClient::onDataReady()
{
    qDebug() << "Data coming";

    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (!expeted_data)
    {
        if (socket->bytesAvailable() >= sizeof(quint16))
            socket->read(reinterpret_cast<char*>(&expeted_data), sizeof(expeted_data));
    }

    if (socket->bytesAvailable() < expeted_data)
        return;

    if (expeted_data == 0)
    {
        qDebug() << "Empty message";
        return;
    }

    QByteArray data(expeted_data, 0);
    socket->read(data.data(), expeted_data);
    expeted_data = 0;

    parse_message(data);
}
