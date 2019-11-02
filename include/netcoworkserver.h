#ifndef NETCOWORKSERVER_H
#define NETCOWORKSERVER_H

#include "netcoworkprovider.h"

#include <QTcpServer>
#include <QTcpSocket>


class NetCoworkServer : public QTcpServer, public NetCoworkProvider
{
    Q_OBJECT

public:
    NetCoworkServer();

    virtual void start(const std::string& address, uint16_t port) override;
    virtual void stop() override;

public slots:
    void onNewConnection();

    void onDataReady();

protected:
    virtual void send_data(Message& data) override;
    virtual bool is_server() override;

private:
    void send_data(const QByteArray& data);

private:
    std::vector<QTcpSocket*> sockets;
};

#endif // NETCOWORKSERVER_H