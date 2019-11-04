#ifndef NETCOWORKSERVER_H
#define NETCOWORKSERVER_H

#include "netcoworkprovider.h"

#include <QTcpServer>
#include <QTcpSocket>

#include <set>
#include <memory>


class CreationFilter
{
public:
    virtual bool allow(QTcpSocket* socket, uint32_t class_id) = 0;
};


class ClassFilter : public CreationFilter
{
public:
    ClassFilter(std::set<uint32_t> _private_classes);

    virtual bool allow(QTcpSocket* socket, uint32_t class_id) override;

private:
    std::set<uint32_t> private_classes;
};


class NetCoworkServer : public QTcpServer, public NetCoworkProvider
{
    Q_OBJECT

public:
    NetCoworkServer();

    virtual void start(const std::string& address, uint16_t port) override;
    virtual void stop() override;

    enum class CreationPolicy
    {
        SERVER_ONLY,
        CUSTOM,
        ALL
    };

    void set_creation_policy(CreationPolicy new_policy);

    bool set_filter(std::unique_ptr<CreationFilter>);

public slots:
    void onNewConnection();

    void onDataReady();

protected:
    virtual void send_data(Message& data) override;
    virtual bool is_server() override;
    virtual bool creation_filter(uint32_t class_id) override;

private:
    void send_data(const QByteArray& data);

private:
    std::vector<QTcpSocket*> sockets;
    CreationPolicy policy = CreationPolicy::SERVER_ONLY;
    std::unique_ptr<CreationFilter> filter;
};

#endif // NETCOWORKSERVER_H
