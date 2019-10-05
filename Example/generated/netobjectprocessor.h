#ifndef NETOBJECTIMPL_H
#define NETOBJECTIMPL_H

#include "netcoworkfactory.h"
#include "netcoworkprovider.h"
#include "netobjectsync.h"

#include <QColor>
#include <QDataStream>


class NetObjectProcessor : public NetCoworkFactory
{
public:
    NetObjectProcessor(NetCoworkProvider* _provider);

    iNetObject* get_object()
    {
        uint32_t cnt = counter++;
        Message m;
        m.add_value(cnt);
        send_func_call(m);
        auto* obj = new NetObjectSync(this, cnt, generate_object());
        add_object(obj);
        return obj;
    }

    //virtual void handle_call(Message& data) override
    //{
    //    uint32_t cnt = data.get_value<uint32_t>();
    //
    //    if (cnt != ++counter)
    //        throw std::runtime_error("Wrong object counter");
    //
    //    auto* obj = new NetObjectSync<NetObjectProcessor>(this, cnt, generate_object());
    //    add_object(obj);
    //}

private:
    iNetObject* generate_object() const;

    virtual NetCoworker* create_object(uint32_t object_id) const override
    {
        counter = object_id + 1;
        auto* obj = new NetObjectSync(this, object_id, generate_object());
        return obj;
    }

    virtual std::string get_name() const override
    {
        return "NetObject";
    }

    virtual Message get_sync_message(NetCoworker* obj) const override
    {
        NetObjectSync* NetObject_obj = dynamic_cast<NetObjectSync*>(obj);
        if (!NetObject_obj)
            return Message();

        Message msg;
        msg.set_metadata(get_class_id(), obj->get_object_id());
        msg.add_value<uint32_t>(0);
        msg.add_value(NetObject_obj->get_button_name());
        msg.add_value(NetObject_obj->get_x());
        msg.add_value(NetObject_obj->get_y());

        return msg;
    }

    virtual void sync(NetCoworker* obj, Message& msg) const override
    {
        NetObjectSync* NetObject_obj = dynamic_cast<NetObjectSync*>(obj);
        if (!NetObject_obj)
            std::logic_error("Wrong object type in NetObjectProcessor");

        NetObject_obj->get_impl()->set_button_name(msg.get_string());
        NetObject_obj->get_impl()->set_x(msg.get_value<int32_t>());
        NetObject_obj->get_impl()->set_y(msg.get_value<int32_t>());
    }

private:
    static uint32_t counter;
};



#endif // NETOBJECTIMPL_H
