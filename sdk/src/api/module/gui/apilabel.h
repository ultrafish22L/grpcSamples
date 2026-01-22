// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _API_LABEL_H_
#define _API_LABEL_H_   1

#include "apiguicomponent.h"
#include "octanetypes.h"

namespace Octane
{

//--------------------------------------------------------------------------------------------------
/// Label that displays text.
class OCTANEAPI_DECL ApiLabel : public ApiGuiComponent
{
    OCTANEAPI_NO_COPY(ApiLabel);

public:

    /// Creates a new label.
    /// 
    /// @param[in]  text
    ///     Text to display on the label.
    static ApiLabel* create(
        const char *text);

    /// Destroys this label created by create(..).
    void destroy();

    /// Returns the text on the label.
    const char* text() const;

    /// Changes the label text.
    ///
    /// @param[in]  newText
    ///     New text to set in the label.
    /// @param[in]  sendEvent
    ///     TRUE to notify the label listeners.
    void setText(
        const char *newText,
        const bool sendEvent);

private:

    ApiLabel();
};


} // namespace Octane

#endif // #ifndef _API_LABEL_H_
