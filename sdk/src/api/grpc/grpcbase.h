// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once
#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)

#include <stdint.h>
#include <string>

namespace OctaneGRPC
{

    // Base class for all proxy classes
    class GRPCBase
    {
    public:

        /// Attach object reference so that the proxy knows which object to apple the method call on the server
        /// @param[in] handle
        ///    A unique 64-bit identifier for the object on the server.
        /// @return
        ///    None.
        virtual void attachObjectHandle(
            int64_t handle);

        /// Retrieves the currently attached object handle.
        ///
        /// This handle represents the unique identifier of the server-side object associated
        /// with this proxy instance.
        ///
        /// @return
        ///    The 64-bit object handle currently attached to this interface.
        virtual int64_t getObjectHandle() const;

        /// Returns the input string if it is non-null, otherwise returns an empty string.
        ///
        /// @param[in] str
        ///     A C-style string to check.
        /// @return
        ///     The input string if not null; otherwise, an empty std::string.
        static std::string checkString(const char* str);

        /// Indicates if the proxy is referencing an object on the server
        /// @return
        ///    TRUE is the object reference is not valid, otherwise FALSE
        bool isNull();

        /// Set the object reference of the proxy to null.
        void setNull();

    protected:
        // the object reference handle used to indentify the object on the server to which the
        // method calls should be applied
        int64_t mHandle = 0;
    };
} //namespace OctaneGRPC
#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)