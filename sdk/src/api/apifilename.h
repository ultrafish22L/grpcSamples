// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _API_FILE_NAME_H_
#define _API_FILE_NAME_H_   1

#include "octanetypes.h"

namespace Octane
{

//--------------------------------------------------------------------------------------------------
/// Portable way for dealing with file names and paths.
class OCTANEAPI_DECL ApiFileName
{
    OCTANEAPI_NO_COPY(ApiFileName);

public:

    /// Creates a new ApiFileName instance.
    ///
    /// @param[in]  path
    ///     String representing a path name. Leaving this NULL will create an empty file name.
    /// @return
    ///     Pointer to the newly created file name. Don't call delete on this pointer but use
    ///     destroy() instead.
    static ApiFileName* create(
        const char *path = NULL);

    /// Destroys the ApiFileName object created by create() and other getters below.
    void destroy();

    /// Assigns a new file name path to this instance.
    void set(
        const char * newPath);

    /// Clears the instance. isEmpty() will return TRUE afterwards.
    void clear();

    /// Returns TRUE if this is an empty instance, i.e. getFullString() would return "".
    bool isEmpty() const;

    /// Returns TRUE if the stored file name is absolute, i.e. would always point to the
    /// same file, independent of your current working directory. On Windows, this implies
    /// both !isRelative() and !getRootString().empty() .
    bool isAbsolute() const;

    /// Returns TRUE if the stored file name is relative.
    bool isRelative() const;

    /// Returns the parent directory of the file name (including any root, like drive/server).
    /// NOTE: The returned filename needs to be deleted with destroy().
    ApiFileName* getParent() const;

    /// Returns a file name of the file part (without root and directory).
    /// NOTE: The returned filename needs to be deleted with destroy().
    ApiFileName* getFileOnly() const;

    /// Returns the full file name as string.
    ///
    /// The returned pointer will remain valid until this object is destroyed or modified.
    const char* getFullString() const;

    /// Returns the root of the file name as string (only != "" on Windows).
    ///
    /// The returned pointer will remain valid until this object is destroyed or modified.
    const char* getRootString() const;

    /// Returns the directory part of the file name as string (including the root part on Windows).
    ///
    /// The returned pointer will remain valid until this object is destroyed or modified.
    const char* getParentString() const;

    /// Returns the file part of the instance as string.
    ///
    /// The returned pointer will remain valid until this object is destroyed or modified.
    const char* getFileString() const;

    /// Returns the suffix of the last token (i.e. the file). The suffix is the part following the
    /// the last "." of the file name, including the ".".
    ///
    /// The returned pointer will remain valid until this object is destroyed or modified.
    ///
    /// @param[in]  toLowerCase
    ///     If set to TRUE the suffix characters will be converted to lower case.
    const char* getSuffix(
        const bool toLowerCase = true) const;

    /// Sets the suffix of the last token (i.e. the file). The suffix is the part following the
    /// the last "." of the file name, including the ".".
    /// If the filename has already a suffix, it will be replaced, otherwise the specified suffix
    /// will be appended.
    ///
    /// @param[in]  suffix
    ///     The suffix that will be set. MUST be either empty or start with a '.'.
    void setSuffix(
        const char * suffix);

    /// Similar to setSuffix(), but returning a new FileName instead.
    /// NOTE: The returned filename needs to be deleted with destroy().
    ApiFileName* withSuffix(
        const char * suffix) const;

    /// Makes this file name relative to the specified file name. This and the other path must
    /// either both be absolute (having the same root) or both relative. If both are relative,
    /// it's assumed that they are both starting at the same working directory.
    ///
    /// @param[in]  base
    ///     The path relative to which this path will be afterwards.
    ///     NOTE: This file name is interpreted to be a directory only.
    /// @return
    ///     FALSE if it was not possible to make this file name relative to the other, otherwise
    ///     TRUE.
    bool makeRelativeTo(
        const ApiFileName & base);

    /// Returns the concatenation of this file name with another. If the other file name is absolute
    /// only the other file name is returned.
    /// NOTE: The returned filename needs to be deleted with destroy().
    ApiFileName* getConcat(
        const ApiFileName &other) const;

    /// Concats other filename to this file name.
    void concat(
        const ApiFileName & other);

    /// Returns TRUE if this instance is equal to the other one.
    /// 
    /// Note: On Linux this comparison is case-sensitive, on other operating systems it is not.
    bool equals(
        const ApiFileName & other) const;

    /// Returns TRUE if this instance is not equal to the other one.
    /// 
    /// Note: On Linux this comparison is case-sensitive, on other operating systems it is not.
    bool notEquals(
        const ApiFileName & other) const;

    /// Returns TRUE if this instance is "less" than the other one (useful for ordered maps).
    /// 
    /// Note: On Linux this comparison is case-sensitive, on other operating systems it is not.
    bool lessThan(
        const ApiFileName & other) const;

    /// Returns TRUE if this instance is equal to the other one, using a case-sensitive comparison
    /// on all platforms.
    bool exactlyEquals(
        const ApiFileName & other) const;

    /// Returns TRUE if this instance is "less" than the other one, using a case-sensitive comparison
    /// on all platforms.
    bool exactlyLessThan(
        const ApiFileName & other) const;

    /// Appends some text to the file name of the last token, but makes sure
    /// that it is inserted in front of the suffix (if the last token has one).
    void appendToFileName(
        const char * text);

    /// Returns TRUE if this file name exists as directory OR as file. This file name must be an
    /// absolute file name (asserted), otherwise FALSE is returned.
    bool exists() const;

    /// Returns TRUE if this file name exists and is a file. This file name must be an absolute file
    /// name (asserted), otherwise FALSE is returned.
    bool existsAsFile() const;

    /// Returns TRUE if this file name exists and is a file. This file name must be an absolute file
    /// name (asserted), otherwise FALSE is returned.
    bool existsAsDirectory() const;

    /// Returns TRUE if we can write to the specified file name.
    bool hasWriteAccess() const;

    /// Tries to create a directory with this file name, which must be an absolute file name
    /// (asserted). Returns TRUE if it succeeded (or the directory already existed) and FALSE if
    /// the directory could not be created.
    bool createDirectory() const;
};

} // namespace Octane


#endif // #ifndef _API_FILE_NAME_H_
