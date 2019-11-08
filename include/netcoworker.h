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
    explicit NetCoworker(const NetCoworkFactory* _factory, uint32_t object_id = UINT32_MAX);

    virtual void handle_call(Message& msg) = 0;

    uint32_t get_class_id() const;

    uint32_t get_object_id() const;

    const NetCoworkFactory* get_factory() const;

protected:
    void send_func_call(Message& msg) const;

private:
    friend class NetCoworkProvider;

    void set_object_id(uint32_t new_object_id);

private:
    const NetCoworkFactory* factory;
    uint32_t object_id = UINT32_MAX;
};

#endif // NETCOWORKER_H
