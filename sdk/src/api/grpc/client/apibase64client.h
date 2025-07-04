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


#include "apibase64.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiBase64
class ApiBase64Proxy : public GRPCBase
{
public:
    /// Encodes the given data block as base64.
    /// 
    /// @param[in]  data
    ///     The data block to encode.
    /// @param[in]  size
    ///     The size of the data block.
    /// @param[out] encoded 
    ///     The base64-encoded string. This should be cleaned up by calling cleanupResult().
    /// @param[in]  useBase64Url
    ///     Set to TRUE to use base 64 URL-safe encoding
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if the encoding was successful.
    static bool encode(
            const char *                              data,
            const size_t                              size,
            Octane::CharArrayT &                      encoded,
            const bool                                useBase64Url
            );

    /// Encodes the given data block as base64. The decoder will skip over white space, but will
    /// terminate on the first other character which is not a base64 digit (including the null
    /// character).
    /// 
    /// @param[in] data
    ///     The data block to encode.
    /// @param[in] size
    ///     The maximum size of the data block to decode.
    /// @param[out] decoded
    ///     The base64-encoded string. This should be cleaned up by calling cleanupResult().
    /// @param[in] useBase64Url
    ///     Set to TRUE to use base 64 URL-safe encoding
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if the encoding was successful
    static bool decode(
            const char *                              data,
            const size_t                              size,
            Octane::CharArrayT &                      decoded,
            const bool                                useBase64Url
            );

private:
    static GRPCSettings & getGRPCSettings();
};
