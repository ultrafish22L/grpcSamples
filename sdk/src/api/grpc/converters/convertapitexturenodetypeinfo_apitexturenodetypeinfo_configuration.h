// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
#include <functional>
#include "octaneinfos.h"
namespace octaneapi { class ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration; }
struct ApiNodeInfoProxy;
class ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_ConfigurationConverter
{
public:
    static void convert(
        const octaneapi::ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration & in,
        Octane::ApiTextureNodeTypeInfo::Configuration & out);

    static void convert(
        const Octane::ApiTextureNodeTypeInfo::Configuration & in,
        octaneapi::ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
