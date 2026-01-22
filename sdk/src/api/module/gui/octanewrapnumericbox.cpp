// Copyright (C) 2026 OTOY NZ Ltd.

// system includes
#include <algorithm>
// application includes
#include "apinumericbox.h"
// myself
#include "octanewrapnumericbox.h"

using namespace OctaneWrap;

NumericBox::NumericBox(
    const double step)
:
    mApiNumericBox(NULL)
{
    mApiNumericBox = Octane::ApiNumericBox::create(step, onValueChanged, this);
    mComponent     = mApiNumericBox;
}


NumericBox::~NumericBox()
{
    mApiNumericBox->destroy();
    mApiNumericBox = NULL;
}


double NumericBox::value() const
{
    return mApiNumericBox->value();
}


void NumericBox::setValue(
    const double newValue,
    const bool   sendEvent)
{
    mApiNumericBox->setValue(newValue, sendEvent);
}


void NumericBox::setLimits( 
    const double minimum,
    const double maximum, 
    const double sliderMinimum,
    const double sliderMaximum)
{
    mApiNumericBox->setLimits(minimum, maximum, sliderMinimum, sliderMaximum);
}


void NumericBox::addListener(
    NumericBoxListener &listener)
{
    mListeners.push_back(&listener);
}


void NumericBox::removeListener(
    NumericBoxListener &listener)
{
    mListeners.erase(std::find(mListeners.begin(), mListeners.end(), &listener));
}


void NumericBox::onValueChanged(
    Octane::ApiNumericBox &numericBox,
    void                  *privateData)
{
    NumericBox *myBox = static_cast<NumericBox*>(privateData);
    // notify listeners
    for (size_t i=0; i<myBox->mListeners.size(); ++i)
    {
        myBox->mListeners[i]->valueChanged(*myBox);
    }
}
