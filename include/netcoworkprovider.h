#ifndef NETCOWORKPROVIDER_H
#define NETCOWORKPROVIDER_H

#include "message.h"


class NetCoworker;
class NetCoworkFactory;


class NetCoworkProvider
{
public:
    ~NetCoworkProvider() = default;

    virtual void start(const std::string& address, uint16_t port) = 0;
    virtual void stop() = 0;

    void send_func_call(Message& data);

    void add_object(NetCoworker* object);

    template<class Factory>
    Factory* register_new_class()
    {
        Factory* factory = new Factory(this);
        add_new_factory(factory);
        return factory;
    }

    virtual bool is_server() = 0;

protected:
    virtual void send_data(Message& data) = 0;
    void parse_message(const QByteArray& message);

    const NetCoworkFactory* get_factory(uint32_t i);
    uint32_t factory_count() const;

    NetCoworker* get_object(uint32_t i) const;
    uint32_t object_count();

private:
    void add_new_factory(NetCoworkFactory* factory);

    void process_func(uint32_t class_id, uint32_t object_id, Message& data);

private:
    std::vector<NetCoworker*> coworkers;
    std::vector<NetCoworkFactory*> factories;
    std::map<std::string, uint32_t> class_ids;
};


#endif // NETCOWORKPROVIDER_H