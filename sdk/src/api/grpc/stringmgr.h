// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once
// system headers
#include <iostream>
#include <mutex>
#include <string>
#include <vector>

namespace OctaneGRPC
{
    // Class to store dynamically allocated strings. The GRPC API reuses a lot of structures from
    // the Octane API which often refer to strings as char * rather than std:;string. This means the
    // string objects that these char *  members point to need to be stored. This class solves that
    // problem by providing an interface to store the string objects and remove them.
    class StringManager
    {
    public:
        /// Provides access to the singleton instance of StringManager.
        ///
        /// @return
        /// A reference to the singleton instance of StringManager.
        static StringManager& getInstance();

        /// Dynamically allocates a new string, Store the pointer and return a const char* pointing to the string
        ///
        /// @param[in] str
        ///     The input string to add.
        /// @return
        ///     A const char* pointing to the internal copy of the string.
        const char* addString(
            const std::string& str);

        /// Dynamically allocates a new string, Store the pointer and return a const char* pointing to the string
        ///
        /// @param[in] str
        ///     The input null-terminated C-style string to add.
        /// @return
        ///     const char* pointing to the internal copy of the string.
        const char* addString(
            const char* str);

        /// Removes a previously added string based on its const char* pointer.
        ///
        /// @param[in] ptr
        ///     A pointer to the string previously returned by addString().
        /// @return
        ///     TRUE if the string was successfully removed.
        bool removeString(
            const char* ptr);

        // Clean up dynamically allocated strings
        void cleanup();

        /// Returns the input string if it is non-null, otherwise returns an empty string.
        ///
        /// @param[in] str
        ///     A C-style string to check.
        /// @return
        ///     The input string if not null; otherwise, an empty std::string.
        static std::string checkString(
            const char* str);

        // Deleted constructors to enforce singleton pattern
        StringManager(const StringManager&) = delete;

        // Delete assignment operator to enforce singleton pattern
        StringManager& operator=(const StringManager&) = delete;

    private:
        // Private constructor to prevent external instantiation
        StringManager() = default;

        // Destructor automatically cleans up singleton instance
        ~StringManager() = default;

        // Collection of string pointers
        std::vector<std::string*> mStrings;

        // Mutex for thread-safe operations
        std::mutex mMutex;
    };
} //namespace OctaneGRPC
