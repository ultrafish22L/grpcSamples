// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
#include <functional>
namespace Octane { struct ApiNodeInfo; }
namespace octaneapi { class ApiNodeInfo; }
namespace OctaneGRPC
{
    struct ApiNodeInfoProxy;
}
namespace OctaneGRPC
{

class ApiNodeInfoConverter
{
public:
#if !defined(OCTANE_STANDALONE) && !defined(OCTANE_DLLEXPORT)
    static void convert(
        const octaneapi::ApiNodeInfo & in,
        ApiNodeInfoProxy & out);
#endif // #if !defined(OCTANE_STANDALONE) && !defined(OCTANE_DLLEXPORT)
#if defined(OCTANE_STANDALONE) || defined(OCTANE_DLLEXPORT) 

    static void convert(
        const Octane::ApiNodeInfo & in,
        octaneapi::ApiNodeInfo & out);
#endif // #if defined(OCTANE_STANDALONE) || defined(OCTANE_DLLEXPORT) 
};

} //namespace OctaneGRPC;
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
