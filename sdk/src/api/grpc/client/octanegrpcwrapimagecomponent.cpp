// Copyright (C) 2025 OTOY NZ Ltd.

// myself
#include "octanegrpcwrapimagecomponent.h"
// application includes
#include "apiimagecomponent.h"
#include "octanegrpcwrapimage.h"
;
using namespace OctaneWrap;


ImageComponent::ImageComponent(
    Image &image)
{
    mApiImageComponent = OctaneGRPC::ApiImageComponentProxy::create(image.mApiImage);
    mComponent         = &mApiImageComponent;
}


ImageComponent::~ImageComponent()
{
    mApiImageComponent.destroy();
    //mApiImageComponent = NULL;
}


void ImageComponent::updateTo(
    const Image & image)
{
    // not supported by the grpc api
    //grpc::Status status;
    //mApiImageComponent.updateTo(image.wrappedImage(), status);
}
