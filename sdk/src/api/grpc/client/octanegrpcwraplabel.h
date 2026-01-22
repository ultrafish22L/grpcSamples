// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_LABEL_H_
#define _OCTANE_WRAP_LABEL_H_   1

// system includes
#include <string>
// api includes
#include "octanetypes.h"
#include "octanegrpcwrapguicomponent.h"
#include "apilabelclient.h"

namespace Octane
{
class ApiLabel;
}

namespace OctaneWrap
{

//--------------------------------------------------------------------------------------------------
/// Convenience wrapper for ApiLabel.
class Label : public GuiComponent
{
    OCTANEAPI_NO_COPY(Label);

public:

    /// Creates a label.
    ///
    /// @param[in]  text
    ///     Text that appears on the label.
    Label(
        const std::string &text);

    /// Destructs this label.
    virtual ~Label();

    /// Returns the text on the label.
    std::string text() const;

    /// Changes the label text.
    ///
    /// @param[in]  newText
    ///     New text to set in the label.
    /// @param[in]  sendEvent
    ///     TRUE to notify the label listeners.
    void setText(
        const std::string &text,
        const bool        sendEvent);

private:

    /// wrapped label
    OctaneGRPC::ApiLabelProxy mApiLabel;
};

} // namespace OctaneWrap


#endif // #ifndef _OCTANE_WRAP_LABEL_H_
