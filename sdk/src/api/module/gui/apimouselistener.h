// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _API_GUI_MOUSE_LISTENER_H_
#define _API_GUI_MOUSE_LISTENER_H_   1

#include "octanetypes.h"

namespace Octane
{

class ApiGuiComponent;

enum ApiMouseEventType
{
    API_MOUSE_EVENT_TYPE_MOUSE_MOVE         = 0,
    API_MOUSE_EVENT_TYPE_MOUSE_ENTER        = 1,
    API_MOUSE_EVENT_TYPE_MOUSE_EXIT         = 2,
    API_MOUSE_EVENT_TYPE_MOUSE_DOWN         = 3,
    API_MOUSE_EVENT_TYPE_MOUSE_DRAG         = 4,
    API_MOUSE_EVENT_TYPE_MOUSE_UP           = 5,
    API_MOUSE_EVENT_TYPE_MOUSE_DOUBLE_CLICK = 6,
    API_MOUSE_EVENT_TYPE_MOUSE_WHEEL_MOVE   = 7,
};

struct ApiMouseEvent
{
    /// The X position of the mouse, relative to the component that is passed-in
    float           mPositionX;
    /// The Y position of the mouse, relative to the component that is passed-in
    float           mPositionY;
    /// The component that the mouse event applies to
    ApiGuiComponent *mEventComponent;
    /// The component that originally received the event
    ApiGuiComponent *mOriginator;
    /// The X and Y positions of the corresponding mouse-down event(relative to the component that is passed-in).
    /// If there isn't a corresponding mouse-down (e.g. for a mouse-move), this will just be
    /// the same as the current mouse-x position.
    float           mMouseDownPosX;
    float           mMouseDownPosY;
    /// Number of clicks made by the user
    int             mNumberOfClicks;

    static ApiMouseEvent make();
};


struct ApiMouseWheelDetails
{
    /// The amount that the wheel has been moved in the X axis.
    /// If isReversed is true, then a negative deltaX means that the wheel has been
    ///     pushed physically to the left.
    /// If isReversed is false, then a negative deltaX means that the wheel has been
    ///     pushed physically to the right.
    float mDeltaX;
    /// The amount that the wheel has been moved in the Y axis.
    /// If isReversed is true, then a negative deltaY means that the wheel has been
    ///     pushed physically upwards.
    /// If isReversed is false, then a negative deltaY means that the wheel has been
    ///     pushed physically downwards.
    float mDeltaY;
    /// Indicates whether the user has reversed the direction of the wheel.
    /// See deltaX and deltaY for an explanation of the effects of this value.
    bool mIsReversed;
    /// If true, then the wheel has continuous, un-stepped motion.
    bool mIsSmooth;
    /// If true, then this event is part of the intertial momentum phase that follows
    /// the wheel being released.
    bool mIsInertial;

    static ApiMouseWheelDetails make();
};


//--------------------------------------------------------------------------------------------------
class OCTANEAPI_DECL ApiMouseListener
{
    OCTANEAPI_NO_COPY(ApiMouseListener);

public:

    /// Mouse event call back type
    /// 
    /// @param[in] type
    ///     The type of the mouse event
    /// @param[in] event
    ///     Details of the mouse event 
    /// @param[in] wheelDetails
    ///     Details of the mouse wheel 
    /// @param[in] privateData
    ///     User data
    typedef void (*MouseEventCallbackT)(
        const ApiMouseEventType    type,
        const ApiMouseEvent        &event,
        const ApiMouseWheelDetails &wheelDetails,
        void                       *privateData);

    static ApiMouseListener* create(
        MouseEventCallbackT mouseEventsCallback,
        void                *privateData);

    /// Destroys the listener created with create(..).
    void destroy();
};

} // namespace Octane


#endif // #ifndef _API_GUI_MOUSE_LISTENER_H_
