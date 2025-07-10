// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapitexturepininfo.h"
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

void ApiTexturePinInfoConverter::convert(
    const octaneapi::ApiTexturePinInfo & in,
    Octane::ApiTexturePinInfo & out)
{

    // Found structure 1 ApiTexturePinInfo
    // from proto type = const octaneapi::ApiTexturePinInfo &,
        //to octane type = Octane::ApiTexturePinInfo &
    // list out parameters
    //cl=ApiTexturePinInfo, field.mName = isValid field.mType = bool, protoType=bool
    //cl=ApiTexturePinInfo, field.mName = minValue field.mType = float, protoType=float
    out.mMinValue = in.minvalue();////simple 3////
    //cl=ApiTexturePinInfo, field.mName = maxValue field.mType = float, protoType=float
    out.mMaxValue = in.maxvalue();////simple 3////
    //cl=ApiTexturePinInfo, field.mName = sliderMinValue field.mType = float, protoType=float
    out.mSliderMinValue = in.sliderminvalue();////simple 3////
    //cl=ApiTexturePinInfo, field.mName = sliderMaxValue field.mType = float, protoType=float
    out.mSliderMaxValue = in.slidermaxvalue();////simple 3////
    //cl=ApiTexturePinInfo, field.mName = defaultValue field.mType = Octane::ApiTexturePinInfo::DataT, protoType=float_4
    out.mDefaultValue.x = in.defaultvalue().x();
    out.mDefaultValue.y = in.defaultvalue().y();
    out.mDefaultValue.z = in.defaultvalue().z();
    out.mDefaultValue.w = in.defaultvalue().w();
    //cl=ApiTexturePinInfo, field.mName = usesSpectrum field.mType = bool, protoType=bool
    out.mUsesSpectrum = in.usesspectrum();////simple 3////
    //cl=ApiTexturePinInfo, field.mName = allowLog field.mType = bool, protoType=bool
    out.mAllowLog = in.allowlog();////simple 3////
    //cl=ApiTexturePinInfo, field.mName = defaultIsLog field.mType = bool, protoType=bool
    out.mDefaultIsLog = in.defaultislog();////simple 3////
    //cl=ApiTexturePinInfo, field.mName = displayPercentages field.mType = bool, protoType=bool
    out.mDisplayPercentages = in.displaypercentages();////simple 3////
    //cl=ApiTexturePinInfo, field.mName = alwaysDisplaySign field.mType = bool, protoType=bool
    out.mAlwaysDisplaySign = in.alwaysdisplaysign();////simple 3////
    // all fields resolved OK;
}


void ApiTexturePinInfoConverter::convert(
    const Octane::ApiTexturePinInfo & in,
    octaneapi::ApiTexturePinInfo & out)
{

    // Found structure 1 ApiTexturePinInfo
    // from octane type = const Octane::ApiTexturePinInfo &,
        //to proto type = octaneapi::ApiTexturePinInfo &
    // list out parameters
    out.set_isvalid(true);////mDummy 4////
    out.set_minvalue(in.mMinValue);////simple 4b////
    out.set_maxvalue(in.mMaxValue);////simple 4b////
    out.set_sliderminvalue(in.mSliderMinValue);////simple 4b////
    out.set_slidermaxvalue(in.mSliderMaxValue);////simple 4b////

    octaneapi::float_4 * defaultValueOut = new octaneapi::float_4;////approved////
    defaultValueOut->set_x(in.mDefaultValue.x);
    defaultValueOut->set_y(in.mDefaultValue.y);
    defaultValueOut->set_z(in.mDefaultValue.z);
    defaultValueOut->set_w(in.mDefaultValue.w);
    out.set_allocated_defaultvalue(defaultValueOut);
    out.set_usesspectrum(in.mUsesSpectrum);////simple 4b////
    out.set_allowlog(in.mAllowLog);////simple 4b////
    out.set_defaultislog(in.mDefaultIsLog);////simple 4b////
    out.set_displaypercentages(in.mDisplayPercentages);////simple 4b////
    out.set_alwaysdisplaysign(in.mAlwaysDisplaySign);////simple 4b////
    // all fields resolved OK;
}


#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
