// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _API_PACKAGE_H_
#define _API_PACKAGE_H_ 1


#include "apiarray.h"
#include "apifilename.h"
#include "octanetypes.h"



namespace Octane
{


//--------------------------------------------------------------------------------------------------
/// Functions to fetch files from an ORBX package. Useful for modules that have assets stored in the
/// package.
class OCTANEAPI_DECL ApiPackage
{
    OCTANEAPI_NO_COPY(ApiPackage);

public:

    /// Deallocates a data buffer that was returned by readFile().
    static void freeBuffer(
        ByteArrayT &buffer);

    /// Deallocates a string array that 
    static void freeArray(
        StringArrayT &stringArray);

    /// Open a package for reading files. This will keep the package open until close() is called.
    static ApiPackage* open(
        const char *const packagePath);


    /// Closes a package. The pointer will be invalid afterwards and can not be used anymore.
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
    void getFileList(
        StringArrayT &     fileList,
        const char * const regExpr = nullptr) const;

    /// Checks if a file exists in the package.
    /// 
    /// @param[in] path
    ///      The path to the child file, must be a relative path.
    /// @return
    ///      TRUE if the file exists, FALSE otherwise.
    bool fileExists(
        const char *const path) const;

    /// Checks if a file exists in the package.
    /// 
    /// @param[in] path
    ///      The path to the child file, must be a relative path.
    /// @return
    ///      TRUE if the file exists, FALSE otherwise.
    bool fileExists(
        const ApiFileName &path) const;

    /// Reads a file from the package.
    ///
    /// NOTE: The returned buffer needs to be deallocated via freeBuffer().
    ///
    /// @param[in]  path
    ///      A relative path of the file in a package specified as C string.
    /// @param[out]  data
    ///      The contents of the file, which needs to be deallocated via freeBuffer() after use.
    /// @return 
    ///     TRUE if successful, FALSE if path is not a relative path or if the file doesn't exist,
    ///     or an error occurred while opening the file.
    bool readFile(
        const char *const path,
        ByteArrayT        &data) const;

    /// Reads data from the package as a cstring. 
    ///
    /// @param[in]  path
    ///      A relative path of the file in a package.
    /// @param[out] data
    ///      file data, This should deleted via freeString().
    /// @param[out] size
    ///      size of the data.
    /// @return 
    /// TRUE if successful.
    /// FALSE if path is not a relative path or if the file doesn't exist, or an error occurs while opening the file.
    bool readFile(
        const ApiFileName &path,
        ByteArrayT        &data) const;
};

} // namespace Octane


#endif // #ifndef _API_PACKAGE_H_
