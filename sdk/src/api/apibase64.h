// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _API_BASE_64_H_
#define _API_BASE_64_H_ 1

// api includes
#include "apiarray.h"
#include "octanetypes.h"

namespace Octane
{

//--------------------------------------------------------------------------------------------------
/// This utility class provides methods to encode to and decode from Base64 and Base64-URL
/// encoding to UTF-8
class OCTANEAPI_DECL ApiBase64
{
public:

    /// Cleans up the result returned from any of the other API calls.
    static void cleanupResult(
        CharArrayT &result);
    
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
    /// @return
    ///     TRUE if the encoding was successful.
    static bool encode(
        const char   *data,
        const size_t size,
        CharArrayT   &encoded,
        const bool   useBase64Url = false);

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
    /// @return
    ///     TRUE if the encoding was successful
    static bool decode(
        const char   *data,
        const size_t size,
        CharArrayT   &decoded,
        const bool   useBase64Url = false);
};

} // namespace Octane


#endif // #ifndef _API_BASE_64_H_
