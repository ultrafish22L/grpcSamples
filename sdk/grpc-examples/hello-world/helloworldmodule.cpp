// Copyright (C) 2025 OTOY NZ Ltd.

//#include "grpcmain.h"
#include "helloworldmodule.h"
#include <thread>
#include "octanegrpcwrappers.h"
#include "octanegrpcwrapcommandmodule.h"
#include "octanegrpcwrapnodegraphmodule.h"
#include "octanegrpcwrapworkpanemodule.h"
#include "apilogmanagerclient.h"
#include "moduleids.h"
#include <grpc/grpc.h>
#include <iostream>
#include "grpcmodulebase.h"


// global user interface components.
ApiWindowProxy      gWindow;
ApiTextButtonProxy  gButton;
ApiTextEditorProxy  gEditor;


// internal cleanup function
static void cleanup()
{
    if (!gWindow.isNull())
    {
        gWindow.destroy();
        gWindow.setNull();
    }
    if (!gButton.isNull())
    {
        gButton.destroy();
        gButton.setNull();
    }
    if (!gEditor.isNull())
    {
        gEditor.destroy();
        gEditor.setNull();
    }
}


// called when the user clicks a button
static void buttonClicked(
    ApiTextButtonProxy & button,
    void *)
{
    ApiLogManagerProxy::log("Button clicked");
    gEditor.clear();
    gEditor.setText("Hello, World!", false);
}


// called when the window is closed by the user
static void windowClose(
    ApiWindowProxy & window,
    void *)
{
    ApiLogManagerProxy::log("Window closed");
    cleanup();
}


// Run function for hello world. This function is called every time the user selects the plugin
// from the plugin menu in the standalone.
static bool helloWorldRun(
    void *)
{
    // write something in the log
    ApiLogManagerProxy::log("Hello, World!");

    // create the user interface using the grid to make it all nicely resizable
    ApiGridLayoutProxy layout = ApiGridLayoutProxy::create();
    layout.startSetup(-1, -1, -1,-1);
    {
        // text editor on the first row
        gEditor = ApiTextEditorProxy::create(1, NULL, NULL);
        gEditor.setEnabled(true);
        layout.add(gEditor, 0, 0);

        // text button on the second row
        gButton = ApiTextButtonProxy::create("Hello!",
            buttonClicked,
            NULL
            );
        layout.add(gButton, 0, 1);

        // button does not resize
        layout.setRowElasticity(1, 0.f);
    }
    layout.endSetup();

    gWindow = ApiWindowProxy::create("Hello, World! Plugin", windowClose, NULL);
    gWindow.addContentComponent(layout);
    gWindow.setSize(480, 240);
    gWindow.show();
    return true;
}


HelloWorldModule::HelloWorldModule(
    GRPCModuleBase * moduleBase)
:
    mModuleBase(moduleBase)
{

}


int main(int argc, char * argv[])
{
    std::string serverSocket;
    std::string moduleSocket;
 
    // Parse command line arguments
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        // Look for --serverSocket="..."
        if (arg.rfind("--serverSocket=", 0) == 0)
        {
            // length of "--serverSocket=" is 15
            serverSocket = arg.substr(15);

            // Remove surrounding quotes if present
            if (!serverSocket.empty() && serverSocket.front() == '"')
            {
                serverSocket.erase(0, 1);
            }
            if (!serverSocket.empty() && serverSocket.back() == '"')
            {
                serverSocket.pop_back();
            }
        }
        // Look for --moduleSocket="..."
        else if (arg.rfind("--moduleSocket=", 0) == 0)
        {
            moduleSocket = arg.substr(15); // length of "--moduleSocket=" is 15

            // Remove surrounding quotes if present
            if (!moduleSocket.empty() && moduleSocket.front() == '"')
            {
                moduleSocket.erase(0, 1);
            }
            if (!moduleSocket.empty() && moduleSocket.back() == '"')
            {
                moduleSocket.pop_back();
            }
        }
    }
     

    // Create our gRPC manager
    GRPCModuleBase grpcMain;
    HelloWorldModule helloWorld(&grpcMain);
    GRPCMainInterface * mainInterface = &helloWorld;

    // Start the gRPC server in a background thr6ead
    if (!grpcMain.startServer(mainInterface, moduleSocket, serverSocket))
    {
        // std::cerr << "Failed to start gRPC server.\n";
        return 1; // or handle error
    }

    // std::cout << "Server is running. Press Enter to stop...\n";
    // Block until user presses Enter (or you handle signals in production)
    grpcMain.waitUntilServerStops();
     
    return 0;
}


void HelloWorldModule::start(
    const std::string & callbackSourse,
    const bool          displayEnglish,
    const int           secondLanguage)
{
    ApiImageProxy nullIcon;
    OctaneWrap::CommandModule::registerModule(
        MODULE_ID_EXAMPLE_HELLO_WORLD,
        "|Octane GRPC Examples|Hello, World! (GRPC)",
        "Prints a greeting in the Octane log window (GRPC).",
        "Octane dev team (GRPC)",
        Octane::ocsVersion(0, 1, 0),
        &helloWorldRun,
        nullIcon);
}


void HelloWorldModule::stop()
{
    cleanup();

    if (mModuleBase)
    {
        mModuleBase->stopServer();
    }
}


bool HelloWorldModule::isReady()
{
    return true;
}
