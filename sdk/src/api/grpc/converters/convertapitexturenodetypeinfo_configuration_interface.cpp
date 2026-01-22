// Copyright (C) 2026 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapitexturenodetypeinfo_configuration_interface.h"
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

void ApiTextureNodeTypeInfo_Configuration_InterfaceConverter::convert(
    const Octane::ApiTextureNodeTypeInfo::Configuration::Interface & in,
    octaneapi::ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration_ApiTextureNodeTypeInfo_Configuration_Interface & out)
{

    // Found structure 3 Configuration
    // from octane type = const Octane::ApiTextureNodeTypeInfo::Configuration::Interface &,
        //to proto type = octaneapi::ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration_ApiTextureNodeTypeInfo_Configuration_Interface &
    // list out parameters
    // all fields resolved OK;
    // Found structure 3 Interface
    // from octane type = const Octane::ApiTextureNodeTypeInfo::Configuration::Interface &,
        //to proto type = octaneapi::ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration_ApiTextureNodeTypeInfo_Configuration_Interface &
    // list out parameters
    out.set_outputvaluetype( static_cast<octaneapi::TextureValueType>(in.mOutputValueType)); // enum 2
    // mInputValueTypes
    for(uint32_t h = 0; h < in.mInputPinCount; h++)
    {
        out.add_inputvaluetypes(static_cast<octaneapi::TextureValueType>(in.mInputValueTypes[h]));
        out.add_inputpinids(static_cast<octaneapi::PinId>(in.mInputPinIds[h]));
    }
    out.set_inputpincount(in.mInputPinCount);////simple 4b////
    // all fields resolved OK;
}


void ApiTextureNodeTypeInfo_Configuration_InterfaceConverter::convert(
    const octaneapi::ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration_ApiTextureNodeTypeInfo_Configuration_Interface & in,
    Octane::ApiTextureNodeTypeInfo::Configuration::Interface & out)
{

    // Found structure 4 Configuration
    // from proto type = const octaneapi::ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration_ApiTextureNodeTypeInfo_Configuration_Interface &,
        //to octane type = Octane::ApiTextureNodeTypeInfo::Configuration::Interface &
    // list out parameters
    // all fields resolved OK;
    // Found structure 4 Interface
    // from proto type = const octaneapi::ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration_ApiTextureNodeTypeInfo_Configuration_Interface &,
        //to octane type = Octane::ApiTextureNodeTypeInfo::Configuration::Interface &
    // list out parameters
    //cl=Interface, field.mName = outputValueType field.mType = Octane::TextureValueType, protoType=TextureValueType
    out.mOutputValueType = static_cast<Octane::TextureValueType>(in.outputvaluetype());// enum 1 
    //cl=Interface, field.mName = inputValueTypes field.mType = Octane::TextureValueType *, protoType=repeated TextureValueType
    // mInputValueTypes
    if (in.inputvaluetypes().size() > 0)
    {
        int arraySize = in.inputpincount();
        auto inputValueTypesArray = new Octane::TextureValueType[arraySize]; // memory leak
        auto inputPinIds = new uint32_t[arraySize]; // memory leak
        for(int h = 0; h < arraySize; h++)
        {
            inputValueTypesArray[h] = static_cast<Octane::TextureValueType>(in.inputvaluetypes().Get(h));
            inputPinIds[h] = in.inputpinids().Get(h);
        }
        out.mInputPinCount = arraySize;
        out.mInputValueTypes = inputValueTypesArray;
    }
    else
    {
        out.mInputPinCount = 0;
        out.mInputValueTypes = nullptr;
    }
    //cl=Interface, field.mName = inputPinCount field.mType = uint32_t, protoType=uint32
    out.mInputPinCount = in.inputpincount();////simple 3////
    // all fields resolved OK;
}


} // namespace octaneGRPC
#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
