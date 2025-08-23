// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiTexturePinInfo; }
namespace octaneapi { class ApiTexturePinInfo; }

namespace OctaneGRPC
{
    struct ApiNodeInfoProxy;
}
namespace OctaneGRPC
{

class ApiTexturePinInfoConverter
{
public:
    static void convert(
        const octaneapi::ApiTexturePinInfo & in,
        Octane::ApiTexturePinInfo & out);

    static void convert(
        const Octane::ApiTexturePinInfo & in,
        octaneapi::ApiTexturePinInfo & out);
};

} //namespace OctaneGRPC;
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
