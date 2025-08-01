// Copyright (C) 2025 OTOY NZ Ltd.

// system includes
#include <algorithm>
// application includes
#include "apicolorswatch.h"
// myself
#include "octanewrapcolorswatch.h"

using namespace OctaneWrap;


ColorSwatch::ColorSwatch(
    const bool disableGammaCorrection)
{
    mApiColorSwatch = Octane::ApiColorSwatch::create(disableGammaCorrection,
                                                     internalChangeCallback,
                                                     this);
    mComponent = mApiColorSwatch;
}


ColorSwatch::~ColorSwatch()
{
    mApiColorSwatch->destroy();
    mApiColorSwatch = NULL;
}


void ColorSwatch::addListener(
    ColorSwatchListener &listener)
{
    mListeners.push_back(&listener);
}


void ColorSwatch::removeListener(
    ColorSwatchListener &listener)
{
    mListeners.erase(std::find(mListeners.begin(), mListeners.end(), &listener));
}


void ColorSwatch::setColor(
    const Octane::ApiColorHdr &color)
{
    return mApiColorSwatch->setColor(color);
}


Octane::ApiColorHdr ColorSwatch::color() const
{
    return mApiColorSwatch->color();
}


void ColorSwatch::internalChangeCallback(
    Octane::ApiColorSwatch&,
    void                  *privateData)
{
    ColorSwatch *me = static_cast<ColorSwatch*>(privateData);

    // notify all the listeners
    for (size_t i=0; i<me->mListeners.size(); ++i)
    {
        me->mListeners[i]->swatchValueChanged(*me);
    }
}
