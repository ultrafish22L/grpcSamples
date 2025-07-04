// Copyright (C) 2025 OTOY NZ Ltd.

#include "texcommandermodule.h"
#include "apiwindow.h"
#include "application.h"
#include "grpcmodulebase.h"
#include <thread>
#include "apicommandmoduleinfoclient.h"
#include "apimoduleglobalclient.h"
#include "moduleids.h"
#include "octanewraputil.h"

Application * gApplication = nullptr;


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
    TexCommanderModule helloWorld(&grpcMain);
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



// executed by the command
static bool launchWindow(
    void *)
{
    if(!gApplication)
    {
        gApplication = new Application;
    }
    gApplication->launchWindow();
    return true;
}


TexCommanderModule::TexCommanderModule(GRPCModuleBase * modulebase)
:
    mModuleBase(modulebase)
{

}


void TexCommanderModule::start(
    const std::string & callbackSourse,
    const bool          displayEnglish,
    const int           secondLanguage)
{
    ApiImageProxy icon;
    //// register a command that launches the module
    registerModule(
        MODULE_ID_EXAMPLE_TEX_COMMANDER,
        "|22 Octane Examples 2|22 Launch TexCommander 2",
        "22 Texture manager example module 2",
        "22 Octane dev team 2",
        Octane::ocsVersion(0, 1, 0),
        &launchWindow,
        icon);
}


void TexCommanderModule::stop()
{
    delete gApplication;
    if (mModuleBase)
    {
        mModuleBase->stopServer();
    }
}


bool TexCommanderModule::isReady()
{
    return true;
}


void TexCommanderModule::registerModule(
    const Octane::ModuleIdT                                   moduleId,
    const char *                                              fullName,
    const char *                                              description,
    const char *                                              author,
    const Octane::VersionT                                    versionNumber,
    const Octane::ApiCommandModuleInfo::CommandModuleRunFuncT runFunction,
    const ApiImageProxy &                                     icon,
    const char *                                              shortcutGroupName,
    const int                                                 shortcutKeyCode,
    const int                                                 shortcutModifierKeyFlag)
{
    ApiCommandModuleInfoProxy info = ApiCommandModuleInfoProxy::create(moduleId, fullName, description, author, versionNumber);
    info.setRunFunction(runFunction);

    info.setIcon(&icon);
    info.assignShortcutKey(shortcutGroupName, shortcutKeyCode, shortcutModifierKeyFlag);

    // register as dynamically linked module
    ApiModuleGlobalProxy::registerCommandModule(info);

    info.destroy();
}
