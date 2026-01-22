// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once
#include <vector>
#include "octaneenums.h"
namespace OctaneGRPC
{
    class ApiItemProxy;
    class ApiRootNodeGraphProxy;
}

using namespace Octane;
namespace OctaneGRPC
{
    struct GRPCChangeManagerChangeEvent
    {
        /// The various node system event we have:
        enum Type
        {
            ITEM_ADDED = Octane::ChangeEventType::ITEM_ADDED,
            ITEM_DELETE = Octane::ChangeEventType::ITEM_DELETE,
            CONNECTION_CHANGED = Octane::ChangeEventType::CONNECTION_CHANGED,
            DESTINATION_ADDED = Octane::ChangeEventType::DESTINATION_ADDED,
            PINS_CHANGED = Octane::ChangeEventType::PINS_CHANGED,
            ITEM_VALUE_CHANGED = Octane::ChangeEventType::ITEM_VALUE_CHANGED,
            ITEM_INPUT_CHANGED = Octane::ChangeEventType::ITEM_INPUT_CHANGED,
            ITEM_NAME_CHANGED = Octane::ChangeEventType::ITEM_NAME_CHANGED,
            ITEM_MOVED = Octane::ChangeEventType::ITEM_MOVED,
            LINKER_ORDER_CHANGED = Octane::ChangeEventType::LINKER_ORDER_CHANGED,
            ITEM_UI_OPERATION_FLAG_CHANGED = Octane::ChangeEventType::ITEM_UI_OPERATION_FLAG_CHANGED,
            TIME_TRANSFORM_CHANGED = Octane::ChangeEventType::TIME_TRANSFORM_CHANGED
        };

        /// The change type of the event.
        Type             mType;
        /// The owner of added/removed items (used for ITEM_ADDED, ITEM_DELETE).
        /// This can be a node graph or a pin. In case it's a pin, mChangedOwner points
        /// to the parent node of the pin and the pin is identified via mChangedOwnerPinIx.
        const ApiItemProxy* mChangedOwner;
        /// The index of the pin, if mChangedOwner is a node.
        uint32_t         mChangedOwnerPinIx;
        /// The item that got changed.
        const ApiItemProxy* mChangedItem;
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
            GRAPH_TIME_CHANGED = Octane::TimeEventType::GRAPH_TIME_CHANGED,
            GRAPH_INTERVAL_CHANGED = Octane::TimeEventType::GRAPH_INTERVAL_CHANGED,
            FRAME_RATE_CHANGED = Octane::TimeEventType::FRAME_RATE_CHANGED,
        };

        /// Type of event.
        Type                   mType;
        /// The root node graph affected, which is only set if mType is GRAPH_TIME_CHANGED or
        /// GRAPH_INTERVAL_CHANGED.
        const ApiRootNodeGraphProxy* mRootGraph;
    };


    struct GRPCChangeTimeObserver
    {
        /// Callback, called on a time change event.
        typedef void (*OnChangeT)(
            const GRPCChangeManagerTimeChangeEvent& eventData,
            void* userData);

        OnChangeT mCallback;
        int       mCallbackId;
        void* mUserData;
    };


    struct GRPCChangeObserver
    {
        /// Callback, called on a change event.
        typedef void (*OnChangeT)(
            const GRPCChangeManagerChangeEvent& eventData,
            void* userData);

        OnChangeT mCallback;
        int       mCallbackId;
        void* mUserData;
    };


    struct GRPCProjectManagerObserver
    {
        /// Callback, called on a change event.
        typedef void (*OnChangeT)(
            void* userData);

        OnChangeT mCallback;
        int       mCallbackId;
        void* mUserData;
    };


    struct GRPCSelectionManagerObserver
    {
        /// Callback, called on a change event.
        typedef void (*OnChangeT)(
            void* userData);

        OnChangeT mCallback;
        int       mCallbackId;
        void* mUserData;
    };
};