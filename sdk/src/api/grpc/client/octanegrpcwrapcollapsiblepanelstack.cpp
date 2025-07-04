// Copyright (C) 2025 OTOY NZ Ltd.

// api includes
#include "apicollapsiblepanelstack.h"
// myself
#include "octanegrpcwrapcollapsiblepanelstack.h"

using namespace OctaneWrap;

CollapsiblePanelStack::CollapsiblePanelStack()
//:
  //  mApiPanelStack(NULL)
{
    mApiPanelStack = ApiCollapsiblePanelStackProxy::create();
    mComponent     = &mApiPanelStack;
}


CollapsiblePanelStack::~CollapsiblePanelStack()
{
    mApiPanelStack.destroy();
}


void CollapsiblePanelStack::addPanel(
    const std::string &caption,
    GuiComponent      &component,
    const bool        open)
{
    mApiPanelStack.addPanel(caption.c_str(), *component.wrappedComponent(), open);
}


void CollapsiblePanelStack::setOpen(
    const int  index,
    const bool open)
{
    mApiPanelStack.setOpen(index, open);
}


void CollapsiblePanelStack::clear()
{
    mApiPanelStack.clear();
}
