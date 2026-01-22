// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _API_WINDOW_H_
#define _API_WINDOW_H_  1

#include "apiguicomponent.h"
#include "octanetypes.h"

namespace Octane
{

//--------------------------------------------------------------------------------------------------
/// Resizable gui window. 
class OCTANEAPI_DECL ApiWindow : public ApiGuiComponent
{
    OCTANEAPI_NO_COPY(ApiWindow);

public:

    /// types
    typedef void (*OnWindowCloseCallbackT)(ApiWindow&, void*);

    /// Creates a new ApiWindow.
    ///
    /// @param[in]  title
    ///     Title displayed on the window.
    /// @param[in]  closeCallback
    ///     Close callback, this callback is called when the user closes the window. The window
    ///     should be destroyed in this callback. May be null.
    /// @param[in]  privateData
    ///     Optional data, passed back when the callback is called.
    /// @return
    ///     Pointer to the window created.
    static ApiWindow *create(
        const char             *title,
        OnWindowCloseCallbackT closeCallback,
        void                   *privateData = NULL);

    /// Destroys this window.
    void destroy();

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
        ApiGuiComponent & contentComponent);

    /// Shows this window. The window will pop-up in the centre of the window that is currently
    /// active in the application.
    void show();

    /// Hides this window again.
    void hide();

    /// Returns whether this window is visible.
    bool visible() const;

    /// Returns the native window handle of the window.
    void * nativeHandle();

private:
    
    ApiWindow();
};

} // namespace Octane


#endif // #ifndef _API_WINDOW_H_
