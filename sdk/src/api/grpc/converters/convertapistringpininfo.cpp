// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapistringpininfo.h"
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

void ApiStringPinInfoConverter::convert(
    const octaneapi::ApiStringPinInfo & in,
    Octane::ApiStringPinInfo & out)
{

    // Found structure 1 ApiStringPinInfo
    // from proto type = const octaneapi::ApiStringPinInfo &,
        //to octane type = Octane::ApiStringPinInfo &
    // list out parameters
    //cl=ApiStringPinInfo, field.mName = isValid field.mType = bool, protoType=bool
    //cl=ApiStringPinInfo, field.mName = defaultValue field.mType = const char *, protoType=string
    out.mDefaultValue =  (char*)StringManager::getInstance().addString(in.defaultvalue());
    //cl=ApiStringPinInfo, field.mName = filePatterns field.mType = const char *, protoType=string
    out.mFilePatterns =  (char*)StringManager::getInstance().addString(in.filepatterns());
    //cl=ApiStringPinInfo, field.mName = values field.mType = const char *const *, protoType=StringArrayT
    char * * valuesTemp = new char *[in.values().data_size()];////222////
    // Store the array for auto deletion. The pointer returned to the caller will be valid until the next time this function is called.
    ObjectStore::getInstance().addPointer<char*>("values", valuesTemp);
    for(int h = 0; h < in.values().data_size(); h++)
    {
         valuesTemp[h] = (char*)StringManager::getInstance().addString(in.values().data(h));
    }
    // memory leak
    out.mValues = valuesTemp;
    //cl=ApiStringPinInfo, field.mName = valueCount field.mType = size_t, protoType=uint32
    out.mValueCount = in.valuecount();////simple 3////
    //cl=ApiStringPinInfo, field.mName = multiLine field.mType = bool, protoType=bool
    out.mMultiLine = in.multiline();////simple 3////
    //cl=ApiStringPinInfo, field.mName = isFile field.mType = bool, protoType=bool
    out.mIsFile = in.isfile();////simple 3////
    //cl=ApiStringPinInfo, field.mName = forSaving field.mType = bool, protoType=bool
    out.mForSaving = in.forsaving();////simple 3////
    //cl=ApiStringPinInfo, field.mName = allowCustomValue field.mType = bool, protoType=bool
    out.mAllowCustomValue = in.allowcustomvalue();////simple 3////
    //cl=ApiStringPinInfo, field.mName = updateWhileTyping field.mType = bool, protoType=bool
    out.mUpdateWhileTyping = in.updatewhiletyping();////simple 3////
    // all fields resolved OK;
}


void ApiStringPinInfoConverter::convert(
    const Octane::ApiStringPinInfo & in,
    octaneapi::ApiStringPinInfo & out)
{

    // Found structure 1 ApiStringPinInfo
    // from octane type = const Octane::ApiStringPinInfo &,
        //to proto type = octaneapi::ApiStringPinInfo &
    // list out parameters
    out.set_isvalid(true);////mDummy 4////

    std::string * defaultValueStr = new std::string();////approved//// 
    *defaultValueStr = StringManager::checkString(in.mDefaultValue);
    out.set_allocated_defaultvalue(defaultValueStr);

    std::string * filePatternsStr = new std::string();////approved//// 
    *filePatternsStr = StringManager::checkString(in.mFilePatterns);
    out.set_allocated_filepatterns(filePatternsStr);
   // 1D array
    octaneapi::StringArrayT * valuesOut = new octaneapi::StringArrayT;////approved////
    for(uint32_t h = 0; h < 0; h++)
    {
        valuesOut->add_data(in.mValues[h]);
    }
    out.set_allocated_values(valuesOut);
    out.set_valuecount(static_cast<uint32_t>(in.mValueCount));////simple 4////
    out.set_multiline(in.mMultiLine);////simple 4b////
    out.set_isfile(in.mIsFile);////simple 4b////
    out.set_forsaving(in.mForSaving);////simple 4b////
    out.set_allowcustomvalue(in.mAllowCustomValue);////simple 4b////
    out.set_updatewhiletyping(in.mUpdateWhileTyping);////simple 4b////
    // all fields resolved OK;
}


#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
