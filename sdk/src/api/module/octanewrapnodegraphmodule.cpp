// Copyright (C) 2026 OTOY NZ Ltd.

//myself
#include "octanewrapnodegraphmodule.h"


using namespace Octane;
using namespace OctaneWrap;



NodeGraphModule::NodeGraphModule()
:
    mGraph(NULL)
{}


NodeGraphModule::~NodeGraphModule()
{}


void NodeGraphModule::onTrigger()
{}


Octane::ApiModuleNodeGraph* NodeGraphModule::graph() const
{
    return mGraph;
}


void NodeGraphModule::destroyCallback(
    void *const userData)
{
    delete static_cast<NodeGraphModule*>(userData);
}


void NodeGraphModule::onEvaluateCallback(
    void *const userData)
{
    static_cast<NodeGraphModule*>(userData)->onEvaluate();
}


void NodeGraphModule::onTriggerCallback(
    void *const userData)
{
    static_cast<NodeGraphModule*>(userData)->onTrigger();
}
