// Copyright (C) 2026 OTOY NZ Ltd.

// myself
#include "objectmgr.h"
// system headers
#include <map>
#include <string>
#include <mutex>
#include <stdexcept>

namespace OctaneGRPC
{

    // Singleton access
    ObjectStore& ObjectStore::getInstance()
    {
        static ObjectStore instance;
        return instance;
    }


    void ObjectStore::removePointer(const std::string& key)
    {
        std::lock_guard<std::mutex> lock(mMutex);
        auto it = mPointers.find(key);
        if (it == mPointers.end())
        {
            throw std::runtime_error("Invalid key: pointer not found");
        }
        deletePointer(it->second);
        mPointers.erase(it);
    }


    ObjectStore::~ObjectStore()
    {
        std::lock_guard<std::mutex> lock(mMutex);
        for (auto& entry : mPointers)
        {
            deletePointer(entry.second);
        }
        mPointers.clear();
    }


    void ObjectStore::deletePointer(void* rawPtr)
    {
        // If you store arrays allocated with new[], you must change this to delete[].
        delete reinterpret_cast<char*>(rawPtr);
    }

} // namespace OctaneGRPC
