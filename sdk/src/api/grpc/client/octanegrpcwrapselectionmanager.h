// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_SELECTION_MANAGER_H_
#define _OCTANE_WRAP_SELECTION_MANAGER_H_   1

// system includes
#include <string>
#include <vector>
// api includes
#include "apiselectionmanager.h"
#include "octaneids.h"
#include "octanetypes.h"
#include "grpcchangeevents.h"

#include "apiitemclient.h"
#include "apinodeclient.h"
#include "apiselectionmanagerclient.h"

namespace OctaneWrap
{

//--------------------------------------------------------------------------------------------------
/// Interface for selection observers.
class SelectionObserver : public GRPCSelectionManagerObserver// Octane::ApiSelectionManager::Observer
{
public:

    /// 
    SelectionObserver();

    /// Called whenever the selection changed.
    /// 
    /// @param[in]  renderTargetUpdated
    ///     TRUE if the render target that is rendering changed.
    virtual void onSelectionChanged() = 0;

private:

    static void internalCallback(
        void       *privateData);
};



//--------------------------------------------------------------------------------------------------
/// Wraps ApiSelectionManager.
class SelectionManager
{

public:

    /// Returns TRUE if the specified item is currently selected.
    static bool isItemSelected(
        const ApiItemProxy &item);

    /// Returns TRUE if the specified pin is currently selected on the specified node.
    static bool isPinSelected(
        const ApiNodeProxy &node,
        const Octane::PinId   pinId);

    /// Returns TRUE if the specified pin is currently selected on the specified node.
    static bool isPinSelected(
        const ApiNodeProxy &node,
        const std::string     &pinName);

    /// Returns TRUE if the specified pin is currently selected on the specified node.
    static bool isPinSelectedIx(
        const ApiNodeProxy &node,
        const uint32_t        pinIx);

    /// Returns the number of selected items.
    static size_t selectedItemCount();

    /// Returns the number of selected pins.
    static size_t selectedPinCount();

    /// Copies the set of currently selected items into the vector.
    static void getSelection(
        std::vector<ApiItemProxy> &selectedItems);

    /// Copies the set of currently selected pins into the vector.
    static void getSelection(
        std::vector<ApiPinSelectionProxy> &selectedPins);

    /// De-selects everything and sends a selection change event if something actually got
    /// deselected.
    static void clearSelection();

    /// Replaces the complete current selection with a new item/pin selection and sends a selection
    /// change event.
    ///
    /// @param[in]  selectedItems
    ///     The selected node items or an empty array if no items should be selected.
    /// @param[in]  selectedPins
    ///     The explicitely selected node pins or an empty array if no pins should be selected
    ///     explicitely.
    /// @param[in]  selectDestPins
    ///     If TRUE the destination pins of all selected items will be selected implicitely.
    static void setSelection(
        std::vector<ApiItemProxy>         selectedItems,
        std::vector<ApiPinSelectionProxy> selectedPins,
        bool                              selectDestPins     = true);

    /// Adds an item to the current selection and sends a change event if the selection changed.
    ///
    /// @param[in]  item
    ///     The selected node item.
    /// @param[in]  selectDestPins
    ///     If TRUE the destination pins of the selected item will be selected implicitely.
    static void select(
        const ApiItemProxy &item,
        const bool            selectDestPins     = true);

    /// Adds a pin to the current selection and sends a change event if the selection changed.
    static void select(
        const ApiPinSelectionProxy &pinSelection,
        const bool                                      selectConnectedItem = true);

    /// Removed an item from the current selection and sends a change event if the selection changed.
    static void deselect(
        const ApiItemProxy &item);

    /// Removes a pin from the current selection and sends a change event if the selection changed.
    static void deselect(
        const ApiPinSelectionProxy &pin);

    /// If the old item was selected, the new item will be selected and the old item deselected.
    static void swapSelection(
        const ApiItemProxy &oldItem,
        const ApiItemProxy &newItem);

    /// Adds a selection changed observer. Any module that registers itself MUST remove itself
    /// before the application closes.
    /// 
    /// @param[in]  observer
    ///     Selection change observer.
    static void addSelectionObserver(
        SelectionObserver &observer);

    /// Removes a selection observer.
    static void removeSelectionObserver(
        SelectionObserver &observer);

    /// Inits a selection from a node and a pin ID. Make sure the pin ID is valid because otherwise
    /// the returned selection will be bogus.
    static ApiPinSelectionProxy create(
        ApiNodeProxy     &node,
        const Octane::PinId pinId);

    /// Inits a selection from a node and a pin name.
    static ApiPinSelectionProxy create(
        ApiNodeProxy   &node,
        const std::string &pinName);

private:

    SelectionManager();
};

} // namespace OctaneWrap


#endif // #ifndef _OCTANE_WRAP_SELECTION_MANAGER_H_
