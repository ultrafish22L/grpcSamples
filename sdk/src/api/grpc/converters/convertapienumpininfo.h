// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiEnumPinInfo; }
namespace octaneapi { class ApiEnumPinInfo; }

struct ApiNodeInfoProxy;
class ApiEnumPinInfoConverter
{
public:
    static void convert(
        const octaneapi::ApiEnumPinInfo & in,
        Octane::ApiEnumPinInfo & out);

    static void convert(
        const Octane::ApiEnumPinInfo & in,
        octaneapi::ApiEnumPinInfo & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
