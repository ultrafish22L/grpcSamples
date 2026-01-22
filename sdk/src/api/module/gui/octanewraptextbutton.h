// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_TEXT_BUTTON_H_
#define _OCTANE_WRAP_TEXT_BUTTON_H_  1

// system includes
#include <string>
#include <vector>
// api includes
#include "octanetypes.h"
#include "octanewrapguicomponent.h"

namespace Octane
{
class ApiTextButton;
}

namespace OctaneWrap
{

class TextButton;

//--------------------------------------------------------------------------------------------------
/// Interface for the button listener.
class ButtonListener
{
public:

    virtual void buttonClicked(
        OctaneWrap::TextButton &button) =0;
};



//--------------------------------------------------------------------------------------------------
/// Wraps ApiTextButton.
class TextButton : public GuiComponent
{
    OCTANEAPI_NO_COPY(TextButton);

public:

    /// Create a new text button
    /// 
    /// @param[in]  text
    ///     Text to appear on the button.
    TextButton(
        const std::string &text);

    /// Destruct this button.
    virtual ~TextButton();

    /// Updates the text on the button.
    void setText(
        const std::string &text);

    /// Returns the text on the button.
    std::string text() const;

    /// Adds a listener.
    void addListener(
        ButtonListener &listener);

    /// Removes a listener.
    void removeListener(
        ButtonListener &listener);

private:

    /// Wrapped ApiTextButton.
    Octane::ApiTextButton        *mApiTextButton;
    /// List of button listeners.
    std::vector<ButtonListener*> mListener;

    /// internal C callback
    static void buttonClicked(
        Octane::ApiTextButton &button,
        void                  *privateData);
};

} // namespace OctaneWrap


#endif // #ifndef _OCTANE_WRAP_TEXT_BUTTON_H_
