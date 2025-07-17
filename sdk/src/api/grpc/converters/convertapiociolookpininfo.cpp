// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapiociolookpininfo.h"
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
class ApiNodeInfoProxy
{
    //stub
};
#endif

void ApiOcioLookPinInfoConverter::convert(
    const octaneapi::ApiOcioLookPinInfo & in,
    Octane::ApiOcioLookPinInfo & out)
{

    // Found structure 1 ApiOcioLookPinInfo
    // from proto type = const octaneapi::ApiOcioLookPinInfo &,
        //to octane type = Octane::ApiOcioLookPinInfo &
    // list out parameters
    //cl=ApiOcioLookPinInfo, field.mName = isValid field.mType = bool, protoType=bool
    //cl=ApiOcioLookPinInfo, field.mName = forView field.mType = bool, protoType=bool
    out.mForView = in.forview();////simple 3////
    // all fields resolved OK;
}


void ApiOcioLookPinInfoConverter::convert(
    const Octane::ApiOcioLookPinInfo & in,
    octaneapi::ApiOcioLookPinInfo & out)
{

    // Found structure 1 ApiOcioLookPinInfo
    // from octane type = const Octane::ApiOcioLookPinInfo &,
        //to proto type = octaneapi::ApiOcioLookPinInfo &
    // list out parameters
    out.set_isvalid(true);////mDummy 4////
    out.set_forview(in.mForView);////simple 4b////
    // all fields resolved OK;
}


#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
