// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiStringPinInfo; }
namespace octaneapi { class ApiStringPinInfo; }

namespace OctaneGRPC
{
    struct ApiNodeInfoProxy;
}
namespace OctaneGRPC
{

class ApiStringPinInfoConverter
{
public:
    static void convert(
        const octaneapi::ApiStringPinInfo & in,
        Octane::ApiStringPinInfo & out);

    static void convert(
        const Octane::ApiStringPinInfo & in,
        octaneapi::ApiStringPinInfo & out);
};

} //namespace OctaneGRPC;
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
