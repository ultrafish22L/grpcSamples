// Copyright (C) 2026 OTOY NZ Ltd.

#include "grpcsettings.h"

namespace OctaneGRPC
{

GRPCSettings& GRPCSettings::getInstance()
{
    static GRPCSettings instance;
    return instance;
}


bool GRPCSettings::isRunningAsModule()
{
    return getInstance().callbackSource() != "";
}


void GRPCSettings::releaseCallbackId(
    const std::string& funcType,
    int                 callbackId)
{
    std::lock_guard<std::mutex> lock(getInstance().mMutex);
    auto& pool = getInstance().mCallbackPools[funcType];

    // Remove from used and return to available heap
    if (pool.usedIds.erase(callbackId)) // returns 1 if erased, 0 if not found
    {
        pool.availableIds.push(callbackId);
    }
    else
    {
        // Optionally handle attempt to release untracked ID
        throw std::runtime_error("Attempt to release unused or invalid callback ID: " + std::to_string(callbackId));
    }
}


int GRPCSettings::getNextCallbackId(
    const std::string& funcType)
{
    return -1;
    std::lock_guard<std::mutex> lock(getInstance().mMutex);
    auto& pool = getInstance().mCallbackPools[funcType];

    if (pool.availableIds.empty())
    {
        // Either initialize or exhausted
        if (pool.maxSize > 0 && pool.usedIds.size() >= pool.maxSize)
        {
            throw std::runtime_error("No available callback IDs for funcType: " + funcType);
        }

        // Fill all IDs from 1 to maxSize lazily
        for (int i = 1; i <= pool.maxSize; ++i)
        {
            if (pool.usedIds.find(i) == pool.usedIds.end())
            {
                pool.availableIds.push(i);
            }
        }

        // If still no available IDs
        if (pool.availableIds.empty())
        {
            throw std::runtime_error("No available callback IDs after refill.");
        }
    }

    int id = pool.availableIds.top();
    pool.availableIds.pop();
    pool.usedIds.insert(id);
    return id;
}


void GRPCSettings::setServerAddress(
    const std::string& newAddress)
{
    mServerAddress = newAddress;
    mInitialized = false;
}


void GRPCSettings::setUniqueString(
    const std::string& uniqueString)
{
    mUniqueString = uniqueString;
}


std::string GRPCSettings::callbackSource()
{
    return mUniqueString;
}


std::shared_ptr<grpc::Channel>& GRPCSettings::getChannel()
{
    if (mInitialized && mChannel)
    {
        return mChannel; // fast path, no locking
    }

    std::lock_guard<std::mutex> lock(mMutex);
    if (!mInitialized || !mChannel)
    {
        grpc::ChannelArguments args;
        mChannel = grpc::CreateChannel(mServerAddress, grpc::InsecureChannelCredentials());
        mInitialized = true;
    }

    return mChannel;
}

} // namespace OctaneGRPC