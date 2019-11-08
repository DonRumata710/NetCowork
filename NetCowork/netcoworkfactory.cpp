#include "netcoworkfactory.h"

#include "netcoworkprovider.h"


void NetCoworkFactory::send_func_call(Message& msg) const
{
    if (class_id == UINT32_MAX)
        throw std::logic_error("unregistered class " + get_name());

    msg.set_class_id(class_id);
    provider->send_func_call(msg);
}

NetCoworkFactory::NetCoworkFactory(NetCoworkProvider* provider) :
    provider(provider)
{}

void NetCoworkFactory::set_class_id(uint32_t id)
{
    class_id = id;
}

uint32_t NetCoworkFactory::get_class_id() const
{
    return class_id;
}

void NetCoworkFactory::add_object(NetCoworker* obj)
{
    provider->add_local_object(obj);
}
