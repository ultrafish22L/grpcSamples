// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _API_NUMERIC_BOX_H_
#define _API_NUMERIC_BOX_H_ 1

// system includes
#include <float.h>
// api includes
#include "apiguicomponent.h"
#include "octanetypes.h"

namespace Octane
{

//--------------------------------------------------------------------------------------------------
/// Numeric input field.
class OCTANEAPI_DECL ApiNumericBox : public ApiGuiComponent
{
    OCTANEAPI_NO_COPY(ApiNumericBox);

public:

    /// types
    typedef void (*NumericBoxChangedCallbackT)(ApiNumericBox&, void*);

    /// Creates a numeric box.
    ///
    /// @param[in]  step
    ///     Step size between 2 consecutive values (use a step size of 1 for integer boxes).
    /// @param[in]  callback
    ///     Callback, called every time the user changes the value in the box.
    /// @param[in]  privateData
    ///     Private data passed back into the callback.
    /// @return
    ///     Pointer to the box.
    static ApiNumericBox* create(
        const double               step,
        NumericBoxChangedCallbackT callback,
        void                       *privateData);

    /// Destroys this numeric box.
    void destroy();

    /// Returns the current value in the box.
    double value() const;

    /// Sets the value in the box.
    ///
    /// @param[in]  newValue
    ///     The new value for the box.
    /// @param[in]  sendEvent
    ///     TRUE to send the event to the callback.
    void setValue(
        const double newValue,
        const bool   sendEvent);

    /// Sets the limits of this box. These limits are used to clamp the value. If the slider minimum
    /// or maximum are at the minimum/maximum float range, no slider is displayed.
    ///
    /// @param[in]  minimum
    ///     Minimum allowed value.
    /// @param[in]  maximum
    ///     Maximum allowed value.
    /// @param[in]  sliderMinimum
    ///     Minimum displayed value on the slider.
    /// @param[in]  sliderMaximum
    ///     Maximum displayed value on the slider.
    void setLimits( 
        const double minimum,
        const double maximum, 
        const double sliderMinimum = -FLT_MAX,
        const double sliderMaximum = FLT_MAX);

private:

    ApiNumericBox();
};


} // namespace Octane

#endif // #ifndef _API_NUMERIC_BOX_H_
