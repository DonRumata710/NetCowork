#include "netcoworkprovider.h"

#include "netcoworkfactory.h"
#include "netcoworker.h"


void NetCoworkProvider::send_func_call(Message& msg)
{
    send_data(msg);
}

void NetCoworkProvider::add_object(NetCoworker *object)
{
    coworkers.push_back(object);
}

void NetCoworkProvider::set_add_object_callback(std::function<void(NetCoworker*, uint32_t, uint32_t)> func)
{
    callback = func;
}

void NetCoworkProvider::parse_message(const QByteArray& message)
{
    uint32_t class_id = *(reinterpret_cast<uint32_t*>(message.mid(0, 4).data()));
    uint32_t object_id = *(reinterpret_cast<uint32_t*>(message.mid(4, 4).data()));
    Message msg(message.mid(8));
    process_func(class_id, object_id, msg);
}

const NetCoworkFactory* NetCoworkProvider::get_factory(uint32_t i)
{
    return factories[i];
}

uint32_t NetCoworkProvider::factory_count() const
{
    return static_cast<uint32_t>(factories.size());
}

NetCoworker* NetCoworkProvider::get_object(uint32_t i) const
{
    return coworkers[i];
}

uint32_t NetCoworkProvider::object_count()
{
    return static_cast<uint32_t>(coworkers.size());
}

void NetCoworkProvider::add_new_factory(NetCoworkFactory* factory)
{
    factories.push_back(factory);
    uint32_t new_class_local_id = static_cast<uint32_t>(factories.size() - 1);

    if (is_server())
    {
        class_ids[factory->get_name()] = new_class_local_id;
        factory->set_class_id(new_class_local_id);

        Message msg;
        msg.add_value(factory->get_name());
        msg.set_metadata(UINT32_MAX, new_class_local_id);
        send_data(msg);
    }
}

void NetCoworkProvider::process_func(uint32_t class_id, uint32_t object_id, Message& msg)
{
    if (class_id == UINT32_MAX)
    {
        std::string name = msg.get_string();
        auto it = class_ids.find(name);
        if (it != class_ids.end())
            throw std::logic_error("There is no such class on this client");
        class_ids.insert(decltype(class_ids)::value_type(name, object_id));

        for (auto factory : factories)
        {
            if (factory->get_name() == name)
                factory->set_class_id(object_id);
        }
    }
    else
    {
        for (auto object : coworkers)
        {
            if (object->get_class_id() == class_id && object->get_object_id() == object_id)
            {
                object->handle_call(msg);
                return;
            }
        }

        if (!creation_filter(class_id))
        {
            return;
        }

        NetCoworker* coworker = factories[class_id]->create_object(object_id);
        coworkers.push_back(coworker);
        if (msg.get_value<uint32_t>() == 0)
            factories[class_id]->sync(coworker, msg);
        if (callback)
            callback(coworker, class_id, object_id);
    }
}
