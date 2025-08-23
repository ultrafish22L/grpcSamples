// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once


#include "clientcallbackmgr.h"
#include <grpcpp/grpcpp.h>
#include "apimodule.h"
// system headers
#include <condition_variable>
#include <mutex>
#include <thread>

// forward declarations
namespace OctaneGRPC
{
    class MainComponent;
    class ApiImageProxy;
    class GRPCMainInterface;
    class CallbackHandlerImpl;
}

namespace OctaneGRPC
{
// Main class the starts/stops the grpc server. Derive from this class to create a module
class GRPCModuleBase
{
public:
    GRPCModuleBase();

    ~GRPCModuleBase();

    /// Starts the gRPC server to listen for incoming calls from Octane.
    ///
    /// @param[in] mainInterface
    ///    Interface pointer to the Module implementation.
    /// @param[in] clientURL
    ///    The URL (Unix socket) of the server we instantiate for receiving callbacks from Octane.
    /// @param[in] serverURL
    ///    The URL (Unix socket) of the GRPC server on Octanme
    /// @return
    ///    TRUE if the server started successfully, otherwise FALSE.
    bool startServer(
        GRPCMainInterface* mainInterface,
        const std::string& clientURL,
        const std::string& serverURL);

    // Stop the server
    void stopServer();

    // does not return until server stops
    void waitUntilServerStops();

private:


    // start the actual grpc server
    void runGrpcServer();

    // internal function used when stopping the grpc server
    void stopServerImpl();

    // variables used to control the grpc server loop
    std::mutex                           mWaitMutex;
    bool mServerRunning = false;
    bool mServerStarted = false;
    bool mFailedToStart = false;
    std::condition_variable              mStartCV;
    std::condition_variable              mWaitCV;
    std::thread                          mServerThread;

    /// The service implementation handling callback-related RPC calls.
    std::unique_ptr<CallbackHandlerImpl> mCallbackService;

    /// gRPC ServerBuilder used to configure and initialize the server.
    grpc::ServerBuilder                  mBuilder;

    /// The active gRPC server instance.
    std::unique_ptr<grpc::Server>        mServer;

    // the address to the GRPC server runnibg insode octane
    std::string                          mServerURL;

    // the URL we export on out grpc server
    std::string                          mOurURL;

    // the interface that modules must override
    GRPCMainInterface* mMainInterface;
};

}// namespace OctaneGRPC