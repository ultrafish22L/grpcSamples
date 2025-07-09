// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiTexturePinTypeInfo; }
namespace octaneapi { class ApiTexturePinTypeInfo; }

struct ApiNodeInfoProxy;
class ApiTexturePinTypeInfoConverter
{
public:
    static void convert(
        const octaneapi::ApiTexturePinTypeInfo & in,
        Octane::ApiTexturePinTypeInfo & out);

    static void convert(
        const Octane::ApiTexturePinTypeInfo & in,
        octaneapi::ApiTexturePinTypeInfo & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
