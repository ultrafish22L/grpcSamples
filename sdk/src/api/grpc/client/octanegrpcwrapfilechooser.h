// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_FILE_CHOOSER_H_
#define _OCTANE_WRAP_FILE_CHOOSER_H_  1

// system includes
#include <functional>
#include <string>
#include <vector>
// api includes
#include "octanetypes.h"
#include "apifilechooserclient.h"

namespace Octane
{
class ApiFileChooser;
}
using namespace OctaneGRPC;
namespace OctaneWrap
{

//--------------------------------------------------------------------------------------------------
/// Wraps ApiFileChooser.
class FileChooser
{
    OCTANEAPI_NO_COPY(FileChooser);

public:

    /// Creates a new file chooser.
    /// 
    /// @param[in]  dialogTitle
    ///     Title that appears on the top of the dialog.
    /// @param[in]  initialDirectory
    ///     Absolute path to start directory. If this is left empty a sensible default directory
    ///     is chosen.
    /// @param[in]  filePatterns
    ///     A set of file patterns to specify which files can be selected - each pattern should be
    ///     separated by a comma or semi-colon, e.g. "*" or "*.jpg;*.gif". An empty string means
    ///     that all files are allowed.
    /// @return
    ///     Pointer to the chooser or nullptr if something went wrong.
    FileChooser(
        const std::string &dialogTitle,
        const std::string &initialDirectory = "",
        const std::string &filePatterns     = "");

    /// Destructor for the file chooser.
    virtual ~FileChooser();

    /// Shows a dialog box to choose a file to open. This will display the dialog box modally,
    /// using an "open file" mode, so that it won't allow non-existent files or directories to
    /// be chosen.
    ///
    /// @return TRUE if the user selected a file, in which case, use the result() method to find
    ///         out what it was. Returns FALSE if they cancelled instead.
    bool browseForFileToOpen();

    /// Same as browseForFileToOpen(), but allows the user to select multiple files.  The files
    /// that are returned can be obtained by calling results(). See browseForFileToOpen().
    bool browseForMultipleFilesToOpen();

    /// Shows a dialog box to choose a file to save.  This will display the dialog box modally,
    /// using an "save file" mode, so it will allow non-existent files to be chosen,
    /// but not directories.
    ///
    ///  @param[in] warnAboutOverwritingExistingFiles
    ///     If true, the dialog box will ask the user if they're sure they want to overwrite a
    ///     file that already exists
    ///  @return
    ///     TRUE if the user chose a file and pressed 'ok', in which case, use the result()
    ///     method to find out what the file was. Returns false if they cancelled instead.
    bool browseForFileToSave(
        const bool warnAboutOverwritingExistingFiles);

    /// Shows a dialog box to choose a directory.  This will display the dialog box modally, using
    /// an "open directory" mode, so it will only allow directories to be returned, not files.
    /// @return
    ///     TRUE if the user chose a directory and pressed 'ok', in which case, use the result()
    ///     method to find out what they chose. Returns FALSE if they cancelled instead.
    bool browseForDirectory();

    /// Same as browseForFileToOpen(), but allows the user to select multiple files and directories.
    /// The files that are returned can be obtained by calling results().
    bool browseForMultipleFilesOrDirectories();

    /// Returns the last file that was chosen by one of the browseFor methods.  After calling the
    /// appropriate browseFor... method, this method lets you find out what file or directory they
    /// chose.  Note that the file returned is only valid if the browse method returned true (i.e.
    /// if the user pressed 'ok' rather than cancelling). Otherwise an empty string shall be
    /// returned.
    std::string result() const;

    /// Returns a list of all the files that were chosen during the last call to a browse method.
    std::vector<std::string> results() const;

private:

    /// Wrapped ApiFileChooser.
    ApiFileChooserProxy mApiFileChooser;
};

} // namespace OctaneWrap


#endif // #ifndef _OCTANE_WRAP_FILE_CHOOSER_H_
