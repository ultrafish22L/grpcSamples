// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef __APIPROJECTWORKSPACE_H__
#define __APIPROJECTWORKSPACE_H__

// library includes
#include "apiarray.h"
#include "apiguicomponent.h"


namespace Octane
{

class ApiSceneOutliner;
class ApiNodeGraphEditor;
class ApiNodeInspector;
class ApiNodeGraph;

//--------------------------------------------------------------------------------------------------
/// Project workspace that can be used for docking the various workpane components. It is
/// deliberately not allowed to be created explicitly, it must be obtained from a ApiMainWindow.
class OCTANEAPI_DECL ApiProjectWorkspace : public ApiGuiComponent
{

public:

    // -- override of ApiGuiComponent --
    
    /// Gets all the node graph editors in the project workspace. The ApiArray will remain valid
    /// until this function is called again (on any instance), or until the ProjectWorkspace is
    /// destroyed, or until node graph editors are added/destroyed.
    ApiArray<ApiNodeGraphEditor*> getNodeGraphEditors();
    
    /// Resets the workspace to the default layout for plugins. References to any of the components
    /// in the layout may be changed after using this function.
    void resetLayout();

    /// Loads the layout given. 
    ///
    /// @returns 
    ///     TRUE if the layout was successfully loaded.
    bool loadLayout(
        const char *layoutString);

    /// Serializes the current layout. The pointer returned is owned by Octane and will change when
    /// the function is called again (on any instance).
    ///
    /// @returns
    ///     The layout (OCL) serialized from the current layout.
    const char * serializeLayout() const;

private:

    ApiProjectWorkspace();
};

}


#endif // #ifndef __APIPROJECTWORKSPACE_H__
