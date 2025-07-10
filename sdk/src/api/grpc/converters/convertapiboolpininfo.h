// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiBoolPinInfo; }
namespace octaneapi { class ApiBoolPinInfo; }

class ApiNodeInfoProxy;
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
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
