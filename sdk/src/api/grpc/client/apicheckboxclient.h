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


#include "apicheckbox.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiCheckBox
class ApiCheckBoxProxy : public ApiGuiComponentProxy
{
public:
    /// Creates a new checkbox. Returns a NULL pointer when creation failed.
    ///
    /// @param[in]  text
    ///     Text to display alongside the check box. Can be a NULL pointer.
    /// @param[in]  checkCallback
    ///     Callback, called when the checkbox is checked/unchecked. Can be a NULL pointer.
    /// @param[in]  privateData
    ///     Private data, passed back with the callback.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Pointer to the check box. Don't call delete on this pointer but call destroy().
    static ApiCheckBoxProxy create(
            const char *                              text,
            GRPCCheckedCallbackT                     callback,
            void *                                    privateData
            );

    /// Destroys the component created with create(..).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroy();

    /// Sets the button checked.
    ///
    /// @param[in]  checked
    ///     TRUE for checked, FALSE for unchecked.
    /// @param[in]  sendEvent
    ///     TRUE to trigger an event callback.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setChecked(
            const bool                                checked,
            const bool                                sendEvent
            );

    /// Checks if the checkbox is checked (ticked).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isChecked() const;

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
