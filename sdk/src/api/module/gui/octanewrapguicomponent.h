// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _GUI_COMPONENT_H_
#define _GUI_COMPONENT_H_   1

// system includes
#include <string>
#include <vector>
// api includes
#include "octanetypes.h"
#include "apimouselistener.h"


namespace Octane
{
    class ApiGuiComponent;
}

namespace OctaneWrap
{

class MouseListener;


//--------------------------------------------------------------------------------------------------
/// Base class wrapper for gui components.
class GuiComponent
{
    OCTANEAPI_NO_COPY(GuiComponent);

public:

    GuiComponent();

    virtual ~GuiComponent();

    /// Adds a component as a child component.
    void addChildComponent(
        GuiComponent &child);

    /// Removes the passed in component as child component.
    void removeChildComponent(
        GuiComponent &child);

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

    /// Returns the component that this class wraps.
    Octane::ApiGuiComponent* wrappedComponent();

    /// Returns the component that this class wraps (const-version).
    const Octane::ApiGuiComponent* wrappedComponent() const;

    /// Sets the tooltip for this component. Not all components support tooltips and for them,
    /// this function is a no-operation. The ones that support tooltips are: buttons, combo boxes,
    /// progress bar, text editor and numeric box.
    void setTooltip(
        const std::string &tooltip);

    /// Returns the tooltip. When the component doesn't support a tooltip, an empty string is
    /// returned.
    std::string tooltip() const;

    /// Add a mouse listener to this component
    void addMouseListener (
        MouseListener *newListener);

    /// Remove a mouse listener from this component
    void removeMouseListener (
        MouseListener *listenerToRemove);

protected:

    /// wrapped component
    Octane::ApiGuiComponent     *mComponent;
    /// wrapped mouse listener
    Octane::ApiMouseListener*   mApiMouseListener;
    /// mouse listeners for this component
    std::vector<MouseListener*> mMouseListeners;

    /// internal mouse events callback
    static void mouseEventsCallback(
        const Octane::ApiMouseEventType    type,
        const Octane::ApiMouseEvent        &event,
        const Octane::ApiMouseWheelDetails &wheel,
        void                               *privateData);
};

} // namespace Octane


#endif // #ifndef _GUI_COMPONENT_H_
