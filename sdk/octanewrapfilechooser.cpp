// Copyright (C) 2025 OTOY NZ Ltd.

// application includes
#include "apifilechooser.h"
// myself
#include "octanewrapfilechooser.h"

using namespace OctaneWrap;


FileChooser::FileChooser(
    const std::string &dialogTitle,
    const std::string &initialDirectory,
    const std::string &filePatterns)
:
    mApiFileChooser(NULL)
{
    mApiFileChooser = Octane::ApiFileChooser::create(dialogTitle.c_str(),
                                                     initialDirectory.c_str(),
                                                     filePatterns.c_str());
}


FileChooser::~FileChooser()
{
    mApiFileChooser->destroy();
    mApiFileChooser = NULL;
}


bool FileChooser::browseForFileToOpen()
{
    return mApiFileChooser->browseForFileToOpen();
}


bool FileChooser::browseForMultipleFilesToOpen()
{
    return mApiFileChooser->browseForMultipleFilesToOpen();
}


bool FileChooser::browseForFileToSave(
    const bool warnAboutOverwritingExistingFiles)
{
    return mApiFileChooser->browseForFileToSave(warnAboutOverwritingExistingFiles);
}


bool FileChooser::browseForDirectory()
{
    return mApiFileChooser->browseForDirectory();
}


bool FileChooser::browseForMultipleFilesOrDirectories()
{
    return mApiFileChooser->browseForMultipleFilesOrDirectories();
}


std::string FileChooser::result() const
{
    return std::string(mApiFileChooser->result());
}


std::vector<std::string> FileChooser::results() const
{
    Octane::ApiArray<const char*> results = mApiFileChooser->results();
    std::vector<std::string> resultVector;
    for (size_t i=0; i<results.mSize; ++i)
    {
        resultVector.push_back(results.mData[i]);
    }
    return resultVector;
}
