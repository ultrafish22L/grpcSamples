// Copyright (C) 2025 OTOY NZ Ltd.

#include "grpcmodulebase.h"
#include "emptymodule.h"
#include <thread>
#include <string>



int main(
    int    argc,
    char * argv[])
{
    std::string serverSocket;
    std::string moduleSocket;

    // Parse command line arguments
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        // Look for "--serverSocket="
        if (arg.rfind("--serverSocket=", 0) == 0)
        {
            int len = strlen("serverSocket = ");
            serverSocket = arg.substr(len);

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
        // Look for "--moduleSocket="
        else if (arg.rfind("--moduleSocket=", 0) == 0)
        {
            int len = strlen("moduleSocket = ");
            moduleSocket = arg.substr(len);

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
    EmptyModule helloWorld(&grpcMain);
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


EmptyModule::EmptyModule(
    GRPCModuleBase * moduleBase)
:
    mModuleBase(moduleBase)
{

}


void EmptyModule::start(
    const std::string & callbackSourse,
    const bool          displayEnglish,
    const int           secondLanguage)
{

}


void EmptyModule::stop()
{
    if (mModuleBase)
    {
        mModuleBase->stopServer();
    }
}


bool EmptyModule::isReady()
{
    return true;
}
