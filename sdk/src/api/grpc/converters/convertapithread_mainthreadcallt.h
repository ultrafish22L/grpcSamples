// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace octaneapi { class MainThreadCallT; }
namespace Octane::ApiThread { struct ApiThread::MainThreadCallT; }

struct ApiNodeInfoProxy;
class ApiThread_MainThreadCallTConverter
{
public:
    static void convert(
        const Octane::ApiThread::MainThreadCallT & in,
        octaneapi::MainThreadCallT & out);

    static void convert(
        const octaneapi::MainThreadCallT & in,
        Octane::ApiThread::MainThreadCallT & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
