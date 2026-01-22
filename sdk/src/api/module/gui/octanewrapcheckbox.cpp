// Copyright (C) 2026 OTOY NZ Ltd.

// system includes
#include <algorithm>
// application includes
#include "apicheckbox.h"
// myself
#include "octanewrapcheckbox.h"

using namespace OctaneWrap;


CheckBox::CheckBox(
    const std::string &text)
:
    mApiCheckBox(NULL)
{
    mApiCheckBox = Octane::ApiCheckBox::create(text.c_str(), onClicked, this);
    mComponent   = mApiCheckBox;
}


CheckBox::~CheckBox()
{
    mApiCheckBox->destroy();
    mApiCheckBox = NULL;
}


void CheckBox::setChecked(
    const bool checked,
    const bool sendEvent)
{
    mApiCheckBox->setChecked(checked, sendEvent);
}


bool CheckBox::isChecked() const
{
    return mApiCheckBox->isChecked();
}
 

void CheckBox::addListener(
    CheckBoxListener &listener)
{
    mListeners.push_back(&listener);
}


void CheckBox::removeListener(
    CheckBoxListener &listener)
{
    mListeners.erase(std::find(mListeners.begin(), mListeners.end(), &listener));
}


void CheckBox::onClicked(
    Octane::ApiCheckBox &checkBox,
    void                *privateData)
{
    CheckBox *myCheckBox = static_cast<CheckBox*>(privateData);
    // notify the listeners
    for (size_t i=0; i<myCheckBox->mListeners.size(); ++i)
    {
        myCheckBox->mListeners[i]->onClicked(*myCheckBox);
    }
}
