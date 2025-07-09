// Copyright (C) 2025 OTOY NZ Ltd.

// myself
#include "octanegrpcwrapselectionmanager.h"
// application includes
#include "apinodesystem.h"
#include "apiselectionmanagerclient.h"


using namespace OctaneWrap;

//--------------------------------------------------------------------------------------------------
// Implementation of SelectionObserver.

SelectionObserver::SelectionObserver()
{
    mCallback    = internalCallback;
    mUserData = this;
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
    const ApiItemProxy &item)
{
    return ApiSelectionManagerProxy::isItemSelected(item);
}


bool SelectionManager::isPinSelected(
    const ApiNodeProxy &node,
    const Octane::PinId   pinId)
{
    return ApiSelectionManagerProxy::isPinSelected(node, pinId);
}


bool SelectionManager::isPinSelected(
    const ApiNodeProxy &node,
    const std::string     &pinName)
{
    return ApiSelectionManagerProxy::isPinSelected(node, pinName.c_str());
}


bool SelectionManager::isPinSelectedIx(
    const ApiNodeProxy &node,
    const uint32_t        pinIx)
{
    return ApiSelectionManagerProxy::isPinSelectedIx(node, pinIx);
}


size_t SelectionManager::selectedItemCount()
{
    return ApiSelectionManagerProxy::selectedItemCount();
}


size_t SelectionManager::selectedPinCount()
{
    return ApiSelectionManagerProxy::selectedPinCount();
}


void SelectionManager::getSelection(
    std::vector<ApiItemProxy> &selectedItems)
{

    std::vector<ApiItemProxy> apiItems;
    ApiSelectionManagerProxy::getSelection(apiItems);
    selectedItems = apiItems;
}


void SelectionManager::getSelection(
    std::vector<ApiPinSelectionProxy> &selectedPins)
{
    std::vector<ApiPinSelectionProxy> apiPins;
    ApiSelectionManagerProxy::getSelection(apiPins);
    selectedPins = apiPins;
}


void SelectionManager::clearSelection()
{
    ApiSelectionManagerProxy::clearSelection();
}


void SelectionManager::setSelection(
    std::vector<ApiItemProxy>         selectedItems,
    std::vector<ApiPinSelectionProxy> selectedPins,
    bool                              selectDestPins)
{
    std::vector<ApiItemProxy*> apiItems;
    for (auto & p : selectedItems)
    {
        apiItems.push_back(&p);
    }
    std::vector<ApiPinSelectionProxy*> pinItems;
    for (auto & p : selectedPins)
    {
        pinItems.push_back(&p);
    }
    Octane::ApiArray<ApiItemProxy*> apiSelectedItems(apiItems.data(), apiItems.size());
    Octane::ApiArray<ApiPinSelectionProxy*> apiSelectedPins(pinItems.data(), pinItems.size());

    ApiSelectionManagerProxy::setSelection(apiSelectedItems,
                                           apiSelectedPins,
                                           selectDestPins
                                           );
}


void SelectionManager::select(
    const ApiItemProxy &  item,
    const bool            selectDestPins)
{
    ApiSelectionManagerProxy::select(item, selectDestPins);
}


void SelectionManager::select(
    const ApiPinSelectionProxy &pinSelection,
    const bool                                      selectConnectedItem)
{
    ApiSelectionManagerProxy::select(pinSelection, selectConnectedItem);
}


void SelectionManager::deselect(
    const ApiItemProxy &item)
{
    ApiSelectionManagerProxy::deselect(item);
}


void SelectionManager::deselect(
    const ApiPinSelectionProxy &pin)
{
    ApiSelectionManagerProxy::deselect(pin);
}


void SelectionManager::swapSelection(
    const ApiItemProxy &oldItem,
    const ApiItemProxy &newItem)
{
    ApiSelectionManagerProxy::swapSelection(oldItem, newItem);
}


void SelectionManager::addSelectionObserver(
    SelectionObserver &observer)
{
    ApiSelectionManagerProxy::addSelectionObserver(observer);
}


void SelectionManager::removeSelectionObserver(
    SelectionObserver &observer)
{
    ApiSelectionManagerProxy::removeSelectionObserver(observer);
}


ApiPinSelectionProxy SelectionManager::create(
    ApiNodeProxy        &node,
    const Octane::PinId pinId)
{
    ApiPinSelectionProxy selection(0, node);
    
    uint32_t foundIndex;
    if (node.findPin(pinId, foundIndex))
    {
        selection.mPinIndex = foundIndex;
    }

    return selection;
}


ApiPinSelectionProxy SelectionManager::create(
    ApiNodeProxy      &node,
    const std::string &pinName)
{
    ApiPinSelectionProxy selection(0, node);

    uint32_t foundIndex;
    if (node.findPin(pinName.c_str(), foundIndex))
    {
        selection.mPinIndex = foundIndex;
    }

    return selection;
}
