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
namespace OctaneGRPC
{
    class ApiNodeGraphProxy;
}
#include "apiguicomponentclient.h"


#include "apinodegrapheditor.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiNodeGraphEditor
class ApiNodeGraphEditorProxy : public ApiGuiComponentProxy
{
public:
    static ApiNodeGraphEditorProxy create(
            const ApiNodeGraphProxy *                 content,
            const bool                                unfold,
            void *                                    privateData
            );

    void destroy();

    /// Sets the node graph of this ApiNodeGraphEditor. All other tabs will be closed, and this node
    /// graph will be opened in a tab that cannot be closed.
    ///
    /// @param[in]  graph
    ///     Pointer to the node graph. Must not be NULL and must have the current version.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setContentGraph(
            const ApiNodeGraphProxy *const   graph
            );

    /// Opens another node graph in a different tab, and makes it visible. If the node graph is
    /// already open in the editor, then it will switch to its corresponding tab.
    ///
    /// @param[in]  graph
    ///     Pointer to the node graph. Must not be NULL and must have the current version.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void addGraph(
            const ApiNodeGraphProxy *const   graph
            );

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
