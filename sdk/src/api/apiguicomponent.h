// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _API_GUI_COMPONENT_H_
#define _API_GUI_COMPONENT_H_   1

#include "octanetypes.h"

namespace Octane
{

class ApiMouseListener;


//--------------------------------------------------------------------------------------------------
/// Base class for gui components.
class OCTANEAPI_DECL ApiGuiComponent
{
    OCTANEAPI_NO_COPY(ApiGuiComponent);

public:

    /// Adds a component as a child component.
    void addChildComponent(
        ApiGuiComponent &child);

    /// Removes the passed in component as child component.
    void removeChildComponent(
        ApiGuiComponent &child);

    /// Sets the size of this component in pixel.
    void setSize(
        const int width,
        const int height);

    /// Returns the width of this component in pixels.
    int width() const;

    /// Returns the height of this component in pixels.
    int height() const;

    /// Sets the position of the top-left corner relative to the bounds of the parent component.
    void setTopLeftPosition(
        const int x,
        const int y);

    /// Returns the x-position of this component.
    int xPosition() const;

    /// Returns the y-position of this component.
    int yPosition() const;

    /// Enables/disables this component.
    void setEnabled(
        const bool enabled);

    /// Checks if this component is enabled/disabled.
    bool isEnabled() const;

    /// Sets the tooltip for this component. Not all components support tooltips and for them,
    /// this function is a no-operation. The ones that support tooltips are: buttons, combo boxes,
    /// progress bar, text editor and numeric box.
    void setTooltip(
        const char *tooltip);

    /// Returns the tooltip. When the component doesn't support a tooltip, an empty string is
    /// returned.
    const char* tooltip() const;

    /// Add a mouse listener to this component
    void addMouseListener (
        ApiMouseListener *newListener,
        bool             wantsEventsForAllNestedChildComponents = false);

    /// Remove a mouse listener from this component
    void removeMouseListener (
        ApiMouseListener *listenerToRemove);

protected:

    ApiGuiComponent();
};

} // namespace Octane


#endif // #ifndef _API_GUI_COMPONENT_H_
