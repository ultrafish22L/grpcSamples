// Copyright (C) 2026 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapidevicesharedsurfaceinfo.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"
#ifdef NO_PCH
#include "apirender.grpc.pb.h"
#endif // #ifdef NO_PCH
#include "apirender.h"

#if !defined(OCTANE_STANDALONE) && !defined(OCTANE_DLLEXPORT)
#include "grpcapinodeinfo.h"
#else 
struct ApiNodeInfoProxy
{
    //stub
};
#endif

namespace OctaneGRPC
{

void ApiDeviceSharedSurfaceInfoConverter::convert(
    const octaneapi::ApiDeviceSharedSurfaceInfo & in,
    Octane::ApiDeviceSharedSurfaceInfo & out)
{

    // Found structure 1 ApiDeviceSharedSurfaceInfo
    // from proto type = const octaneapi::ApiDeviceSharedSurfaceInfo &,
        //to octane type = Octane::ApiDeviceSharedSurfaceInfo &
    // list out parameters
}


void ApiDeviceSharedSurfaceInfoConverter::convert(
    const Octane::ApiDeviceSharedSurfaceInfo & in,
    octaneapi::ApiDeviceSharedSurfaceInfo & out)
{

    // Found structure 1 ApiDeviceSharedSurfaceInfo
    // from octane type = const Octane::ApiDeviceSharedSurfaceInfo &,
        //to proto type = octaneapi::ApiDeviceSharedSurfaceInfo &
    // list out parameters
}


} // namespace octaneGRPC
#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
