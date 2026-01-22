// Copyright (C) 2026 OTOY NZ Ltd.

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
    const OctaneGRPC::ApiItemProxy &item)
{
    return OctaneGRPC::ApiSelectionManagerProxy::isItemSelected(item);
}


bool SelectionManager::isPinSelected(
    const OctaneGRPC::ApiNodeProxy &node,
    const Octane::PinId   pinId)
{
    return OctaneGRPC::ApiSelectionManagerProxy::isPinSelected(node, pinId);
}


bool SelectionManager::isPinSelected(
    const OctaneGRPC::ApiNodeProxy &node,
    const std::string     &pinName)
{
    return OctaneGRPC::ApiSelectionManagerProxy::isPinSelected(node, pinName.c_str());
}


bool SelectionManager::isPinSelectedIx(
    const OctaneGRPC::ApiNodeProxy &node,
    const uint32_t        pinIx)
{
    return OctaneGRPC::ApiSelectionManagerProxy::isPinSelectedIx(node, pinIx);
}


size_t SelectionManager::selectedItemCount()
{
    return OctaneGRPC::ApiSelectionManagerProxy::selectedItemCount();
}


size_t SelectionManager::selectedPinCount()
{
    return OctaneGRPC::ApiSelectionManagerProxy::selectedPinCount();
}


void SelectionManager::getSelection(
    std::vector<OctaneGRPC::ApiItemProxy> &selectedItems)
{

    std::vector<OctaneGRPC::ApiItemProxy> apiItems;
    OctaneGRPC::ApiSelectionManagerProxy::getSelection(apiItems);
    selectedItems = apiItems;
}


void SelectionManager::getSelection(
    std::vector<OctaneGRPC::ApiPinSelectionProxy> &selectedPins)
{
    std::vector<OctaneGRPC::ApiPinSelectionProxy> apiPins;
    OctaneGRPC::ApiSelectionManagerProxy::getSelection(apiPins);
    selectedPins = apiPins;
}


void SelectionManager::clearSelection()
{
    OctaneGRPC::ApiSelectionManagerProxy::clearSelection();
}


void SelectionManager::setSelection(
    std::vector<OctaneGRPC::ApiItemProxy>         selectedItems,
    std::vector<OctaneGRPC::ApiPinSelectionProxy> selectedPins,
    bool                              selectDestPins)
{
    std::vector<OctaneGRPC::ApiItemProxy*> apiItems;
    for (auto & p : selectedItems)
    {
        apiItems.push_back(&p);
    }
    std::vector<OctaneGRPC::ApiPinSelectionProxy*> pinItems;
    for (auto & p : selectedPins)
    {
        pinItems.push_back(&p);
    }
    Octane::ApiArray<OctaneGRPC::ApiItemProxy*> apiSelectedItems(apiItems.data(), apiItems.size());
    Octane::ApiArray<OctaneGRPC::ApiPinSelectionProxy*> apiSelectedPins(pinItems.data(), pinItems.size());

    OctaneGRPC::ApiSelectionManagerProxy::setSelection(apiSelectedItems,
                                           apiSelectedPins,
                                           selectDestPins
                                           );
}


void SelectionManager::select(
    const OctaneGRPC::ApiItemProxy &  item,
    const bool            selectDestPins)
{
    OctaneGRPC::ApiSelectionManagerProxy::select(item, selectDestPins);
}


void SelectionManager::select(
    const OctaneGRPC::ApiPinSelectionProxy &pinSelection,
    const bool                                      selectConnectedItem)
{
    OctaneGRPC::ApiSelectionManagerProxy::select(pinSelection, selectConnectedItem);
}


void SelectionManager::deselect(
    const OctaneGRPC::ApiItemProxy &item)
{
    OctaneGRPC::ApiSelectionManagerProxy::deselect(item);
}


void SelectionManager::deselect(
    const OctaneGRPC::ApiPinSelectionProxy &pin)
{
    OctaneGRPC::ApiSelectionManagerProxy::deselect(pin);
}


void SelectionManager::swapSelection(
    const OctaneGRPC::ApiItemProxy &oldItem,
    const OctaneGRPC::ApiItemProxy &newItem)
{
    OctaneGRPC::ApiSelectionManagerProxy::swapSelection(oldItem, newItem);
}


void SelectionManager::addSelectionObserver(
    SelectionObserver & observer)
{
    OctaneGRPC::ApiSelectionManagerProxy::addSelectionObserver(observer);
}


void SelectionManager::removeSelectionObserver(
    SelectionObserver & observer)
{
    OctaneGRPC::ApiSelectionManagerProxy::removeSelectionObserver(observer);
}


OctaneGRPC::ApiPinSelectionProxy SelectionManager::create(
    OctaneGRPC::ApiNodeProxy        &node,
    const Octane::PinId pinId)
{
    OctaneGRPC::ApiPinSelectionProxy selection(0, node);
    
    uint32_t foundIndex;
    if (node.findPin(pinId, foundIndex))
    {
        selection.mPinIndex = foundIndex;
    }

    return selection;
}


OctaneGRPC::ApiPinSelectionProxy SelectionManager::create(
    OctaneGRPC::ApiNodeProxy      &node,
    const std::string &pinName)
{
    OctaneGRPC::ApiPinSelectionProxy selection(0, node);

    uint32_t foundIndex;
    if (node.findPin(pinName.c_str(), foundIndex))
    {
        selection.mPinIndex = foundIndex;
    }

    return selection;
}
