// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
#include <functional>
#include "octaneinfos.grpc.pb.h"
#include <functional>
#include "octaneinfos.h"
namespace octaneapi { class ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration; }
struct ApiNodeInfoProxy;
class ApiTransformPinInfo_ApiTransformPinInfo_BoundsConverter
{
public:
    static void convert(
        const octaneapi::ApiTransformPinInfo_ApiTransformPinInfo_Bounds & in,
        Octane::ApiTransformPinInfo::Bounds & out);

    static void convert(
        const Octane::ApiTransformPinInfo::Bounds & in,
        octaneapi::ApiTransformPinInfo_ApiTransformPinInfo_Bounds & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
