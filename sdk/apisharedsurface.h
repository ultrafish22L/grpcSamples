// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#include "octaneenums.h"
#include "octanetypes.h"

#ifdef OCTANE_INTERNAL
# include "shared-surface.h"
# include <memory>
#endif


namespace Octane
{

/// Details of a graphics API surface shared between Octane and a plugin.
class OCTANEAPI_DECL ApiSharedSurface final
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
    /// @return
    ///     The created shared surface. Will not be null. Must be released.
    static ApiSharedSurface * createD3D11(
        uint64_t adapterLuid,
        void * handle);


    /// Returns whether two ApiSharedSurface pointers refer to the same underlying shared surface
    /// object.
    ///
    /// @param a
    ///     The first object to compare, or null.
    /// @param b
    ///     The second object to compare, or null.
    /// @return
    ///     True if both a and b are null or both are non-null and point to objects that refer to
    ///     the same underlying shared surface object. False otherwise.
    static bool equals(
        const ApiSharedSurface * a,
        const ApiSharedSurface * b);

    /// Defines a strict total order of ApiSharedSurface pointers based on the underlying shared
    /// surface object. This allows this type to be used in an ordered map/set.
    ///
    /// @param a
    ///     The first object to compare, or null.
    /// @param b
    ///     The second object to compare, or null.
    /// @return
    ///     True if a is less than b, where null is considered less than everything else, and two
    ///     non-null pointers are ordered based on their underlying shared surface objects.
    static bool isLessThan(
        const ApiSharedSurface * a,
        const ApiSharedSurface * b);

    /// Returns a hash value that's the same for ApiSharedSurface instances that refer to the same
    /// underlying shared surface object. This allows this type to be used in an unordered map/set.
    ///
    /// @param surface
    ///     The object for which to get the hash, or null.
    /// @return
    ///     A hash value the underlying shared surface object, or some fixed hash value if surface
    ///     is null.
    static size_t hash(
        const ApiSharedSurface * surface);


    /// Destroys this specific ApiSharedSurface instance, decrementing the reference count of the
    /// underlying shared surface object.
    void release();

    /// Creates a new ApiSharedSurface instance that refers to the same underlying shared surface
    /// object as this instance.
    ///
    /// @return
    ///     The created instance. Will not be null. Must be released.
    ApiSharedSurface * clone() const;

    /// Gets the type of the shared surface.
    ///
    /// Must not be called after release, even if there are other references to the same underlying
    /// shared surface object.
    ///
    /// Will always return the same value for the same instance. Will not return
    /// SHARED_SURFACE_TYPE_NONE.
    SharedSurfaceType getType() const;

    /// Gets the LUID of the D3D11 adapter on which the shared texture exists. Must not be called
    /// unless the type is SHARED_SURFACE_TYPE_D3D11.
    ///
    /// Must not be called after release, even if there are other references to the same underlying
    /// shared surface object.
    ///
    /// Will always return the same value for the same instance. Will not return null.
    uint64_t getD3D11AdapterLuid() const;

    /// Gets the HANDLE for a shared ID3D11Texture2D instance. Must not be called unless the type is
    /// SHARED_SURFACE_TYPE_D3D11.
    ///
    /// The texture's keyed mutex must be acquired and released with a key of 0 around any access to
    /// the texture.
    ///
    /// The handle returned must not be used after the underlying shared surface object is
    /// destroyed. Duplicate it with DuplicateHandle before calling release if you want to continue
    /// to use it.
    ///
    /// Must not be called after release, even if there are other references to the same underlying
    /// shared surface object.
    ///
    /// Will always return the same value for the same instance. Will not return null.
    void * getD3D11Handle() const;


#ifdef OCTANE_INTERNAL
    static ApiSharedSurface * createFromInternal(
        std::shared_ptr<const SharedSurface> surface);

    static std::shared_ptr<const SharedSurface> getInternal(
        const ApiSharedSurface * surface);
#endif

private:

    ApiSharedSurface();

    ApiSharedSurface(
        const ApiSharedSurface &other);

    ApiSharedSurface &operator=(
        const ApiSharedSurface &other);

    ~ApiSharedSurface();

};

}
