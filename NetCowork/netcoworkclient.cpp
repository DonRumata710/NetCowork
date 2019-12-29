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
    socket.flush();
}

void NetCoworkClient::send_data(Message&& msg)
{
    socket.write(msg.get_data());
    socket.flush();
}

void NetCoworkClient::respond(Message& msg)
{
    Q_UNUSED(msg)
    throw std::logic_error("Unexpected method call in client");
}

void NetCoworkClient::respond(Message&& msg)
{
    Q_UNUSED(msg)
    throw std::logic_error("Unexpected method call in client");
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
    if (socket->bytesAvailable() > 0)
    {
        Message msg(Message::get_message(socket));
        qDebug() << "Message data:" << msg.get_class_id() << msg.get_object_id() << msg.get_func_id();
        process_func(msg);

        if (!socket->atEnd())
            onDataReady();
    }
}
