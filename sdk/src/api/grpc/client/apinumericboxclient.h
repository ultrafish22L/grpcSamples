// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once

#include "octanetypes.h"
#ifdef OCTANEAPI_DECL
#undef OCTANEAPI_DECL
#endif
#define OCTANEAPI_DECL
#include "octanevectypes.h"
#include "grpcbase.h"
#include "clientcallbackmgr.h"
#include "grpcapinodeinfo.h"
#include "apiguicomponentclient.h"


#include "apinumericbox.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiNumericBox
class ApiNumericBoxProxy : public ApiGuiComponentProxy
{
public:
    /// Creates a numeric box.
    ///
    /// @param[in]  step
    ///     Step size between 2 consecutive values (use a step size of 1 for integer boxes).
    /// @param[in]  callback
    ///     Callback, called every time the user changes the value in the box.
    /// @param[in]  privateData
    ///     Private data passed back into the callback.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Pointer to the box.
    static ApiNumericBoxProxy create(
            const double                              step,
            GRPCNumericBoxChangedCallbackT           callback,
            void *                                    privateData
            );

    /// Destroys this numeric box.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroy();

    /// Returns the current value in the box.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    double value() const;

    /// Sets the value in the box.
    ///
    /// @param[in]  newValue
    ///     The new value for the box.
    /// @param[in]  sendEvent
    ///     TRUE to send the event to the callback.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setValue(
            const double                              newValue,
            const bool                                sendEvent
            );

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
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setLimits(
            const double                              minimum,
            const double                              maximum,
            const double                              sliderMinimum,
            const double                              sliderMaximum
            );

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
