#ifndef NETCOWORKCLIENT_H
#define NETCOWORKCLIENT_H


#include "netcoworkprovider.h"

#include <QTcpSocket>


class NetCoworkClient : public QObject, public NetCoworkProvider
{
    Q_OBJECT

public:
    NetCoworkClient();

    virtual void start(const std::string& address, uint16_t port) override;
    virtual void stop() override;

public slots:
    void onConnected();

    void onDataReady();

protected:
    virtual void send_data(Message& data) override;
    virtual void send_data(Message&& msg) override;
    virtual void respond(Message& msg) override;
    virtual void respond(Message&& msg) override;
    virtual bool is_server() override;

private:
    QTcpSocket socket;
    uint16_t expeted_data = 0;
};

#endif // NETCOWORKCLIENT_H
