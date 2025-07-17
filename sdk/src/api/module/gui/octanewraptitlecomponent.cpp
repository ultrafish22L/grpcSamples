// Copyright (C) 2025 OTOY NZ Ltd.

// application includes
#include "apititlecomponent.h"
// myself
#include "octanewraptitlecomponent.h"

using namespace OctaneWrap;


TitleComponent::TitleComponent(
    const std::string &text)
{
    mApiTitleComponent = Octane::ApiTitleComponent::create(text.c_str());
    mComponent         = mApiTitleComponent;
}


TitleComponent::~TitleComponent()
{
    mApiTitleComponent->destroy();
    mApiTitleComponent = NULL;
}
