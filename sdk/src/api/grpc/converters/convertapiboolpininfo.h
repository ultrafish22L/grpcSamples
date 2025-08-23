// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiBoolPinInfo; }
namespace octaneapi { class ApiBoolPinInfo; }

namespace OctaneGRPC
{
    struct ApiNodeInfoProxy;
}
namespace OctaneGRPC
{

class ApiBoolPinInfoConverter
{
public:
    static void convert(
        const octaneapi::ApiBoolPinInfo & in,
        Octane::ApiBoolPinInfo & out);

    static void convert(
        const Octane::ApiBoolPinInfo & in,
        octaneapi::ApiBoolPinInfo & out);
};

} //namespace OctaneGRPC;
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
