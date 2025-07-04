// Copyright (C) 2025 OTOY NZ Ltd.

// application includes
#include "appwindow.h"
#include "texnodemodel.h"
// myself
#include "application.h"


Application::Application()
:
    mWindow(NULL),
    mTexNodeModel(new TexNodeModel)
{}


Application::~Application()
{
    delete mTexNodeModel;
    delete mWindow;
}


void Application::launchWindow()
{
    if (!mWindow)
    {
        mWindow = new AppWindow(*mTexNodeModel);
        mWindow->show();
        mWindow->addListener(*this);
    }
}


void Application::onWindowClose(
    OctaneWrap::Window &window)
{
    // destroy the window
    delete mWindow;
    mWindow = NULL;
}
