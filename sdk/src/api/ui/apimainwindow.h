// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#include "apiguicomponent.h"
#include "octanetypes.h"


namespace Octane
{

class ApiNodeGraph;
class ApiProjectWorkspace;


//--------------------------------------------------------------------------------------------------
/// Main window that will contain a menu bar and a status bar.  There should only be one of these
/// objects instantiated.
class OCTANEAPI_DECL ApiMainWindow : public ApiGuiComponent
{
    OCTANEAPI_NO_COPY(ApiMainWindow);

public:

    typedef void (*OnMainWindowCloseCallbackT)(void *const privateData);

    /// Fetches or creates a new ApiMainWindow. Only one can exist. 
    ///
    /// @param[in] callback
    ///     A function ptr that will be called when this window is closed. Keep in mind that when
    ///     the window is closed by the user, it will not be destroyed by Octane, only exiting the
    ///     API will destroy it.
    /// @param[in] callbackPrivateData
    ///     Private void ptr that will be passed to the callback above when the window is closed.
    /// @return
    ///     Pointer to the MainWindow created. This pointer will still be owned by Octane, do not
    ///     destroy it.
    static ApiMainWindow* fetchOrCreateInstance(
        OnMainWindowCloseCallbackT callback            = NULL,
        void                *const callbackPrivateData = NULL);

    /// Yields to perform some UI tasks. Unblocks the UI for a specified amount of time. Note that 
    /// this function calls Thread::sleep(), so if you need this function to not yield the thread,
    /// (which sometimes causes problems), then pass 0 to clear the message queue and return 
    /// without yielding.
    static void runDispatchLoopUntil(
        const int millis);

    /// Sets the DPI of the UI. 
    static void setDpi(
        const uint32_t dpi);

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
    void addContentComponent(
        ApiGuiComponent &contentComponent);

    /// Returns the ProjectWorkspace of this MainWindow. This pointer is owned by Octane; do not
    /// destroy it.
    const ApiProjectWorkspace * projectWorkspace() const;

    /// Returns the ProjectWorkspace of this MainWindow. This pointer is owned by Octane; do not
    /// destroy it.
    ApiProjectWorkspace * projectWorkspace();

    /// Shows this window.
    ///
    /// @param maximized
    ///     Whether to show the window maximized. If false, the window will pop up in the center of
    ///     the window that is currently active in the application.
    void show(
        bool maximized = false);

    /// Hides this window again.
    void hide();

    /// Returns TRUE if this window is visible.
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
    void setDefaultGraph(
        ApiNodeGraph * graph);

    /// Gets the default ApiNodeGraph to be shown by any ApiNodeGraphEditors created by the user.
    ApiNodeGraph* defaultGraph() const;

private:
    
    ApiMainWindow();
};



} // namespace Octane
