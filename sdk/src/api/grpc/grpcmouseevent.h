// Copyright (C) 2025 OTOY NZ Ltd.

//#include "/apimouselistener.h"

namespace OctaneGRPC
{
    class ApiGuiComponentProxy;
}

namespace OctaneGRPC
{
    struct GRPCApiMouseEventData
    {
        /// The X position of the mouse, relative to the component that is passed-in
        float           mPositionX;
        /// The Y position of the mouse, relative to the component that is passed-in
        float           mPositionY;
        /// The component that the mouse event applies to
        ApiGuiComponentProxy* mEventComponent = nullptr;
        /// The component that originally received the event
        ApiGuiComponentProxy* mOriginator = nullptr;
        /// The X and Y positions of the corresponding mouse-down event(relative to the component that is passed-in).
        /// If there isn't a corresponding mouse-down (e.g. for a mouse-move), this will just be
        /// the same as the current mouse-x position.
        float           mMouseDownPosX;
        float           mMouseDownPosY;
        /// Number of clicks made by the user
        int             mNumberOfClicks;
    };
} //namespace OctaneGRPC
