// Copyright (C) 2025 OTOY NZ Ltd.

// myself
#include "octanegrpcwraptextbutton.h"
// system includes
#include <algorithm>
#include <functional>
// application includes
#include "apitextbutton.h"

using namespace OctaneWrap;

TextButton::TextButton(
    const std::string &text)
//:
//    mApiTextButton(NULL)
{
    mApiTextButton = ApiTextButtonProxy::create(text.c_str(), buttonClicked, this);
    mComponent     = &mApiTextButton;
}


TextButton::~TextButton()
{
    mApiTextButton.destroy();
}


void TextButton::setText(
    const std::string &text)
{
    mApiTextButton.setText(text.c_str());
}


std::string TextButton::text() const
{
   return std::string(mApiTextButton.text());
}


void TextButton::addListener(
    ButtonListener &listener)
{
    mListener.push_back(&listener);
}


void TextButton::removeListener(
    ButtonListener &listener)
{
    mListener.erase(std::find(mListener.begin(), mListener.end(), &listener));
}


void TextButton::buttonClicked(
    ApiTextButtonProxy    &button,
    void                  *privateData)
{
    TextButton *myButton = static_cast<TextButton*>(privateData);

    // notify the listeners
    for (size_t i=0; i<myButton->mListener.size(); ++i)
    {
        myButton->mListener[i]->buttonClicked(*myButton);
    }
}
