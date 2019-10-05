#ifndef NETCOWORKER_H
#define NETCOWORKER_H

#include "message.h"

#include <QObject>
#include <QDataStream>


class NetCoworkFactory;


class NetCoworker : public QObject
{
    Q_OBJECT

public:
    NetCoworker(const NetCoworkFactory* _factory, uint32_t object_id);

    virtual void handle_call(Message& msg) = 0;

    [[deprecated]]
    uint32_t get_class_id() const;

    uint32_t get_object_id() const;

    const NetCoworkFactory* get_factory() const;

protected:
    void send_func_call(Message& msg) const;

private:
    const NetCoworkFactory* factory;
    uint32_t object_id = UINT32_MAX;
};

#endif // NETCOWORKER_H
