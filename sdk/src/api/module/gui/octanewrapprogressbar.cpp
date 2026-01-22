// Copyright (C) 2026 OTOY NZ Ltd.

// application includes
#include "apiprogressbar.h"
// myself
#include "octanewrapprogressbar.h"

using namespace OctaneWrap;


ProgressBar::ProgressBar()
:
    mApiProgressBar(NULL)
{
    mApiProgressBar = Octane::ApiProgressBar::create();
    mComponent      = mApiProgressBar;
}


ProgressBar::~ProgressBar()
{
    mApiProgressBar->destroy();
    mApiProgressBar = NULL;
}


void ProgressBar::setProgress(
    const double newValue)
{
    mApiProgressBar->setProgress(newValue);
}


double ProgressBar::progress() const
{
    return mApiProgressBar->progress();
}


void ProgressBar::setText(
    const std::string &newText)
{
    mApiProgressBar->setText(newText.c_str());
}
