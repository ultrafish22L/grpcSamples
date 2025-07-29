// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapitexturenodetypeinfo_configuration_parameters.h"
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

void ApiTextureNodeTypeInfo_Configuration_ParametersConverter::convert(
    const Octane::ApiTextureNodeTypeInfo::Configuration::Parameters & in,
    octaneapi::ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration_ApiTextureNodeTypeInfo_Configuration_Parameters & out)
{

    // Found structure 3 Configuration
    // from octane type = const Octane::ApiTextureNodeTypeInfo::Configuration::Parameters &,
        //to proto type = octaneapi::ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration_ApiTextureNodeTypeInfo_Configuration_Parameters &
    // list out parameters
    // all fields resolved OK;
    // Found structure 3 Parameters
    // from octane type = const Octane::ApiTextureNodeTypeInfo::Configuration::Parameters &,
        //to proto type = octaneapi::ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration_ApiTextureNodeTypeInfo_Configuration_Parameters &
    // list out parameters
    out.set_outputvaluetype( static_cast<octaneapi::TextureValueType>(in.mOutputValueType)); // enum 2
    out.set_inputvaluetype( static_cast<octaneapi::TextureValueType>(in.mInputValueType)); // enum 2
    out.set_isinputvaluetypetoggled(in.mIsInputValueTypeToggled);////simple 4b////
    // all fields resolved OK;
}


void ApiTextureNodeTypeInfo_Configuration_ParametersConverter::convert(
    const octaneapi::ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration_ApiTextureNodeTypeInfo_Configuration_Parameters & in,
    Octane::ApiTextureNodeTypeInfo::Configuration::Parameters & out)
{

    // Found structure 4 Configuration
    // from proto type = const octaneapi::ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration_ApiTextureNodeTypeInfo_Configuration_Parameters &,
        //to octane type = Octane::ApiTextureNodeTypeInfo::Configuration::Parameters &
    // list out parameters
    // all fields resolved OK;
    // Found structure 4 Parameters
    // from proto type = const octaneapi::ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration_ApiTextureNodeTypeInfo_Configuration_Parameters &,
        //to octane type = Octane::ApiTextureNodeTypeInfo::Configuration::Parameters &
    // list out parameters
    //cl=Parameters, field.mName = outputValueType field.mType = Octane::TextureValueType, protoType=TextureValueType
    out.mOutputValueType = static_cast<Octane::TextureValueType>(in.outputvaluetype());// enum 1 
    //cl=Parameters, field.mName = inputValueType field.mType = Octane::TextureValueType, protoType=TextureValueType
    out.mInputValueType = static_cast<Octane::TextureValueType>(in.inputvaluetype());// enum 1 
    //cl=Parameters, field.mName = isInputValueTypeToggled field.mType = bool, protoType=bool
    out.mIsInputValueTypeToggled = in.isinputvaluetypetoggled();////simple 3////
    // all fields resolved OK;
}


#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
