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


#include "octaneinfos.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiTextureValueTypeSet
class ApiTextureValueTypeSetProxy : public GRPCBase
{
public:
    /// Gets the number of texture value types.
    ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The number of texture value types, which may be zero.
    uint32_t size(            ) const;

    /// Gets the TextureValueType at a given index (TEXTURE_VALUE_TYPE_UNKNOWN if out of bounds).
    ///
    /// @param index
    ///     The index of a TextureValueType.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The TextureValueType at a given index (TEXTURE_VALUE_TYPE_UNKNOWN if out of bounds).
    Octane::TextureValueType at(
            uint32_t                                  index
            ) const;

    /// Checks if a given TextureValueType is included in the set.
    ///
    /// @param index
    ///     The index of a TextureValueType.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if the given TextureValueType is included in the set, FALSE otherwise.
    bool contains(
            Octane::TextureValueType                  textureValueType
            ) const;

    /// Return the bitfield encoding all the texture value types in the set.
    ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     A 32-wide bit field, encoding texture value types (single bit per TextureValueType enum option).
    uint32_t bitField(            ) const;

private:
    static GRPCSettings & getGRPCSettings();
};
