// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapideviceresourcestatistics.h"
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
class ApiNodeInfoProxy
{
    //stub
};
#endif

void ApiDeviceResourceStatisticsConverter::convert(
    const octaneapi::ApiDeviceResourceStatistics & in,
    Octane::ApiDeviceResourceStatistics & out)
{

    // Found structure 1 ApiDeviceResourceStatistics
    // from proto type = const octaneapi::ApiDeviceResourceStatistics &,
        //to octane type = Octane::ApiDeviceResourceStatistics &
    // list out parameters
    //cl=ApiDeviceResourceStatistics, field.mName = runtimeDataSize field.mType = uint64_t, protoType=uint64
    out.mRuntimeDataSize = in.runtimedatasize();////simple 3////
    //cl=ApiDeviceResourceStatistics, field.mName = filmDataSize field.mType = uint64_t, protoType=uint64
    out.mFilmDataSize = in.filmdatasize();////simple 3////
    //cl=ApiDeviceResourceStatistics, field.mName = geometryDataSize field.mType = uint64_t, protoType=uint64
    out.mGeometryDataSize = in.geometrydatasize();////simple 3////
    //cl=ApiDeviceResourceStatistics, field.mName = nodeSystemDataSize field.mType = uint64_t, protoType=uint64
    out.mNodeSystemDataSize = in.nodesystemdatasize();////simple 3////
    //cl=ApiDeviceResourceStatistics, field.mName = imagesDataSize field.mType = uint64_t, protoType=uint64
    out.mImagesDataSize = in.imagesdatasize();////simple 3////
    //cl=ApiDeviceResourceStatistics, field.mName = compositorDataSize field.mType = uint64_t, protoType=uint64
    out.mCompositorDataSize = in.compositordatasize();////simple 3////
    //cl=ApiDeviceResourceStatistics, field.mName = denoiserDataSize field.mType = uint64_t, protoType=uint64
    out.mDenoiserDataSize = in.denoiserdatasize();////simple 3////
    // all fields resolved OK;
}


void ApiDeviceResourceStatisticsConverter::convert(
    const Octane::ApiDeviceResourceStatistics & in,
    octaneapi::ApiDeviceResourceStatistics & out)
{

    // Found structure 1 ApiDeviceResourceStatistics
    // from octane type = const Octane::ApiDeviceResourceStatistics &,
        //to proto type = octaneapi::ApiDeviceResourceStatistics &
    // list out parameters
    out.set_runtimedatasize(in.mRuntimeDataSize);////simple 4b////
    out.set_filmdatasize(in.mFilmDataSize);////simple 4b////
    out.set_geometrydatasize(in.mGeometryDataSize);////simple 4b////
    out.set_nodesystemdatasize(in.mNodeSystemDataSize);////simple 4b////
    out.set_imagesdatasize(in.mImagesDataSize);////simple 4b////
    out.set_compositordatasize(in.mCompositorDataSize);////simple 4b////
    out.set_denoiserdatasize(in.mDenoiserDataSize);////simple 4b////
    // all fields resolved OK;
}


#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
