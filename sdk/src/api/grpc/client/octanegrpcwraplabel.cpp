// Copyright (C) 2026 OTOY NZ Ltd.

// myself
#include "octanegrpcwraplabel.h"
// application includes
#include "apilabel.h"

using namespace OctaneGRPC;
using namespace OctaneWrap;

Label::Label(
    const std::string &text)
//:
//    mApiLabel(NULL)
{
    mApiLabel  = ApiLabelProxy::create(text.c_str());
    mComponent = &mApiLabel;
}


Label::~Label()
{
    mApiLabel.destroy();
    //mApiLabel = NULL;
}


std::string Label::text() const
{
    return std::string(mApiLabel.text());
}


void Label::setText(
    const std::string &text,
    const bool        sendEvent)
{
    mApiLabel.setText(text.c_str(), sendEvent);
}
