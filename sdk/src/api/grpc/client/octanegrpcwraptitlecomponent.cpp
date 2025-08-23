// Copyright (C) 2025 OTOY NZ Ltd.

// myself
#include "octanegrpcwraptitlecomponent.h"
// application includes
#include "apititlecomponent.h"

using namespace OctaneWrap;


TitleComponent::TitleComponent(
    const std::string &text)
{
    mApiTitleComponent = OctaneGRPC::ApiTitleComponentProxy::create(text.c_str());
    mComponent         = &mApiTitleComponent;
}


TitleComponent::~TitleComponent()
{
    mApiTitleComponent.destroy();
    //mApiTitleComponent = NULL;
}
