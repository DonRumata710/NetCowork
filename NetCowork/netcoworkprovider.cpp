#include "netcoworkprovider.h"

#include "netcoworker.h"

#include <QDebug>

#include <stdexcept>


void NetCoworkProvider::send_func_call(Message& msg, const NetCoworker* obj)
{
    if (obj->get_class_id() == UINT32_MAX || obj->get_object_id() == UINT32_MAX)
    {
        messages.push_back({ std::move(msg), obj });
        return;
    }
    send_data(msg);
}

void NetCoworkProvider::add_local_object(NetCoworker* object)
{
    if (is_server())
    {
        object->set_object_id(coworkers.size());
        coworkers.push_back(object);
    }
    else
    {
        requests.push_back(object);
    }

    send_data(object->get_factory()->get_sync_message(object));
}

void NetCoworkProvider::set_add_object_callback(std::function<void(NetCoworker*, uint32_t, uint32_t)> func)
{
    obj_callback = func;
}

void NetCoworkProvider::set_add_class_callback(std::function<void(NetCoworkFactory*, uint32_t)> func)
{
    class_callback = func;
}

const NetCoworkFactory* NetCoworkProvider::get_factory(uint32_t i)
{
    return factories[i].get();
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

void NetCoworkProvider::add_new_factory(std::unique_ptr<NetCoworkFactory> factory)
{
    uint32_t new_class_local_id = static_cast<uint32_t>(factories.size());

    if (is_server())
    {
        class_ids[factory->get_name()] = new_class_local_id;
        factory->set_class_id(new_class_local_id);

        Message msg;
        msg.add_value(factory->get_name());
        msg.set_metadata(UINT32_MAX, new_class_local_id);
        send_data(msg);
    }

    factories.push_back(std::move(factory));
}

void NetCoworkProvider::process_func(Message& msg)
{
    if (msg.get_class_id() == UINT32_MAX)
    {
        std::string name = msg.get_string();
        auto it = class_ids.find(name);
        if (it != class_ids.end())
            throw std::logic_error("There is no such class on this client");
        class_ids.insert(decltype(class_ids)::value_type(name, msg.get_object_id()));

        for (const auto& factory : factories)
        {
            if (factory->get_name() == name)
            {
                factory->set_class_id(msg.get_object_id());
                if (class_callback)
                    class_callback(factory.get(), msg.get_object_id());
            }
        }
    }
    else
    {
        if (msg.get_object_id() != UINT32_MAX)
        {
            for (auto object : coworkers)
            {
                if (object->get_class_id() == msg.get_class_id() && object->get_object_id() == msg.get_object_id())
                {
                    if (msg.get_func_id() == 0)
                        factories[msg.get_class_id()]->sync(object, msg);
                    else
                        object->handle_call(msg);
                    return;
                }
            }
        }

        if (!creation_filter(msg.get_class_id()))
        {
            return;
        }

        if (is_server())
        {
            if (msg.get_object_id() != UINT32_MAX)
            {
                qCritical() << "fake id";
                return;
            }

            msg.set_object_id(coworkers.size());

            qDebug() << "client object creation:" << msg.get_object_id();

            Message responce;
            responce.set_metadata(msg.get_class_id(), msg.get_object_id(), 0);
            respond(responce);
        }
        else if (msg.get_size() == 0)
        {
            for (auto req_it = requests.begin(); req_it < requests.end(); ++req_it)
            {
                auto& obj = *req_it;
                if (obj->get_class_id() == msg.get_class_id())
                {
                    obj->set_object_id(msg.get_object_id());

                    auto deffered_msg = messages.begin();
                    while (deffered_msg < messages.end())
                    {
                        if (deffered_msg->second->get_object_id() == msg.get_object_id() && deffered_msg->second->get_class_id() == msg.get_class_id())
                        {
                            deffered_msg->first.set_class_id(deffered_msg->second->get_class_id());
                            deffered_msg->first.set_object_id(deffered_msg->second->get_object_id());

                            send_data(deffered_msg->first);
                            deffered_msg = messages.erase(deffered_msg);
                        }
                        else
                        {
                            ++deffered_msg;
                        }
                    }
                    requests.erase(req_it);

                    qDebug() << "sync message";
                    return;
                }
            }
        }

        if (msg.get_object_id() == UINT32_MAX)
            return;

        NetCoworker* coworker = factories[msg.get_class_id()]->create_object();
        coworker->set_object_id(msg.get_object_id());
        coworkers.push_back(coworker);
        if (msg.get_func_id() == 0)
        {
            factories[msg.get_class_id()]->sync(coworker, msg);
            if (obj_callback)
                obj_callback(coworker, msg.get_class_id(), msg.get_object_id());
        }

        qDebug() << "creation message";
    }
}

bool NetCoworkProvider::creation_filter(uint32_t class_id)
{
    return true;
}
