// Copyright (C) 2025 OTOY NZ Ltd.

// myself
#include "octanegrpcwrapimage.h"

using namespace OctaneWrap;


Image* Image::loadFromFile(
    const std::string &fullPath)
{
    ApiImageProxy apiImage = ApiImageProxy::loadFromFile(fullPath.c_str());
    if (!apiImage.isNull())
    {
        return new Image(apiImage);
    }
    return NULL;
}


Image* Image::loadFromMemory(
    const void   *imageData,
    const size_t sizeInBytes)
{
    ApiImageProxy apiImage = ApiImageProxy::loadFromMemory(imageData, sizeInBytes);
    if (!apiImage.isNull())
    {
        return new Image(apiImage);
    }
    return NULL;
}


Image::Image(
    const Octane::ApiImage::PixelFormat pixelFormat,
    const int                           width,
    const int                           height,
    const bool                          clear)
{
    mApiImage = ApiImageProxy::create(pixelFormat, width, height, clear);
}


Image::Image(
    const Octane::ApiImage::PixelFormat pixelFormat,
    const int                           width,
    const int                           height,
    const void *const                   data)
{
    mApiImage = ApiImageProxy::create(pixelFormat, width, height, data);
}


Image::~Image()
{
    mApiImage.destroy();
}


int Image::width() const
{
    return mApiImage.width();
}


int Image::height() const
{
    return mApiImage.height();
}


Octane::ApiImage::PixelFormat Image::pixelFormat() const
{
    return mApiImage.pixelFormat();
}


bool Image::isARGB() const
{
    return mApiImage.isARGB();
}


bool Image::isRGB() const
{
    return mApiImage.isRGB();
}


bool Image::isSingleChannel() const
{
    return mApiImage.isSingleChannel();
}


bool Image::hasAlphaChannel() const
{
    return mApiImage.hasAlphaChannel();
}
    

void Image::clear(
    const int                 x,
    const int                 y,
    const int                 width,
    const int                 height,
    const Octane::ApiColorLdr color)
{
    return mApiImage.clear(x, y, width, height, color);
}


void Image::updateTo(
    const void *const imageData,
     const int imageSize)
{
    mApiImage.updateTo(imageData, imageSize);
}


Octane::ApiColorLdr Image::pixelAt(
    const int x,
    const int y) const
{
    return mApiImage.pixelAt(x, y);
}


void Image::setPixelAt(
    const int                 x,
    const int                 y,
    const Octane::ApiColorLdr color)
{
    mApiImage.setPixelAt(x, y, color);
}


void Image::multiplyAlphaAt(
    const int   x,
    const int   y,
    const float multiplier)
{
    mApiImage.multiplyAlphaAt(x, y, multiplier);
}


void Image::multiplyAllAlphas(
    const float amountToMultiplyBy)
{
    mApiImage.multiplyAllAlphas(amountToMultiplyBy);
}


void Image::desaturate()
{
    mApiImage.desaturate();
}


ApiImageProxy* Image::wrappedImage()
{
    return &mApiImage;
}


const ApiImageProxy* Image::wrappedImage() const
{
    return &mApiImage;
}


Image::Image(
    ApiImageProxy & apiImage)
{
     mApiImage = apiImage;
}
