// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)

#include "grpcbase.h"


void GRPCBase::attachObjectHandle(int64_t handle)
{
    mHandle = handle;
}


int64_t GRPCBase::getObjectHandle() const
{
    return mHandle;
}


std::string GRPCBase::checkString(
    const char * str)
{
    if (str == nullptr)
    {
        return "";
    }
    return std::string(str);
}


bool GRPCBase::isNull() const
{
    return mHandle == 0;
}

void GRPCBase::setNull()
{
    mHandle = 0;
}
#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)