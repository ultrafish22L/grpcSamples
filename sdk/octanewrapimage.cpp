// Copyright (C) 2025 OTOY NZ Ltd.

// myself
#include "octanewrapimage.h"

using namespace OctaneWrap;


Image* Image::loadFromFile(
    const std::string &fullPath)
{
    Octane::ApiImage *apiImage = Octane::ApiImage::loadFromFile(fullPath.c_str());
    if (apiImage)
    {
        return new Image(apiImage);
    }
    return NULL;
}


Image* Image::loadFromMemory(
    const void   *imageData,
    const size_t sizeInBytes)
{
    Octane::ApiImage *apiImage = Octane::ApiImage::loadFromMemory(imageData, sizeInBytes);
    if (apiImage)
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
:
    mApiImage(Octane::ApiImage::create(pixelFormat, width, height, clear))
{}


Image::Image(
    const Octane::ApiImage::PixelFormat pixelFormat,
    const int                           width,
    const int                           height,
    const void *const                   data)
:
    mApiImage(Octane::ApiImage::create(pixelFormat, width, height, data))
{}


Image::~Image()
{
    mApiImage->destroy();
    mApiImage = NULL;
}


int Image::width() const
{
    return mApiImage->width();
}


int Image::height() const
{
    return mApiImage->height();
}


Octane::ApiImage::PixelFormat Image::pixelFormat() const
{
    return mApiImage->pixelFormat();
}


bool Image::isARGB() const
{
    return mApiImage->isARGB();
}


bool Image::isRGB() const
{
    return mApiImage->isRGB();
}


bool Image::isSingleChannel() const
{
    return mApiImage->isSingleChannel();
}


bool Image::hasAlphaChannel() const
{
    return mApiImage->hasAlphaChannel();
}
    

void Image::clear(
    const int                 x,
    const int                 y,
    const int                 width,
    const int                 height,
    const Octane::ApiColorLdr color)
{
    return mApiImage->clear(x, y, width, height, color);
}


void Image::updateTo(
    const void *const imageData)
{
    mApiImage->updateTo(imageData);
}


Octane::ApiColorLdr Image::pixelAt(
    const int x,
    const int y) const
{
    return mApiImage->pixelAt(x, y);
}


void Image::setPixelAt(
    const int                 x,
    const int                 y,
    const Octane::ApiColorLdr color)
{
    mApiImage->setPixelAt(x, y, color);
}


void Image::multiplyAlphaAt(
    const int   x,
    const int   y,
    const float multiplier)
{
    mApiImage->multiplyAlphaAt(x, y, multiplier);
}


void Image::multiplyAllAlphas(
    const float amountToMultiplyBy)
{
    mApiImage->multiplyAllAlphas(amountToMultiplyBy);
}


void Image::desaturate()
{
    mApiImage->desaturate();
}


Octane::ApiImage* Image::wrappedImage()
{
    return mApiImage;
}


const Octane::ApiImage* Image::wrappedImage() const
{
    return mApiImage;
}


Image::Image(
    Octane::ApiImage *apiImage)
:
    mApiImage(apiImage)
{}
