// Copyright (C) 2025 OTOY NZ Ltd.

// application includes
#include "apiimagecomponent.h"
#include "octanewrapimage.h"
// myself
#include "octanewrapimagecomponent.h"

using namespace OctaneWrap;


ImageComponent::ImageComponent(
    Image &image)
{
    mApiImageComponent = Octane::ApiImageComponent::create(*image.mApiImage);
    mComponent         = mApiImageComponent;
}


ImageComponent::~ImageComponent()
{
    mApiImageComponent->destroy();
    mApiImageComponent = NULL;
}


void ImageComponent::updateTo(
    const Image & image)
{
    mApiImageComponent->updateTo(*image.wrappedImage());
}
