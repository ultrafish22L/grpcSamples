// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiProjectionPinInfo; }
namespace octaneapi { class ApiProjectionPinInfo; }

struct ApiNodeInfoProxy;
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
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
