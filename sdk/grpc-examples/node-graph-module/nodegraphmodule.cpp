// Copyright (C) 2025 OTOY NZ Ltd.

#include "nodegraphmodule.h"
#include "grpcmodulebase.h"
#include "switcher.h"
#include "baketotexture.h"
#include "moduleids.h"
#include <thread>
#include "octanegrpcwrapnodegraphmodule.h"


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
    NodeGraphModule helloWorld(&grpcMain);
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


NodeGraphModule::NodeGraphModule(GRPCModuleBase * moduleBase)
    :
    mModuleBase(moduleBase)
{

}


void NodeGraphModule::start(
    const std::string & callbackSourse,
    const bool          displayEnglish,
    const int           secondLanguage)
{
    // register a command that launches the module
    OctaneWrap::NodeGraphModule::registerModule<Switcher>(
        MODULE_ID_EXAMPLE_SWITCHER_NODE_GRAPH,
        "|Module graphs (GRPC)|Switcher (GRPC)",
        "Provides switch control for all node types (GRPC)",
        "Octane dev team (GRPC)",
        Octane::ocsVersion(0, 1, 0),
        false);

    OctaneWrap::NodeGraphModule::registerModule<BakeToTexture>(
        MODULE_ID_EXAMPLE_PREVIEW_RENDER_TO_TEXTURE,
        "|Module graphs (GRPC)|Bake to image (GRPC)",
        "Renders preview to texture (GRPC)",
        "Octane dev team (GRPC)",
        Octane::ocsVersion(0, 1, 0),
        false);
}


void NodeGraphModule::stop()
{
    if (mModuleBase)
    {
        mModuleBase->stopServer();
    }
}


bool NodeGraphModule::isReady()
{
    return true;
}
