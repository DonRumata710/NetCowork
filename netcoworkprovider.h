#ifndef NETCOWORKPROVIDER_H
#define NETCOWORKPROVIDER_H

#include "message.h"


class NetCoworker;
class NetCoworkFactory;


class NetCoworkProvider
{
public:
    void send_func_call(uint32_t class_id, uint32_t object_id, Message& data);

    void add_object(NetCoworker* object);

    int register_new_class(NetCoworkFactory* factory);

protected:
    virtual void send_data(Message& data) = 0;
    void parse_message(const QByteArray& message);

    const std::vector<NetCoworker*>& get_coworkers() const;

private:
    void process_func(uint32_t class_id, uint32_t object_id, Message& data);

private:
    std::vector<NetCoworker*> coworkers;
    std::vector<NetCoworkFactory*> factories;
};


#endif // NETCOWORKPROVIDER_H
