// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _API_PROGRESS_BAR_H_
#define _API_PROGRESS_BAR_H_    1

#include "apiguicomponent.h"
#include "octanetypes.h"

namespace Octane
{

//--------------------------------------------------------------------------------------------------
/// Displays progress for operations.
class OCTANEAPI_DECL ApiProgressBar : public ApiGuiComponent
{
    OCTANEAPI_NO_COPY(ApiProgressBar);

public:

    /// Creates a new progress bar.
    /// 
    /// @param[in]  displayPercentage
    ///     TRUE to use a percentage display on the progress bar.
    /// @return
    ///     Pointer to the progress bar or nullptr if something went wrong.
    static ApiProgressBar* create();

    /// Destroys this progress bar.
    void destroy();

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
        const char *newText);

private:

    ApiProgressBar();
};


} // namespace Octane

#endif // #ifndef _API_PROGRESS_BAR_H_
