// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once
#include <vector>
#include "octaneenums.h"

class ApiItemProxy;
class ApiRootNodeGraphProxy;

using namespace Octane;

struct GRPCChangeManagerChangeEvent
{
    /// The various node system event we have:
    enum Type
    {
        ITEM_ADDED                     = ChangeEventType::ITEM_ADDED,
        ITEM_DELETE                    = ChangeEventType::ITEM_DELETE,
        CONNECTION_CHANGED             = ChangeEventType::CONNECTION_CHANGED,
        DESTINATION_ADDED              = ChangeEventType::DESTINATION_ADDED,
        PINS_CHANGED                   = ChangeEventType::PINS_CHANGED,
        ITEM_VALUE_CHANGED             = ChangeEventType::ITEM_VALUE_CHANGED,
        ITEM_INPUT_CHANGED             = ChangeEventType::ITEM_INPUT_CHANGED,
        ITEM_NAME_CHANGED              = ChangeEventType::ITEM_NAME_CHANGED,
        ITEM_MOVED                     = ChangeEventType::ITEM_MOVED,
        LINKER_ORDER_CHANGED           = ChangeEventType::LINKER_ORDER_CHANGED,
        ITEM_UI_OPERATION_FLAG_CHANGED = ChangeEventType::ITEM_UI_OPERATION_FLAG_CHANGED,
        TIME_TRANSFORM_CHANGED         = ChangeEventType::TIME_TRANSFORM_CHANGED
    };

    /// The change type of the event.
    Type             mType;
    /// The owner of added/removed items (used for ITEM_ADDED, ITEM_DELETE).
    /// This can be a node graph or a pin. In case it's a pin, mChangedOwner points
    /// to the parent node of the pin and the pin is identified via mChangedOwnerPinIx.
    const ApiItemProxy * mChangedOwner;
    /// The index of the pin, if mChangedOwner is a node.
    uint32_t         mChangedOwnerPinIx;
    /// The item that got changed.
    const ApiItemProxy *  mChangedItem;
    /// The index of the pin of which a connection got changed (used for CONNECTION_CHANGED).
    /// In this case mChangedItem will be the parent node of the pin.
    uint32_t              mChangedPinIx;
    /// The indices of the changed attributes/pins if the
    /// event is either ITEM_VALUE_CHANGED or ITEM_INPUT_CHANGED, otherwise empty.
    std::vector<uint32_t> mChangedIndices;
};


struct GRPCChangeManagerTimeChangeEvent
{
    enum Type
    {
        GRAPH_TIME_CHANGED     = TimeEventType::GRAPH_TIME_CHANGED,
        GRAPH_INTERVAL_CHANGED = TimeEventType::GRAPH_INTERVAL_CHANGED,
        FRAME_RATE_CHANGED     = TimeEventType::FRAME_RATE_CHANGED,
    };

    /// Type of event.
    Type                   mType;
    /// The root node graph affected, which is only set if mType is GRAPH_TIME_CHANGED or
    /// GRAPH_INTERVAL_CHANGED.
    const ApiRootNodeGraphProxy * mRootGraph;
};


struct GRPCChangeTimeObserver
{
    /// Callback, called on a time change event.
    typedef void (*OnChangeT)(
        const GRPCChangeManagerTimeChangeEvent & eventData,
        void *                                    userData);

    OnChangeT mCallback;
    int       mCallbackId;
    void *    mUserData;
};


struct GRPCChangeObserver
{
    /// Callback, called on a change event.
    typedef void (*OnChangeT)(
        const GRPCChangeManagerChangeEvent & eventData,
        void *                               userData);

    OnChangeT mCallback;
    int       mCallbackId;
    void *    mUserData;
};


struct GRPCProjectManagerObserver
{
    /// Callback, called on a change event.
    typedef void (*OnChangeT)(
        void *                               userData);

    OnChangeT mCallback;
    int       mCallbackId;
    void *    mUserData;
};


struct GRPCSelectionManagerObserver
{
    /// Callback, called on a change event.
    typedef void (*OnChangeT)(
        void *                                  userData);

    OnChangeT mCallback;
    int       mCallbackId;
    void *    mUserData;
};