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


#include "apiprogressbar.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiProgressBar
class ApiProgressBarProxy : public ApiGuiComponentProxy
{
public:
    /// Creates a new progress bar.
    ///
    /// @param[in]  displayPercentage
    ///     TRUE to use a percentage display on the progress bar.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Pointer to the progress bar or nullptr if something went wrong.
    static ApiProgressBarProxy create();

    /// Destroys this progress bar.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroy();

    /// Set the progress to a new value.
    ///
    /// @param[in]  newValue
    ///     If value is not in [0,1], a spinning progress bar is shown.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setProgress(
            const double   newValue
            );

    /// Returns the current progress.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    double progress() const;

    /// Sets the text displayed on the progress bar.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setText(
            const char *   newText
            );

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
