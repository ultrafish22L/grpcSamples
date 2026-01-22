// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
#include <functional>
#include "octaneinfos.grpc.pb.h"
#include <functional>
#include "octaneinfos.h"
namespace octaneapi { class ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration_ApiTextureNodeTypeInfo_Configuration_Interface; }
namespace OctaneGRPC
{
    struct ApiNodeInfoProxy;
}
namespace OctaneGRPC
{

class ApiTextureNodeTypeInfo_Configuration_InterfaceConverter
{
public:
    static void convert(
        const Octane::ApiTextureNodeTypeInfo::Configuration::Interface & in,
        octaneapi::ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration_ApiTextureNodeTypeInfo_Configuration_Interface & out);

    static void convert(
        const octaneapi::ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration_ApiTextureNodeTypeInfo_Configuration_Interface & in,
        Octane::ApiTextureNodeTypeInfo::Configuration::Interface & out);
};

} //namespace OctaneGRPC;
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
