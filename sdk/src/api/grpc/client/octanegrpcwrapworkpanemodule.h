// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_WORK_PANE_MODULE_H_
#define _OCTANE_WRAP_WORK_PANE_MODULE_H_   1
// system
#include <functional>
//api includes
#include "apimodulenodegraph.h"
#include "apimodule.h"
#include "apiworkpanemoduleinfoclient.h"
#include "apimoduleglobalclient.h"
class ApiGridLayoutProxy;

namespace OctaneWrap
{

    //--------------------------------------------------------------------------------------------------
    /// Base class for a work pane module
    class WorkPaneModule
    {

    public:

        /// Creates info for Api work pane module and handles the registration of module. This can
        /// only be registered from within the OCTANE_MODULE_START function.
        ///
        /// @param[in]  moduleId
        ///     Unique ID for this module. should start from 1000100
        /// @param[in]  fullName
        ///     Name with categories that will appear in the user interface.
        ///     Must have at least one category to display it in the Windows menu
        ///     eg: "|Octane examples|Hello world" or |Hello world.
        ///     and "Hello world" this will not be shown in the menu, can be used for internal commands
        /// @param[in]  description
        ///     Describes what the work pane module does.
        /// @param[in]  author
        ///     Name of the author for this module.
        /// @param[in]  versionNumber
        ///     Version number of the module.
        /// @param[in]  toolbarModuleIds
        ///      modules that will be displayed in the toolbar of this module.
        /// @param[in]  toolbarModuleIdsSize
        ///      toolbarModuleIds list size.
        /// @param[in]  isStaticallyLinked
        ///     Must be set to TRUE when registering a statically linked module. This is only
        ///     supported for built-in modules.
        template<class T>
        static void registerModule(
            const Octane::ModuleIdT moduleId,
            const char              *fullName,
            const char              *description,
            const char              *author,
            const Octane::VersionT  versionNumber,
            const Octane::ModuleIdT *toolbarModuleIds,
            const size_t            toolbarModuleIdsSize,
            const bool              isStaticallyLinked = false);

        // Constructor
        WorkPaneModule();

        // Destructor
        virtual ~WorkPaneModule();

        /// Populates the grid with random components. We don't take ownership over the grid.
        virtual void onInit(
            OctaneGRPC::ApiGridLayoutProxy &parentGrid) = 0;

    private:

        // Create function is called once after the workPane is created.
        template<class T> 
        static void* initCallback(
            OctaneGRPC::ApiGridLayoutProxy * parentGrid);

        // Cleanup function is called when a work pane is being destroyed.
        static void cleanupCallback(
            void *userData);
    };


    template<class T> 
    void* WorkPaneModule::initCallback(
            OctaneGRPC::ApiGridLayoutProxy * parentGrid)
    {
        T* t = new T();
        t->onInit(*parentGrid);
        return t;
    }


    template<class T> 
    void WorkPaneModule::registerModule(
        const Octane::ModuleIdT moduleId,
        const char              *fullName,
        const char              *description,
        const char              *author,
        const Octane::VersionT  versionNumber,
        const Octane::ModuleIdT *toolbarModuleIds,
        const size_t            toolbarModuleIdsSize,
        const bool              isStaticallyLinked)
{
        OctaneGRPC::ApiWorkPaneModuleInfoProxy info = OctaneGRPC::ApiWorkPaneModuleInfoProxy::create(
            moduleId, fullName, description, author, versionNumber);

        info.setInitFunction(WorkPaneModule::initCallback<T>);
        info.setCleanupFunction(WorkPaneModule::cleanupCallback);
        info.setWorkPaneToolbarIds(toolbarModuleIds, toolbarModuleIdsSize);

        if (isStaticallyLinked)
        {
            // register as statically linked module
            OctaneGRPC::ApiModuleGlobalProxy::registerStaticWorkPaneModule(info);
        }
        else
        {
            // register as dynamically linked module
            OctaneGRPC::ApiModuleGlobalProxy::registerWorkPaneModule(info);
        }

        info.destroy();
    }



} // namespace OctaneWrap


#endif // _OCTANE_WRAP_MODULE_GRAPH_H_
