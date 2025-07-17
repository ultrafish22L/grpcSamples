// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapitexturepintypeinfo.h"
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

void ApiTexturePinTypeInfoConverter::convert(
    const octaneapi::ApiTexturePinTypeInfo & in,
    Octane::ApiTexturePinTypeInfo & out)
{

    // Found structure 1 ApiTexturePinTypeInfo
    // from proto type = const octaneapi::ApiTexturePinTypeInfo &,
        //to octane type = Octane::ApiTexturePinTypeInfo &
    // list out parameters
    //cl=ApiTexturePinTypeInfo, field.mName = isValid field.mType = bool, protoType=bool
    //cl=ApiTexturePinTypeInfo, field.mName = mode field.mType = Octane::TexturePinValueTypeMode, protoType=TexturePinValueTypeMode
    out.mMode = static_cast<Octane::TexturePinValueTypeMode>(in.mode());// enum 1 
    //cl=ApiTexturePinTypeInfo, field.mName = valueType field.mType = Octane::TextureValueType, protoType=TextureValueType
    out.mValueType = static_cast<Octane::TextureValueType>(in.valuetype());// enum 1 
    //cl=ApiTexturePinTypeInfo, field.mName = valueTypeWhenToggled field.mType = Octane::TextureValueType, protoType=TextureValueType
    out.mValueTypeWhenToggled = static_cast<Octane::TextureValueType>(in.valuetypewhentoggled());// enum 1 
    //cl=ApiTexturePinTypeInfo, field.mName = nodeInputTypesAreDerivedFromOutputType field.mType = bool, protoType=bool
    out.mNodeInputTypesAreDerivedFromOutputType = in.nodeinputtypesarederivedfromoutputtype();////simple 3////
    // all fields resolved OK;
}


void ApiTexturePinTypeInfoConverter::convert(
    const Octane::ApiTexturePinTypeInfo & in,
    octaneapi::ApiTexturePinTypeInfo & out)
{

    // Found structure 1 ApiTexturePinTypeInfo
    // from octane type = const Octane::ApiTexturePinTypeInfo &,
        //to proto type = octaneapi::ApiTexturePinTypeInfo &
    // list out parameters
    out.set_isvalid(true);////mDummy 4////
    out.set_mode( static_cast<octaneapi::TexturePinValueTypeMode>(in.mMode)); // enum 2
    out.set_valuetype( static_cast<octaneapi::TextureValueType>(in.mValueType)); // enum 2
    out.set_valuetypewhentoggled( static_cast<octaneapi::TextureValueType>(in.mValueTypeWhenToggled)); // enum 2
    out.set_nodeinputtypesarederivedfromoutputtype(in.mNodeInputTypesAreDerivedFromOutputType);////simple 4b////
    // all fields resolved OK;
}


#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
