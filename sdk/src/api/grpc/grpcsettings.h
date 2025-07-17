// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once
#include <grpcpp/grpcpp.h>
#include <map>
#include <queue>
#include <set>


/// Manages global configuration and state for gRPC communication.
class GRPCSettings
{
public:
    virtual ~GRPCSettings() = default;

    /// Provides access to the singleton instance of GRPCSettings.
    /// @return
    ///    A reference to the singleton instance of GRPCSettings.
    static GRPCSettings & getInstance();

    /// Returns TRUE if we are running as  Module (module sdk))
    static bool isRunningAsModule();

    /// Retrieves the next available callback ID for the given function type.
    ///
    /// @param[in] funcType
    ///    A string representing the type of callback function.
    /// @return
    ///    A unique integer ID associated with the function type.
    int getNextCallbackId(
        const std::string & funcType);

    /// Releases a previously acquired callback ID for the given function type.
    ///
    /// @param[in] funcType
    ///    A string representing the type of callback function.
    /// @param[in] callbackId
    ///    The callback ID to be released.
    void releaseCallbackId(
        const std::string & funcType,
        int                 callbackId);

    /// Sets the address of the server (a Unix domain socket).
    ///
    /// @param[in] newAddress
    ///    The server address to set.
    void setServerAddress(
        const std::string & newAddress);

    /// Sets the unique identifier string received from the server when configuring callback functions.
    /// This is only called, and must be called when running as a module (aka module sdk)
    /// @param[in] newAddress
    ///    The unique string identifier provided by the server.
    void setUniqueString(
        const std::string & newAddress);

    /// Retrieves the unique string identifier used to identify the module instance to octane.
    ///
    /// @return
    ///    A string representing the callback source.
    std::string callbackSource();

    GRPCSettings(const GRPCSettings &) = delete;

    GRPCSettings & operator=(const GRPCSettings &) = delete;

    std::shared_ptr<grpc::Channel> & getChannel();
protected:
    GRPCSettings() = default;
    bool mInitialized = false;
    std::string mServerAddress;
    std::string mUniqueString;
    std::shared_ptr<grpc::Channel> mChannel;
    std::mutex mMutex;

    struct CallbackPool
    {
        std::priority_queue<int, std::vector<int>, std::greater<int>> availableIds;
        std::set<int> usedIds;
        int maxSize = 40;
    };

    std::map<std::string, CallbackPool> mCallbackPools;

};
