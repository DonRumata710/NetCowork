#ifndef NETCOWORKSERVER_H
#define NETCOWORKSERVER_H

#include "netcoworkprovider.h"

#include <QTcpServer>
#include <QTcpSocket>


class NetCoworkServer : public QTcpServer, public NetCoworkProvider
{
    Q_OBJECT

public:
    NetCoworkServer(const QHostAddress& address, uint16_t port);

public slots:
    void onNewConnection();

    void onDataReady();

protected:
    virtual void send_data(Message& data) override;

private:
    void send_data(const QByteArray& data);

private:
    std::vector<QTcpSocket*> sockets;
};

#endif // NETCOWORKSERVER_H
