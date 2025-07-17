// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#include "octanetypes.h"
#ifdef OCTANEAPI_DECL
#undef OCTANEAPI_DECL
#endif
#define OCTANEAPI_DECL
#include "octanevectypes.h"
#include "grpcbase.h"
#include "clientcallbackmgr.h"
#include "grpcapinodeinfo.h"
class ApiItemProxy;
class ApiNodeProxy;


#include "apiselectionmanager.h"


class Convert;

class GRPCSettings;

#include "grpcchangeevents.h"
#include "apinodeclient.h"

struct ApiPinSelectionProxy : public GRPCBase
{
    ApiPinSelectionProxy() = default;

    ApiPinSelectionProxy(uint32_t pinIndex, const ApiNodeProxy& node)
:
    mPinIndex(pinIndex), mNode(node)
    {}

    uint32_t mPinIndex = 0;
    ApiNodeProxy mNode;
};

/// Proxy class for ApiSelectionManager
class ApiSelectionManagerProxy : public GRPCBase
{
public:
    /// Returns TRUE if the specified item is currently selected.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool isItemSelected(
            const ApiItemProxy &   item
            );

    /// Returns TRUE if the specified pin is currently selected on the specified node.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool isPinSelected(
            const ApiNodeProxy &                      node,
            const Octane::PinId                       pinId
            );

    /// Returns TRUE if the specified pin is currently selected on the specified node.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool isPinSelected(
            const ApiNodeProxy &                      node,
            const char *                              pinName
            );

    /// Returns TRUE if the specified pin is currently selected on the specified node.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool isPinSelectedIx(
            const ApiNodeProxy &                      node,
            const uint32_t                            pinIx
            );

    /// Returns the number of selected items.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static size_t selectedItemCount();

    /// Returns the number of selected pins.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static size_t selectedPinCount();

    /// Copies the set of currently selected items into the specified array. The array should be
    /// cleaned up via a call to deleteSelectionArray().
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void getSelection(
            std::vector<ApiItemProxy> &   selectedItems
            );

    /// Copies the set of currently selected pins into the specified array. The array should be
    /// cleaned up via a call to deletePinSelectionArray().
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void getSelection(
            std::vector<ApiPinSelectionProxy> &   selectedPins
            );

    /// De-selects everything and sends a selection change event if something actually got
    /// deselected.
    /// @param[out] status
    ///     Contains the status of the gRPC call
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
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void setSelection(
            Octane::ApiArray<ApiItemProxy *>          selectedItems,
            Octane::ApiArray<ApiPinSelectionProxy *>  selectedPins,
            const bool                                selectDestPins
            );

    /// Adds an item to the current selection and sends a change event if the selection changed.
    ///
    /// @param[in]  item
    ///     The selected node item.
    /// @param[in]  selectDestPins
    ///     If TRUE the destination pins of the selected item will be selected implicitely.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void select(
            const ApiItemProxy &                      item,
            const bool                                selectDestPins
            );

    /// Adds a pin to the current selection and sends a change event if the selection changed.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void select(
            ApiPinSelectionProxy                      pinSelection,
            const bool                                selectConnectedItem
            );

    /// Removed an item from the current selection and sends a change event if the selection changed.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void deselect(
            const ApiItemProxy &   item
            );

    /// Removes a pin from the current selection and sends a change event if the selection changed.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void deselect(
            ApiPinSelectionProxy   pin
            );

    /// If the old item was selected, the new item will be selected and the old item deselected.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void swapSelection(
            const ApiItemProxy &                      oldItem,
            const ApiItemProxy &                      newItem
            );

    /// Adds a selection changed observer. Any module that registers itself MUST remove itself
    /// before the application closes.
    ///
    /// @param[in]  observer
    ///     Selection change observer.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void addSelectionObserver(
            GRPCSelectionManagerObserver   observer
            );

    /// Removes a selection observer.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void removeSelectionObserver(
            GRPCSelectionManagerObserver   observer
            );

private:
    static GRPCSettings & getGRPCSettings();
};
