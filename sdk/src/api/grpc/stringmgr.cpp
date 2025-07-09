// Copyright (C) 2025 OTOY NZ Ltd.

// myself
#include "stringmgr.h"
// system
#include <algorithm>

StringManager & StringManager::getInstance()
{
    static StringManager instance;
    return instance;
}


const char * StringManager::addString(
    const std::string & str)
{
    std::lock_guard<std::mutex> lock(mMutex);

    // Dynamically allocate the string
    std::string * newStr = new std::string(str);

    // and store the pointer
    mStrings.emplace_back(newStr);

    // Return a const char* pointing to the stored string
    return newStr->c_str();
}


const char * StringManager::addString(
    const char * str)
{
    std::lock_guard<std::mutex> lock(mMutex);
    std::string * newStr = new std::string(str);
    mStrings.emplace_back(newStr);
    return newStr->c_str(); 
}


bool StringManager::removeString(
    const char * ptr)
{
    std::lock_guard<std::mutex> lock(mMutex);
    auto it = std::find_if(mStrings.begin(), mStrings.end(),
        [ptr](std::string * s) {
            return s && s->c_str() == ptr;
        });

    if (it != mStrings.end())
    {
        delete * it;
        mStrings.erase(it);
        return true;
    }
    return false;
}


void StringManager::cleanup()
{
    std::lock_guard<std::mutex> lock(mMutex);
    for (std::string * str : mStrings)
    {
        // Delete each dynamically allocated string
        delete str;
    }
    mStrings.clear();
}


std::string StringManager::checkString(
    const char * str)
{
    if (str == nullptr)
    {
        return "";
    }
    return std::string(str);
}
