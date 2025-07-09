// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiAttributeInfo; }
namespace octaneapi { class ApiAttributeInfo; }

class ApiNodeInfoProxy;
class ApiAttributeInfoConverter
{
public:
    static void convert(
        const octaneapi::ApiAttributeInfo & in,
        Octane::ApiAttributeInfo & out);

    static void convert(
        const Octane::ApiAttributeInfo & in,
        octaneapi::ApiAttributeInfo & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
