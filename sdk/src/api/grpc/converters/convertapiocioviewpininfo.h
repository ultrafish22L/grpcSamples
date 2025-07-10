// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiOcioViewPinInfo; }
namespace octaneapi { class ApiOcioViewPinInfo; }

class ApiNodeInfoProxy;
class ApiOcioViewPinInfoConverter
{
public:
    static void convert(
        const octaneapi::ApiOcioViewPinInfo & in,
        Octane::ApiOcioViewPinInfo & out);

    static void convert(
        const Octane::ApiOcioViewPinInfo & in,
        octaneapi::ApiOcioViewPinInfo & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
