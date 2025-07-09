// Copyright (C) 2025 OTOY NZ Ltd.

// application includes
#include "apilabel.h"
// myself
#include "octanewraplabel.h"

using namespace OctaneWrap;

Label::Label(
    const std::string &text)
:
    mApiLabel(NULL)
{
    mApiLabel  = Octane::ApiLabel::create(text.c_str());
    mComponent = mApiLabel;
}


Label::~Label()
{
    mApiLabel->destroy();
    mApiLabel = NULL;
}


std::string Label::text() const
{
    return std::string(mApiLabel->text());
}


void Label::setText(
    const std::string &text,
    const bool        sendEvent)
{
    mApiLabel->setText(text.c_str(), sendEvent);
}
