// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapiocioviewpininfo.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"
#ifdef NO_PCH
#include "octaneinfos.grpc.pb.h"
#endif // #ifdef NO_PCH
#include "octaneinfos.h"

#if !defined(OCTANE_STANDALONE) && !defined(OCTANE_DLLEXPORT)
#include "grpcapinodeinfo.h"
#else 
struct ApiNodeInfoProxy
{
    //stub
};
#endif

void ApiOcioViewPinInfoConverter::convert(
    const octaneapi::ApiOcioViewPinInfo & in,
    Octane::ApiOcioViewPinInfo & out)
{

    // Found structure 1 ApiOcioViewPinInfo
    // from proto type = const octaneapi::ApiOcioViewPinInfo &,
        //to octane type = Octane::ApiOcioViewPinInfo &
    // list out parameters
    //cl=ApiOcioViewPinInfo, field.mName = isValid field.mType = bool, protoType=bool
    // all fields resolved OK;
}


void ApiOcioViewPinInfoConverter::convert(
    const Octane::ApiOcioViewPinInfo & in,
    octaneapi::ApiOcioViewPinInfo & out)
{

    // Found structure 1 ApiOcioViewPinInfo
    // from octane type = const Octane::ApiOcioViewPinInfo &,
        //to proto type = octaneapi::ApiOcioViewPinInfo &
    // list out parameters
    out.set_isvalid(true);////mDummy 4////
    // all fields resolved OK;
}


#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
