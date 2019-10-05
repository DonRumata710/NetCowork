#include "netobjectprocessor.h"

uint32_t NetObjectProcessor::counter(0);

NetObjectProcessor::NetObjectProcessor(NetCoworkProvider *_provider) :
    NetCoworkFactory(_provider)
{}
