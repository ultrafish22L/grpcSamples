// Copyright (C) 2026 OTOY NZ Ltd.

// myself
#include "octanegrpcwrapwindow.h"
// system includes
#include <algorithm>
// application includes
#include "apiwindow.h"


using namespace OctaneWrap;

//--------------------------------------------------------------------------------------------------
// Implementation of Window

Window::Window(
    const std::string &title)
//:
//    mApiWindow(NULL)
{
    mApiWindow = OctaneGRPC::ApiWindowProxy::create(title.c_str(), windowCloseCallback, this);
    mComponent = &mApiWindow;
}


Window::~Window()
{
    mApiWindow.destroy();
}


void Window::addContentComponent(
    GuiComponent &contentComponent)
{
    mApiWindow.addContentComponent(*contentComponent.wrappedComponent());
}


void Window::show()
{
    mApiWindow.show();
}


void Window::hide()
{
    mApiWindow.hide();
}


void * Window::nativeHandle()
{
    return mApiWindow.nativeHandle();
}


void Window::addListener(
    WindowListener &listener)
{
    mListeners.push_back(&listener);
}


void Window::removeListener(
    WindowListener &listener)
{
    mListeners.erase(std::find(mListeners.begin(), mListeners.end(), &listener));
}


void Window::windowCloseCallback(
    OctaneGRPC::ApiWindowProxy & window,
    void *                       privateData)
{
    Window *myWindow = static_cast<Window*>(privateData);

    // notify the listeners
    for (size_t i=0; i<myWindow->mListeners.size(); ++i)
    {
        myWindow->mListeners[i]->onWindowClose(*myWindow);
    }
}
