// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _API_MODAL_DIALOG_H_
#define _API_MODAL_DIALOG_H_    1

#include "apiguicomponent.h"
#include "octanetypes.h"


namespace Octane
{

//--------------------------------------------------------------------------------------------------
/// Dialog window that is modal. A modal window blocks gui events to all other components except
/// to those that are children of the modal window.
class OCTANEAPI_DECL ApiModalDialog : public ApiGuiComponent
{
    OCTANEAPI_NO_COPY(ApiModalDialog);

public:

    /// Creates a new modal dialog. On creation, the dialog is not visible.
    ///
    /// @param[in]  dialogTitle
    ///     Text shown in the title bar of the dialog.
    /// @return
    ///     Dialog that should be destroyed with destroy().
    static ApiModalDialog* create(
        const char *dialogTitle);

    /// Destroys the dialog created with create().
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
        ApiGuiComponent &contentComponent);    

    /// Shows this dialog. This will block until the dialog is closed. When the dialog is already
    /// visible, this will return immediately.
    ///
    /// @return
    ///     Value passed into the close call.
    int show();

    /// Closes the dialog. This will unblock the show() call.
    /// 
    /// @param[in]  retValue
    ///     Return value, returned by the show call.
    void close(
        const int retValue);

    //-- popup dialogs --

    /// Results of showing a dialog to the user.
    enum DialogResult
    {
        DIALOG_RESULT_YES    = 0,
        DIALOG_RESULT_NO     = 1,
        DIALOG_RESULT_CANCEL = 2,
    };

    /// Displays an information message in a popup.
    static void showInfoMessageDialog(
        const char *dialogTitle,
        const char *infoMessage);

    /// Displays an error message in a popup.
    static void showErrorMessageDialog(
        const char *dialogTitle,
        const char *errorMessage);

    /// Displays a 2-button dialog with an ok and cancel button. Returns TRUE when the user clicked
    /// OK and FALSE if the user clicked cancel.
    static bool showOkCancelDialog(
        const char *dialogTitle,
        const char *message,
        const char *okButtonText     = "OK",
        const char *cancelButtonText = "Cancel");

    /// Displays a 3-button dialog with a yes, no and cancel buttons.
    static DialogResult showYesNoCancelDialog(
        const char *dialogTitle,
        const char *message,
        const char *yesButtonText    = "Yes",
        const char *noButtonText     = "No",
        const char *cancelButtonText = "Cancel");

private:

    ApiModalDialog();
};

} // namespace Octane


#endif // #ifndef _API_MODAL_DIALOG_H_
