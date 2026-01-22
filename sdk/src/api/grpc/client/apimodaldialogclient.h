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
    class ApiGuiComponentProxy;
}
#include "apiguicomponentclient.h"


#include "apimodaldialog.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiModalDialog
class ApiModalDialogProxy : public ApiGuiComponentProxy
{
public:
    /// Creates a new modal dialog. On creation, the dialog is not visible.
    ///
    /// @param[in]  dialogTitle
    ///     Text shown in the title bar of the dialog.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Dialog that should be destroyed with destroy().
    static ApiModalDialogProxy create(
            const char *   dialogTitle
            );

    /// Destroys the dialog created with create().
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

    /// Shows this dialog. This will block until the dialog is closed. When the dialog is already
    /// visible, this will return immediately.
    ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Value passed into the close call.
    int show();

    /// Closes the dialog. This will unblock the show() call.
    ///
    /// @param[in]  retValue
    ///     Return value, returned by the show call.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void close(
            const int   retValue
            );

    /// Displays an information message in a popup.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void showInfoMessageDialog(
            const char *                              dialogTitle,
            const char *                              infoMessage
            );

    /// Displays an error message in a popup.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void showErrorMessageDialog(
            const char *                              dialogTitle,
            const char *                              errorMessage
            );

    /// Displays a 2-button dialog with an ok and cancel button. Returns TRUE when the user clicked
    /// OK and FALSE if the user clicked cancel.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool showOkCancelDialog(
            const char *                              dialogTitle,
            const char *                              message,
            const char *                              okButtonText,
            const char *                              cancelButtonText
            );

    /// Displays a 3-button dialog with a yes, no and cancel buttons.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::ApiModalDialog::DialogResult showYesNoCancelDialog(
            const char *                              dialogTitle,
            const char *                              message,
            const char *                              yesButtonText,
            const char *                              noButtonText,
            const char *                              cancelButtonText
            );

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
