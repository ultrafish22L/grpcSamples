// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_COLLAPSIBLE_PANEL_STACK_H_
#define _OCTANE_WRAP_COLLAPSIBLE_PANEL_STACK_H_ 1

// system includes
#include <string>
#include <vector>
// api includes
#include "octanetypes.h"
#include "octanegrpcwrapguicomponent.h"
#include "apicollapsiblepanelstackclient.h"

namespace Octane
{
class ApiCollapsiblePanelStack;
}

namespace OctaneWrap
{

//--------------------------------------------------------------------------------------------------
/// Wraps ApiCollapsiblePanelStack.
class CollapsiblePanelStack : public GuiComponent
{
    OCTANEAPI_NO_COPY(CollapsiblePanelStack);

public:

    /// Creates a new collapsible panel stack.
    CollapsiblePanelStack();

    /// Destructor.
    virtual ~CollapsiblePanelStack();

    /// Adds a new panel to the panel stack. The panel is inserted at the bottom of the stack.
    /// The panel has variable height (scrollable) but will be as wide as the child component that
    /// is embedded.
    /// 
    /// @param[in]  caption
    ///     Caption that appears on the top of the panel.
    /// @param[in]  component
    ///     Component filling the panel. This component is not owned and should be valid as long
    ///     as it's part of the panel stack.
    /// @param[in]  open
    ///     TRUE to create the panel in the open state.
    void addPanel(
        const std::string &caption,
        GuiComponent      &component,
        const bool        open  = true);

    /// Opens up a panel in the stack.
    void setOpen(
        const int  index,
        const bool open);

    /// Clears the panels on this component.
    void clear();

private:

    /// the wrapped api panel stack
    OctaneGRPC::ApiCollapsiblePanelStackProxy mApiPanelStack;
};

};



#endif // #ifndef _OCTANE_WRAP_COLLAPSIBLE_PANEL_STACK_H_
