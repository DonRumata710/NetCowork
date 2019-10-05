#ifndef NETOBJECTSYNC_H
#define NETOBJECTSYNC_H

#include "netobject.h"
#include "netcoworker.h"


class NetObjectProcessor;


class NetObjectSync : public NetCoworker, public iNetObject
{
public:
    NetObjectSync(const NetObjectProcessor* _proc, uint32_t object_id, iNetObject* obj);

    void setPos(int32_t x, int32_t y) override
    {
        impl->setPos(x, y);

        Message msg;

        msg.add_value(uint32_t(1));
        msg.add_value(x);
        msg.add_value(y);

        send_func_call(msg);
    }

    virtual void set_x(int32_t new_x) override
    {
        impl->set_x(new_x);

        Message msg;

        msg.add_value(uint32_t(2));
        msg.add_value(new_x);

        send_func_call(msg);
    }

    virtual void set_y(int32_t new_y) override
    {
        impl->set_y(new_y);

        Message msg;

        msg.add_value(uint32_t(3));
        msg.add_value(new_y);

        send_func_call(msg);
    }

    virtual void set_button_name(const std::string& new_button_name) override
    {
        impl->set_button_name(new_button_name);

        Message msg;
        msg.add_value(uint32_t(4));
        msg.add_value(new_button_name);

        send_func_call(msg);
    }

    virtual int32_t get_x() const override
    {
        return impl->get_x();
    }

    virtual int32_t get_y() const override
    {
        return impl->get_y();
    }

    virtual std::string get_button_name() const override
    {
        return impl->get_button_name();
    }

    virtual void handle_call(Message& data) override
    {
        uint32_t func_id = data.get_value<uint32_t>();

        switch (func_id)
        {
        case 0:
            throw std::logic_error("Unexpected sync signal");
        case 1:
        {
            int32_t x = data.get_value<int32_t>();
            int32_t y = data.get_value<int32_t>();
            impl->setPos(x, y);
            break;
        }
        case 2:
        {
            int32_t x = data.get_value<int32_t>();
            impl->set_x(x);
            break;
        }
        case 3:
        {
            int32_t y = data.get_value<int32_t>();
            impl->set_y(y);
            break;
        }
        case 4:
        {
            std::string button = data.get_string();
            impl->set_button_name(button);
            break;
        }
        default:
            throw std::runtime_error("Unknown function call");
        }
    }

    iNetObject* get_impl() { return impl; }

private:
    iNetObject* impl = nullptr;
};

#endif // NETOBJECTSYNC_H
