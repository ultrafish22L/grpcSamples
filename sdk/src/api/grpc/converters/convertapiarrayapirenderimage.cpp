// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapiarrayapirenderimage.h"
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

void ApiArrayApiRenderImageConverter::convert(
    const octaneapi::ApiArrayApiRenderImage & in,
    std::vector<Octane::ApiRenderImage> & out)
{

    for (int i = 0; i < in.data_size(); ++i)
    {
        const ::octaneapi::ApiRenderImage & image = in.data(i);
        int imagesize = image.buffer().size();
        const char * imagedata = image.buffer().data().data();
        int imageSizeX = image.size().x();
        int imageSizeY = image.size().y();

        Octane::ApiRenderImage img;

        img.mCalculatedSamplesPerPixel = image.calculatedsamplesperpixel(); 
        img.mType = static_cast<Octane::ImageType>(image.type());
        img.mColorSpace = static_cast<Octane::NamedColorSpace>(image.colorspace());
        img.mIsLinear = image.islinear();
        img.mSize.x = image.size().x();
        img.mSize.y = image.size().y();
        img.mPitch = image.pitch();

        //buffer
        img.mBuffer = nullptr;
        size_t imgSize = img.mSize.x * img.mSize.x * img.mPitch;// image.mbuffer().size();
        if (imgSize > 0)
        {
            img.mBuffer = new char[imgSize];
            memcpy((void*)img.mBuffer, (char*)image.buffer().data().data(), image.buffer().size());
        }
        else
        {
            assert(false);
        }

        img.mTonemappedSamplesPerPixel = image.tonemappedsamplesperpixel();
        img.mCalculatedSamplesPerPixel = image.calculatedsamplesperpixel();
        img.mRegionSamplesPerPixel = image.regionsamplesperpixel();
        img.mMaxSamplesPerPixel = image.maxsamplesperpixel();
        img.mSamplesPerSecond = image.samplespersecond();
        img.mRenderTime = image.rendertime();
        img.mChangeLevel = static_cast<Octane::CLevelT>(image.changelevel().value());
        img.mHasPendingUpdates = image.haspendingupdates();
        img.mSubSampling = static_cast<Octane::SubSampleMode>(image.subsampling());
        img.mHasAlpha = image.hasalpha();
        img.mPremultipliedAlphaType = static_cast<Octane::PremultipliedAlphaType>(image.premultipliedalphatype());
        img.mKeepEnvironment = image.keepenvironment();
        out.push_back(img);
    }
}


void ApiArrayApiRenderImageConverter::convert(
    const Octane::ApiArray<Octane::ApiRenderImage> & in,
    octaneapi::ApiArrayApiRenderImage & out)
{

    for (size_t i = 0; i < in.mSize; ++i)
    {
        auto * newImage = out.add_data();
        const auto & renderImage = in.mData[i];
        newImage->set_type(static_cast<octaneapi::ImageType>(renderImage.mType));
        newImage->set_colorspace(static_cast<octaneapi::NamedColorSpace>(renderImage.mColorSpace));
        newImage->set_islinear(renderImage.mIsLinear);
    
        // Use mutable_ instead of set_allocated_
        auto * size = newImage->mutable_size();
        size->set_x(renderImage.mSize.x);
        size->set_y(renderImage.mSize.y); 
        newImage->set_pitch(renderImage.mPitch);
    
        if (renderImage.mBuffer)
        {
            auto * buffer = newImage->mutable_buffer();  // not set_allocated_*
            size_t imageBufferSize = 0;
            switch (renderImage.mType)
            {
            case Octane::IMAGE_TYPE_LDR_RGBA:
                imageBufferSize = renderImage.mSize.y * renderImage.mPitch * 4;
                break;
            case Octane::IMAGE_TYPE_LDR_MONO_ALPHA:
                imageBufferSize = renderImage.mSize.y * renderImage.mPitch * 2;
                break;
            case Octane::IMAGE_TYPE_HDR_RGBA:
                imageBufferSize = renderImage.mSize.y * renderImage.mPitch * 4;
                break;
            case Octane::IMAGE_TYPE_HDR_MONO_ALPHA:
                imageBufferSize = renderImage.mSize.y * renderImage.mPitch * 2;
                break;
            default:
                assert(false);
            }
            if (renderImage.mBuffer && imageBufferSize > 0)
            {
                buffer->set_size(static_cast<uint32_t>(imageBufferSize));
                buffer->set_data(reinterpret_cast<const char*>(renderImage.mBuffer), imageBufferSize);
            }
        }
    
        newImage->set_tonemappedsamplesperpixel(renderImage.mTonemappedSamplesPerPixel);
        newImage->set_calculatedsamplesperpixel(renderImage.mCalculatedSamplesPerPixel);
        newImage->set_regionsamplesperpixel(renderImage.mRegionSamplesPerPixel);
        newImage->set_maxsamplesperpixel(renderImage.mMaxSamplesPerPixel);
        newImage->set_samplespersecond(renderImage.mSamplesPerSecond);
        newImage->set_rendertime(renderImage.mRenderTime);
    
        auto* level = newImage->mutable_changelevel();
        level->set_value(renderImage.mChangeLevel);
    
        newImage->set_haspendingupdates(renderImage.mHasPendingUpdates);
        newImage->set_subsampling(static_cast<octaneapi::SubSampleMode>(renderImage.mSubSampling));
        newImage->set_hasalpha(renderImage.mHasAlpha);
        newImage->set_premultipliedalphatype(static_cast<octaneapi::PremultipliedAlphaType>(renderImage.mPremultipliedAlphaType));
        newImage->set_keepenvironment(renderImage.mKeepEnvironment);
    }
}


} // namespace octaneGRPC
#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
