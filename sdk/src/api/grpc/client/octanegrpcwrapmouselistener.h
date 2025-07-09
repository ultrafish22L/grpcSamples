// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_MOUSE_LISTENER_H_
#define _OCTANE_WRAP_MOUSE_LISTENER_H_ 1

#include "apimouselistener.h"

struct GRPCApiMouseEventData;

namespace OctaneWrap
{

class MouseListener
{

public:

    MouseListener();

    virtual ~MouseListener();

    /// Called when the mouse moves inside a component.
    ///
    /// If the mouse button isn't pressed and the mouse moves over a component,
    /// this will be called to let the component react to this.
    ///
    /// A component will always get a mouseEnter callback before a mouseMove.
    ///
    /// @param[in]
    ///     event details about the position and status of the mouse event, including
    ///     the source component in which it occurred
    virtual void mouseMove(
        const GRPCApiMouseEventData &event);

    /// Called when the mouse first enters a component.
    ///
    /// If the mouse button isn't pressed and the mouse moves into a component,
    /// this will be called to let the component react to this.
    ///
    /// When the mouse button is pressed and held down while being moved in
    /// or out of a component, no mouseEnter or mouseExit callbacks are made - only
    /// mouseDrag messages are sent to the component that the mouse was originally
    /// clicked on, until the button is released.
    ///
    /// @param[in]
    ///     event details about the position and status of the mouse event, including
    ///     the source component in which it occurred
    virtual void mouseEnter(
        const GRPCApiMouseEventData &event);

    /// Called when the mouse moves out of a component.
    ///
    /// This will be called when the mouse moves off the edge of this
    /// component.
    ///
    /// If the mouse button was pressed, and it was then dragged off the
    /// edge of the component and released, then this callback will happen
    /// when the button is released, after the mouseUp callback.
    ///
    /// @param[in]
    ///     event details about the position and status of the mouse event, including
    ///     the source component in which it occurred
    virtual void mouseExit(
        const GRPCApiMouseEventData &event);

    /// Called when a mouse button is pressed.
    ///
    /// The MouseEvent object passed in contains lots of methods for finding out
    /// which button was pressed, as well as which modifier keys (e.g. shift, ctrl)
    /// were held down at the time.
    ///
    /// Once a button is held down, the mouseDrag method will be called when the
    /// mouse moves, until the button is released.
    ///
    /// @param[in]
    ///     event details about the position and status of the mouse event, including
    ///     the source component in which it occurred
    virtual void mouseDown(
        const GRPCApiMouseEventData &event);

    /// Called when the mouse is moved while a button is held down.
    ///
    /// When a mouse button is pressed inside a component, that component
    /// receives mouseDrag callbacks each time the mouse moves, even if the
    /// mouse strays outside the component's bounds.
    ///
    /// @param[in]
    ///     event details about the position and status of the mouse event, including
    ///     the source component in which it occurred
    virtual void mouseDrag(
        const GRPCApiMouseEventData &event);

    /// Called when a mouse button is released.
    ///
    /// A mouseUp callback is sent to the component in which a button was pressed
    /// even if the mouse is actually over a different component when the
    /// button is released.
    ///
    /// The MouseEvent object passed in contains lots of methods for finding out
    /// which buttons were down just before they were released.
    ///
    /// @param[in]
    ///     event details about the position and status of the mouse event, including
    ///     the source component in which it occurred
    virtual void mouseUp(
        const GRPCApiMouseEventData &event);

    /// Called when a mouse button has been double-clicked on a component.
    ///
    /// The MouseEvent object passed in contains lots of methods for finding out
    /// which button was pressed, as well as which modifier keys (e.g. shift, ctrl)
    /// were held down at the time.
    ///
    /// @param[in]
    ///     event details about the position and status of the mouse event, including
    ///     the source component in which it occurred
    virtual void mouseDoubleClick(
        const GRPCApiMouseEventData &event);

    /// Called when the mouse-wheel is moved.
    ///
    /// This callback is sent to the component that the mouse is over when the
    /// wheel is moved.
    ///
    /// If not overridden, a component will forward this message to its parent, so
    /// that parent components can collect mouse-wheel messages that happen to
    /// child components which aren't interested in them.
    ///
    /// @param[in] event
    ///     event details about the position and status of the mouse event, including
    ///     the source component in which it occurred
    /// @param[in] wheel   
    ///     details about the wheel movement
    virtual void mouseWheelMove(
        const GRPCApiMouseEventData        &event,
        const Octane::ApiMouseWheelDetails &wheelDetails);

};

} // namespace OctaneWrap


#endif // #ifndef _OCTANE_WRAP_MOUSE_LISTENER_H_
