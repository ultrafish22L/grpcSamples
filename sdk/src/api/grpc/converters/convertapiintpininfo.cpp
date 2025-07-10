// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapiintpininfo.h"
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

void ApiIntPinInfoConverter::convert(
    const octaneapi::ApiIntPinInfo & in,
    Octane::ApiIntPinInfo & out)
{

    // Found structure 1 ApiIntPinInfo
    // from proto type = const octaneapi::ApiIntPinInfo &,
        //to octane type = Octane::ApiIntPinInfo &
    // list out parameters
    //cl=ApiIntPinInfo, field.mName = isValid field.mType = bool, protoType=bool
    //cl=ApiIntPinInfo, field.mName = dimCount field.mType = uint8_t, protoType=uint32
    out.mDimCount = in.dimcount();////simple 3////
    //cl=ApiIntPinInfo, field.mName = dimInfos field.mType = Octane::ApiIntPinInfo::DimInfo [4], protoType=repeated ApiIntPinInfo.ApiIntPinInfo_DimInfo
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
    //cl=ApiIntPinInfo, field.mName = defaultValue field.mType = Octane::ApiIntPinInfo::DataT, protoType=int32_4
    out.mDefaultValue.x = in.defaultvalue().x();
    out.mDefaultValue.y = in.defaultvalue().y();
    out.mDefaultValue.z = in.defaultvalue().z();
    out.mDefaultValue.w = in.defaultvalue().w();
    //cl=ApiIntPinInfo, field.mName = useSliders field.mType = bool, protoType=bool
    out.mUseSliders = in.usesliders();////simple 3////
    //cl=ApiIntPinInfo, field.mName = allowLog field.mType = bool, protoType=bool
    out.mAllowLog = in.allowlog();////simple 3////
    //cl=ApiIntPinInfo, field.mName = defaultIsLog field.mType = bool, protoType=bool
    out.mDefaultIsLog = in.defaultislog();////simple 3////
    //cl=ApiIntPinInfo, field.mName = isColor field.mType = bool, protoType=bool
    out.mIsColor = in.iscolor();////simple 3////
    //cl=ApiIntPinInfo, field.mName = alwaysDisplaySign field.mType = bool, protoType=bool
    out.mAlwaysDisplaySign = in.alwaysdisplaysign();////simple 3////
    // all fields resolved OK;
}


void ApiIntPinInfoConverter::convert(
    const Octane::ApiIntPinInfo & in,
    octaneapi::ApiIntPinInfo & out)
{

    // Found structure 1 ApiIntPinInfo
    // from octane type = const Octane::ApiIntPinInfo &,
        //to proto type = octaneapi::ApiIntPinInfo &
    // list out parameters
    out.set_isvalid(true);////mDummy 4////
    out.set_dimcount(in.mDimCount);////simple 4b////
   // [] array
    for(int h = 0; h < 4; h++)
    {
        octaneapi::ApiIntPinInfo::ApiIntPinInfo_DimInfo* item = out.add_diminfos();// 5d
        item->set_minvalue(in.mDimInfos[h].mMinValue);
        item->set_maxvalue(in.mDimInfos[h].mMaxValue);
        item->set_name(in.mDimInfos[h].mName);
        item->set_sliderminvalue(in.mDimInfos[h].mSliderMinValue);
        item->set_slidermaxvalue(in.mDimInfos[h].mSliderMaxValue);
    }

    octaneapi::int32_4 * defaultValueOut = new octaneapi::int32_4;////approved////
    defaultValueOut->set_x(in.mDefaultValue.x);
    defaultValueOut->set_y(in.mDefaultValue.y);
    defaultValueOut->set_z(in.mDefaultValue.z);
    defaultValueOut->set_w(in.mDefaultValue.w);
    out.set_allocated_defaultvalue(defaultValueOut);
    out.set_usesliders(in.mUseSliders);////simple 4b////
    out.set_allowlog(in.mAllowLog);////simple 4b////
    out.set_defaultislog(in.mDefaultIsLog);////simple 4b////
    out.set_iscolor(in.mIsColor);////simple 4b////
    out.set_alwaysdisplaysign(in.mAlwaysDisplaySign);////simple 4b////
    // all fields resolved OK;
}


#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
