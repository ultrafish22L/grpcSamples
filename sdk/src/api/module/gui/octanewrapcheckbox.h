// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_CHECK_BOX_H_
#define _OCTANE_WRAP_CHECK_BOX_H_   1

// system includes
#include <string>
#include <vector>
// api includes
#include "octanetypes.h"
#include "octanewrapguicomponent.h"

namespace Octane
{
class ApiCheckBox;
}

namespace OctaneWrap
{

class CheckBox;

//--------------------------------------------------------------------------------------------------
/// Interface for check box listeners.
class CheckBoxListener
{
public:

    virtual void onClicked(
        OctaneWrap::CheckBox &checkBox) =0;
};



//--------------------------------------------------------------------------------------------------
/// Convenience wrapper for ApiCheckBox.
class CheckBox : public GuiComponent
{
    OCTANEAPI_NO_COPY(CheckBox);

public:

    /// Creates a check box.
    ///
    /// @param[in]  text
    ///     Text that appears next to the check mark.
    CheckBox(
        const std::string &text);

    /// Destructs this check box.
    virtual ~CheckBox();

    /// Sets the button checked.
    /// 
    /// @param[in]  checked
    ///     TRUE for checked, FALSE for unchecked.
    /// @param[in]  sendEvent
    ///     TRUE to trigger an event callback.
    void setChecked(
        const bool checked,
        const bool sendEvent);

    /// Checks if the checkbox is checked (ticked).
    bool isChecked() const;
 
    /// Adds a listener.
    void addListener(
        CheckBoxListener &listener);

    /// Removes a listener.
    void removeListener(
        CheckBoxListener &listener);

private:

    /// Wrapped checkbox
    Octane::ApiCheckBox            *mApiCheckBox;
    /// List of listeners.
    std::vector<CheckBoxListener*> mListeners;

    /// internal C callback
    static void onClicked(
        Octane::ApiCheckBox &checkBox,
        void                *privateData);
};

} // namespace OctaneWrap


#endif // #ifndef _OCTANE_WRAP_CHECK_BOX_H_
