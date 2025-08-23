// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapitransformpininfo_apitransformpininfo_bounds.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"

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

void ApiTransformPinInfo_ApiTransformPinInfo_BoundsConverter::convert(
    const octaneapi::ApiTransformPinInfo_ApiTransformPinInfo_Bounds & in,
    Octane::ApiTransformPinInfo::Bounds & out)
{

    // Found structure 4 Bounds
    // from proto type = const octaneapi::ApiTransformPinInfo_ApiTransformPinInfo_Bounds &,
        //to octane type = Octane::ApiTransformPinInfo::Bounds &
    // list out parameters
    //cl=Bounds, field.mName = defaultValue field.mType = double, protoType=double
    out.mDefaultValue = in.defaultvalue();////simple 3////
    //cl=Bounds, field.mName = minValue field.mType = double, protoType=double
    out.mMinValue = in.minvalue();////simple 3////
    //cl=Bounds, field.mName = maxValue field.mType = double, protoType=double
    out.mMaxValue = in.maxvalue();////simple 3////
    // all fields resolved OK;
}


void ApiTransformPinInfo_ApiTransformPinInfo_BoundsConverter::convert(
    const Octane::ApiTransformPinInfo::Bounds & in,
    octaneapi::ApiTransformPinInfo_ApiTransformPinInfo_Bounds & out)
{

    // Found structure 3 Bounds
    // from octane type = const Octane::ApiTransformPinInfo::Bounds &,
        //to proto type = octaneapi::ApiTransformPinInfo_ApiTransformPinInfo_Bounds &
    // list out parameters
    out.set_defaultvalue(in.mDefaultValue);////simple 4b////
    out.set_minvalue(in.mMinValue);////simple 4b////
    out.set_maxvalue(in.mMaxValue);////simple 4b////
    // all fields resolved OK;
}


} // namespace octaneGRPC
#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
