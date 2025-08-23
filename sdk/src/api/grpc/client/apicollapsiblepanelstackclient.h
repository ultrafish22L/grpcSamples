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
namespace OctaneGRPC
{
    class ApiGuiComponentProxy;
}
#include "apiguicomponentclient.h"


#include "apicollapsiblepanelstack.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiCollapsiblePanelStack
class ApiCollapsiblePanelStackProxy : public ApiGuiComponentProxy
{
public:
    /// Creates a new collapsible panel stack that should be destroyed with destroy().
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static ApiCollapsiblePanelStackProxy create();

    /// Destroys the panel stack created with create().
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroy();

    /// Adds a new panel to the panel stack. The panel is inserted at the bottom of the stack.
    /// The panel has variable height (scrollable) but will be as wide as the child component that
    /// is embedded.
    ///
    /// @param[in]  caption
    ///     Caption that appears on the top of the panel.
    /// @param[in]  component
    ///     Component filling the panel. This component is not owned and should be valid as long
    ///     as it's part of the panel stack.
    /// @param[in]  open
    ///     TRUE to create the panel in the open state.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void addPanel(
            const char *                              caption,
            ApiGuiComponentProxy &                    component,
            const bool                                open
            );

    /// Opens up a panel in the stack.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setOpen(
            const int                                 index,
            const bool                                open
            );

    /// Clears the panels on this component.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void clear();

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
