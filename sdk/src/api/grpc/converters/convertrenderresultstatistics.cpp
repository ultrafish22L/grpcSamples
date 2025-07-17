// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertrenderresultstatistics.h"
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

void RenderResultStatisticsConverter::convert(
    const octaneapi::RenderResultStatistics & in,
    Octane::RenderResultStatistics & out)
{

    // Found structure 1 RenderResultStatistics
    // from proto type = const octaneapi::RenderResultStatistics &,
        //to octane type = Octane::RenderResultStatistics &
    // list out parameters
    //cl=RenderResultStatistics, field.mName = setSize field.mType = Octane::uint32_2, protoType=uint32_2
    out.mSetSize = {
       in.setsize().x(),
       in.setsize().y() };
    //cl=RenderResultStatistics, field.mName = usedSize field.mType = Octane::uint32_2, protoType=uint32_2
    out.mUsedSize = {
       in.usedsize().x(),
       in.usedsize().y() };
    //cl=RenderResultStatistics, field.mName = subSampleMode field.mType = Octane::SubSampleMode, protoType=SubSampleMode
    out.mSubSampleMode = static_cast<Octane::SubSampleMode>(in.subsamplemode());// enum 1 
    //cl=RenderResultStatistics, field.mName = upSamplingRatio field.mType = float, protoType=float
    out.mUpSamplingRatio = in.upsamplingratio();////simple 3////
    //cl=RenderResultStatistics, field.mName = bufferType field.mType = Octane::TonemapBufferType, protoType=TonemapBufferType
    out.mBufferType = static_cast<Octane::TonemapBufferType>(in.buffertype());// enum 1 
    //cl=RenderResultStatistics, field.mName = colorSpace field.mType = Octane::NamedColorSpace, protoType=NamedColorSpace
    out.mColorSpace = static_cast<Octane::NamedColorSpace>(in.colorspace());// enum 1 
    //cl=RenderResultStatistics, field.mName = isLinear field.mType = bool, protoType=bool
    out.mIsLinear = in.islinear();////simple 3////
    //cl=RenderResultStatistics, field.mName = hasAlpha field.mType = bool, protoType=bool
    out.mHasAlpha = in.hasalpha();////simple 3////
    //cl=RenderResultStatistics, field.mName = premultipliedAlphaType field.mType = Octane::PremultipliedAlphaType, protoType=PremultipliedAlphaType
    out.mPremultipliedAlphaType = static_cast<Octane::PremultipliedAlphaType>(in.premultipliedalphatype());// enum 1 
    //cl=RenderResultStatistics, field.mName = keepEnvironment field.mType = bool, protoType=bool
    out.mKeepEnvironment = in.keepenvironment();////simple 3////
    //cl=RenderResultStatistics, field.mName = changeLevel field.mType = Octane::CLevelT, protoType=CLevelT
    //TES86588 

    const octaneapi::CLevelT & changeLevelRef = in.changelevel();
    out.mChangeLevel = changeLevelRef.value();
    //cl=RenderResultStatistics, field.mName = hasPendingUpdates field.mType = bool, protoType=bool
    out.mHasPendingUpdates = in.haspendingupdates();////simple 3////
    //cl=RenderResultStatistics, field.mName = deepBinCount field.mType = uint8_t, protoType=uint32
    out.mDeepBinCount = in.deepbincount();////simple 3////
    //cl=RenderResultStatistics, field.mName = deepSeedSpp field.mType = uint32_t, protoType=uint32
    out.mDeepSeedSpp = in.deepseedspp();////simple 3////
    //cl=RenderResultStatistics, field.mName = cryptomatteSeedSpp field.mType = uint32_t, protoType=uint32
    out.mCryptomatteSeedSpp = in.cryptomatteseedspp();////simple 3////
    //cl=RenderResultStatistics, field.mName = deepPassesEnabled field.mType = bool, protoType=bool
    out.mDeepPassesEnabled = in.deeppassesenabled();////simple 3////
    //cl=RenderResultStatistics, field.mName = tonemapPassesCount field.mType = uint32_t, protoType=uint32
    out.mTonemapPassesCount = in.tonemappassescount();////simple 3////
    //cl=RenderResultStatistics, field.mName = tonemapPasses field.mType = Octane::RenderPassId [128], protoType=ApiArrayRenderPassId
    if (in.tonemappasses().data_size() == 128)
    {
        for(int h = 0; h < 128; h++)
        {
             out.mTonemapPasses[h] = static_cast<Octane::RenderPassId >(in.tonemappasses().data(h));
        }
    }
    else
    {
         assert(false);
    }
    //cl=RenderResultStatistics, field.mName = passesCount field.mType = uint32_t, protoType=uint32
    out.mPassesCount = in.passescount();////simple 3////
    //cl=RenderResultStatistics, field.mName = renderPasses field.mType = Octane::RenderPassId [128], protoType=ApiArrayRenderPassId
    if (in.renderpasses().data_size() == 128)
    {
        for(int h = 0; h < 128; h++)
        {
             out.mRenderPasses[h] = static_cast<Octane::RenderPassId >(in.renderpasses().data(h));
        }
    }
    else
    {
         assert(false);
    }
    //cl=RenderResultStatistics, field.mName = beautyWipeCount field.mType = uint32_t, protoType=uint32
    out.mBeautyWipeCount = in.beautywipecount();////simple 3////
    //cl=RenderResultStatistics, field.mName = beautySamplesPerPixel field.mType = uint32_t, protoType=uint32
    out.mBeautySamplesPerPixel = in.beautysamplesperpixel();////simple 3////
    //cl=RenderResultStatistics, field.mName = beautyMaxSamplesPerPixel field.mType = uint32_t, protoType=uint32
    out.mBeautyMaxSamplesPerPixel = in.beautymaxsamplesperpixel();////simple 3////
    //cl=RenderResultStatistics, field.mName = beautySamplesPerSecond field.mType = double, protoType=double
    out.mBeautySamplesPerSecond = in.beautysamplespersecond();////simple 3////
    //cl=RenderResultStatistics, field.mName = regionSamplesPerPixel field.mType = uint32_t, protoType=uint32
    out.mRegionSamplesPerPixel = in.regionsamplesperpixel();////simple 3////
    //cl=RenderResultStatistics, field.mName = denoisedSamplesPerPixel field.mType = uint32_t, protoType=uint32
    out.mDenoisedSamplesPerPixel = in.denoisedsamplesperpixel();////simple 3////
    //cl=RenderResultStatistics, field.mName = regionDenoisedSamplesPerPixel field.mType = uint32_t, protoType=uint32
    out.mRegionDenoisedSamplesPerPixel = in.regiondenoisedsamplesperpixel();////simple 3////
    //cl=RenderResultStatistics, field.mName = infoWipeCount field.mType = uint32_t, protoType=uint32
    out.mInfoWipeCount = in.infowipecount();////simple 3////
    //cl=RenderResultStatistics, field.mName = infoSamplesPerPixel field.mType = uint32_t, protoType=uint32
    out.mInfoSamplesPerPixel = in.infosamplesperpixel();////simple 3////
    //cl=RenderResultStatistics, field.mName = infoMaxSamplesPerPixel field.mType = uint32_t, protoType=uint32
    out.mInfoMaxSamplesPerPixel = in.infomaxsamplesperpixel();////simple 3////
    //cl=RenderResultStatistics, field.mName = infoSamplesPerSecond field.mType = double, protoType=double
    out.mInfoSamplesPerSecond = in.infosamplespersecond();////simple 3////
    //cl=RenderResultStatistics, field.mName = state field.mType = Octane::RenderState, protoType=RenderState
    out.mState = static_cast<Octane::RenderState>(in.state());// enum 1 
    //cl=RenderResultStatistics, field.mName = renderTime field.mType = double, protoType=double
    out.mRenderTime = in.rendertime();////simple 3////
    //cl=RenderResultStatistics, field.mName = estimatedRenderTime field.mType = double, protoType=double
    out.mEstimatedRenderTime = in.estimatedrendertime();////simple 3////
    // all fields resolved OK;
}


void RenderResultStatisticsConverter::convert(
    const Octane::RenderResultStatistics & in,
    octaneapi::RenderResultStatistics & out)
{

    // Found structure 1 RenderResultStatistics
    // from octane type = const Octane::RenderResultStatistics &,
        //to proto type = octaneapi::RenderResultStatistics &
    // list out parameters

    octaneapi::uint32_2 * setSizeOut = new octaneapi::uint32_2;////approved////
    setSizeOut->set_x(in.mSetSize.x);
    setSizeOut->set_y(in.mSetSize.y);
    out.set_allocated_setsize(setSizeOut);

    octaneapi::uint32_2 * usedSizeOut = new octaneapi::uint32_2;////approved////
    usedSizeOut->set_x(in.mUsedSize.x);
    usedSizeOut->set_y(in.mUsedSize.y);
    out.set_allocated_usedsize(usedSizeOut);
    out.set_subsamplemode( static_cast<octaneapi::SubSampleMode>(in.mSubSampleMode)); // enum 2
    out.set_upsamplingratio(in.mUpSamplingRatio);////simple 4b////
    out.set_buffertype( static_cast<octaneapi::TonemapBufferType>(in.mBufferType)); // enum 2
    out.set_colorspace( static_cast<octaneapi::NamedColorSpace>(in.mColorSpace)); // enum 2
    out.set_islinear(in.mIsLinear);////simple 4b////
    out.set_hasalpha(in.mHasAlpha);////simple 4b////
    out.set_premultipliedalphatype( static_cast<octaneapi::PremultipliedAlphaType>(in.mPremultipliedAlphaType)); // enum 2
    out.set_keepenvironment(in.mKeepEnvironment);////simple 4b////
    //TEST788 

    octaneapi::CLevelT * changeLevelOut = new octaneapi::CLevelT;////132//approved////
    changeLevelOut->set_value(in.mChangeLevel);
    out.set_allocated_changelevel(changeLevelOut);
    out.set_haspendingupdates(in.mHasPendingUpdates);////simple 4b////
    out.set_deepbincount(in.mDeepBinCount);////simple 4b////
    out.set_deepseedspp(in.mDeepSeedSpp);////simple 4b////
    out.set_cryptomatteseedspp(in.mCryptomatteSeedSpp);////simple 4b////
    out.set_deeppassesenabled(in.mDeepPassesEnabled);////simple 4b////
    out.set_tonemappassescount(in.mTonemapPassesCount);////simple 4b////
   // [] array
    octaneapi::ApiArrayRenderPassId * tonemapPassesOut = new octaneapi::ApiArrayRenderPassId;////approved////
    for(int h = 0; h < 128; h++)
    {
        tonemapPassesOut->add_data(static_cast<octaneapi::RenderPassId >(in.mTonemapPasses[h]));// 5
    }
    out.set_allocated_tonemappasses(tonemapPassesOut);
    out.set_passescount(in.mPassesCount);////simple 4b////
   // [] array
    octaneapi::ApiArrayRenderPassId * renderPassesOut = new octaneapi::ApiArrayRenderPassId;////approved////
    for(int h = 0; h < 128; h++)
    {
        renderPassesOut->add_data(static_cast<octaneapi::RenderPassId >(in.mRenderPasses[h]));// 5
    }
    out.set_allocated_renderpasses(renderPassesOut);
    out.set_beautywipecount(in.mBeautyWipeCount);////simple 4b////
    out.set_beautysamplesperpixel(in.mBeautySamplesPerPixel);////simple 4b////
    out.set_beautymaxsamplesperpixel(in.mBeautyMaxSamplesPerPixel);////simple 4b////
    out.set_beautysamplespersecond(in.mBeautySamplesPerSecond);////simple 4b////
    out.set_regionsamplesperpixel(in.mRegionSamplesPerPixel);////simple 4b////
    out.set_denoisedsamplesperpixel(in.mDenoisedSamplesPerPixel);////simple 4b////
    out.set_regiondenoisedsamplesperpixel(in.mRegionDenoisedSamplesPerPixel);////simple 4b////
    out.set_infowipecount(in.mInfoWipeCount);////simple 4b////
    out.set_infosamplesperpixel(in.mInfoSamplesPerPixel);////simple 4b////
    out.set_infomaxsamplesperpixel(in.mInfoMaxSamplesPerPixel);////simple 4b////
    out.set_infosamplespersecond(in.mInfoSamplesPerSecond);////simple 4b////
    out.set_state( static_cast<octaneapi::RenderState>(in.mState)); // enum 2
    out.set_rendertime(in.mRenderTime);////simple 4b////
    out.set_estimatedrendertime(in.mEstimatedRenderTime);////simple 4b////
    // all fields resolved OK;
}


#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
