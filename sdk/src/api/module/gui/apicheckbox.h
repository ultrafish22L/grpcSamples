// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _API_CHECKBOX_H_
#define _API_CHECKBOX_H_    1

#include "apiguicomponent.h"
#include "octanetypes.h"

namespace Octane
{

//--------------------------------------------------------------------------------------------------
/// Check box with text alongside it.
class OCTANEAPI_DECL ApiCheckBox : public ApiGuiComponent
{
    OCTANEAPI_NO_COPY(ApiCheckBox);

public:

    /// types
    typedef void (*CheckedCallbackT)(ApiCheckBox&, void*);

    /// Creates a new checkbox. Returns a NULL pointer when creation failed.
    ///
    /// @param[in]  text
    ///     Text to display alongside the check box. Can be a NULL pointer.
    /// @param[in]  checkCallback
    ///     Callback, called when the checkbox is checked/unchecked. Can be a NULL pointer.
    /// @param[in]  privateData
    ///     Private data, passed back with the callback.
    /// @return
    ///     Pointer to the check box. Don't call delete on this pointer but call destroy().
    static ApiCheckBox* create(
        const char       *text,
        CheckedCallbackT callback,
        void             *privateData);

    /// Destroys the component created with create(..).
    void destroy();

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
    
private:

    ApiCheckBox();
};

}


#endif // #ifndef _API_CHECKBOX_H_
