// Copyright (C) 2025 OTOY NZ Ltd.

#include "callbackservice.h"
#include "grpcsettings.h"
#include "grpcmodulebase.h"
#include "grpcmaininterface.h"
#ifndef _WIN32
#include <unistd.h>
#endif

static std::thread gStopThread;


// hack required to compile, else we get unresolved external errors
Octane::ApiTextureValueTypeSet::ApiTextureValueTypeSet(uint32_t bitfield)
{

}


Octane::ApiCompatibilityModeInfoSet::ApiCompatibilityModeInfoSet(void)
{

}


namespace OctaneGRPC
{
    GRPCModuleBase::GRPCModuleBase()
    {
        mCallbackService = std::make_unique<CallbackHandlerImpl>();
    }


    GRPCModuleBase::~GRPCModuleBase()
    {
        // Ensure the server is shut down if it’s still running.
        if (mServer)
        {
            stopServer();
        }
    }


    void GRPCModuleBase::runGrpcServer()
    {
        std::shared_ptr<grpc::ServerCredentials> creds;
        creds = grpc::InsecureServerCredentials();

#ifdef _WIN32
        // Clean up any existing socket
        _unlink(mOurURL.c_str());
#else
        unlink(mOurURL.c_str());
#endif

        mBuilder.AddListeningPort("unix:" + mOurURL, creds);
        mCallbackService.get()->mMain = this;
        mCallbackService.get()->setInterface(mMainInterface);
        mBuilder.RegisterService(mCallbackService.get());
        mServer = mBuilder.BuildAndStart();
        {
            if (!mServer)
            {
                std::cerr << "Failed to start the gRPC server. Verify your setup." << std::endl;
                mFailedToStart = true;
                mStartCV.notify_all();
                return;
            }
            // Success: mark running, started
            mServerRunning = true;
            mServerStarted = true;
        }
        mStartCV.notify_all();

        mServer->Wait();

        {
            std::lock_guard<std::mutex> lock(mWaitMutex);
            mServerRunning = false;
        }
        mWaitCV.notify_all();
    }


    bool GRPCModuleBase::startServer(
        GRPCMainInterface* mainInterface,
        const std::string& clientURL,
        const std::string& serverURL)
    {
        mServerURL = "unix:" + serverURL;
        mOurURL = clientURL;
        mMainInterface = mainInterface;
        GRPCSettings::getInstance().setServerAddress(mServerURL);
        // Start the gRPC server in a separate thread
        mServerThread = std::thread(&GRPCModuleBase::runGrpcServer, this);

        // Wait until runGrpcServer signals either "started" or "failed"
        {
            std::unique_lock<std::mutex> lock(mWaitMutex);
            mStartCV.wait(lock, [this]
                {
                    return mServerStarted || mFailedToStart;
                });
        }

        // If we failed to start, join the thread (which likely has already exited)
        if (mFailedToStart)
        {
            if (mServerThread.joinable())
            {
                mServerThread.join();
            }
            return false;
        }
        return true;
    }


    void GRPCModuleBase::stopServer()
    {
        gStopThread = std::thread([this] {
            stopServerImpl();
            });
    }


    void GRPCModuleBase::stopServerImpl()
    {
        if (mServer)
        {
            mServer->Shutdown();

            if (mServerThread.joinable())
            {
                mServerThread.join();
            }

            mServer.reset();
        }
    }


    void GRPCModuleBase::waitUntilServerStops()
    {
        std::unique_lock<std::mutex> lock(mWaitMutex);

        mWaitCV.wait(lock, [this]
            {
                return !mServerRunning;
            });

        if (gStopThread.joinable())
        {
            gStopThread.join();
        }
    }

}