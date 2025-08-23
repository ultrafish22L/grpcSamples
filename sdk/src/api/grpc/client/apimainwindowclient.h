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
    class ApiNodeGraphProxy;
    class ApiProjectWorkspaceProxy;
}
#include "apiguicomponentclient.h"


#include "apimainwindow.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiMainWindow
class ApiMainWindowProxy : public ApiGuiComponentProxy
{
public:
    /// Fetches or creates a new ApiMainWindow. Only one can exist.
    ///
    /// @param[in] callback
    ///     A function ptr that will be called when this window is closed. Keep in mind that when
    ///     the window is closed by the user, it will not be destroyed by Octane, only exiting the
    ///     API will destroy it.
    /// @param[in] callbackPrivateData
    ///     Private void ptr that will be passed to the callback above when the window is closed.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Pointer to the MainWindow created. This pointer will still be owned by Octane, do not
    ///     destroy it.
    static ApiMainWindowProxy fetchOrCreateInstance(
            Octane::ApiMainWindow::OnMainWindowCloseCallbackT callback,
            void *const                               callbackPrivateData
            );

    /// Yields to perform some UI tasks. Unblocks the UI for a specified amount of time. Note that
    /// this function calls Thread::sleep(), so if you need this function to not yield the thread,
    /// (which sometimes causes problems), then pass 0 to clear the message queue and return
    /// without yielding.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void runDispatchLoopUntil(
            const int   millis
            );

    /// Sets the DPI of the UI.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void setDpi(
            const uint32_t   dpi
            );

    /// Windows only have a single content component. You don't add to a window by calling
    /// addChildComponent() but using addContentComponent instead.
    ///
    /// The assumption is that the size of the content component is the minimimum size as possible
    /// and the content component can only stretch.
    ///
    /// @param[in]  contentComponent
    ///     Content component that is displayed in the window. The window doesn't take ownership
    ///     of the component so it's up to the caller to delete it afterwards. Don't delete this
    ///     component before the window was closed.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void addContentComponent(
            ApiGuiComponentProxy &   contentComponent
            );

    /// Returns the ProjectWorkspace of this MainWindow. This pointer is owned by Octane; do not
    /// destroy it.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiProjectWorkspaceProxy projectWorkspace() const;

    /// Returns the ProjectWorkspace of this MainWindow. This pointer is owned by Octane; do not
    /// destroy it.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiProjectWorkspaceProxy projectWorkspace();

    /// Shows this window.
    ///
    /// @param maximized
    ///     Whether to show the window maximized. If false, the window will pop up in the center of
    ///     the window that is currently active in the application.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void show(
            bool   maximized
            );

    /// Hides this window again.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void hide();

    /// Returns TRUE if this window is visible.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool visible() const;

    /// Sets default ApiNodeGraph to be shown by any ApiNodeGraphEditors created by the user.
    ///
    /// Please note that the set node graph will only be used by newly create node graph editors and
    /// doesn't affect already existing node graph editors. Ideally, this should be set before the
    /// any node graph editors are created, i.e. right at the beginning.
    ///
    /// @param[in]  graph
    ///     The node graph that should be set as the default node graph of the workspace. If NULL,
    ///     then the root node graph of the current project will be used instead (see
    ///     @ref ApiProjectManager::rootNodeGraph()).
    ///     Must have the current Octane version.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setDefaultGraph(
            ApiNodeGraphProxy *   graph
            );

    /// Gets the default ApiNodeGraph to be shown by any ApiNodeGraphEditors created by the user.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiNodeGraphProxy defaultGraph() const;

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
