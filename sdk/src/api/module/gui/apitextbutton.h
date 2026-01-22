// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _API_TEXT_BUTTON_H_
#define _API_TEXT_BUTTON_H_ 1

#include "apiguicomponent.h"
#include "octanetypes.h"

namespace Octane
{

//--------------------------------------------------------------------------------------------------
/// Clickable button with a text written on it.
class OCTANEAPI_DECL ApiTextButton : public ApiGuiComponent
{
    OCTANEAPI_NO_COPY(ApiTextButton);

public:

    /// types
    typedef void (*ButtonClickedCallbackT)(ApiTextButton&, void*);

    /// Creates a new text button. Returns a NULL pointer on failure.
    ///
    /// @param[in]  text
    ///     Text to appear on the button.
    /// @param[in]  clickCallback
    ///     Function called when the user clicks the button.
    /// @param[in]  privateData
    ///     Data passed back untouched into the callback.
    /// @return
    ///     Pointer the new button.
    static ApiTextButton* create(
        const char             *text,
        ButtonClickedCallbackT clickCallback,
        void                   *privateData);

    /// Destroys the component created with create(..).
    void destroy();

    /// Updates the text on the button.
    void setText(
        const char *text);

    /// Returns the text on the button.
    const char* text() const;

private:

    ApiTextButton();
};

} // namespace Octane


#endif // #ifndef _API_TEXT_BUTTON_H_
