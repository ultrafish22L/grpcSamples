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


#include "apicolorswatch.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiColorSwatch
class ApiColorSwatchProxy : public ApiGuiComponentProxy
{
public:
    /// Creates a new color swatch.
    ///
    /// @param[in]  disableGammaCorrection
    ///     TRUE if the colour picker should not apply any gamma correction. The value returned by
    ///     color() will also not be gamma corrected.
    /// @param[in]  changeCallback
    ///     Callback called when the color in the swatch changes.
    /// @param[in]  privateData
    ///     Private data passed back unchanged in the callback.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Pointer to the new color swatch.
    static ApiColorSwatchProxy create(
            const bool                                disableGammaCorrection,
            GRPCColorChangedT                        changeCallback,
            void *                                    privateData
            );

    /// Destroys this color swatch.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroy();

    /// Set the color displayed in the color swatch.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setColor(
            const Octane::ApiColorHdr &   color
            );

    /// Returns the color selected in the color swatch.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::ApiColorHdr color() const;

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
