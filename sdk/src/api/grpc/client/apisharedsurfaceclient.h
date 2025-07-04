// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#include "octanetypes.h"
#ifdef OCTANEAPI_DECL
#undef OCTANEAPI_DECL
#endif
#define OCTANEAPI_DECL
#include "octanevectypes.h"
#include "grpcbase.h"
#include "clientcallbackmgr.h"
#include "grpcapinodeinfo.h"


#include "apisharedsurface.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiSharedSurface
class ApiSharedSurfaceProxy : public GRPCBase
{
public:
    /// Creates a shared surface with a D3D11 texture.
    ///
    /// The texture's keyed mutex will be acquired and released with a key of 0 around any access to
    /// the texture.
    ///
    /// @param adapterLuid
    ///     The LUID of the D3D11 adapter on which the shared texture exists. The two fields from
    ///     the LUID struct are combined with `(static_cast<uint64_t>(luid.HighPart) << 32) |
    ///     luid.LowPart`.
    /// @param handle
    ///     HANDLE for a shared ID3D11Texture2D instance. Must not be null. This must have been
    ///     obtained from IDXGIResource1::CreateSharedHandle with the DXGI_SHARED_RESOURCE_READ flag
    ///     enabled. The underlying shared surface object will take ownership of this handle and
    ///     will call CloseHandle when the last reference to it goes away. The format of the texture
    ///     must be DXGI_FORMAT_R8G8B8A8_UNORM_SRGB or DXGI_FORMAT_R32G32B32A32_FLOAT.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The created shared surface. Will not be null. Must be released.
    static ApiSharedSurfaceProxy createD3D11(
            uint64_t                                  adapterLuid,
            void *                                    handle
            );

    /// Returns whether two ApiSharedSurface pointers refer to the same underlying shared surface
    /// object.
    ///
    /// @param a
    ///     The first object to compare, or null.
    /// @param b
    ///     The second object to compare, or null.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     True if both a and b are null or both are non-null and point to objects that refer to
    ///     the same underlying shared surface object. False otherwise.
    static bool equals(
            const ApiSharedSurfaceProxy *             a,
            const ApiSharedSurfaceProxy *             b
            );

    /// Defines a strict total order of ApiSharedSurface pointers based on the underlying shared
    /// surface object. This allows this type to be used in an ordered map/set.
    ///
    /// @param a
    ///     The first object to compare, or null.
    /// @param b
    ///     The second object to compare, or null.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     True if a is less than b, where null is considered less than everything else, and two
    ///     non-null pointers are ordered based on their underlying shared surface objects.
    static bool isLessThan(
            const ApiSharedSurfaceProxy *             a,
            const ApiSharedSurfaceProxy *             b
            );

    /// Returns a hash value that's the same for ApiSharedSurface instances that refer to the same
    /// underlying shared surface object. This allows this type to be used in an unordered map/set.
    ///
    /// @param surface
    ///     The object for which to get the hash, or null.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     A hash value the underlying shared surface object, or some fixed hash value if surface
    ///     is null.
    static size_t hash(
            const ApiSharedSurfaceProxy *             surface
            );

    /// Destroys this specific ApiSharedSurface instance, decrementing the reference count of the
    /// underlying shared surface object.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void release(            );

    /// Creates a new ApiSharedSurface instance that refers to the same underlying shared surface
    /// object as this instance.
    ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The created instance. Will not be null. Must be released.
    ApiSharedSurfaceProxy clone(            ) const;

    /// Gets the type of the shared surface.
    ///
    /// Must not be called after release, even if there are other references to the same underlying
    /// shared surface object.
    ///
    /// Will always return the same value for the same instance. Will not return
    /// SHARED_SURFACE_TYPE_NONE.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::SharedSurfaceType getType(            ) const;

    /// Gets the LUID of the D3D11 adapter on which the shared texture exists. Must not be called
    /// unless the type is SHARED_SURFACE_TYPE_D3D11.
    ///
    /// Must not be called after release, even if there are other references to the same underlying
    /// shared surface object.
    ///
    /// Will always return the same value for the same instance. Will not return null.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    uint64_t getD3D11AdapterLuid(            ) const;

private:
    static GRPCSettings & getGRPCSettings();
};
