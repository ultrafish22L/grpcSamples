// Copyright (C) 2026 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapibitmaskpininfo.h"
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

void ApiBitMaskPinInfoConverter::convert(
    const octaneapi::ApiBitMaskPinInfo & in,
    Octane::ApiBitMaskPinInfo & out)
{

    // Found structure 1 ApiBitMaskPinInfo
    // from proto type = const octaneapi::ApiBitMaskPinInfo &,
        //to octane type = Octane::ApiBitMaskPinInfo &
    // list out parameters
    //cl=ApiBitMaskPinInfo, field.mName = isValid field.mType = bool, protoType=bool
    //cl=ApiBitMaskPinInfo, field.mName = labels field.mType = const Octane::ApiBitMaskPinInfo::Label *, protoType=repeated ApiBitMaskPinInfo_Label
    if (in.labels().size() > 0)
    {
        int arraySize = in.labels().size();
        auto labelArray = new Octane::ApiBitMaskPinInfo::Label[arraySize]; // memory leak
        for(int h = 0; h < arraySize; h++)
        {
            labelArray[h].mName = (char*)StringManager::getInstance().addString(in.labels().Get(h).name());
            labelArray[h].mShortName = (char*)StringManager::getInstance().addString(in.labels().Get(h).shortname());
        }
        out.mLabelCount = arraySize;
        out.mLabels = labelArray;
    }
    else
    {
        out.mLabelCount = 0;
        out.mLabels = nullptr;
    }
    //cl=ApiBitMaskPinInfo, field.mName = labelCount field.mType = uint32_t, protoType=uint32
    out.mLabelCount = in.labelcount();////simple 3////
    //cl=ApiBitMaskPinInfo, field.mName = defaultValue field.mType = int32_t, protoType=int32
    out.mDefaultValue = in.defaultvalue();////simple 3////
    // all fields resolved OK;
}


void ApiBitMaskPinInfoConverter::convert(
    const Octane::ApiBitMaskPinInfo & in,
    octaneapi::ApiBitMaskPinInfo & out)
{

    // Found structure 1 ApiBitMaskPinInfo
    // from octane type = const Octane::ApiBitMaskPinInfo &,
        //to proto type = octaneapi::ApiBitMaskPinInfo &
    // list out parameters
    out.set_isvalid(true);////mDummy 4////
   // Label array
    if(in.mLabels)
    {
        //octaneapi::ApiBitMaskPinInfo_ApiBitMaskPinInfo_Label * labelsOut = new octaneapi::ApiBitMaskPinInfo_ApiBitMaskPinInfo_Label;
        for(uint32_t h = 0; h < in.mLabelCount; h++)
        {
            auto * item = out.add_labels();
            std:: string * name_ = new std::string(in.mLabels[h].mName);
            item->set_allocated_name(name_);
            std:: string * shortname_ = new std::string(in.mLabels[h].mShortName);
            item->set_allocated_shortname(shortname_);
        }
        //out.set_allocated_labels(labelsOut);
    }
    out.set_labelcount(in.mLabelCount);////simple 4b////
    out.set_defaultvalue(in.mDefaultValue);////simple 4b////
    // all fields resolved OK;
}


} // namespace octaneGRPC
#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
