// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapidevicememoryusage.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"
#ifdef NO_PCH
#include "apirender.grpc.pb.h"
#endif // #ifdef NO_PCH
#include "apirender.h"

#if !defined(OCTANE_STANDALONE) && !defined(OCTANE_DLLEXPORT)
#include "grpcapinodeinfo.h"
#else 
class ApiNodeInfoProxy
{
    //stub
};
#endif

void ApiDeviceMemoryUsageConverter::convert(
    const octaneapi::ApiDeviceMemoryUsage & in,
    Octane::ApiDeviceMemoryUsage & out)
{

    // Found structure 1 ApiDeviceMemoryUsage
    // from proto type = const octaneapi::ApiDeviceMemoryUsage &,
        //to octane type = Octane::ApiDeviceMemoryUsage &
    // list out parameters
    //cl=ApiDeviceMemoryUsage, field.mName = usedDeviceMemory field.mType = uint64_t, protoType=uint64
    out.mUsedDeviceMemory = in.useddevicememory();////simple 3////
    //cl=ApiDeviceMemoryUsage, field.mName = freeDeviceMemory field.mType = uint64_t, protoType=uint64
    out.mFreeDeviceMemory = in.freedevicememory();////simple 3////
    //cl=ApiDeviceMemoryUsage, field.mName = totalDeviceMemory field.mType = uint64_t, protoType=uint64
    out.mTotalDeviceMemory = in.totaldevicememory();////simple 3////
    //cl=ApiDeviceMemoryUsage, field.mName = outOfCoreMemory field.mType = uint64_t, protoType=uint64
    out.mOutOfCoreMemory = in.outofcorememory();////simple 3////
    //cl=ApiDeviceMemoryUsage, field.mName = peerToPeerBytesUsed field.mType = uint64_t, protoType=uint64
    out.mPeerToPeerBytesUsed = in.peertopeerbytesused();////simple 3////
    // all fields resolved OK;
}


void ApiDeviceMemoryUsageConverter::convert(
    const Octane::ApiDeviceMemoryUsage & in,
    octaneapi::ApiDeviceMemoryUsage & out)
{

    // Found structure 1 ApiDeviceMemoryUsage
    // from octane type = const Octane::ApiDeviceMemoryUsage &,
        //to proto type = octaneapi::ApiDeviceMemoryUsage &
    // list out parameters
    out.set_useddevicememory(in.mUsedDeviceMemory);////simple 4b////
    out.set_freedevicememory(in.mFreeDeviceMemory);////simple 4b////
    out.set_totaldevicememory(in.mTotalDeviceMemory);////simple 4b////
    out.set_outofcorememory(in.mOutOfCoreMemory);////simple 4b////
    out.set_peertopeerbytesused(in.mPeerToPeerBytesUsed);////simple 4b////
    // all fields resolved OK;
}


#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
