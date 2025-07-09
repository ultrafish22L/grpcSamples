// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
#include <functional>
#include "octaneinfos.grpc.pb.h"
#include <functional>
#include "octaneinfos.h"
namespace octaneapi { class ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration_ApiTextureNodeTypeInfo_Configuration_Interface; }
namespace octaneapi { class ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration_ApiTextureNodeTypeInfo_Configuration_Parameters; }
struct ApiNodeInfoProxy;
class ApiTextureNodeTypeInfo_Configuration_ParametersConverter
{
public:
    static void convert(
        const Octane::ApiTextureNodeTypeInfo::Configuration::Parameters & in,
        octaneapi::ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration_ApiTextureNodeTypeInfo_Configuration_Parameters & out);

    static void convert(
        const octaneapi::ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration_ApiTextureNodeTypeInfo_Configuration_Parameters & in,
        Octane::ApiTextureNodeTypeInfo::Configuration::Parameters & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
