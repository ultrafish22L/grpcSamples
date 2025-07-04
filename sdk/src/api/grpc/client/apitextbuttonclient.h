// Copyright (C) 2025 OTOY NZ Ltd.

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


#include "apitextbutton.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiTextButton
class ApiTextButtonProxy : public ApiGuiComponentProxy
{
public:
    /// Creates a new text button. Returns a NULL pointer on failure.
    ///
    /// @param[in]  text
    ///     Text to appear on the button.
    /// @param[in]  clickCallback
    ///     Function called when the user clicks the button.
    /// @param[in]  privateData
    ///     Data passed back untouched into the callback.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Pointer the new button.
    static ApiTextButtonProxy create(
            const char *                              text,
            GRPCButtonClickedCallbackT               clickCallback,
            void *                                    privateData
            );

    /// Destroys the component created with create(..).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroy(            );

    /// Updates the text on the button.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setText(
            const char *                              text
            );

    /// Returns the text on the button.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string text(            ) const;

private:
    static GRPCSettings & getGRPCSettings();
};
