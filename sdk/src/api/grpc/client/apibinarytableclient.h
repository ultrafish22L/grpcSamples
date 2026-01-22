// Copyright (C) 2026 OTOY NZ Ltd.

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
namespace OctaneGRPC
{
    class ApiBinaryGroupProxy;
}


#include "apibinaryfile.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiBinaryTable
class ApiBinaryTableProxy : public GRPCBase
{
public:
    /// Create a new binary table. Don't use delete but call destroy() to cleanup.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static ApiBinaryTableProxy create();

    /// Destroys this binary table. Only do this on tables created via create(). Not on tables
    /// that are returned via get.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroy();

    /// Returns TRUE if this table doesn't have any entries.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isEmpty() const;

    /// Returns the number of entries in this table.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    size_t size() const;

    /// Erases the entry with the passed in id. No operation if the entry doen not exist.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void erase(
            const int32_t   id
            );

    /// Returns TRUE if there is an entry with the passed in id.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool has(
            const int32_t   id
            ) const;

    /// Returns TRUE if the 2 objects refer to the same table internally.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool equals(
            const ApiBinaryTableProxy &   other
            ) const;

    bool get(
            const int32_t                             id,
            bool &                                    value
            ) const;

    bool get(
            const int32_t                             id,
            int8_t &                                  value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::int8_2 &                          value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::int8_3 &                          value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::int8_4 &                          value
            ) const;

    bool get(
            const int32_t                             id,
            uint8_t &                                 value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::uint8_2 &                         value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::uint8_3 &                         value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::uint8_4 &                         value
            ) const;

    bool get(
            const int32_t                             id,
            int16_t &                                 value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::int16_2 &                         value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::int16_3 &                         value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::int16_4 &                         value
            ) const;

    bool get(
            const int32_t                             id,
            uint16_t &                                value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::uint16_2 &                        value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::uint16_3 &                        value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::uint16_4 &                        value
            ) const;

    bool get(
            const int32_t                             id,
            int32_t &                                 value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::int32_2 &                         value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::int32_3 &                         value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::int32_4 &                         value
            ) const;

    bool get(
            const int32_t                             id,
            uint32_t &                                value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::uint32_2 &                        value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::uint32_3 &                        value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::uint32_4 &                        value
            ) const;

    bool get(
            const int32_t                             id,
            int64_t &                                 value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::int64_2 &                         value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::int64_3 &                         value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::int64_4 &                         value
            ) const;

    bool get(
            const int32_t                             id,
            uint64_t &                                value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::uint64_2 &                        value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::uint64_3 &                        value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::uint64_4 &                        value
            ) const;

    bool get(
            const int32_t                             id,
            float &                                   value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::float_2 &                         value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::float_3 &                         value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::float_4 &                         value
            ) const;

    bool get(
            const int32_t                             id,
            double &                                  value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::double_2 &                        value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::double_3 &                        value
            ) const;

    bool get(
            const int32_t                             id,
            Octane::double_4 &                        value
            ) const;

    /// Returned string should be deleted via cleanupString().
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool get(
            const int32_t                             id,
            std::string &                             value
            ) const;

    /// Values should be cleaned up via destroy().
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool getGroup(
            const int32_t                             id,
            ApiBinaryGroupProxy *&                    group
            ) const;

    bool getTable(
            const int32_t                             id,
            ApiBinaryTableProxy *&                    table
            ) const;

    void set(
            const int32_t                             id,
            const bool                                value
            );

    void set(
            const int32_t                             id,
            const int8_t                              value
            );

    void set(
            const int32_t                             id,
            const Octane::int8_2                      value
            );

    void set(
            const int32_t                             id,
            const Octane::int8_3                      value
            );

    void set(
            const int32_t                             id,
            const Octane::int8_4                      value
            );

    void set(
            const int32_t                             id,
            const uint8_t                             value
            );

    void set(
            const int32_t                             id,
            const Octane::uint8_2                     value
            );

    void set(
            const int32_t                             id,
            const Octane::uint8_3                     value
            );

    void set(
            const int32_t                             id,
            const Octane::uint8_4                     value
            );

    void set(
            const int32_t                             id,
            const int16_t                             value
            );

    void set(
            const int32_t                             id,
            const Octane::int16_2                     value
            );

    void set(
            const int32_t                             id,
            const Octane::int16_3                     value
            );

    void set(
            const int32_t                             id,
            const Octane::int16_4                     value
            );

    void set(
            const int32_t                             id,
            const uint16_t                            value
            );

    void set(
            const int32_t                             id,
            const Octane::uint16_2                    value
            );

    void set(
            const int32_t                             id,
            const Octane::uint16_3                    value
            );

    void set(
            const int32_t                             id,
            const Octane::uint16_4                    value
            );

    void set(
            const int32_t                             id,
            const int32_t                             value
            );

    void set(
            const int32_t                             id,
            const Octane::int32_2                     value
            );

    void set(
            const int32_t                             id,
            const Octane::int32_3                     value
            );

    void set(
            const int32_t                             id,
            const Octane::int32_4                     value
            );

    void set(
            const int32_t                             id,
            const uint32_t                            value
            );

    void set(
            const int32_t                             id,
            const Octane::uint32_2                    value
            );

    void set(
            const int32_t                             id,
            const Octane::uint32_3                    value
            );

    void set(
            const int32_t                             id,
            const Octane::uint32_4                    value
            );

    void set(
            const int32_t                             id,
            const int64_t                             value
            );

    void set(
            const int32_t                             id,
            const Octane::int64_2                     value
            );

    void set(
            const int32_t                             id,
            const Octane::int64_3                     value
            );

    void set(
            const int32_t                             id,
            const Octane::int64_4                     value
            );

    void set(
            const int32_t                             id,
            const uint64_t                            value
            );

    void set(
            const int32_t                             id,
            const Octane::uint64_2                    value
            );

    void set(
            const int32_t                             id,
            const Octane::uint64_3                    value
            );

    void set(
            const int32_t                             id,
            const Octane::uint64_4                    value
            );

    void set(
            const int32_t                             id,
            const float                               value
            );

    void set(
            const int32_t                             id,
            const Octane::float_2                     value
            );

    void set(
            const int32_t                             id,
            const Octane::float_3                     value
            );

    void set(
            const int32_t                             id,
            const Octane::float_4                     value
            );

    void set(
            const int32_t                             id,
            const double                              value
            );

    void set(
            const int32_t                             id,
            const Octane::double_2                    value
            );

    void set(
            const int32_t                             id,
            const Octane::double_3                    value
            );

    void set(
            const int32_t                             id,
            const Octane::double_4                    value
            );

    void set(
            const int32_t                             id,
            const char *                              value
            );

    void setGroup(
            const int32_t                             id,
            const ApiBinaryGroupProxy &               group
            );

    void setTable(
            const int32_t                             id,
            const ApiBinaryTableProxy &               table
            );

    /// Writes this ApiBinaryTable into a file.
    ///
    /// @param[in]  path
    ///     Full path to the output file.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if the operation was successful, FALSE if not.
    bool write(
            const char *   path
            );

    /// Reads an ApiBinaryTable from a file.
    ///
    /// @param[in]  path
    ///     Full path to the input file.
    /// @param[out] octaneVersion
    ///     Octane version number used to write the input file.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Pointer to the binary table. Should be destroyed via destroy. A Null pointer when
    ///     the file could not be read.
    static ApiBinaryTableProxy read(
            const char *                              path,
            uint32_t &                                octaneVersion
            );

    /// Dumps the table into the log (use for debugging only).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void dump(
            const uint32_t   indent
            ) const;

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
