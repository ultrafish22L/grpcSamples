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
class ApiGuiComponentProxy;
#include "apiguicomponentclient.h"


#include "apiwindow.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiWindow
class ApiWindowProxy : public ApiGuiComponentProxy
{
public:
    /// Creates a new ApiWindow.
    ///
    /// @param[in]  title
    ///     Title displayed on the window.
    /// @param[in]  closeCallback
    ///     Close callback, this callback is called when the user closes the window. The window
    ///     should be destroyed in this callback. May be null.
    /// @param[in]  privateData
    ///     Optional data, passed back when the callback is called.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Pointer to the window created.
    static ApiWindowProxy create(
            const char *                              title,
            GRPCOnWindowCloseCallbackT               closeCallback,
            void *                                    privateData
            );

    /// Destroys this window.
    /// @param[out] status
    ///     Contains the status of the gRPC call
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
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void addContentComponent(
            ApiGuiComponentProxy &   contentComponent
            );

    /// Shows this window. The window will pop-up in the centre of the window that is currently
    /// active in the application.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void show();

    /// Hides this window again.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void hide();

    /// Returns whether this window is visible.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool visible() const;

    /// Returns the native window handle of the window.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void * nativeHandle();

private:
    static GRPCSettings & getGRPCSettings();
};
