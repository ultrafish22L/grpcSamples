// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _API_COLLAPSIBLE_PANEL_STACK_H_
#define _API_COLLAPSIBLE_PANEL_STACK_H_ 1

#include "apiguicomponent.h"
#include "octanetypes.h"

namespace Octane
{

//--------------------------------------------------------------------------------------------------
/// A panel which holds a vertical stack of components which can be expanded and contracted. Each
/// panel in the stack is a component.
class OCTANEAPI_DECL ApiCollapsiblePanelStack : public ApiGuiComponent
{
    OCTANEAPI_NO_COPY(ApiCollapsiblePanelStack);

public:    

    /// Creates a new collapsible panel stack that should be destroyed with destroy().
    static ApiCollapsiblePanelStack* create();

    /// Destroys the panel stack created with create().
    void destroy();

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
        const char      *caption,
        ApiGuiComponent &component,
        const bool      open  = true);

    /// Opens up a panel in the stack.
    void setOpen(
        const int  index,
        const bool open);

    /// Clears the panels on this component.
    void clear();

private:

    ApiCollapsiblePanelStack();
};

} // namespace Octane


#endif // #ifndef _API_COLLAPSIBLE_PANEL_STACK_H_
