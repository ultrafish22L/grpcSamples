// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapitexturestatistics.h"
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

void ApiTextureStatisticsConverter::convert(
    const octaneapi::ApiTextureStatistics & in,
    Octane::ApiTextureStatistics & out)
{

    // Found structure 1 ApiTextureStatistics
    // from proto type = const octaneapi::ApiTextureStatistics &,
        //to octane type = Octane::ApiTextureStatistics &
    // list out parameters
    //cl=ApiTextureStatistics, field.mName = usedRgba32Textures field.mType = uint32_t, protoType=uint32
    out.mUsedRgba32Textures = in.usedrgba32textures();////simple 3////
    //cl=ApiTextureStatistics, field.mName = usedRgba64Textures field.mType = uint32_t, protoType=uint32
    out.mUsedRgba64Textures = in.usedrgba64textures();////simple 3////
    //cl=ApiTextureStatistics, field.mName = usedY8Textures field.mType = uint32_t, protoType=uint32
    out.mUsedY8Textures = in.usedy8textures();////simple 3////
    //cl=ApiTextureStatistics, field.mName = usedY16Textures field.mType = uint32_t, protoType=uint32
    out.mUsedY16Textures = in.usedy16textures();////simple 3////
    //cl=ApiTextureStatistics, field.mName = usedVirtualTextures field.mType = uint32_t, protoType=uint32
    out.mUsedVirtualTextures = in.usedvirtualtextures();////simple 3////
    // all fields resolved OK;
}


void ApiTextureStatisticsConverter::convert(
    const Octane::ApiTextureStatistics & in,
    octaneapi::ApiTextureStatistics & out)
{

    // Found structure 1 ApiTextureStatistics
    // from octane type = const Octane::ApiTextureStatistics &,
        //to proto type = octaneapi::ApiTextureStatistics &
    // list out parameters
    out.set_usedrgba32textures(in.mUsedRgba32Textures);////simple 4b////
    out.set_usedrgba64textures(in.mUsedRgba64Textures);////simple 4b////
    out.set_usedy8textures(in.mUsedY8Textures);////simple 4b////
    out.set_usedy16textures(in.mUsedY16Textures);////simple 4b////
    out.set_usedvirtualtextures(in.mUsedVirtualTextures);////simple 4b////
    // all fields resolved OK;
}


#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
