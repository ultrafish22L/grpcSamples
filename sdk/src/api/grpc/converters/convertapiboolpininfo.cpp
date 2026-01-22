// Copyright (C) 2026 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapiboolpininfo.h"
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

void ApiBoolPinInfoConverter::convert(
    const octaneapi::ApiBoolPinInfo & in,
    Octane::ApiBoolPinInfo & out)
{

    // Found structure 1 ApiBoolPinInfo
    // from proto type = const octaneapi::ApiBoolPinInfo &,
        //to octane type = Octane::ApiBoolPinInfo &
    // list out parameters
    //cl=ApiBoolPinInfo, field.mName = isValid field.mType = bool, protoType=bool
    //cl=ApiBoolPinInfo, field.mName = defaultValue field.mType = bool, protoType=bool
    out.mDefaultValue = in.defaultvalue();////simple 3////
    // all fields resolved OK;
}


void ApiBoolPinInfoConverter::convert(
    const Octane::ApiBoolPinInfo & in,
    octaneapi::ApiBoolPinInfo & out)
{

    // Found structure 1 ApiBoolPinInfo
    // from octane type = const Octane::ApiBoolPinInfo &,
        //to proto type = octaneapi::ApiBoolPinInfo &
    // list out parameters
    out.set_isvalid(true);////mDummy 4////
    out.set_defaultvalue(in.mDefaultValue);////simple 4b////
    // all fields resolved OK;
}


} // namespace octaneGRPC
#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
