// Copyright (C) 2025 OTOY NZ Ltd.

// myself
#include "octanegrpcwrapmodaldialog.h"
// application includes
#include "apimodaldialog.h"

using namespace OctaneWrap;

ModalDialog::ModalDialog(
    const std::string &dialogTitle)
{
    mApiModalDialog = OctaneGRPC::ApiModalDialogProxy::create(dialogTitle.c_str());
    mComponent      = &mApiModalDialog;
}


ModalDialog::~ModalDialog()
{
    mApiModalDialog.destroy();
    //mApiModalDialog = NULL;
}


void ModalDialog::addContentComponent(
    GuiComponent &contentComponent)
{
    mApiModalDialog.addContentComponent(*contentComponent.wrappedComponent());
}


int ModalDialog::show()
{
    return mApiModalDialog.show();
}


void ModalDialog::close(
    const int retValue)
{
    mApiModalDialog.close(retValue);
}


void ModalDialog::showInfoMessageDialog(
    const std::string &dialogTitle,
    const std::string &infoMessage)
{
   OctaneGRPC::ApiModalDialogProxy::showInfoMessageDialog(dialogTitle.c_str(), infoMessage.c_str());
}


void ModalDialog::showErrorMessageDialog(
    const std::string &dialogTitle,
    const std::string &errorMessage)
{
    OctaneGRPC::ApiModalDialogProxy::showErrorMessageDialog(dialogTitle.c_str(), errorMessage.c_str());
}


bool ModalDialog::showOkCancelDialog(
    const std::string &dialogTitle,
    const std::string &message,
    const std::string &okButtonText,
    const std::string &cancelButtonText)
{
    return OctaneGRPC::ApiModalDialogProxy::showOkCancelDialog(dialogTitle.c_str(),
                                                   message.c_str(),
                                                   okButtonText.c_str(),
                                                   cancelButtonText.c_str()
                                                   );
}


Octane::ApiModalDialog::DialogResult ModalDialog::showYesNoCancelDialog(
    const std::string &dialogTitle,
    const std::string &message,
    const std::string &yesButtonText,
    const std::string &noButtonText,
    const std::string &cancelButtonText)
{
    return OctaneGRPC::ApiModalDialogProxy::showYesNoCancelDialog(dialogTitle.c_str(),
                                                      message.c_str(),
                                                      yesButtonText.c_str(),
                                                      noButtonText.c_str(),
                                                      cancelButtonText.c_str()
                                                      );
}
