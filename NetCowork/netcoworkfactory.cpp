#include "netcoworkfactory.h"

#include "netcoworkprovider.h"


NetCoworkFactory::NetCoworkFactory(NetCoworkProvider* provider) :
    provider(provider)
{}

uint32_t NetCoworkFactory::get_class_id() const
{
    return class_id;
}

void NetCoworkFactory::send_func_call(Message& msg, const NetCoworker* coworker) const
{
    msg.set_class_id(class_id);
    provider->send_func_call(msg, coworker);
}

void NetCoworkFactory::set_class_id(uint32_t id)
{
    class_id = id;
}

void NetCoworkFactory::add_object(NetCoworker* obj)
{
    provider->add_local_object(obj);
}
