// Copyright (C) 2026 OTOY NZ Ltd.

// myself
#include "octanegrpcwrapfilechooser.h"
// application includes
#include "apifilechooser.h"


using namespace OctaneWrap;


FileChooser::FileChooser(
    const std::string &dialogTitle,
    const std::string &initialDirectory,
    const std::string &filePatterns)
//:
//    mApiFileChooser(NULL)
{
    mApiFileChooser = ApiFileChooserProxy::create(dialogTitle.c_str(),
                                                     initialDirectory.c_str(),
                                                     filePatterns.c_str());
}


FileChooser::~FileChooser()
{
    mApiFileChooser.destroy();
    //mApiFileChooser = NULL;
}


bool FileChooser::browseForFileToOpen()
{
    return mApiFileChooser.browseForFileToOpen();
}


bool FileChooser::browseForMultipleFilesToOpen()
{
    return mApiFileChooser.browseForMultipleFilesToOpen();
}


bool FileChooser::browseForFileToSave(
    const bool warnAboutOverwritingExistingFiles)
{
    return mApiFileChooser.browseForFileToSave(warnAboutOverwritingExistingFiles);
}


bool FileChooser::browseForDirectory()
{
    return mApiFileChooser.browseForDirectory();
}


bool FileChooser::browseForMultipleFilesOrDirectories()
{
    return mApiFileChooser.browseForMultipleFilesOrDirectories();
}


std::string FileChooser::result() const
{
    return std::string(mApiFileChooser.result());
}


std::vector<std::string> FileChooser::results() const
{
    std::vector<std::string> resultVector = mApiFileChooser.results();
    return resultVector;
}
