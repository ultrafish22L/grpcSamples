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
class ApiNodeGraphEditorProxy;
#include "apiguicomponentclient.h"


#include "apiprojectworkspace.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiProjectWorkspace
class ApiProjectWorkspaceProxy : public ApiGuiComponentProxy
{
public:
    /// Gets all the node graph editors in the project workspace. The ApiArray will remain valid
    /// until this function is called again (on any instance), or until the ProjectWorkspace is
    /// destroyed, or until node graph editors are added/destroyed.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::vector<ApiNodeGraphEditorProxy> getNodeGraphEditors(            );

    /// Resets the workspace to the default layout for plugins. References to any of the components
    /// in the layout may be changed after using this function.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void resetLayout(            );

    /// Loads the layout given. 
    ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @returns 
    ///     TRUE if the layout was successfully loaded.
    bool loadLayout(
            const char *                              layoutString
            );

    /// Serializes the current layout. The pointer returned is owned by Octane and will change when
    /// the function is called again (on any instance).
    ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @returns
    ///     The layout (OCL) serialized from the current layout.
    std::string serializeLayout(            ) const;

private:
    static GRPCSettings & getGRPCSettings();
};
