#ifndef NETCOWORKPROVIDER_H
#define NETCOWORKPROVIDER_H

#include "message.h"
#include "netcoworkfactory.h"

#include <functional>


class NetCoworker;


class NetCoworkProvider
{
public:
    virtual ~NetCoworkProvider() = default;

    virtual void start(const std::string& address, uint16_t port) = 0;
    virtual void stop() = 0;

    void send_func_call(Message& data, const NetCoworker* obj);

    void add_local_object(NetCoworker* object);

    template<class Factory>
    Factory* register_new_class()
    {
        Factory* factory = new Factory(this);
        add_new_factory(std::unique_ptr<NetCoworkFactory>(factory));
        return factory;
    }

    virtual bool is_server() = 0;

    void set_add_object_callback(std::function<void (NetCoworker*, uint32_t, uint32_t)> func);
    void set_add_class_callback(std::function<void (NetCoworkFactory*, uint32_t)> func);

protected:
    virtual void send_data(Message& msg) = 0;
    virtual void send_data(Message&& msg) = 0;
    virtual void respond(Message& msg) = 0;
    virtual void respond(Message&& msg) = 0;
    void process_func(Message& data);

    const NetCoworkFactory* get_factory(uint32_t i);
    uint32_t factory_count() const;

    NetCoworker* get_object(uint32_t i) const;
    uint32_t object_count();

private:
    void add_new_factory(std::unique_ptr<NetCoworkFactory> factory);

    virtual bool creation_filter(uint32_t class_id);

private:
    std::vector<NetCoworker*> coworkers;
    std::vector<std::unique_ptr<NetCoworkFactory>> factories;
    std::map<std::string, uint32_t> class_ids;

    std::function<void (NetCoworker*, uint32_t, uint32_t)> obj_callback;
    std::function<void (NetCoworkFactory*, uint32_t)> class_callback;

    std::vector<NetCoworker*> requests;
    std::vector<std::pair<Message, const NetCoworker*>> messages;
};


#endif // NETCOWORKPROVIDER_H
