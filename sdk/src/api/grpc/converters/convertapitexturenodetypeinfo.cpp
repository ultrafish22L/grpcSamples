// Copyright (C) 2026 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapitexturenodetypeinfo.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"
#ifdef NO_PCH
#include "octaneinfos.grpc.pb.h"
#endif // #ifdef NO_PCH
#include "octaneinfos.h"

#include "convertapitexturenodetypeinfo.h"
#include "convertapitexturevaluetypeset.h"
#include "convertapitexturenodetypeinfo_apitexturenodetypeinfo_configuration.h"
#include "convertapitransformpininfo_apitransformpininfo_bounds.h"
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

void ApiTextureNodeTypeInfoConverter::convert(
    const octaneapi::ApiTextureNodeTypeInfo & in,
    Octane::ApiTextureNodeTypeInfo & out)
{

    // Found structure 1 ApiTextureNodeTypeInfo
    // from proto type = const octaneapi::ApiTextureNodeTypeInfo &,
        //to octane type = Octane::ApiTextureNodeTypeInfo &
    // list out parameters
    //cl=ApiTextureNodeTypeInfo, field.mName = isValid field.mType = bool, protoType=bool
    //cl=ApiTextureNodeTypeInfo, field.mName = outputMode field.mType = Octane::TextureNodeTypeMode, protoType=TextureNodeTypeMode
    out.mOutputMode = static_cast<Octane::TextureNodeTypeMode>(in.outputmode());// enum 1 
    //cl=ApiTextureNodeTypeInfo, field.mName = inputMode field.mType = Octane::TextureNodeTypeMode, protoType=TextureNodeTypeMode
    out.mInputMode = static_cast<Octane::TextureNodeTypeMode>(in.inputmode());// enum 1 
    //cl=ApiTextureNodeTypeInfo, field.mName = canToggleValueTypesOfPins field.mType = bool, protoType=bool
    out.mCanToggleValueTypesOfPins = in.cantogglevaluetypesofpins();////simple 3////
    //cl=ApiTextureNodeTypeInfo, field.mName = staticOutputValueType field.mType = Octane::TextureValueType, protoType=TextureValueType
    out.mStaticOutputValueType = static_cast<Octane::TextureValueType>(in.staticoutputvaluetype());// enum 1 
    //cl=ApiTextureNodeTypeInfo, field.mName = inputValueTypes field.mType = Octane::ApiTextureValueTypeSet, protoType=ApiTextureValueTypeSet
    ApiTextureValueTypeSetConverter::convert(in.inputvaluetypes(), out.mInputValueTypes);
    //cl=ApiTextureNodeTypeInfo, field.mName = outputValueTypes field.mType = Octane::ApiTextureValueTypeSet, protoType=ApiTextureValueTypeSet
    ApiTextureValueTypeSetConverter::convert(in.outputvaluetypes(), out.mOutputValueTypes);
    //cl=ApiTextureNodeTypeInfo, field.mName = configurationsCount field.mType = uint32_t, protoType=uint32
    out.mConfigurationsCount = in.configurationscount();////simple 3////
    //cl=ApiTextureNodeTypeInfo, field.mName = configurations field.mType = Octane::ApiTextureNodeTypeInfo::Configuration *, protoType=repeated ApiTextureNodeTypeInfo_Configuration
    // configurations : convert to octane type
    // convert(in.configurations(), out.mConfigurations);
    if (in.configurations().size() > 0)
    {
        int arraySize = in.configurations().size();
        auto configArray = new Octane::ApiTextureNodeTypeInfo::Configuration[arraySize]; // memory leak
        for(int h = 0; h < arraySize; h++)
        {
            ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_ConfigurationConverter::convert(in.configurations().Get(h), configArray[h]);
        }
        out.mConfigurationsCount = arraySize;
        out.mConfigurations = configArray;
    }
    else
    {
        out.mConfigurationsCount = 0;
        out.mConfigurations = nullptr;
    }
    // all fields resolved OK;
}


void ApiTextureNodeTypeInfoConverter::convert(
    const Octane::ApiTextureNodeTypeInfo & in,
    octaneapi::ApiTextureNodeTypeInfo & out)
{

    // Found structure 1 ApiTextureNodeTypeInfo
    // from octane type = const Octane::ApiTextureNodeTypeInfo &,
        //to proto type = octaneapi::ApiTextureNodeTypeInfo &
    // list out parameters
    out.set_isvalid(true);////mDummy 4////
    out.set_outputmode( static_cast<octaneapi::TextureNodeTypeMode>(in.mOutputMode)); // enum 2
    out.set_inputmode( static_cast<octaneapi::TextureNodeTypeMode>(in.mInputMode)); // enum 2
    out.set_cantogglevaluetypesofpins(in.mCanToggleValueTypesOfPins);////simple 4b////
    out.set_staticoutputvaluetype( static_cast<octaneapi::TextureValueType>(in.mStaticOutputValueType)); // enum 2
    ApiTextureValueTypeSetConverter::convert(in.mInputValueTypes, *(out.mutable_inputvaluetypes()));
    ApiTextureValueTypeSetConverter::convert(in.mOutputValueTypes, *(out.mutable_outputvaluetypes()));
    out.set_configurationscount(in.mConfigurationsCount);////simple 4b////
    // configurations 2 convert to grpc type
    if(in.mConfigurations)
    {
        for(uint32_t h = 0; h < in.mConfigurationsCount; h++)
        {
            auto item = out.add_configurations();
            ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_ConfigurationConverter::convert(in.mConfigurations[h], *item);
        }
    }
    // all fields resolved OK;
}


} // namespace octaneGRPC
#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
