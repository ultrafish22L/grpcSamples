// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _API_DIAGNOSTICS_H_
#define _API_DIAGNOSTICS_H_   1

#include "octanetypes.h"

namespace Octane
{

//--------------------------------------------------------------------------------------------------
/// Class supporting diagnostic features. 
class OCTANEAPI_DECL ApiDiagnostics
{
    OCTANEAPI_NO_COPY(ApiDiagnostics);

public:

    /// Crashes the software after the specified number of seconds
    ///
    /// @param[in]  delayInSeconds
    ///     The delay before generating the access violation
    static void diagnosticCommand(
        const uint32_t commandType,
        const uint32_t delayInSeconds);
};

} // namespace Octane


#endif // #ifndef _API_DIAGNOSTICS_H_
