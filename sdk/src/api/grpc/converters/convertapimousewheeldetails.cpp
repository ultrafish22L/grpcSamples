// Copyright (C) 2026 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapimousewheeldetails.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"
#ifdef NO_PCH
#include "apimouselistener.grpc.pb.h"
#endif // #ifdef NO_PCH
#include "apimouselistener.h"

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

void ApiMouseWheelDetailsConverter::convert(
    const octaneapi::ApiMouseWheelDetails & in,
    Octane::ApiMouseWheelDetails & out)
{

    // Found structure 1 ApiMouseWheelDetails
    // from proto type = const octaneapi::ApiMouseWheelDetails &,
        //to octane type = Octane::ApiMouseWheelDetails &
    // list out parameters
    //cl=ApiMouseWheelDetails, field.mName = deltaX field.mType = float, protoType=float
    out.mDeltaX = in.deltax();////simple 3////
    //cl=ApiMouseWheelDetails, field.mName = deltaY field.mType = float, protoType=float
    out.mDeltaY = in.deltay();////simple 3////
    //cl=ApiMouseWheelDetails, field.mName = isReversed field.mType = bool, protoType=bool
    out.mIsReversed = in.isreversed();////simple 3////
    //cl=ApiMouseWheelDetails, field.mName = isSmooth field.mType = bool, protoType=bool
    out.mIsSmooth = in.issmooth();////simple 3////
    //cl=ApiMouseWheelDetails, field.mName = isInertial field.mType = bool, protoType=bool
    out.mIsInertial = in.isinertial();////simple 3////
    // all fields resolved OK;
}


void ApiMouseWheelDetailsConverter::convert(
    const Octane::ApiMouseWheelDetails & in,
    octaneapi::ApiMouseWheelDetails & out)
{

    // Found structure 1 ApiMouseWheelDetails
    // from octane type = const Octane::ApiMouseWheelDetails &,
        //to proto type = octaneapi::ApiMouseWheelDetails &
    // list out parameters
    out.set_deltax(in.mDeltaX);////simple 4b////
    out.set_deltay(in.mDeltaY);////simple 4b////
    out.set_isreversed(in.mIsReversed);////simple 4b////
    out.set_issmooth(in.mIsSmooth);////simple 4b////
    out.set_isinertial(in.mIsInertial);////simple 4b////
    // all fields resolved OK;
}


} // namespace octaneGRPC
#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
