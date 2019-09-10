#include "netcoworkfactory.h"


NetCoworkFactory::NetCoworkFactory(NetCoworkProvider *provider) :
    NetCoworker(provider, 0, provider->register_new_class())
{}
