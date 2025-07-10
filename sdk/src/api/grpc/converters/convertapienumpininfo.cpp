// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapienumpininfo.h"
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

void ApiEnumPinInfoConverter::convert(
    const octaneapi::ApiEnumPinInfo & in,
    Octane::ApiEnumPinInfo & out)
{

    // Found structure 1 ApiEnumPinInfo
    // from proto type = const octaneapi::ApiEnumPinInfo &,
        //to octane type = Octane::ApiEnumPinInfo &
    // list out parameters
    //cl=ApiEnumPinInfo, field.mName = isValid field.mType = bool, protoType=bool
    //cl=ApiEnumPinInfo, field.mName = values field.mType = const Octane::ApiEnumPinInfo::Value *, protoType=repeated ApiEnumPinInfo_Value
    if (in.values().size() > 0)
    {
        int arraySize = in.values().size();
        auto labelArray = new Octane::ApiEnumPinInfo::Value[arraySize]; // memory leak
        for(int h = 0; h < arraySize; h++)
        {
            labelArray[h].mLabel = (char*)StringManager::getInstance().addString(in.values().Get(h).label());
            labelArray[h].mValue = in.values().Get(h).value();
        }
        out.mValueCount = arraySize;
        out.mValues = labelArray;
    }
    else
    {
        out.mValueCount = 0;
        out.mValues = nullptr;
    }
    //cl=ApiEnumPinInfo, field.mName = valueCount field.mType = uint32_t, protoType=uint32
    out.mValueCount = in.valuecount();////simple 3////
    //cl=ApiEnumPinInfo, field.mName = defaultValue field.mType = int32_t, protoType=int32
    out.mDefaultValue = in.defaultvalue();////simple 3////
    // all fields resolved OK;
}


void ApiEnumPinInfoConverter::convert(
    const Octane::ApiEnumPinInfo & in,
    octaneapi::ApiEnumPinInfo & out)
{

    // Found structure 1 ApiEnumPinInfo
    // from octane type = const Octane::ApiEnumPinInfo &,
        //to proto type = octaneapi::ApiEnumPinInfo &
    // list out parameters
    out.set_isvalid(true);////mDummy 4////
   // Value array
    if(in.mValues)
    {
        //octaneapi::ApiEnumPinInfo_ApiEnumPinInfo_Value * valuesOut = new octaneapi::ApiEnumPinInfo_ApiEnumPinInfo_Value;
        for(uint32_t h = 0; h < in.mValueCount; h++)
        {
            auto * item = out.add_values();
            std:: string * label_ = new std::string(in.mValues[h].mLabel);
            item->set_allocated_label(label_);
            item->set_value(in.mValues[h].mValue);
        }
        //out.set_allocated_values(valuesOut);
    }
    out.set_valuecount(in.mValueCount);////simple 4b////
    out.set_defaultvalue(in.mDefaultValue);////simple 4b////
    // all fields resolved OK;
}


#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
