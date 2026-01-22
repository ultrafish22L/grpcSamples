// Copyright (C) 2026 OTOY NZ Ltd.

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
namespace OctaneGRPC
{
    class ApiFileNameProxy;
}


#include "apipackage.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiPackage
class ApiPackageProxy : public GRPCBase
{
public:
    /// Deallocates a string array that
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void freeArray(
            Octane::StringArrayT &   stringArray
            );

    /// Open a package for reading files. This will keep the package open until close() is called.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static ApiPackageProxy open(
            const char *const   packagePath
            );

    /// Closes a package. The pointer will be invalid afterwards and can not be used anymore.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void close();

    /// Creates a list of all files stored in the ORBX package.
    ///
    /// @param[out] fileList
    ///     Will receive the files stored in the package.
    ///     @note To avoid leaking memory, you have to free the string array after usage via
    ///           freeArray().
    /// @param[in]  regExpr
    ///     A regular expression pattern to search for, The regular expression is compared only againt
    ///  base filenames. The function will return all files in the package, if it is set to NULL.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void getFileList(
            std::vector<std::string> &                fileList,
            const char *const                         regExpr
            ) const;

    /// Checks if a file exists in the package.
    ///
    /// @param[in] path
    ///      The path to the child file, must be a relative path.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///      TRUE if the file exists, FALSE otherwise.
    bool fileExists(
            const char *const   path
            ) const;

    /// Checks if a file exists in the package.
    ///
    /// @param[in] path
    ///      The path to the child file, must be a relative path.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///      TRUE if the file exists, FALSE otherwise.
    bool fileExists(
            const ApiFileNameProxy &   path
            ) const;

    /// Reads a file from the package.
    ///
    /// NOTE: The returned buffer needs to be deallocated via freeBuffer().
    ///
    /// @param[in]  path
    ///      A relative path of the file in a package specified as C string.
    /// @param[out]  data
    ///      The contents of the file, which needs to be deallocated via freeBuffer() after use.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if successful, FALSE if path is not a relative path or if the file doesn't exist,
    ///     or an error occurred while opening the file.
    bool readFile(
            const char *const                         path,
            std::vector<uint8_t> &                    data
            ) const;

    /// Reads data from the package as a cstring.
    ///
    /// @param[in]  path
    ///      A relative path of the file in a package.
    /// @param[out] data
    ///      file data, This should deleted via freeString().
    /// @param[out] size
    ///      size of the data.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    /// TRUE if successful.
    /// FALSE if path is not a relative path or if the file doesn't exist, or an error occurs while opening the file.
    bool readFile(
            const ApiFileNameProxy &                  path,
            std::vector<uint8_t> &                    data
            ) const;

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
