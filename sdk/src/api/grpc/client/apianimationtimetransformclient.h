// Copyright (C) 2025 OTOY NZ Ltd.

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


#include "apianimationtimetransform.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiAnimationTimeTransform
class ApiAnimationTimeTransformProxy : public GRPCBase
{
public:
    /// Returns the type of this time transform. Can be used to cast it to the actual type.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::AnimationTimeTransformType type() const;

private:
    static GRPCSettings & getGRPCSettings();
};
