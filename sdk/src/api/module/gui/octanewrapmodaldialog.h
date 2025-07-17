// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_MODAL_DIALOG_H_
#define _OCTANE_WRAP_MODAL_DIALOG_H_    1

// system includes
#include <string>
// api includes
#include "apimodaldialog.h"
#include "octanetypes.h"
#include "octanewrapguicomponent.h"



namespace OctaneWrap
{

//--------------------------------------------------------------------------------------------------
/// Wraps ApiModalDialog.
class ModalDialog : public GuiComponent
{
    OCTANEAPI_NO_COPY(ModalDialog);

public:

    /// Creates a new modal dialog. On creation, the dialog is not visible.
    ///
    /// @param[in]  dialogTitle
    ///     Text shown in the title bar of the dialog.
    ModalDialog(
        const std::string &dialogTitle);

    /// Destructor.
    virtual ~ModalDialog();

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

    /// Displays an information message in a popup.
    static void showInfoMessageDialog(
        const std::string &dialogTitle,
        const std::string &infoMessage);

    /// Displays an error message in a popup.
    static void showErrorMessageDialog(
        const std::string &dialogTitle,
        const std::string &errorMessage);

    /// Displays a 2-button dialog with an ok and cancel button. Returns TRUE when the user clicked
    /// OK and FALSE if the user clicked cancel.
    static bool showOkCancelDialog(
        const std::string &dialogTitle,
        const std::string &message,
        const std::string &okButtonText,
        const std::string &cancelButtonText);

    /// Displays a 3-button dialog with a yes, no and cancel buttons.
    static Octane::ApiModalDialog::DialogResult showYesNoCancelDialog(
        const std::string &dialogTitle,
        const std::string &message,
        const std::string &yesButtonText,
        const std::string &noButtonText,
        const std::string &cancelButtonText);


private:

    Octane::ApiModalDialog *mApiModalDialog;
};

} // namespace OctaneWrap

#endif // #ifndef _OCTANE_WRAP_MODAL_DIALOG_H_
