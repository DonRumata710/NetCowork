#include "netcoworkclient.h"


NetCoworkClient::NetCoworkClient(const QHostAddress &address, uint16_t port)
{
    connect(&socket, &QTcpSocket::connected, this, &NetCoworkClient::onConnected);
    socket.connectToHost(address, port);
}

void NetCoworkClient::send_data(Message& msg)
{
    socket.write(msg.get_data());
}

void NetCoworkClient::onConnected()
{
    connect(&socket, &QTcpSocket::readyRead, this, &NetCoworkClient::onDataReady);
}

void NetCoworkClient::onDataReady()
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
}
