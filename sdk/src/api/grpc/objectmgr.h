// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once

#include <map>
#include <string>
#include <mutex>
#include <stdexcept>
#include "objectmgr.h"

namespace OctaneGRPC
{

    class ObjectStore
    {
    public:
        /// Provides access to the singleton instance of ObjectStore.
        /// @return
        ///     A reference to the singleton instance of ObjectStore.
        static ObjectStore& getInstance();

        /// Adds a dynamically allocated pointer under the given string key.
        /// - If the key already exists, the existing pointer will be deleted.
        /// - The new pointer will be stored and managed internally.
        /// - The caller must allocate the pointer using new.
        /// 
        /// @tparam T
        ///     Type of the object being stored.
        /// @param[in] key
        ///     A unique string key to associate with the pointer.
        /// @param[in] ptr
        ///     A pointer to the dynamically allocated object.
        template<typename T>
        void addPointer(const std::string& key, T* ptr)
        {
            std::lock_guard<std::mutex> lock(mMutex);
            // If there's already a pointer here, delete it.
            auto it = mPointers.find(key);
            if (it != mPointers.end())
            {
                deletePointer(it->second); // calls delete
                mPointers.erase(it);
            }
            // Store the new pointer as void*.
            mPointers[key] = reinterpret_cast<void*>(ptr);
        }


        /// Retrieves the pointer associated with the given string key.
        /// The caller must cast the result to the correct type (e.g. getPointer<MyType>("key")).
        /// @param T
        ///     Expected type of the stored object.
        /// @param[in] key
        ///     The string key associated with the pointer.
        /// @return
        ///     A pointer to the stored object, or nullptr if the key is not found.
        template<typename T>
        T* getPointer(const std::string& key)
        {
            std::lock_guard<std::mutex> lock(mMutex);
            auto it = mPointers.find(key);
            if (it == mPointers.end())
            {
                return nullptr;
            }
            return reinterpret_cast<T*>(it->second);
        }

        /// Removes the pointer associated with the given string key.
        /// - The pointer is deleted internally.
        /// - If the key is not found, throws std::runtime_error.
        ///
        /// @param[in] key
        ///     The string key associated with the object to remove.
        void removePointer(
            const std::string& key);

        // Prohibit copying to preserve singleton
        ObjectStore(
            const ObjectStore&) = delete;

        ObjectStore& operator=(
            const ObjectStore&) = delete;

        // Destructor: deletes all pointers still in the map
        ~ObjectStore();

    private:
        ObjectStore() = default; // private constructor for singleton

      // Helper to call "delete" on a void* (assuming it was allocated with new T).
        void deletePointer(void* rawPtr);

    private:
        std::map<std::string, void*> mPointers;
        std::mutex mMutex;
    };
} // namespace OctaneGRPC
