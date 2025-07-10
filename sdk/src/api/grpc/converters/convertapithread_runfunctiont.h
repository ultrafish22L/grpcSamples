// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace octaneapi { class RunFunctionT; }
namespace Octane::ApiThread { struct ApiThread::RunFunctionT; }

class ApiNodeInfoProxy;
class ApiThread_RunFunctionTConverter
{
public:
    static void convert(
        const Octane::ApiThread::RunFunctionT & in,
        octaneapi::RunFunctionT & out);

    static void convert(
        const octaneapi::RunFunctionT & in,
        Octane::ApiThread::RunFunctionT & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
