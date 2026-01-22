// Copyright (C) 2026 OTOY NZ Ltd.

// myself
#include "octanegrpcwrapfilename.h"

using namespace OctaneWrap;


FileName::FileName()
{}


FileName::FileName(
    const char* str)
{
    mApiFileName = OctaneGRPC::ApiFileNameProxy::create(str);
}


FileName::FileName(
    const std::string &str)
{
    mApiFileName = OctaneGRPC::ApiFileNameProxy::create(str.c_str());
}


FileName::FileName(
    const FileName &other)
{
    mApiFileName = other.mApiFileName;
}


FileName::~FileName()
{
    mApiFileName.destroy();
}


FileName& FileName::operator=(
    const FileName &other)
{
    if (&other == this) { return *this; }
    mApiFileName.set(other.getFullString().c_str());
    return *this;
}


FileName& FileName::operator=(
    const char *str)
{
    mApiFileName.set(str);
    return *this;
}


FileName& FileName::operator=(
    const std::string &str)
{
    mApiFileName.set(str.c_str());
    return *this;
}


void FileName::clear()
{

    mApiFileName.clear();
}


bool FileName::isEmpty() const
{
    return mApiFileName.isEmpty();
}


bool FileName::isAbsolute() const
{
    return mApiFileName.isAbsolute();
}


bool FileName::isRelative() const
{
    return mApiFileName.isRelative();
}


FileName FileName::getParent() const
{
    return FileName(mApiFileName.getParent());
}


FileName FileName::getFileOnly() const
{
    return FileName(mApiFileName.getFileOnly());
}


std::string FileName::getFullString() const
{
    return mApiFileName.getFullString();
}


std::string FileName::getRootString() const
{
    return mApiFileName.getRootString();
}


std::string FileName::getParentString() const
{
    return mApiFileName.getParentString();
}


std::string FileName::getFileString() const
{
    return mApiFileName.getFileString();
}


std::string FileName::getSuffix(
    const bool toLowerCase) const
{
    return mApiFileName.getSuffix(toLowerCase);
}


void FileName::setSuffix(
    const std::string &suffix)
{
    mApiFileName.setSuffix(suffix.c_str());
}


FileName FileName::withSuffix(
    const std::string &suffix) const
{
    return FileName(mApiFileName.withSuffix(suffix.c_str()));
}


bool FileName::makeRelativeTo(
    const FileName &base)
{
    return mApiFileName.makeRelativeTo(base.mApiFileName);
}


FileName FileName::operator+(
    const FileName &other) const
{
    return FileName(mApiFileName.getConcat(other.mApiFileName));
}


FileName& FileName::operator+=(
    const FileName &other)
{
    mApiFileName.concat(other.mApiFileName);
    return *this;
}


bool FileName::operator==(
    const FileName &other) const
{
    return mApiFileName.equals(other.mApiFileName);
}


bool FileName::operator!=(
    const FileName &other) const
{
    return mApiFileName.notEquals(other.mApiFileName);
}


bool FileName::operator<(
    const FileName &other) const
{
    return mApiFileName.lessThan(other.mApiFileName);
}


void FileName::appendToFileName(
    const std::string &text)
{
    return mApiFileName.appendToFileName(text.c_str());
}


bool FileName::exists() const
{
    return mApiFileName.isAbsolute() && mApiFileName.exists();
}


bool FileName::existsAsFile() const
{
    return mApiFileName.isAbsolute() && mApiFileName.existsAsFile();
}


bool FileName::existsAsDirectory() const
{
    return mApiFileName.isAbsolute() && mApiFileName.existsAsDirectory();
}


bool FileName::hasWriteAccess() const
{
    return mApiFileName.hasWriteAccess();
}


bool FileName::createDirectory() const
{
    return mApiFileName.createDirectory();
}


FileName::FileName(
    const OctaneGRPC::ApiFileNameProxy &apiFileName)
{
    mApiFileName = apiFileName;
}
