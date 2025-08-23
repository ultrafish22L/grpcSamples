// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_NUMERIC_BOX_H_
#define _OCTANE_WRAP_NUMERIC_BOX_H_ 1

// system includes
#include <string>
#include <vector>
// api includes
#include "octanetypes.h"
#include "octanegrpcwrapguicomponent.h"
#include "apinumericboxclient.h"

namespace Octane
{
class ApiNumericBox;
}

namespace OctaneWrap
{

class NumericBox;

//--------------------------------------------------------------------------------------------------
/// Interface for numeric box listeners.
class NumericBoxListener
{
public:

    virtual void valueChanged(
        OctaneWrap::NumericBox &numericBox) =0;
};



//--------------------------------------------------------------------------------------------------
/// Convenience wrapper for ApiNumericBox.
class NumericBox : public GuiComponent
{
    OCTANEAPI_NO_COPY(NumericBox);

public:

    /// Creates a numeric box.
    ///
    /// @param[in]  step
    ///     Step size between 2 consecutive values (use a step size of 1 for integer boxes).
    NumericBox(
        const double step);

    /// Destructs this numeric box.
    virtual ~NumericBox();

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

    /// Adds a listener.
    void addListener(
        NumericBoxListener &listener);

    /// Removes a listener.
    void removeListener(
        NumericBoxListener &listener);

private:

    /// Wrapped NumericBox
    OctaneGRPC::ApiNumericBoxProxy    mApiNumericBox;
    /// List of listeners.
    std::vector<NumericBoxListener*>  mListeners;

    /// internal C callback
    static void onValueChanged(
        OctaneGRPC::ApiNumericBoxProxy &  NumericBox,
        void *                            privateData);
};

} // namespace OctaneWrap


#endif // #ifndef _CAMERARESPONSENODE_H
