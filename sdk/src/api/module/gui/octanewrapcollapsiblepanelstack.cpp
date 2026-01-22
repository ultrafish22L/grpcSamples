// Copyright (C) 2026 OTOY NZ Ltd.

// api includes
#include "apicollapsiblepanelstack.h"
// myself
#include "octanewrapcollapsiblepanelstack.h"

using namespace OctaneWrap;

CollapsiblePanelStack::CollapsiblePanelStack()
:
    mApiPanelStack(NULL)
{
    mApiPanelStack = Octane::ApiCollapsiblePanelStack::create();
    mComponent     = mApiPanelStack;
}


CollapsiblePanelStack::~CollapsiblePanelStack()
{
    mApiPanelStack->destroy();
}


void CollapsiblePanelStack::addPanel(
    const std::string &caption,
    GuiComponent      &component,
    const bool        open)
{
    mApiPanelStack->addPanel(caption.c_str(), *component.wrappedComponent(), open);
}


void CollapsiblePanelStack::setOpen(
    const int  index,
    const bool open)
{
    mApiPanelStack->setOpen(index, open);
}


void CollapsiblePanelStack::clear()
{
    mApiPanelStack->clear();
}
