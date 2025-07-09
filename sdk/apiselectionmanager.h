// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _API_SELECTION_MANAGER_H_
#define _API_SELECTION_MANAGER_H_    1

#include "apiarray.h"
#include "octaneids.h"
#include "octanetypes.h"

namespace Octane
{

class ApiItem;
class ApiNode;

//--------------------------------------------------------------------------------------------------
/// Manages the selection of items and pins.
class OCTANEAPI_DECL ApiSelectionManager
{
    OCTANEAPI_NO_COPY(ApiSelectionManager);

public:

    /// identifies a selected pin on a node
    struct PinSelection
    {
        /// The selected node.
        ApiNode  *mNode;
        /// Index of the selected pin on the node.
        uint32_t mPinIndex;
    };

    /// Returns TRUE if the specified item is currently selected.
    static bool isItemSelected(
        const ApiItem &item);

    /// Returns TRUE if the specified pin is currently selected on the specified node.
    static bool isPinSelected(
        const ApiNode &node,
        const PinId   pinId);

    /// Returns TRUE if the specified pin is currently selected on the specified node.
    static bool isPinSelected(
        const ApiNode &node,
        const char    *pinName);

    /// Returns TRUE if the specified pin is currently selected on the specified node.
    static bool isPinSelectedIx(
        const ApiNode  &node,
        const uint32_t pinIx);

    /// Returns the number of selected items.
    static size_t selectedItemCount();

    /// Returns the number of selected pins.
    static size_t selectedPinCount();

    /// Copies the set of currently selected items into the specified array. The array should be
    /// cleaned up via a call to deleteSelectionArray().
    static void getSelection(
        ApiArray<ApiItem*> &selectedItems);

    /// Deletes the array allocated by getSelection().
    static void deleteSelectionArray(
        ApiArray<ApiItem*> &arrayToDelete);

    /// Copies the set of currently selected pins into the specified array. The array should be
    /// cleaned up via a call to deletePinSelectionArray().
    static void getSelection(
        ApiArray<PinSelection> &selectedPins);

    static void deletePinSelectionArray(
        ApiArray<PinSelection> &arrayToDelete);

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
        const ApiArray<ApiItem*>     &selectedItems,
        const ApiArray<PinSelection> &selectedPins,
        const bool                   selectDestPins     = true);

    /// Adds an item to the current selection and sends a change event if the selection changed.
    ///
    /// @param[in]  item
    ///     The selected node item.
    /// @param[in]  selectDestPins
    ///     If TRUE the destination pins of the selected item will be selected implicitely.
    static void select(
        const ApiItem &item,
        const bool    selectDestPins     = true);

    /// Adds a pin to the current selection and sends a change event if the selection changed.
    static void select(
        const PinSelection &pinSelection,
        const bool         selectConnectedItem = true);

    /// Removed an item from the current selection and sends a change event if the selection changed.
    static void deselect(
        const ApiItem &item);

    /// Removes a pin from the current selection and sends a change event if the selection changed.
    static void deselect(
        const PinSelection &pin);

    /// If the old item was selected, the new item will be selected and the old item deselected.
    static void swapSelection(
        const ApiItem &oldItem,
        const ApiItem &newItem);

    // Selection change observer object. This object's callback is called on a change in the
    // selection. It's important that all these observers are removed when the module stops.
    struct Observer
    {
         /// Callback, called on a selection change event.
        typedef void (*OnChangeT)(
            void       *privateData);

        OnChangeT mCallback;
        void      *mPrivateData;
    };

    /// Adds a selection changed observer. Any module that registers itself MUST remove itself
    /// before the application closes.
    /// 
    /// @param[in]  observer
    ///     Selection change observer.
    static void addSelectionObserver(
        Observer &observer);

    /// Removes a selection observer.
    static void removeSelectionObserver(
        Observer &observer);

private:

    ApiSelectionManager();
};

} // namespace Octane


#endif // #ifndef _API_SELECTION_MANAGER_H_
