// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapigaussiansplatcloudnode.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"
#ifdef NO_PCH
#include "apigaussiansplatting.grpc.pb.h"
#endif // #ifdef NO_PCH
#include "apigaussiansplatting.h"

#if !defined(OCTANE_STANDALONE) && !defined(OCTANE_DLLEXPORT)
#include "grpcapinodeinfo.h"
#else 
struct ApiNodeInfoProxy
{
    //stub
};
#endif

void ApiGaussianSplatCloudNodeConverter::convert(
    const octaneapi::ApiGaussianSplatCloudNode & in,
    Octane::ApiGaussianSplatCloudNode & out)
{

    // Found class 1 ApiGaussianSplatCloudNode
    // from proto type = const octaneapi::ApiGaussianSplatCloudNode &,
        //to octane type = Octane::ApiGaussianSplatCloudNode &
    // list out parameters
    // all fields resolved OK;
}


void ApiGaussianSplatCloudNodeConverter::convert(
    const Octane::ApiGaussianSplatCloudNode & in,
    octaneapi::ApiGaussianSplatCloudNode & out)
{

    // Found class 1 ApiGaussianSplatCloudNode
    // from octane type = const Octane::ApiGaussianSplatCloudNode &,
        //to proto type = octaneapi::ApiGaussianSplatCloudNode &
    // list out parameters
    // all fields resolved OK;
}


#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
