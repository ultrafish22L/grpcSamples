// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once

#include <memory>
#include <grpcpp/grpcpp.h>
#ifdef OCTANEAPI_DECL
#undef OCTANEAPI_DECL
#endif
#define OCTANEAPI_DECL
#include "grpcbase.h"
#include "grpcapinodeinfo.h" 


class Convert;

class GRPCSettings;
namespace OctaneGRPC
{
/// Class to create arrays of 'ApiNodePinInfo' objects on the server
class ApiNodePinInfoExService : public OctaneGRPC::GRPCBase
{
public:
    /// Creates an array of ApiNodePinInfoProxy objects on the server (Octane.exe) and returns a vector of 
    /// ApiNodePinInfoProxy objects that reference the tiems in that array.
    ///
    /// @param[in] items
    ///     A pointer to the first element in an array of ApiNodePinInfo structures.
    /// @param[in] count
    ///     The number of elements in the input array.
    /// @return
    ///     A vector containing ApiNodePinInfoProxy objects converted from the input array.
    static std::vector<ApiNodePinInfoProxy> createApiNodePinInfoArray(
        const ApiNodePinInfo* items,
        const int              count);

    /// Creates a single ApiNodePinInfo on the server (octane.exe) and returns a proxy object that references it.
    /// @param[in] nodePinInfo
    ///     The ApiNodePinInfo that we want to add to the server
    /// @return
    ///     the ApiNodePinInfoProxy object we use to reference the newly created object on the server.
    static ApiNodePinInfoProxy createApiNodePinInfo(
        const Octane::ApiNodePinInfo& nodePinInfo);

    /// Deletes the given ApiNodePinInfo on the server.
    ///
    /// @param[in] nodePinInfo
    ///     The proxy object representing the ApiNodePinInfo to be deleted.
    /// @return  
    ///     TRUE if the deletion was successful; otherwise, FALSE.
    static bool deleteApiNodePinInfo(
        const ApiNodePinInfoProxy& nodePinInfo);

    /// Updates an existing ApiNodePinInfo entry on the server.
    ///
    /// @param[in] nodePinInfoProxy
    ///     The proxy object referencing the existing ApiNodePinInfo to update.
    /// @param[in] nodePinInfo
    ///     The updated data to apply to the node pin.
    /// @return
    ///     TRUE if the update was successful; otherwise, FALSE.
    static bool updateApiNodePinInfo(
        const ApiNodePinInfoProxy& nodePinInfoProxy,
        const Octane::ApiNodePinInfo& nodePinInfo);


    /// Retrieves an existing ApiNodePinInfo structure from the server.
    ///
    /// @param[in] nodePinInfoProxy
    ///     The proxy object referencing the existing ApiNodePinInfo to update.
    /// @param[in] nodePinInfo
    ///     The ApiNodePinInfo data
    /// @return
    ///     TRUE if the update was successful; otherwise, FALSE.
    static bool getApiNodePinInfo(
        const ApiNodePinInfoProxy& nodePinInfoProxy,
        Octane::ApiNodePinInfo& nodePinInfo);

private:
    /// Returns a reference to the singleton GRPCSettings object,
    /// which manages global configuration and state related to gRPC communication.
    ///
    /// @return
    ///     A reference to the global GRPCSettings instance.
    static GRPCSettings& getGRPCSettings();

    // The callback function caleld when Octane calls back after a call to PerformBlockingOperation is made
    static std::function<void()> mBlockingOperationCallback;
};

}// nnamespace OctaneGRPC;