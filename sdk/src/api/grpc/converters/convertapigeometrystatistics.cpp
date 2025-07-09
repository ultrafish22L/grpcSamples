// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapigeometrystatistics.h"
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

void ApiGeometryStatisticsConverter::convert(
    const octaneapi::ApiGeometryStatistics & in,
    Octane::ApiGeometryStatistics & out)
{

    // Found structure 1 ApiGeometryStatistics
    // from proto type = const octaneapi::ApiGeometryStatistics &,
        //to octane type = Octane::ApiGeometryStatistics &
    // list out parameters
    //cl=ApiGeometryStatistics, field.mName = triCount field.mType = uint32_t, protoType=uint32
    out.mTriCount = in.tricount();////simple 3////
    //cl=ApiGeometryStatistics, field.mName = dispTriCount field.mType = uint32_t, protoType=uint32
    out.mDispTriCount = in.disptricount();////simple 3////
    //cl=ApiGeometryStatistics, field.mName = hairSegCount field.mType = uint32_t, protoType=uint32
    out.mHairSegCount = in.hairsegcount();////simple 3////
    //cl=ApiGeometryStatistics, field.mName = voxelCount field.mType = uint64_t, protoType=uint64
    out.mVoxelCount = in.voxelcount();////simple 3////
    //cl=ApiGeometryStatistics, field.mName = gaussianSplatCount field.mType = uint64_t, protoType=uint64
    out.mGaussianSplatCount = in.gaussiansplatcount();////simple 3////
    //cl=ApiGeometryStatistics, field.mName = sphereCount field.mType = uint32_t, protoType=uint32
    out.mSphereCount = in.spherecount();////simple 3////
    //cl=ApiGeometryStatistics, field.mName = instanceCount field.mType = uint32_t, protoType=uint32
    out.mInstanceCount = in.instancecount();////simple 3////
    //cl=ApiGeometryStatistics, field.mName = emitPriCount field.mType = uint32_t, protoType=uint32
    out.mEmitPriCount = in.emitpricount();////simple 3////
    //cl=ApiGeometryStatistics, field.mName = emitInstanceCount field.mType = uint32_t, protoType=uint32
    out.mEmitInstanceCount = in.emitinstancecount();////simple 3////
    //cl=ApiGeometryStatistics, field.mName = analyticLiCount field.mType = uint32_t, protoType=uint32
    out.mAnalyticLiCount = in.analyticlicount();////simple 3////
    // all fields resolved OK;
}


void ApiGeometryStatisticsConverter::convert(
    const Octane::ApiGeometryStatistics & in,
    octaneapi::ApiGeometryStatistics & out)
{

    // Found structure 1 ApiGeometryStatistics
    // from octane type = const Octane::ApiGeometryStatistics &,
        //to proto type = octaneapi::ApiGeometryStatistics &
    // list out parameters
    out.set_tricount(in.mTriCount);////simple 4b////
    out.set_disptricount(in.mDispTriCount);////simple 4b////
    out.set_hairsegcount(in.mHairSegCount);////simple 4b////
    out.set_voxelcount(in.mVoxelCount);////simple 4b////
    out.set_gaussiansplatcount(in.mGaussianSplatCount);////simple 4b////
    out.set_spherecount(in.mSphereCount);////simple 4b////
    out.set_instancecount(in.mInstanceCount);////simple 4b////
    out.set_emitpricount(in.mEmitPriCount);////simple 4b////
    out.set_emitinstancecount(in.mEmitInstanceCount);////simple 4b////
    out.set_analyticlicount(in.mAnalyticLiCount);////simple 4b////
    // all fields resolved OK;
}


#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
