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


#include "apifilename.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiFileName
class ApiFileNameProxy : public GRPCBase
{
public:
    /// Creates a new ApiFileName instance.
    ///
    /// @param[in]  path
    ///     String representing a path name. Leaving this NULL will create an empty file name.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Pointer to the newly created file name. Don't call delete on this pointer but use
    ///     destroy() instead.
    static ApiFileNameProxy create(
            const char *   path
            );

    /// Destroys the ApiFileName object created by create() and other getters below.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroy();

    /// Assigns a new file name path to this instance.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void set(
            const char *   newPath
            );

    /// Clears the instance. isEmpty() will return TRUE afterwards.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void clear();

    /// Returns TRUE if this is an empty instance, i.e. getFullString() would return "".
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isEmpty() const;

    /// Returns TRUE if the stored file name is absolute, i.e. would always point to the
    /// same file, independent of your current working directory. On Windows, this implies
    /// both !isRelative() and !getRootString().empty() .
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isAbsolute() const;

    /// Returns TRUE if the stored file name is relative.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isRelative() const;

    /// Returns the parent directory of the file name (including any root, like drive/server).
    /// NOTE: The returned filename needs to be deleted with destroy().
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiFileNameProxy getParent() const;

    /// Returns a file name of the file part (without root and directory).
    /// NOTE: The returned filename needs to be deleted with destroy().
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiFileNameProxy getFileOnly() const;

    /// Returns the full file name as string.
    ///
    /// The returned pointer will remain valid until this object is destroyed or modified.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string getFullString() const;

    /// Returns the root of the file name as string (only != "" on Windows).
    ///
    /// The returned pointer will remain valid until this object is destroyed or modified.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string getRootString() const;

    /// Returns the directory part of the file name as string (including the root part on Windows).
    ///
    /// The returned pointer will remain valid until this object is destroyed or modified.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string getParentString() const;

    /// Returns the file part of the instance as string.
    ///
    /// The returned pointer will remain valid until this object is destroyed or modified.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string getFileString() const;

    /// Returns the suffix of the last token (i.e. the file). The suffix is the part following the
    /// the last "." of the file name, including the ".".
    ///
    /// The returned pointer will remain valid until this object is destroyed or modified.
    ///
    /// @param[in]  toLowerCase
    ///     If set to TRUE the suffix characters will be converted to lower case.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string getSuffix(
            const bool   toLowerCase
            ) const;

    /// Sets the suffix of the last token (i.e. the file). The suffix is the part following the
    /// the last "." of the file name, including the ".".
    /// If the filename has already a suffix, it will be replaced, otherwise the specified suffix
    /// will be appended.
    ///
    /// @param[in]  suffix
    ///     The suffix that will be set. MUST be either empty or start with a '.'.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setSuffix(
            const char *   suffix
            );

    /// Similar to setSuffix(), but returning a new FileName instead.
    /// NOTE: The returned filename needs to be deleted with destroy().
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiFileNameProxy withSuffix(
            const char *   suffix
            ) const;

    /// Makes this file name relative to the specified file name. This and the other path must
    /// either both be absolute (having the same root) or both relative. If both are relative,
    /// it's assumed that they are both starting at the same working directory.
    ///
    /// @param[in]  base
    ///     The path relative to which this path will be afterwards.
    ///     NOTE: This file name is interpreted to be a directory only.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     FALSE if it was not possible to make this file name relative to the other, otherwise
    ///     TRUE.
    bool makeRelativeTo(
            const ApiFileNameProxy &   base
            );

    /// Returns the concatenation of this file name with another. If the other file name is absolute
    /// only the other file name is returned.
    /// NOTE: The returned filename needs to be deleted with destroy().
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiFileNameProxy getConcat(
            const ApiFileNameProxy &   other
            ) const;

    /// Concats other filename to this file name.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void concat(
            const ApiFileNameProxy &   other
            );

    /// Returns TRUE if this instance is equal to the other one.
    ///
    /// Note: On Linux this comparison is case-sensitive, on other operating systems it is not.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool equals(
            const ApiFileNameProxy &   other
            ) const;

    /// Returns TRUE if this instance is not equal to the other one.
    ///
    /// Note: On Linux this comparison is case-sensitive, on other operating systems it is not.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool notEquals(
            const ApiFileNameProxy &   other
            ) const;

    /// Returns TRUE if this instance is "less" than the other one (useful for ordered maps).
    ///
    /// Note: On Linux this comparison is case-sensitive, on other operating systems it is not.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool lessThan(
            const ApiFileNameProxy &   other
            ) const;

    /// Returns TRUE if this instance is equal to the other one, using a case-sensitive comparison
    /// on all platforms.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool exactlyEquals(
            const ApiFileNameProxy &   other
            ) const;

    /// Returns TRUE if this instance is "less" than the other one, using a case-sensitive comparison
    /// on all platforms.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool exactlyLessThan(
            const ApiFileNameProxy &   other
            ) const;

    /// Appends some text to the file name of the last token, but makes sure
    /// that it is inserted in front of the suffix (if the last token has one).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void appendToFileName(
            const char *   text
            );

    /// Returns TRUE if this file name exists as directory OR as file. This file name must be an
    /// absolute file name (asserted), otherwise FALSE is returned.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool exists() const;

    /// Returns TRUE if this file name exists and is a file. This file name must be an absolute file
    /// name (asserted), otherwise FALSE is returned.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool existsAsFile() const;

    /// Returns TRUE if this file name exists and is a file. This file name must be an absolute file
    /// name (asserted), otherwise FALSE is returned.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool existsAsDirectory() const;

    /// Returns TRUE if we can write to the specified file name.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool hasWriteAccess() const;

    /// Tries to create a directory with this file name, which must be an absolute file name
    /// (asserted). Returns TRUE if it succeeded (or the directory already existed) and FALSE if
    /// the directory could not be created.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool createDirectory() const;

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
