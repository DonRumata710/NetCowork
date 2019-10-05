#include "netobjectsync.h"

#include "netobjectprocessor.h"


NetObjectSync::NetObjectSync(const NetObjectProcessor* _proc, uint32_t object_id, iNetObject* obj) :
    NetCoworker(_proc, object_id),
    impl(obj)
{}
