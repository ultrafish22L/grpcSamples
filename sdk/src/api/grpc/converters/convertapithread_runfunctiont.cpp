// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapithread_runfunctiont.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"

#if !defined(OCTANE_STANDALONE) && !defined(OCTANE_DLLEXPORT)
#include "grpcapinodeinfo.h"
#else 
class ApiNodeInfoProxy
{
    //stub
};
#endif

void ApiThread_RunFunctionTConverter::convert(
    const Octane::ApiThread::RunFunctionT & in,
    octaneapi::RunFunctionT & out)
{

    // Found typedef 2 RunFunctionT
}


void ApiThread_RunFunctionTConverter::convert(
    const octaneapi::RunFunctionT & in,
    Octane::ApiThread::RunFunctionT & out)
{

    // Found typedef 1 RunFunctionT
}


#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
