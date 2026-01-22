// Copyright (C) 2026 OTOY NZ Ltd.

// application includes
#include "apinodesystem.h"
// myself
#include "octanewrapselectionmanager.h"

using namespace OctaneWrap;

//--------------------------------------------------------------------------------------------------
// Implementation of SelectionObserver.

SelectionObserver::SelectionObserver()
{
    mCallback    = internalCallback;
    mPrivateData = this;
}


void SelectionObserver::internalCallback(
    void       *privateData)
{
    SelectionObserver *me = static_cast<SelectionObserver*>(privateData);
    me->onSelectionChanged();
}


//--------------------------------------------------------------------------------------------------
// Implementation of SelectionManager.

bool SelectionManager::isItemSelected(
    const Octane::ApiItem &item)
{
    return Octane::ApiSelectionManager::isItemSelected(item);
}


bool SelectionManager::isPinSelected(
    const Octane::ApiNode &node,
    const Octane::PinId   pinId)
{
    return Octane::ApiSelectionManager::isPinSelected(node, pinId);
}


bool SelectionManager::isPinSelected(
    const Octane::ApiNode &node,
    const std::string     &pinName)
{
    return Octane::ApiSelectionManager::isPinSelected(node, pinName.c_str());
}


bool SelectionManager::isPinSelectedIx(
    const Octane::ApiNode &node,
    const uint32_t        pinIx)
{
    return Octane::ApiSelectionManager::isPinSelectedIx(node, pinIx);
}


size_t SelectionManager::selectedItemCount()
{
    return Octane::ApiSelectionManager::selectedItemCount();
}


size_t SelectionManager::selectedPinCount()
{
    return Octane::ApiSelectionManager::selectedPinCount();
}


void SelectionManager::getSelection(
    std::vector<Octane::ApiItem*> &selectedItems)
{
    Octane::ApiArray<Octane::ApiItem*> apiItems;
    Octane::ApiSelectionManager::getSelection(apiItems);
    selectedItems = std::vector<Octane::ApiItem*>(apiItems.mData, apiItems.mData + apiItems.mSize);
    Octane::ApiSelectionManager::deleteSelectionArray(apiItems);
}


void SelectionManager::getSelection(
    std::vector<Octane::ApiSelectionManager::PinSelection> &selectedPins)
{
    Octane::ApiArray<Octane::ApiSelectionManager::PinSelection> apiPins;
    Octane::ApiSelectionManager::getSelection(apiPins);
    selectedPins = std::vector<Octane::ApiSelectionManager::PinSelection>(
            apiPins.mData, apiPins.mData + apiPins.mSize);
    Octane::ApiSelectionManager::deletePinSelectionArray(apiPins);
}


void SelectionManager::clearSelection()
{
    Octane::ApiSelectionManager::clearSelection();
}


void SelectionManager::setSelection(
    const std::vector<Octane::ApiItem*>                          &selectedItems,
    const std::vector<Octane::ApiSelectionManager::PinSelection> &selectedPins,
    const bool                                                   selectDestPins)
{
    Octane::ApiArray<Octane::ApiItem*> apiSelectedItems(selectedItems.data(),
                                                        selectedItems.size());
    Octane::ApiArray<Octane::ApiSelectionManager::PinSelection> apiSelectedPins(selectedPins.data(),
                                                                                selectedPins.size());
    Octane::ApiSelectionManager::setSelection(apiSelectedItems,
                                              apiSelectedPins,
                                              selectDestPins);
}


void SelectionManager::select(
    const Octane::ApiItem &item,
    const bool            selectDestPins)
{
    Octane::ApiSelectionManager::select(item, selectDestPins);
}


void SelectionManager::select(
    const Octane::ApiSelectionManager::PinSelection &pinSelection,
    const bool                                      selectConnectedItem)
{
    Octane::ApiSelectionManager::select(pinSelection, selectConnectedItem);
}


void SelectionManager::deselect(
    const Octane::ApiItem &item)
{
    Octane::ApiSelectionManager::deselect(item);
}


void SelectionManager::deselect(
    const Octane::ApiSelectionManager::PinSelection &pin)
{
    Octane::ApiSelectionManager::deselect(pin);
}


void SelectionManager::swapSelection(
    const Octane::ApiItem &oldItem,
    const Octane::ApiItem &newItem)
{
    Octane::ApiSelectionManager::swapSelection(oldItem, newItem);
}


void SelectionManager::addSelectionObserver(
    SelectionObserver &observer)
{
    Octane::ApiSelectionManager::addSelectionObserver(observer);
}


void SelectionManager::removeSelectionObserver(
    SelectionObserver &observer)
{
    Octane::ApiSelectionManager::removeSelectionObserver(observer);
}


Octane::ApiSelectionManager::PinSelection SelectionManager::create(
    Octane::ApiNode     &node,
    const Octane::PinId pinId)
{
    Octane::ApiSelectionManager::PinSelection selection = { &node, 0 };

    uint32_t foundIndex;
    if (node.findPin(pinId, foundIndex))
    {
        selection.mPinIndex = foundIndex;
    }

    return selection;
}


Octane::ApiSelectionManager::PinSelection SelectionManager::create(
    Octane::ApiNode   &node,
    const std::string &pinName)
{
    Octane::ApiSelectionManager::PinSelection selection = { &node, 0 };

    uint32_t foundIndex;
    if (node.findPin(pinName.c_str(), foundIndex))
    {
        selection.mPinIndex = foundIndex;
    }

    return selection;
}
