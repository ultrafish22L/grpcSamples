// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertnetinterfaceinfo.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"
#ifdef NO_PCH
#include "apinetrendermanager.grpc.pb.h"
#endif // #ifdef NO_PCH
#include "apinetrendermanager.h"

#if !defined(OCTANE_STANDALONE) && !defined(OCTANE_DLLEXPORT)
#include "grpcapinodeinfo.h"
#else 
struct ApiNodeInfoProxy
{
    //stub
};
#endif

void NetInterfaceInfoConverter::convert(
    const octaneapi::NetInterfaceInfo & in,
    Octane::NetInterfaceInfo & out)
{

    // Found structure 1 NetInterfaceInfo
    // from proto type = const octaneapi::NetInterfaceInfo &,
        //to octane type = Octane::NetInterfaceInfo &
    // list out parameters
    //cl=NetInterfaceInfo, field.mName = adapterIP field.mType = Octane::IPv4T, protoType=uint32
    out.mAdapterIP = in.adapterip();////IPv4T////
    //cl=NetInterfaceInfo, field.mName = baseAddress field.mType = Octane::IPv4T, protoType=uint32
    out.mBaseAddress = in.baseaddress();////IPv4T////
    //cl=NetInterfaceInfo, field.mName = mask field.mType = Octane::IPv4T, protoType=uint32
    out.mMask = in.mask();////IPv4T////
    // all fields resolved OK;
}


void NetInterfaceInfoConverter::convert(
    const Octane::NetInterfaceInfo & in,
    octaneapi::NetInterfaceInfo & out)
{

    // Found structure 1 NetInterfaceInfo
    // from octane type = const Octane::NetInterfaceInfo &,
        //to proto type = octaneapi::NetInterfaceInfo &
    // list out parameters
    out.set_adapterip(in.mAdapterIP);////IPv4T//
    out.set_baseaddress(in.mBaseAddress);////IPv4T//
    out.set_mask(in.mMask);////IPv4T//
    // all fields resolved OK;
}


#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
