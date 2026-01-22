// Copyright (C) 2026 OTOY NZ Ltd.

// myself
#include "octanegrpcwrapguicomponent.h"
// system includes
#include <algorithm>
// application includes
#include "apiguicomponent.h"
#include "octanegrpcwrapmouselistener.h"


using namespace OctaneWrap;


GuiComponent::GuiComponent()
//:
//    mComponent(NULL)
{
    mApiMouseListener = OctaneGRPC::ApiMouseListenerProxy::create(
        &GuiComponent::mouseEventsCallback,
        this
        );
}


GuiComponent::~GuiComponent()
{
    if (!mApiMouseListener.isNull())
    {
        mApiMouseListener.destroy();
    }
}


void GuiComponent::addChildComponent(
    GuiComponent & child)
{
    mComponent->addChildComponent(*child.mComponent);
}


void GuiComponent::removeChildComponent(
    GuiComponent &child)
{
    mComponent->removeChildComponent(*child.mComponent);
}


void GuiComponent::setSize(
    const int width,
    const int height)
{
    mComponent->setSize(width, height);
}


int GuiComponent::width() const
{
    return mComponent->width();
}


int GuiComponent::height() const
{
    return mComponent->height();
}


void GuiComponent::setTopLeftPosition(
    const int x,
    const int y)
{
    mComponent->setTopLeftPosition(x, y);
}


int GuiComponent::xPosition() const
{
    return mComponent->xPosition();
}


int GuiComponent::yPosition() const
{
    return mComponent->yPosition();
}


void GuiComponent::setEnabled(
    const bool enabled)
{
    mComponent->setEnabled(enabled);
}


bool GuiComponent::isEnabled() const
{
    return mComponent->isEnabled();
}


OctaneGRPC::ApiGuiComponentProxy * GuiComponent::wrappedComponent()
{
    return mComponent;
}


const OctaneGRPC::ApiGuiComponentProxy * GuiComponent::wrappedComponent() const
{
    return mComponent;
}


void GuiComponent::setTooltip(
    const std::string &tooltip)
{
    mComponent->setTooltip(tooltip.c_str());
}


std::string GuiComponent::tooltip() const
{
    return std::string(mComponent->tooltip());
}


void GuiComponent::addMouseListener (
    MouseListener *newListener)
{
    if (mMouseListeners.size() ==  0)
    {
        mComponent->addMouseListener(&mApiMouseListener, false);
    }
    mMouseListeners.push_back(newListener);
}


void GuiComponent::removeMouseListener (
    MouseListener *listenerToRemove)
{
    mMouseListeners.erase(std::find(mMouseListeners.begin(), mMouseListeners.end(), listenerToRemove));
    if (mMouseListeners.size() ==  0)
    {
        mComponent->removeMouseListener(&mApiMouseListener);
    }
}


void GuiComponent::mouseEventsCallback(
    const Octane::ApiMouseEventType           type,
    const OctaneGRPC::GRPCApiMouseEventData   &event,
    const Octane::ApiMouseWheelDetails        &wheelDetails,
    void                                      *privateData)
{
    GuiComponent * myGuiComponent = static_cast<GuiComponent*>(privateData);
    for (size_t i = 0; i< myGuiComponent->mMouseListeners.size(); i++)
    {
        switch (type)
        {
            case Octane::API_MOUSE_EVENT_TYPE_MOUSE_MOVE:
                myGuiComponent->mMouseListeners[i]->mouseMove(event);
                break;
            case Octane::API_MOUSE_EVENT_TYPE_MOUSE_ENTER:
                myGuiComponent->mMouseListeners[i]->mouseEnter(event);
                break;
            case Octane::API_MOUSE_EVENT_TYPE_MOUSE_EXIT:
                myGuiComponent->mMouseListeners[i]->mouseExit(event);
                break;
            case Octane::API_MOUSE_EVENT_TYPE_MOUSE_DOWN:
                myGuiComponent->mMouseListeners[i]->mouseDown(event);
                break;
            case Octane::API_MOUSE_EVENT_TYPE_MOUSE_DRAG:
                myGuiComponent->mMouseListeners[i]->mouseDrag(event);
                break;
            case Octane::API_MOUSE_EVENT_TYPE_MOUSE_UP:
                myGuiComponent->mMouseListeners[i]->mouseUp(event);
                break;
            case Octane::API_MOUSE_EVENT_TYPE_MOUSE_DOUBLE_CLICK:
                myGuiComponent->mMouseListeners[i]->mouseDoubleClick(event);
                break;
            case Octane::API_MOUSE_EVENT_TYPE_MOUSE_WHEEL_MOVE:
                myGuiComponent->mMouseListeners[i]->mouseWheelMove(event, wheelDetails);
                break;
        }
    }
}