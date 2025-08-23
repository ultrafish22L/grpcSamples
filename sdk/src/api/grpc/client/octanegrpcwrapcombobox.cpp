// Copyright (C) 2025 OTOY NZ Ltd.

#ifdef OCTANEAPI_DECL
#undef OCTANEAPI_DECL
#endif
#define OCTANEAPI_DECL
#define OCTANE_STANDALONE
// system includes
#include <algorithm>
// application includes
#include "apicombobox.h"
// myself

#include "octanegrpcwrapcombobox.h"
#include "apicomboboxclient.h"

using namespace OctaneWrap;


//--------------------------------------------------------------------------------------------------
// Implementation of ComboBoxItem

ComboBoxItem::ComboBoxItem(
    const int         id,
    const std::string &text)
:
    mId(id),
    mText(text)
{}



//--------------------------------------------------------------------------------------------------
// Implementation of ComboBox
/// Creates a new combo box item.
//Octane::ApiComboBoxItem::ApiComboBoxItem(
//    const int  id,
//    const char* text)
//{
//    mId = id;
//    mText = text;
//};


ComboBox::ComboBox(
    const std::vector<ComboBoxItem> &items)
//:
//    mApiComboBox(NULL)
{
    // copy into ApiComboBoxItem
    std::vector<Octane::ApiComboBoxItem> apiItems;
    for (size_t i = 0; i < items.size(); ++i)
    {
        apiItems.push_back(Octane::ApiComboBoxItem(items[i].mId, items[i].mText.c_str()));
    }

    mApiComboBox = OctaneGRPC::ApiComboBoxProxy::create(apiItems.data(),
                                               apiItems.size(), 
                                               onComboBoxChanged,
                                               this);
    mComponent = &mApiComboBox;
}


ComboBox::~ComboBox()
{
    mApiComboBox.destroy();
    //mApiComboBox = NULL;
}


void ComboBox::setSelectedId(
    const int  newItemId,
    const bool sendEvent)
{
    mApiComboBox.setSelectedId(newItemId, sendEvent);
}


int ComboBox::selectedId() const
{
    return mApiComboBox.selectedId();
}


std::string ComboBox::text() const
{
    return std::string(mApiComboBox.text());
}


void ComboBox::addListener(
    ComboBoxListener &listener)
{
    mListeners.push_back(&listener);
}


void ComboBox::removeListener(
    ComboBoxListener &listener)
{
    mListeners.erase(std::find(mListeners.begin(), mListeners.end(), &listener));
}


void ComboBox::onComboBoxChanged(
    OctaneGRPC::ApiComboBoxProxy & comboBox,
    void *                         privateData)
{
    ComboBox *myBox = static_cast<ComboBox*>(privateData);
    // notify listeners
    for (size_t i = 0; i < myBox->mListeners.size(); ++i)
    {
        myBox->mListeners[i]->comboBoxChanged(*myBox);
    }
}
