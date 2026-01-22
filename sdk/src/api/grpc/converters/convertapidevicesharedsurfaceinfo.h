// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiDeviceSharedSurfaceInfo; }
namespace octaneapi { class ApiDeviceSharedSurfaceInfo; }

namespace OctaneGRPC
{
    struct ApiNodeInfoProxy;
}
namespace OctaneGRPC
{

class ApiDeviceSharedSurfaceInfoConverter
{
public:
    static void convert(
        const octaneapi::ApiDeviceSharedSurfaceInfo & in,
        Octane::ApiDeviceSharedSurfaceInfo & out);

    static void convert(
        const Octane::ApiDeviceSharedSurfaceInfo & in,
        octaneapi::ApiDeviceSharedSurfaceInfo & out);
};

} //namespace OctaneGRPC;
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
