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
namespace OctaneGRPC
{
    class ApiRootNodeGraphProxy;
    class ApiItemProxy;
}


#include "apichangemanager.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}

#include "grpcchangeevents.h"

namespace OctaneGRPC
{

/// Proxy class for ApiChangeManager
class ApiChangeManagerProxy : public GRPCBase
{
public:
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
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void observeApiItem(
            const ApiItemProxy &                      item,
            GRPCChangeObserver                       observer,
            const int                                 eventMask
            );

    /// Removes an observer from the item. This function doesn't do anything if
    /// the observer wasn't registered with observeApiItem.
    ///
    /// @param[in]  item
    ///     The item of which the callback will be removed from the callback list.
    /// @param[in]  observer
    ///     The observer that wants to stop observing the item.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void stopObserving(
            const ApiItemProxy &                      item,
            GRPCChangeObserver                       observer
            );

    /// Removes a callback from all the items it's hooked up to. This function
    /// doesn't do anything if the callback wasn't registered with observeApiItem.
    ///
    /// @param[in]  observer
    ///     The observer that wants to stop observing everything.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void stopObserving(
            GRPCChangeObserver   observer
            );

    /// Removes all the observers.
    /// @param[out] status
    ///     Contains the status of the gRPC call
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
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void update();

    /// Adds a time observer to the observer list. From that point on the observer will receive
    /// time change events that are emitted for the specified root node graph.
    /// Note : All observers will receive the TimeEventType::FRAME_RATE_CHANGED event,
    /// regardless of the root node graph they are observing.
    ///
    /// @param[in] observer
    ///     The observer the will be added to the list.
    /// @param[in] rootNodeGraph
    ///     "The root node graph to start observing.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void addTimeObserver(
            GRPCChangeTimeObserver                   observer,
            const ApiRootNodeGraphProxy &             rootNodeGraph
            );

    /// Removes a time observer from the observer list.
    ///
    /// @param[in] observer
    ///     The observer the will be removed from the list.
    /// @param[in] rootNodeGraph
    ///     The root node graph to stop observing. If this is nullptr, the change manager
    ///     will stop the observer observing from all root node graphs it was observing.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void removeTimeObserver(
            GRPCChangeTimeObserver                   observer,
            const ApiRootNodeGraphProxy *             rootNodeGraph
            );

    /// Removes all the time observers.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void stopObservingTime();

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
