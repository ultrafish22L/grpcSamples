// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiStringPinInfo; }
namespace octaneapi { class ApiStringPinInfo; }

class ApiNodeInfoProxy;
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
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
