// Copyright (C) 2026 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapitexturenodetypeinfo_apitexturenodetypeinfo_configuration.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"
#ifdef NO_PCH
#include "apimaterialx.grpc.pb.h"
#endif // #ifdef NO_PCH
#include "apimaterialx.h"
#ifdef NO_PCH
#include "octaneinfos.grpc.pb.h"
#endif // #ifdef NO_PCH
#include "octaneinfos.h"

#include "convertapitexturenodetypeinfo.h"
#include "convertapitexturenodetypeinfo_apitexturenodetypeinfo_configuration.h"
#include "convertapitexturenodetypeinfo_configuration_interface.h"
#include "convertapitexturenodetypeinfo_configuration_parameters.h"
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

void ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_ConfigurationConverter::convert(
    const octaneapi::ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration & in,
    Octane::ApiTextureNodeTypeInfo::Configuration & out)
{

    // Found structure 4 Configuration
    // from proto type = const octaneapi::ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration &,
        //to octane type = Octane::ApiTextureNodeTypeInfo::Configuration &
    // list out parameters
    //cl=Configuration, field.mName = nodeType field.mType = Octane::NodeType, protoType=NodeType
    out.mNodeType = static_cast<Octane::NodeType>(in.nodetype());// enum 1 
    //cl=Configuration, field.mName = parameters field.mType = Octane::ApiTextureNodeTypeInfo::Configuration::Parameters, protoType=Parameters
    //// 721 ////
    ApiTextureNodeTypeInfo_Configuration_ParametersConverter::convert(in.parameters(), out.mParameters);
    //cl=Configuration, field.mName = interface field.mType = Octane::ApiTextureNodeTypeInfo::Configuration::Interface, protoType=ApiTextureNodeTypeInfo.ApiTextureNodeTypeInfo_Configuration.ApiTextureNodeTypeInfo_Configuration_Interface
    //// 722 ////
    ApiTextureNodeTypeInfo_Configuration_InterfaceConverter::convert(in.interface(), out.mInterface);
    // all fields resolved OK;
}


void ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_ConfigurationConverter::convert(
    const Octane::ApiTextureNodeTypeInfo::Configuration & in,
    octaneapi::ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration & out)
{

    // Found structure 3 Configuration
    // from octane type = const Octane::ApiTextureNodeTypeInfo::Configuration &,
        //to proto type = octaneapi::ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration &
    // list out parameters
    out.set_nodetype( static_cast<octaneapi::NodeType>(in.mNodeType)); // enum 2
    //// 721 ////
    ApiTextureNodeTypeInfo_Configuration_ParametersConverter::convert(in.mParameters, *(out.mutable_parameters()));
    //// 722 ////
    ApiTextureNodeTypeInfo_Configuration_InterfaceConverter::convert(in.mInterface, *(out.mutable_interface()));
    // all fields resolved OK;
}


} // namespace octaneGRPC
#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
