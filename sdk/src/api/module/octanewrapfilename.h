// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_FILE_NAME_H_
#define _OCTANE_WRAP_FILE_NAME_H_   1

// system includes
#include <string>
// api includes
#include "octanetypes.h"
#include "apifilename.h"


namespace OctaneWrap
{

//--------------------------------------------------------------------------------------------------
/// Convenience wrapper around ApiFileName.
class FileName
{
public:

    /// Creates an empty instance.
    FileName();

    /// Creates a new instance and initializes it with the specified string.
    FileName(
        const char *str);

    /// Creates a new instance and initializes it with the specified STL string.
    FileName(
        const std::string &str);

    /// Copy constructor
    FileName(
        const FileName &other);

    /// Destructor.
    ~FileName();

    /// Assignment operator.
    FileName& operator=(
        const FileName &other);

    /// Assigns a new path to the instance.
    FileName& operator=(
        const char *str);

    /// Assigns a new path to the instance.
    FileName& operator=(
        const std::string &str);

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

    /// Returns the parent directory of the file name (including any root, like drive/server). If
    /// there is is already the root, it returns this instance.
    FileName getParent() const;

    /// Returns a file name of the file part (without root and directory).
    FileName getFileOnly() const;

    /// Returns the full file name as string.
    std::string getFullString() const;

    /// Returns the root of the file name as string (only != "" on Windows).
    std::string getRootString() const;

    /// Returns the directory part of the file name as string (including the root part on Windows).
    std::string getParentString() const;

    /// Returns the file part of the instance as string.
    std::string getFileString() const;

    /// Returns the suffix of the last token (i.e. the file). The suffix is the part following the
    /// the last "." of the file name, including the ".".
    ///
    /// @param[in]  toLowerCase
    ///     If set to TRUE the suffix characters will be converted to lower case.
    std::string getSuffix(
        const bool toLowerCase = true) const;

    /// Sets the suffix of the last token (i.e. the file). The suffix is the part following the
    /// the last "." of the file name, including the ".".
    /// If the filename has already a suffix, it will be replaced, otherwise the specified suffix
    /// will be appended.
    ///
    /// @param[in]  suffix
    ///     The suffix that will be set. MUST be either empty or start with a '.'.
    void setSuffix(
        const std::string &suffix);

    /// Similar to setSuffix(), but returning a new FileName instead.
    FileName withSuffix(
        const std::string &suffix) const;

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
        const FileName &base);

    /// Returns the concatenation of this file name with another. If the other file name is absolute
    /// only the other file name is returned.
    FileName operator+(
        const FileName &other) const;

    /// Appends another file name to this one and returns this file name. If the other file name is
    /// absolute, this instance will become a copy of the other file name.
    FileName& operator+=(
        const FileName &other);

    /// Returns TRUE if this instance is equal to the other one.
    bool operator==(
        const FileName &other) const;

    /// Returns TRUE if this instance is not equal to the other one.
    bool operator!=(
        const FileName &other) const;

    /// Returns TRUE if this instance is "smaller" than the other one.
    bool operator<(
        const FileName &other) const;

    /// Appends some text to the file name of the last token, but makes sure
    /// that it is inserted in front of the suffix (if the last token has one).
    void appendToFileName(
        const std::string &text);

    /// Returns TRUE if this file name exists as directory OR as file.
    bool exists() const;

    /// Returns TRUE if this file name exists and is a file.
    bool existsAsFile() const;

    /// Returns TRUE if this file name exists and is a file.
    bool existsAsDirectory() const;

    /// Returns TRUE if we can write to the specified file name.
    bool hasWriteAccess() const;

    /// Tries to create a directory with this file name, which must be an absolute file name.
    /// Returns TRUE if it succeeded (or the directory already existed) and FALSE if the directory
    /// could not be created.
    bool createDirectory() const;

private:

    /// wrapped API filename instance
    Octane::ApiFileName * const mApiFileName; 

    /// Takes ownership over passed in object.
    FileName(
        Octane::ApiFileName *apiFileName);
};

} // namespace OctaneWrap


#endif // _OCTANE_WRAP_FILE_NAME_H_
