#ifndef NETCOWORKER_H
#define NETCOWORKER_H

#include "message.h"

#include <netcoworkprovider.h>

#include <QObject>
#include <QDataStream>


class NetCoworker : public QObject
{
    Q_OBJECT

public:
    NetCoworker(NetCoworkProvider*, uint32_t class_id, uint32_t object_id);

    virtual void handle_call(Message& msg) = 0;

    uint32_t get_class_id() const;
    uint32_t get_object_id() const;

    virtual void sync() = 0;

protected:
    void send_call(Message& msg) const;

private:
    NetCoworkProvider* provider;
    uint32_t class_id = UINT32_MAX;
    uint32_t object_id = UINT32_MAX;
};

#endif // NETCOWORKER_H
