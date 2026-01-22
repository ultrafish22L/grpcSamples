// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _API_MODULE_DATA_H_
#define _API_MODULE_DATA_H_ 1

#include "octanetypes.h"

namespace Octane
{

class ApiBinaryTable;

//--------------------------------------------------------------------------------------------------
/// Manages the storing and loading persistent module data. Data can be either application data
/// (global data). Storing and loading of module data is not available in the demo version.
class OCTANEAPI_DECL ApiModuleData
{
    OCTANEAPI_NO_COPY(ApiModuleData);

public:

    /// Loads application data stored for this module.
    /// 
    /// @param[in]  moduleId
    ///     Id of the module loading the data.
    /// @param[out] octaneVersion
    ///     Version of Octane used to store the data.
    /// @return
    ///     Pointer to loaded data. If there was no data stored for the module, an empty table is
    ///     returned. A null pointer is returned when the table could not be loaded. The returned
    ///     data should be disposed of via destroy().
    static ApiBinaryTable* loadApplicationData(
        const ModuleIdT moduleId,
        uint32_t        &octaneVersion);

    /// Stores application data. The application data that was already stored for this module is
    /// overwritten.
    ///
    /// @param[in]  moduleId
    ///     Id of the module storing the data.
    /// @param[in]  table
    ///     Table with the data.
    /// @return
    ///     TRUE when the data was saved successfully, FALSE otherwise.
    static bool storeApplicationData(
        const ModuleIdT      moduleId,
        const ApiBinaryTable &table);
};

} // namespace Octane


#endif // #ifndef _API_MODULE_DATA_H_
