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


#include "apilabel.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiLabel
class ApiLabelProxy : public ApiGuiComponentProxy
{
public:
    /// Creates a new label.
    ///
    /// @param[in]  text
    ///     Text to display on the label.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static ApiLabelProxy create(
            const char *   text
            );

    /// Destroys this label created by create(..).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroy();

    /// Returns the text on the label.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string text() const;

    /// Changes the label text.
    ///
    /// @param[in]  newText
    ///     New text to set in the label.
    /// @param[in]  sendEvent
    ///     TRUE to notify the label listeners.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setText(
            const char *                              newText,
            const bool                                sendEvent
            );

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
