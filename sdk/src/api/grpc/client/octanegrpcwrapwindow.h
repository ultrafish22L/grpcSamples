// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_WINDOW_H_
#define _OCTANE_WRAP_WINDOW_H_  1

// system includes
#include <string>
#include <vector>
// api includes
#include "octanetypes.h"
#include "octanegrpcwrapguicomponent.h"
#include "apiwindowclient.h"

namespace Octane
{
class ApiWindow;
}

namespace OctaneWrap
{

class Window;

//--------------------------------------------------------------------------------------------------
/// Interface for window listeners.
class WindowListener 
{
public:

    virtual void onWindowClose(
        Window &window) =0;
};



//--------------------------------------------------------------------------------------------------
/// Resizable window.
class Window : public GuiComponent
{
    OCTANEAPI_NO_COPY(Window);

public:

    /// Creates a new window. The window is not visible.
    ///
    /// @param[in]  title
    ///     Title to appear on top of the window.
    Window(
        const std::string &title);

    /// Destructor.
    virtual ~Window();

    /// Windows only have a single content component. You don't add to a window by calling
    /// addChildComponent() but using addContentComponent instead.
    ///
    /// The assumption is that the size of the content component is the minimimum size as possible
    /// and the the content component can only stretch.
    ///
    /// @param[in]  contentComponent
    ///     Content component that is displayed in the window. The window doesn't take ownership
    ///     of the component so it's up to the caller to delete it afterwards. Don't delete this
    ///     component before the window was closed.
    void addContentComponent(
        GuiComponent &contentComponent);    

    /// Shows this window. The window will pop-up in the centre of the window that is currently
    /// active in the application.
    void show();

    /// Hides this window again.
    void hide();

    /// Returns the native window handle of the window.
    void * nativeHandle();

    /// Add a listener for this window.
    void addListener(
        WindowListener &listener);

    /// Remove a listener from this window.
    void removeListener(
        WindowListener &listener);

private:

    /// wrapped api window
    ApiWindowProxy               mApiWindow;
    /// list of listeners
    std::vector<WindowListener*> mListeners;

    /// Internal C-style callback.
    static void windowCloseCallback(
        ApiWindowProxy    &window,
        void              *privateData);
};

} // namespace Octane


#endif // #ifndef _OCTANE_WRAP_WINDOW_H_
