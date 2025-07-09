// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

// library includes
#include "apiguicomponent.h"
#include "apinodesystem.h"


namespace Octane
{

//--------------------------------------------------------------------------------------------------
/// Graph editor that can be used from the API
class OCTANEAPI_DECL ApiNodeGraphEditor : public ApiGuiComponent
{
public:

    static ApiNodeGraphEditor * create(
        const Octane::ApiNodeGraph *content,
        const bool                 unfold,
        void                       *privateData);

    void destroy();

    /// Sets the node graph of this ApiNodeGraphEditor. All other tabs will be closed, and this node
    /// graph will be opened in a tab that cannot be closed.
    /// 
    /// @param[in]  graph
    ///     Pointer to the node graph. Must not be NULL and must have the current version.
    void setContentGraph(
        const Octane::ApiNodeGraph *const graph);

    /// Opens another node graph in a different tab, and makes it visible. If the node graph is
    /// already open in the editor, then it will switch to its corresponding tab.
    /// 
    /// @param[in]  graph
    ///     Pointer to the node graph. Must not be NULL and must have the current version.
    void addGraph(
        const Octane::ApiNodeGraph *const graph);

private:

    /// Creates a nodegraph view component
    ApiNodeGraphEditor();
};

}
