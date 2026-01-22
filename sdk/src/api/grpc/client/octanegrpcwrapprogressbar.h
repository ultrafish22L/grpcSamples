// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_PROGRESS_BAR_H_
#define _OCTANE_WRAP_PROGRESS_BAR_H_ 1

// system includes
#include <string>
// api includes
#include "octanetypes.h"
#include "octanegrpcwrapguicomponent.h"
#include "apiprogressbarclient.h"

namespace Octane
{
class ApiProgressBar;
}

namespace OctaneWrap
{

class ProgressBar;

//--------------------------------------------------------------------------------------------------
/// Convenience wrapper for ApiProgressBar.
class ProgressBar : public GuiComponent
{
    OCTANEAPI_NO_COPY(ProgressBar);

public:

    /// Creates a progress bar.
    ProgressBar();

    /// Destructs this progress bar.
    virtual ~ProgressBar();

    /// Set the progress to a new value.
    /// 
    /// @param[in]  newValue
    ///     If value is not in [0,1], a spinning progress bar is shown.
    void setProgress(
        const double newValue);

    /// Returns the current progress.
    double progress() const;

    /// Sets the text displayed on the progress bar.
    void setText(
        const std::string &newText);

private:

    /// Wrapped ProgressBar
    OctaneGRPC::ApiProgressBarProxy mApiProgressBar;
};

} // namespace OctaneWrap


#endif // #ifndef _CAMERARESPONSENODE_H
