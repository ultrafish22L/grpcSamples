// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_NODE_GRAPH_MODULE_H_
#define _OCTANE_WRAP_NODE_GRAPH_MODULE_H_   1

// system
#include <functional>
// application includes
#include "apimodulenodegraph.h"
#include "apimodule.h"
#include "octanegrpcwraputil.h"
#include "apimodulenodegraphclient.h"
#include "apimoduleglobalclient.h"
#include "apinodegraphmoduleinfoclient.h"
namespace OctaneWrap
{

    //--------------------------------------------------------------------------------------------------
    /// Base class for a node graph module
    class NodeGraphModule
    {
    public:

        /// Registers a node graph module implementation in the module registry.
        ///
        /// @tparam  ModuleT
        ///     The type of the module class which needs to be derived from NodeGraphModule. It
        ///     needs to provide a default constructor and implement onInit() and onEvaluate().
        ///
        /// @param[in]  moduleId
        ///     Unique ID for this module. should start from 1000100
        /// @param[in]  fullName
        ///     Name with categories that will appear in the user interface.
        ///     Must have at least one category to display it in the Windows menu
        ///     eg: "|Octane examples|Hello world" or |Hello world.
        ///     and "Hello world" this will not be shown in the menu, can be used for internal commands
        /// @param[in]  description
        ///     Describes what the module node graph does.
        /// @param[in]  author
        ///     Name of the author for this module.
        /// @param[in]  versionNumber
        ///     Version number of the module.
        /// @param[in]  enableTrigger
        ///     If set to TRUE, a trigger button will be provided in the node inspector and
        ///     onTrigger() will be called if a user clicks on it.
        /// @param[in]  outType
        ///     The output type of the node graph.
        template <class ModuleT> 
        static void registerModule(
            const Octane::ModuleIdT   moduleId,
            const char *const         fullName,
            const char *const         description,
            const char *const         author,
            const Octane::VersionT    versionNumber,
            const bool                enableTrigger, 
            const Octane::NodePinType outType = Octane::NodePinType::PT_UNKNOWN);

        /// Default constructor. graph() will return NULL during construction.
        NodeGraphModule();

        /// Destructor
        virtual ~NodeGraphModule();


        //--- To be implemented by child classes ---

        /// Will be called after mGraph has been initialized. This is the moment when you can
        /// initialize the node graph, its inputs, etc.
        virtual void onInit() = 0;

        /// Function will be called when a module graph created and when there is any changes in the 
        /// input values.
        virtual void onEvaluate() = 0;

        /// Will be called when the trigger button is enabled (see registerModule()) and the user
        /// clicks on it. The base implementation does nothing.
        virtual void onTrigger();


    protected:

        /// Returns NULL during construction and the actual node graph object which is controlled by this module
        /// instance after construction has finished .
        OctaneGRPC::ApiModuleNodeGraphProxy* graph() const;
        

    private:

        OctaneGRPC::ApiModuleNodeGraphProxy * mGraph = nullptr;


        /// Helper that wraps the creation of the module by implementing the creation callback.
        template<class ModuleT>
        static void* createCallback(
            OctaneGRPC::ApiModuleNodeGraphProxy *const graph);

        /// Helper that wraps the destruction of the module by implementing the destroy callback.
        static void destroyCallback(
            void *const userData);

        /// Helper that wraps the evaluation of the module by implementing the evaluation callback.
        static void onEvaluateCallback(
            void *const userData);

        /// Helper that wraps the onTrigger callback of the module.
        static void onTriggerCallback(
            void *const userData);
    };


    template <class ModuleT>
    void * NodeGraphModule::createCallback(
        OctaneGRPC::ApiModuleNodeGraphProxy * const graph)
    {
        // safety check
        if (!graph)
        {
            OCTANE_API_ASSERT(graph != nullptr,
                              "no ApiModuleNodeGraph provided in create callback -> bailing out");
            return nullptr;
        }

        // create a new instance of the module and initialise it
        ModuleT *const module = new ModuleT;
        module->mGraph = graph;
        module->onInit();

        // return the created instance
        return module;
    }


    template<class ModuleT>
    void NodeGraphModule::registerModule(
        const Octane::ModuleIdT   moduleId,
        const char *const         fullName,
        const char *const         description,
        const char *const         author,
        const Octane::VersionT    versionNumber,
        const bool                enableTrigger, 
        const Octane::NodePinType outType)
    {
        // create and set up new module info
        OctaneGRPC::ApiNodeGraphModuleInfoProxy info = OctaneGRPC::ApiNodeGraphModuleInfoProxy::create(
            moduleId,
            fullName,
            description,
            author,
            versionNumber
            );
      //  Octane::ApiModuleNodeGraph
        info.setOutType(outType);
        info.setCreateFunction(&NodeGraphModule::createCallback<ModuleT>);
        info.setDestroyFunction(&NodeGraphModule::destroyCallback);
        info.setOnEvaluateFunction(&NodeGraphModule::onEvaluateCallback);
        if (enableTrigger)
        {
            info.setOnTriggerFunction(&NodeGraphModule::onTriggerCallback);
        }

        // register as dynamically linked module
        OctaneGRPC::ApiModuleGlobalProxy::registerNodeGraphModule(info);

        // destroy module info
        info.destroy();
    }


} // namespace OctaneWrap


#endif // _OCTANE_WRAP_MODULE_GRAPH_H_
