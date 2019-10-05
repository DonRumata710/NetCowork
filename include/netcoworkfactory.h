#ifndef NETCOWORKFACTORY_H
#define NETCOWORKFACTORY_H

#include "netcoworker.h"


class NetCoworkFactory
{
    friend class NetCoworkProvider;
    friend class NetCoworkServer;

public:
    uint32_t get_class_id() const;

    void send_func_call(Message& msg) const;

protected:
    NetCoworkFactory(NetCoworkProvider* provider);
    virtual ~NetCoworkFactory() = default;

    void set_class_id(uint32_t id);

    virtual NetCoworker* create_object(uint32_t object_id) const = 0;
    virtual std::string get_name() const = 0;

    virtual Message get_sync_message(NetCoworker* obj) const = 0;
    virtual void sync(NetCoworker* obj, Message& msg) const = 0;

    void add_object(NetCoworker* obj);

private:
    uint32_t class_id = UINT32_MAX;
    NetCoworkProvider* provider;
};


#endif // NETCOWORKFACTORY_H
