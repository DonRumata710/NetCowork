#include "netcoworkprovider.h"

#include "netcoworkfactory.h"
#include "netcoworker.h"


void NetCoworkProvider::send_func_call(uint32_t class_id, uint32_t object_id, Message& msg)
{
    msg.set_metadata(class_id, object_id);
    send_data(msg);
}

void NetCoworkProvider::add_object(NetCoworker *object)
{
    coworkers.push_back(object);
}

int NetCoworkProvider::register_new_class(NetCoworkFactory* factory)
{
    static uint32_t class_id = 0;

    Message msg;
    msg.add_value(QString(factory->get_name().c_str()));
    process_func(0, class_id, msg);

    return class_id++;
}

void NetCoworkProvider::parse_message(const QByteArray& message)
{
    uint32_t class_id = *(reinterpret_cast<uint32_t*>(message.mid(0, 4).data()));
    uint32_t object_id = *(reinterpret_cast<uint32_t*>(message.mid(4, 4).data()));
    Message msg(message.mid(8));
    process_func(class_id, object_id, msg);
}

void NetCoworkProvider::process_func(uint32_t class_id, uint32_t object_id, Message& msg)
{
    if (class_id == 0)
    {
        if (object_id == 0)
        {
            if (factories.size() > )
        }

        coworkers.push_back(factories[object_id]->create_object());
    }
    else
    {
        for (auto object : coworkers)
        {
            if (object->get_class_id() == class_id && object->get_object_id() == object_id)
                object->handle_call(msg);
        }
    }
}

const std::vector<NetCoworker *> &NetCoworkProvider::get_coworkers() const
{
    return coworkers;
}
