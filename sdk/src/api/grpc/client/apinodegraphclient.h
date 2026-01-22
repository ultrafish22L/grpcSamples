// Copyright (C) 2026 OTOY NZ Ltd.

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
    class ApiNodeProxy;
    class ApiItemProxy;
    class ApiItemArrayProxy;
    class ApiNodeArrayProxy;
    class ApiAnimationTimeTransformProxy;
}
#include "apiitemclient.h"


#include "apinodesystem.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiNodeGraph
class ApiNodeGraphProxy : public ApiItemProxy
{
public:
    /// Creates a new graph of the specified type.
    ///
    /// @param[in]  type
    ///     The type of the graph to create.
    /// @param[in]  ownerGraph
    ///     Graph that will own the new graph.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Pointer to the created graph or NULL if creation failed.
    static ApiNodeGraphProxy create(
            const Octane::NodeGraphType               type,
            ApiNodeGraphProxy &                       ownerGraph
            );

    /// Returns info for this graph.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    const Octane::ApiNodeGraphInfo info() const;

    /// Returns this graph's type.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::NodeGraphType type() const;

    /// Returns the owned items of the node graph.
    ///
    /// @param[in]  list
    ///     Empty item list. The graph will fill it in with pointer to the items
    ///     it owns.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void getOwnedItems(
            ApiItemArrayProxy &   list
            ) const;

    /// Returns the list of input nodes.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void getInputNodes(
            ApiNodeArrayProxy &   list
            ) const;

    /// Returns the list of output nodes.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void getOutputNodes(
            ApiNodeArrayProxy &   list
            ) const;

    /// Returns a list with all nodes in the graph of the given type.
    ///
    /// @param[in]  type
    ///     Type of the nodes we'd like to collect.
    /// @param[out] list
    ///     List of nodes that have the given type.
    /// @param[in]  recurse
    ///     Recurses into nested graphs to collect the nodes.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void findNodes(
            const Octane::NodeType                    type,
            ApiNodeArrayProxy &                       list,
            const bool                                recurse
            ) const;

    /// Returns the first node of the specified type.
    /// This function doesn't recurse in sub-graphs.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiNodeProxy findFirstNode(
            const Octane::NodeType   type
            ) const;

    /// Returns the first output linker of the specified pin type.
    /// This function doesn't recurse in sub-graphs.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiNodeProxy findFirstOutputNode(
            const Octane::NodePinType   pinType
            ) const;

    /// Find all items with a given name.
    ///
    /// @param[in]  name
    ///     The name of the items to collect.
    /// @param[out] list
    ///     List of items that match the given name.
    /// @param[in]  recurse
    ///     Recurses into nested graphs to collect the nodes.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void findItemsByName(
            const char *                              name,
            ApiItemArrayProxy &                       list,
            const bool                                recurse
            ) const;

    /// Assigns linear time transformation to the animation of the nested owned items
    /// Can be used to offset or scale the animation playback
    /// @param[in] delay
    ///     offset of the animation start time in seconds
    /// @param[in] speedUp
    ///     scale of the animation playback speed (1 is normal playback, 2 is 2x faster)
    /// @param[in] customInterval
    ///     Start and end time (in seconds) of the untransformed time of the animation that
    ///     should be played. The animation outside this interval will be cut out.
    ///     E.g. if the start time is 2s and the delay is 0s, then the transformed animation
    ///     at time 0 will be that of the untransformed animation at time 2s.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setLinearTimeTransform(
            const float                               delay,
            const float                               speedUp,
            const Octane::TimeSpanT                   customInterval
            );

    /// Returns current ApiAnimationTimeTransform
    /// or NULL if it doesn't have one
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiAnimationTimeTransformProxy timeTransform() const;

    /// Removes animation time transformation
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void clearTimeTransform();

    /// Returns an array of null-terminated strings containing all paths of the assets
    /// currently used by the current node graph
    ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @returns
    ///     The list of asset paths in the current node graph.
    ///     NOTE: The contents of this will be valid until this function is called again
    ///           from any node graph.
    std::vector<std::string> getAssetPaths();

    /// Recenter all items in this graph around the given position.
    ///
    /// @param[in] center
    ///     The point which will be the average of the positions of all items in this graph.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void recenter(
            const OctaneVec::float_2   center
            );

    /// Clears the node graph, i.e. deletes all nodes stored in it. If you call this function on
    /// the root node graph, ALL your nodes will be gone. -> Make sure that you also destroy all
    /// reference to those nodes on the plugin side.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void clear();

    /// Copies the items from the source graph into this graph.
    ///
    /// @param[in]  source
    ///     Source grap who's content we copy.
    /// @param[in]  origItems
    ///     Original items for which we'd like to know what their copies are.
    ///     These items don't have to have the same owner. This list is optional.
    /// @param[in]  origItemCount
    ///     The length of the list of original items.
    /// @param[out] copiedItems
    ///     Copies of the items in the list origItems. The copies are in the same
    ///     order as the origItems list. This list must be provided when origItems
    ///     is provided.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void copyFrom(
            const ApiNodeGraphProxy &                 source,
            const ApiItemProxy *const *               origItems,
            const size_t                              origItemCount,
            ApiItemArrayProxy *                       copiedItems
            );

    /// Copies one item into the node graph.
    ///
    /// @param[in]  sourceItem
    ///     The item to copy, this item must have an owner.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Ptr to the copied item or NULL if the item couldn't be copied.
    ApiItemProxy copyFrom(
            const ApiItemProxy &   sourceItem
            );

    /// Copies the tree starting at rootItem into this graph.
    ///
    /// @param[in]  rootItem
    ///     Item at the root of the copy tree, the item must have an owner. If the item is an
    ///     input linker then the returned copy is either:
    ///     - a copy of the input linker if it doesn't have a non-linker input node
    ///     - a copy of the non-linker input if the input linker has one
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Pointer to the copied item or NULL if the item couldn't be copied.
    ApiItemProxy copyItemTree(
            const ApiItemProxy &   rootItem
            );

    /// Copies an array of items into the node graph.
    ///
    /// @param[in]  sourceItems
    ///     Pointer to an array of items (must not be NULL). All the items in the array
    ///     must have the same owner and that owner can't be NULL.
    /// @param[in]  itemCount
    ///     The size of the array, i.e. the number of items in the array.
    /// @param[out] sourceItemCopies
    ///     Optional empty list. This method will fill it with a pointer to the copy for
    ///     each source items in sourceItems. This list has size itemCount. The copies are
    ///     in the same order as the source items.
    /// @param[in]  origItems
    ///     Optional list of original items for which we'd like to now what their copies are.
    ///     They don't have to be in sourceItems and don't have to have the same owner.
    /// @param[in]  origItemsCount
    ///     Size of origItems.
    /// @param[out] origItemsCopies
    ///     Optional list with the copies of origItems. This list must be provided if
    ///     the original items list is provided.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void copyFrom(
            const ApiItemProxy *const *               sourceItems,
            const size_t                              sourceItemsCount,
            ApiItemArrayProxy *                       sourceItemCopies,
            const ApiItemProxy *const *               origItems,
            const size_t                              origItemsCount,
            ApiItemArrayProxy *                       origItemCopies
            );

    /// Replace a group of node items with a group node containing a copy of these items. Any
    /// connections coming from other nodes are copied through linker nodes into the new group.
    ///
    /// @param[in]  items
    ///     The list of items to copy. All these items will be destroyed after copying.
    ///     The items must all be owned by this graph.
    /// @param[in]  itemsCount
    ///     The number of items in the list.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The nodegraph with the items or NULL.
    ApiNodeGraphProxy groupItems(
            ApiItemProxy *const *const                items,
            const size_t                              itemsCount
            );

    /// Replaces this node graph with a copy of its content in its parent node graph. This node
    /// graph must be owned by a node graph. This node graph will be gone afterwards.
    ///
    /// @param[out]  ungroupedItems
    ///     List of the ungrouped items.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void ungroup(
            ApiItemArrayProxy *const   ungroupedItems
            );

    /// Unfolds the specified node graph if it's inspectable, i.e. places items in a way that items
    /// don't overlap and connections don't intersect much. The order of linker nodes is kept, too.
    /// In the end, all items are moved so that their center of gravity is at (0,0).
    ///
    /// @param[in]  recursive  (optional)
    ///     If set to TRUE, all nested node graphs that are inspectable are unfolded, too.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void unfold(
            const bool   recursive
            );

    /// Shows the node graph in a window, allowing the user to edit this node graph. This call
    /// blocks until the window is closed. Only one window can be shown at any time by
    /// ApiNodeGraph::showWindow(). If another window is already open, this function does nothing.
    ///
    /// @param unfold
    ///     If TRUE the graph will be unfolded.
    /// @param windowState
    ///     Optional window state. When passed into the function we try to restore the window from
    ///     this state (window position, window size and split position).
    /// @param alwaysOnTop
    ///     Whether the window should be set to always on top. Either way, the window is still shown
    ///     modally. This should be set to false unless it causes problems, because when the window
    ///     is always on top tooltips don't work (plus, preventing other applications' windows from
    ///     ever being on top of this one is a bad idea). Set this to true only if the default
    ///     behavior breaks windowing in a way that's worse than broken tooltips.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     String with the last window state. This state can be used to restore the last state of
    ///     the window in the next showWindow() calls. This string is owned by the API and only
    ///     valid till the next call to showWindow().
    std::string showWindow(
            const bool                                unfold,
            const char *                              windowState,
            bool                                      alwaysOnTop
            );

    /// Closes the opened node graph editor window (if any). WARNING: calling this before
    /// showWindow() actually shows the window will not close the window later. This race-condition
    /// is something the plugin should take care of.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void closeWindow();

    /// Opens a dialog window where the user can import items from liveDB and localDB.
    ///
    /// If you use this function you must call closeDbWindow() before destroying this
    /// node graph.
    ///
    /// Do not use this while an ApiMainWindow is open. It may cause deadlocks.
    ///
    /// The function will open the dialog and return. The dialog is a non-modal dialog.
    /// The user may import one or more entries from liveDB or localDB before dismissing the dialog.
    /// Only one such dialog can be open at a time, if you call this while a dialog is already
    /// open, the existing dialog will be closed first.
    ///
    /// @param[in]  dbViewClosingCallback
    ///     Called when the dialog is being closed by the user. May be nullptr.
    /// @param[in]  dbViewLoadedCallback
    ///     Called after an item has been imported. The item will be imported as child items of
    ///     this node graph.
    /// @param[in]  userData
    ///     Passed to the callbacks as the first argument.
    /// @param[in]  showLiveDb
    ///     Show the LiveDB in this window too.
    ///
    /// Usage:
    ///
    /// If you want the dialog to retain its full state every time it is opened, create a
    /// node graph and don't delete it after importing an item:
    /// @code
    ///     Octane::ApiNodeGraph *returnGraph = ...
    /// @endcode
    ///
    /// Define the callbacks:
    /// @code
    ///     void dbViewClosingCallback(void *userData) {
    ///         ...
    ///     }
    ///     void dbViewLoadedCallback(void *userData, Octane::ItemDbOrigin origin) {
    ///         ...
    ///     }
    /// @endcode
    ///
    /// Now you can show the dialog
    /// @code
    ///     pRetGraph->showDbWindow(
    ///         dbViewClosingCallback, dbViewLoadedCallback, returnGraph, /*showLiveDb = */ true);
    /// @endcode
    ///
    /// Use ApiDBMaterialManager::unpackFileData() to unpack the image textures and other
    /// assets in the imported nodes.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void showDbWindow(
            Octane::ApiNodeGraph::DbViewClosingCallbackT * dbViewClosingCallback,
            Octane::ApiNodeGraph::DbViewLoadedCallbackT * dbViewLoadedCallback,
            void *                                    userData,
            const bool                                showLiveDb
            );

    /// Closes the currently opened DB window (if any)
    ///
    /// @param[in]  clearData
    ///     Clears all cached data.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void closeDbWindow(
            bool   clearData
            );

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
