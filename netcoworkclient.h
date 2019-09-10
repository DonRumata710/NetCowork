#ifndef NETCOWORKCLIENT_H
#define NETCOWORKCLIENT_H


#include "netcoworkprovider.h"

#include <QTcpSocket>


class NetCoworkClient : public QObject, public NetCoworkProvider
{
public:
    NetCoworkClient(const QHostAddress& address, uint16_t port);

    virtual void send_data(Message& data) override;

public slots:
    void onConnected();

    void onDataReady();

private:
    QTcpSocket socket;
};

#endif // NETCOWORKCLIENT_H
