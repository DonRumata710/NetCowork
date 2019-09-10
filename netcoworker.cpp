#include "netcoworker.h"


NetCoworker::NetCoworker(NetCoworkProvider* _provider, uint32_t _class_id, uint32_t _object_id) :
    provider(_provider),
    class_id(_class_id),
    object_id(_object_id)
{}

uint32_t NetCoworker::get_class_id() const
{
    return class_id;
}

uint32_t NetCoworker::get_object_id() const
{
    return object_id;
}

void NetCoworker::send_call(Message& msg) const
{
    provider->send_func_call(class_id, object_id, msg);
}
