// Copyright (C) 2026 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapifloatpininfo.h"
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

void ApiFloatPinInfoConverter::convert(
    const octaneapi::ApiFloatPinInfo & in,
    Octane::ApiFloatPinInfo & out)
{

    // Found structure 1 ApiFloatPinInfo
    // from proto type = const octaneapi::ApiFloatPinInfo &,
        //to octane type = Octane::ApiFloatPinInfo &
    // list out parameters
    //cl=ApiFloatPinInfo, field.mName = isValid field.mType = bool, protoType=bool
    //cl=ApiFloatPinInfo, field.mName = dimCount field.mType = uint8_t, protoType=uint32
    out.mDimCount = in.dimcount();////simple 3////
    //cl=ApiFloatPinInfo, field.mName = dimInfos field.mType = Octane::ApiFloatPinInfo::DimInfo [4], protoType=repeated ApiFloatPinInfo.ApiFloatPinInfo_DimInfo
    if (in.diminfos().size() == 4)
    {
        for(int h = 0; h < 4; h++)
        {
            out.mDimInfos[h].mMinValue = in.diminfos().Get(h).minvalue();
            out.mDimInfos[h].mMaxValue = in.diminfos().Get(h).maxvalue();
            out.mDimInfos[h].mName = (char*)StringManager::getInstance().addString(in.diminfos().Get(h).name());
            out.mDimInfos[h].mSliderMinValue = in.diminfos().Get(h).sliderminvalue();
            out.mDimInfos[h].mSliderMaxValue = in.diminfos().Get(h).slidermaxvalue();
            out.mDimInfos[h].mSliderStep = in.diminfos().Get(h).sliderstep();
        }
    }
    else
    {
         assert(false);
    }
    //cl=ApiFloatPinInfo, field.mName = defaultValue field.mType = Octane::ApiFloatPinInfo::DataT, protoType=float_4
    out.mDefaultValue.x = in.defaultvalue().x();
    out.mDefaultValue.y = in.defaultvalue().y();
    out.mDefaultValue.z = in.defaultvalue().z();
    out.mDefaultValue.w = in.defaultvalue().w();
    //cl=ApiFloatPinInfo, field.mName = useSliders field.mType = bool, protoType=bool
    out.mUseSliders = in.usesliders();////simple 3////
    //cl=ApiFloatPinInfo, field.mName = allowLog field.mType = bool, protoType=bool
    out.mAllowLog = in.allowlog();////simple 3////
    //cl=ApiFloatPinInfo, field.mName = defaultIsLog field.mType = bool, protoType=bool
    out.mDefaultIsLog = in.defaultislog();////simple 3////
    //cl=ApiFloatPinInfo, field.mName = displayPercentages field.mType = bool, protoType=bool
    out.mDisplayPercentages = in.displaypercentages();////simple 3////
    //cl=ApiFloatPinInfo, field.mName = useAspectRatio field.mType = bool, protoType=bool
    out.mUseAspectRatio = in.useaspectratio();////simple 3////
    //cl=ApiFloatPinInfo, field.mName = isColor field.mType = bool, protoType=bool
    out.mIsColor = in.iscolor();////simple 3////
    //cl=ApiFloatPinInfo, field.mName = alwaysDisplaySign field.mType = bool, protoType=bool
    out.mAlwaysDisplaySign = in.alwaysdisplaysign();////simple 3////
    // all fields resolved OK;
}


void ApiFloatPinInfoConverter::convert(
    const Octane::ApiFloatPinInfo & in,
    octaneapi::ApiFloatPinInfo & out)
{

    // Found structure 1 ApiFloatPinInfo
    // from octane type = const Octane::ApiFloatPinInfo &,
        //to proto type = octaneapi::ApiFloatPinInfo &
    // list out parameters
    out.set_isvalid(true);////mDummy 4////
    out.set_dimcount(in.mDimCount);////simple 4b////
   // [] array
    for(int h = 0; h < 4; h++)
    {
        octaneapi::ApiFloatPinInfo::ApiFloatPinInfo_DimInfo* item = out.add_diminfos();// 5d
        item->set_minvalue(in.mDimInfos[h].mMinValue);
        item->set_maxvalue(in.mDimInfos[h].mMaxValue);
        item->set_name(StringManager::checkString(in.mDimInfos[h].mName));
        item->set_sliderminvalue(in.mDimInfos[h].mSliderMinValue);
        item->set_slidermaxvalue(in.mDimInfos[h].mSliderMaxValue);
    }

    octaneapi::float_4 * defaultValueOut = new octaneapi::float_4;////approved////
    defaultValueOut->set_x(in.mDefaultValue.x);
    defaultValueOut->set_y(in.mDefaultValue.y);
    defaultValueOut->set_z(in.mDefaultValue.z);
    defaultValueOut->set_w(in.mDefaultValue.w);
    out.set_allocated_defaultvalue(defaultValueOut);
    out.set_usesliders(in.mUseSliders);////simple 4b////
    out.set_allowlog(in.mAllowLog);////simple 4b////
    out.set_defaultislog(in.mDefaultIsLog);////simple 4b////
    out.set_displaypercentages(in.mDisplayPercentages);////simple 4b////
    out.set_useaspectratio(in.mUseAspectRatio);////simple 4b////
    out.set_iscolor(in.mIsColor);////simple 4b////
    out.set_alwaysdisplaysign(in.mAlwaysDisplaySign);////simple 4b////
    // all fields resolved OK;
}


} // namespace octaneGRPC
#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
