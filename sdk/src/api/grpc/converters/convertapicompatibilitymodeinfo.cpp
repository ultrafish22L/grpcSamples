// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapicompatibilitymodeinfo.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"
#ifdef NO_PCH
#include "octaneinfos.grpc.pb.h"
#endif // #ifdef NO_PCH
#include "octaneinfos.h"

#if !defined(OCTANE_STANDALONE) && !defined(OCTANE_DLLEXPORT)
#include "grpcapinodeinfo.h"
#else 
struct ApiNodeInfoProxy
{
    //stub
};
#endif

void ApiCompatibilityModeInfoConverter::convert(
    const octaneapi::ApiCompatibilityModeInfo & in,
    Octane::ApiCompatibilityModeInfo & out)
{

    // Found class 1 ApiCompatibilityModeInfo
    // from proto type = const octaneapi::ApiCompatibilityModeInfo &,
        //to octane type = Octane::ApiCompatibilityModeInfo &
    // list out parameters
    // all fields resolved OK;
}


void ApiCompatibilityModeInfoConverter::convert(
    const Octane::ApiCompatibilityModeInfo & in,
    octaneapi::ApiCompatibilityModeInfo & out)
{

    // Found class 1 ApiCompatibilityModeInfo
    // from octane type = const Octane::ApiCompatibilityModeInfo &,
        //to proto type = octaneapi::ApiCompatibilityModeInfo &
    // list out parameters
    // all fields resolved OK;
}


#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
