// Copyright (C) 2026 OTOY NZ Ltd.

// system includes
#include <algorithm>
// application includes
#include "apitextbutton.h"
// myself
#include "octanewraptextbutton.h"

using namespace OctaneWrap;

TextButton::TextButton(
    const std::string &text)
:
    mApiTextButton(NULL)
{
    mApiTextButton = Octane::ApiTextButton::create(text.c_str(), buttonClicked, this);
    mComponent     = mApiTextButton;
}


TextButton::~TextButton()
{
    mApiTextButton->destroy();
}


void TextButton::setText(
    const std::string &text)
{
    mApiTextButton->setText(text.c_str());
}


std::string TextButton::text() const
{
    return std::string(mApiTextButton->text());
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
    Octane::ApiTextButton &button,
    void                  *privateData)
{
    TextButton *myButton = static_cast<TextButton*>(privateData);

    // notify the listeners
    for (size_t i=0; i<myButton->mListener.size(); ++i)
    {
        myButton->mListener[i]->buttonClicked(*myButton);
    }
}
