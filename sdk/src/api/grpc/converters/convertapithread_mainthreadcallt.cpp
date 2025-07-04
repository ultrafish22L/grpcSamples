// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapithread_mainthreadcallt.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"

#if !defined(OCTANE_STANDALONE) && !defined(OCTANE_DLLEXPORT)
#include "grpcapinodeinfo.h"
#else 
struct ApiNodeInfoProxy
{
    //stub
};
#endif

void ApiThread_MainThreadCallTConverter::convert(
    const Octane::ApiThread::MainThreadCallT & in,
    octaneapi::MainThreadCallT & out)
{

    // Found typedef 2 MainThreadCallT
}


void ApiThread_MainThreadCallTConverter::convert(
    const octaneapi::MainThreadCallT & in,
    Octane::ApiThread::MainThreadCallT & out)
{

    // Found typedef 1 MainThreadCallT
}


#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
