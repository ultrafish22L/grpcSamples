// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _APPLICATION_H_
#define _APPLICATION_H_ 1

// API includes
#include "octanegrpcwrappers.h"


class AppWindow;
class TexNodeModel;



//--------------------------------------------------------------------------------------------------
/// Contains all the application logic for the TexCommander.
class Application : public OctaneWrap::WindowListener
{
public:

    /// Creates a new application object.
    Application();

    /// Destructs the application.
    virtual ~Application();

    /// Launches the application window but only if it did not exist yet.
    void launchWindow();

    //-- Implementation of WindowListener --

    virtual void onWindowClose(
        OctaneWrap::Window &window) override;

private:

    /// Application main window.
    AppWindow    *mWindow;
    /// Model that tracks the texture nodes in the project.
    TexNodeModel *mTexNodeModel;
};



#endif // #ifndef _APPLICATION_H_
