// Copyright (C) 2025 OTOY NZ Ltd.

//myself
#include "octanegrpcwrapworkpanemodule.h"

using namespace OctaneWrap;


WorkPaneModule::WorkPaneModule()
{}


WorkPaneModule::~WorkPaneModule()
{}


void WorkPaneModule::cleanupCallback(
    void *const userData)
{
    delete static_cast<WorkPaneModule*>(userData);
}