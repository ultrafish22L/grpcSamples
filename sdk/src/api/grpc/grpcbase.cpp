// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)

#include "grpcbase.h"



namespace OctaneGRPC
{


void GRPCBase::attachObjectHandle(
    int64_t handle)
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


bool GRPCBase::isNull()
{
    return mHandle == 0;
}


void GRPCBase::setNull()
{
    mHandle = 0;
}

} // namespace OctaneGRPC

#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)