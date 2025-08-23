// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapiprojectionpininfo.h"
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

namespace OctaneGRPC
{

void ApiProjectionPinInfoConverter::convert(
    const octaneapi::ApiProjectionPinInfo & in,
    Octane::ApiProjectionPinInfo & out)
{

    // Found structure 1 ApiProjectionPinInfo
    // from proto type = const octaneapi::ApiProjectionPinInfo &,
        //to octane type = Octane::ApiProjectionPinInfo &
    // list out parameters
    //cl=ApiProjectionPinInfo, field.mName = isValid field.mType = bool, protoType=bool
    //cl=ApiProjectionPinInfo, field.mName = useImageProjection field.mType = bool, protoType=bool
    out.mUseImageProjection = in.useimageprojection();////simple 3////
    // all fields resolved OK;
}


void ApiProjectionPinInfoConverter::convert(
    const Octane::ApiProjectionPinInfo & in,
    octaneapi::ApiProjectionPinInfo & out)
{

    // Found structure 1 ApiProjectionPinInfo
    // from octane type = const Octane::ApiProjectionPinInfo &,
        //to proto type = octaneapi::ApiProjectionPinInfo &
    // list out parameters
    out.set_isvalid(true);////mDummy 4////
    out.set_useimageprojection(in.mUseImageProjection);////simple 4b////
    // all fields resolved OK;
}


} // namespace octaneGRPC
#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
