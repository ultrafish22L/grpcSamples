// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#include "octaneenums.h"
#include "octanetypes.h"



namespace Octane
{

class ApiItem;
class ApiRootNodeGraph;

//--------------------------------------------------------------------------------------------------
/// Register callbacks with the change manager to get notified of changes in the node system.
/// This class is thread-safe.
class OCTANEAPI_DECL ApiChangeManager
{
public:

    //-- Tracking nodesystem changes --

    /// Stores data of a node system event.
    ///
    /// Connect/disconnect events are usually not sent, with the exception of
    /// connecting/disconnecting an external node to/from a pin in which case 
    /// we somehow need to inform the system of the change.
    struct ChangeEvent 
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
        const ApiItem *  mChangedOwner;
        /// The index of the pin, if mChangedOwner is a node.
        uint32_t         mChangedOwnerPinIx;
        /// The item that got changed.
        const ApiItem *  mChangedItem;
        /// The index of the pin of which a connection got changed (used for CONNECTION_CHANGED).
        /// In this case mChangedItem will be the parent node of the pin.
        uint32_t         mChangedPinIx;
        /// Pointer to an array that contains the indices of the changed attributes/pins if the
        /// event is either ITEM_VALUE_CHANGED or ITEM_INPUT_CHANGED, otherwise NULL.
        /// The array is owned by Octane and only valid during the call of onNodeItemChage().
        const uint32_t * mChangedIndices;
        /// The size of mChangedIndices or 0 if mChangedIndices is NULL.
        uint32_t         mChangedIndicesSize;
    };

    // Change observer object. This object's callback is called on a change in the
    // nodesystem. It's important that all these observers are removed when the application
    // ends.
    struct Observer
    {
         /// Callback, called on a change event.
        typedef void (*OnChangeT)(
            const ChangeEvent & event,
            void *              userData);

        OnChangeT mCallback;
        void *    mUserData;
    };

    /// Registers a callback for receiving change events for the item. If the callback
    /// was already registered, the flags from the given event mask will be added to the existing
    /// event mask.
    ///
    /// @param[in]  item
    ///     The item that should be observed (must be valid).
    /// @param[in]  observer 
    ///     The observer interested in changes.
    ///     NOTE: The API doesn't take ownership of the observer so it needs to stay
    ///           valid while the observer is registered.
    /// @param[in]  eventMask
    ///     A bit mask of the events the observer wants to receive for this item.
    static void observeApiItem(
        const ApiItem & item,
        Observer &      observer,
        const int       eventMask);

    /// Removes an observer from the item. This function doesn't do anything if 
    /// the observer wasn't registered with observeApiItem.
    ///
    /// @param[in]  item
    ///     The item of which the callback will be removed from the callback list.
    /// @param[in]  observer 
    ///     The observer that wants to stop observing the item.
    static void stopObserving(
        const ApiItem & item,
        Observer &      observer);

    /// Removes a callback from all the items it's hooked up to. This function
    /// doesn't do anything if the callback wasn't registered with observeApiItem.
    ///
    /// @param[in]  observer 
    ///     The observer that wants to stop observing everything. 
    static void stopObserving(
        Observer & observer);

    /// Removes all the observers.
    static void stopObserving();

    /// Sends an update event to Octane which will then update all its sub-systems, which currently
    /// is mainly the render engine. If you make node changes they will not cause the sub-systems to
    /// update automatically. You have to call update() to achieve this. The advantage is that
    /// plugins can make big and massive changes in the node graph and then cause the render engine
    /// to update only once.
    /// 
    /// NOTE: This function will wait until all asynchronous compression jobs have finished to make
    /// sure that the render data change level you get after this function call represents the
    /// latest change level and won't be bumped up by some texture compression result that arrived
    /// after the update() call.
    static void update();

    //-- Tracking time changes --

    /// Info about a time change.
    struct TimeEvent
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
        const ApiRootNodeGraph *mRootGraph;
    };

    /// Time observer, this objects callback is called when the time of the document changes.
    struct TimeObserver
    {
        /// Callback, called on a time change event.
        typedef void (*OnChangeT)(
            const TimeEvent & event,
            void *            userData);

        OnChangeT mCallback;
        void      *mUserData;
    };

    /// Adds a time observer to the observer list. From that point on the observer will receive
    /// time change events that are emitted for the specified root node graph. 
    /// Note : All observers will receive the TimeEventType::FRAME_RATE_CHANGED event, 
    /// regardless of the root node graph they are observing.
    ///
    /// @param[in] observer
    ///     The observer the will be added to the list.
    /// @param[in] rootNodeGraph
    ///     "The root node graph to start observing. 
    static void addTimeObserver(
        TimeObserver & observer,
        const ApiRootNodeGraph & rootNodeGraph);

    /// Removes a time observer from the observer list.
    ///
    /// @param[in] observer
    ///     The observer the will be removed from the list.
    /// @param[in] rootNodeGraph
    ///     The root node graph to stop observing. If this is nullptr, the change manager
    ///     will stop the observer observing from all root node graphs it was observing.
    static void removeTimeObserver(
        TimeObserver & observer,
        const ApiRootNodeGraph * rootNodeGraph = nullptr);

    /// Removes all the time observers.
    static void stopObservingTime();
};

} // namespace Octane
