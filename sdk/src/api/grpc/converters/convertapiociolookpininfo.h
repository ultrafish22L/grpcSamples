// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiOcioLookPinInfo; }
namespace octaneapi { class ApiOcioLookPinInfo; }

namespace OctaneGRPC
{
    struct ApiNodeInfoProxy;
}
namespace OctaneGRPC
{

class ApiOcioLookPinInfoConverter
{
public:
    static void convert(
        const octaneapi::ApiOcioLookPinInfo & in,
        Octane::ApiOcioLookPinInfo & out);

    static void convert(
        const Octane::ApiOcioLookPinInfo & in,
        octaneapi::ApiOcioLookPinInfo & out);
};

} //namespace OctaneGRPC;
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
