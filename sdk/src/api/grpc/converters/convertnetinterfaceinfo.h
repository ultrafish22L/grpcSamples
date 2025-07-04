// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct NetInterfaceInfo; }
namespace octaneapi { class NetInterfaceInfo; }

struct ApiNodeInfoProxy;
class NetInterfaceInfoConverter
{
public:
    static void convert(
        const octaneapi::NetInterfaceInfo & in,
        Octane::NetInterfaceInfo & out);

    static void convert(
        const Octane::NetInterfaceInfo & in,
        octaneapi::NetInterfaceInfo & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
