// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiProjectionPinInfo; }
namespace octaneapi { class ApiProjectionPinInfo; }

namespace OctaneGRPC
{
    struct ApiNodeInfoProxy;
}
namespace OctaneGRPC
{

class ApiProjectionPinInfoConverter
{
public:
    static void convert(
        const octaneapi::ApiProjectionPinInfo & in,
        Octane::ApiProjectionPinInfo & out);

    static void convert(
        const Octane::ApiProjectionPinInfo & in,
        octaneapi::ApiProjectionPinInfo & out);
};

} //namespace OctaneGRPC;
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
