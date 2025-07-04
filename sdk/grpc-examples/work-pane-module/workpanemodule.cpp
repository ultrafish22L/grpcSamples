// Copyright (C) 2025 OTOY NZ Ltd.

#include "grpcmodulebase.h" 
#include "workpanemodule.h"
#include <thread>
#include "octanegrpcwrappers.h"
#include "octanegrpcwrapcommandmodule.h"
#include "octanegrpcwrapnodegraphmodule.h"
#include "octanegrpcwrapworkpanemodule.h"
#include "apilogmanagerclient.h"
#include "content.h"
#include "moduleids.h"
#include "octanewraputil.h"
#include "apibase64client.h"
#include "octanetoolbarbuttonicons.h"
//#include "grpcmouseevent.h"
#include <grpc/grpc.h>


// Tool bar item ids list
const Octane::ModuleIdT TOOLBAR_COMMAND_IDS[3] = { MODULE_ID_EXAMPLE_WORK_PANE_TOOLBAR_SAVE,
MODULE_ID_EXAMPLE_WORK_PANE_TOOLBAR_LOAD,
MODULE_ID_EXAMPLE_WORK_PANE_TOOLBAR_RELOAD };



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
    WorkPaneModule helloWorld(&grpcMain);
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


WorkPaneModule::WorkPaneModule(GRPCModuleBase * modulebase)
:
    mModuleBase(modulebase)
{

}


void WorkPaneModule::start(
    const std::string & callbackSourse,
    const bool          displayEnglish,
    const int           secondLanguage)
{
    // icon image for tool bar buttons
    OctaneWrap::Image * mToolbarSaveIcon = nullptr;
    OctaneWrap::Image * mToolbarLoadIcon = nullptr;
    OctaneWrap::Image * mToolbarReloadIcon = NULL; 

    // toolbar save button info
    Octane::CharArrayT decoded;
    ApiBase64Proxy::decode(gOctaneSaveButton, gOctaneSaveButtonSize, decoded, false);
    mToolbarSaveIcon = OctaneWrap::Image::loadFromMemory(decoded.mData, decoded.mSize);

    OctaneWrap::CommandModule::registerModule(
        MODULE_ID_EXAMPLE_WORK_PANE_TOOLBAR_SAVE,
        "Save (GRPC)",// will not display in the module menu, use "|name" to display it in the menu
        "Save the log to a text file (GRPC)",
        "Octane dev Team (GRPC)",
        Octane::ocsVersion(0, 1, 0),
        &MainContent::toolbarSaveButtonClicked,
        *(mToolbarSaveIcon->wrappedImage()),
        "Work pane example  (GRPC)",
        't',
        Octane::CTRL_MODIFIER);

    // toolbar load button info
    ApiBase64Proxy::decode(gOctaneLoadButton, gOctaneLoadButtonSize, decoded, false);
    mToolbarLoadIcon = OctaneWrap::Image::loadFromMemory(decoded.mData, decoded.mSize);

    OctaneWrap::CommandModule::registerModule(
        MODULE_ID_EXAMPLE_WORK_PANE_TOOLBAR_LOAD,
        "Load (GRPC)",// will not display in the module menu, use "|name" to display it in the menu
        "Loads data from a text file (GRPC)",
        "Octane dev Team (GRPC)",
        Octane::ocsVersion(0, 1, 0),
        &MainContent::toolbarLoadButtonClicked,
        *(mToolbarLoadIcon->wrappedImage()));

    // toolbar reload button info
    ApiBase64Proxy::decode(gOctaneReloadButton, gOctaneReloadButtonSize, decoded, false);
    mToolbarReloadIcon = OctaneWrap::Image::loadFromMemory(decoded.mData, decoded.mSize);

    OctaneWrap::CommandModule::registerModule(
        MODULE_ID_EXAMPLE_WORK_PANE_TOOLBAR_RELOAD,
        "Reload (GRPC)",// will not display in the module menu, use "|name" to display it in the menu
        "Reload data from a text file (GRPC)",
        "Octane dev Team (GRPC)",
        Octane::ocsVersion(0, 1, 0),
        &MainContent::toolbarReloadButtonClicked,
        *(mToolbarReloadIcon->wrappedImage()));

    // register the work pane module
    OctaneWrap::WorkPaneModule::registerModule<MainContent>(
        MODULE_ID_EXAMPLE_WORK_PANE,
        "|Octane Examples (GRPC)|Work pane (GRPC)",
        "Work pane example module (GRPC)",
        "Octane dev Team (GRPC)",
        Octane::ocsVersion(0, 1, 0),
        TOOLBAR_COMMAND_IDS,
        3,
        false);

    deleteAndZero(mToolbarSaveIcon);
    deleteAndZero(mToolbarLoadIcon);
    deleteAndZero(mToolbarReloadIcon);
}


void WorkPaneModule::stop()
{
    if (mModuleBase)
    {
        mModuleBase->stopServer();
    }
}


bool WorkPaneModule::isReady()
{
    return true;
}
