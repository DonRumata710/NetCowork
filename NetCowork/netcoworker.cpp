#include "netcoworker.h"

#include "netcoworkfactory.h"


NetCoworker::NetCoworker(const NetCoworkFactory* _factory, uint32_t _object_id) :
    factory(_factory),
    object_id(_object_id)
{}

uint32_t NetCoworker::get_class_id() const
{
    return factory->get_class_id();
}

uint32_t NetCoworker::get_object_id() const
{
    return object_id;
}

const NetCoworkFactory* NetCoworker::get_factory() const
{
    return factory;
}

void NetCoworker::send_func_call(Message& msg) const
{
    msg.set_object_id(object_id);
    factory->send_func_call(msg, this);
}

void NetCoworker::set_object_id(uint32_t new_object_id)
{
    object_id = new_object_id;
}
