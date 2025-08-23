// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiFloatPinInfo; }
namespace octaneapi { class ApiFloatPinInfo; }

namespace OctaneGRPC
{
    struct ApiNodeInfoProxy;
}
namespace OctaneGRPC
{

class ApiFloatPinInfoConverter
{
public:
    static void convert(
        const octaneapi::ApiFloatPinInfo & in,
        Octane::ApiFloatPinInfo & out);

    static void convert(
        const Octane::ApiFloatPinInfo & in,
        octaneapi::ApiFloatPinInfo & out);
};

} //namespace OctaneGRPC;
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
