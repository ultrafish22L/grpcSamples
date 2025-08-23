// Copyright (C) 2025 OTOY NZ Ltd.

// myself
#include "octanegrpcwrapprogressbar.h"
// application includes
#include "apiprogressbar.h"
using namespace OctaneWrap;


ProgressBar::ProgressBar()
{
    mApiProgressBar = OctaneGRPC::ApiProgressBarProxy::create();
    mComponent      = &mApiProgressBar;
}


ProgressBar::~ProgressBar()
{
    mApiProgressBar.destroy();
    //mApiProgressBar = NULL;
}


void ProgressBar::setProgress(
    const double newValue)
{
    mApiProgressBar.setProgress(newValue);
}


double ProgressBar::progress() const
{
    return mApiProgressBar.progress();
}


void ProgressBar::setText(
    const std::string &newText)
{
    mApiProgressBar.setText(newText.c_str());
}
