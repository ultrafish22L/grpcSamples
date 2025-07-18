// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiNodePinInfo; }
namespace octaneapi { class ApiNodePinInfo; }

class ApiNodeInfoProxy;
class ApiNodePinInfoConverter
{
public:
    static void convert(
        const octaneapi::ApiNodePinInfo & in,
        Octane::ApiNodePinInfo & out);

    static void convert(
        const Octane::ApiNodePinInfo & in,
        octaneapi::ApiNodePinInfo & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
