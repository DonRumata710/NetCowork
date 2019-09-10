#ifndef NETCOWORKFACTORY_H
#define NETCOWORKFACTORY_H


#include "netcoworker.h"


class NetCoworkFactory : public NetCoworker
{
    friend class NetCoworkProvider;

protected:
    NetCoworkFactory(NetCoworkProvider* provider);

    virtual NetCoworker* create_object() const = 0;
    virtual std::string get_name() const = 0;
};


#endif // NETCOWORKFACTORY_H
