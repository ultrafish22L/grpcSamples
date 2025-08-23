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
namespace OctaneGRPC
{
    class ApiBinaryTableProxy;
}


#include "apibinaryfile.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiBinaryGroup
class ApiBinaryGroupProxy : public GRPCBase
{
public:
    /// Creates a new binary group.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static ApiBinaryGroupProxy create();

    /// Destroys this group.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroy();

    /// Returns TRUE if this group doesn't have any entries.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isEmpty() const;

    /// Returns the number of entries in this group.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    size_t size() const;

    /// Removes the first entry.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void popFront();

    /// Removes the last entry.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void popBack();

    /// Returns the id of the element stored at ix.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    int32_t getId(
            const size_t   ix
            ) const;

    /// Returns TRUE if the 2 objects refer to the same group internally.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool equals(
            const ApiBinaryGroupProxy &   other
            ) const;

    bool get(
            const size_t                              ix,
            bool &                                    value
            ) const;

    bool get(
            const size_t                              ix,
            int8_t &                                  value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::int8_2 &                          value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::int8_3 &                          value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::int8_4 &                          value
            ) const;

    bool get(
            const size_t                              ix,
            uint8_t &                                 value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::uint8_2 &                         value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::uint8_3 &                         value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::uint8_4 &                         value
            ) const;

    bool get(
            const size_t                              ix,
            int16_t &                                 value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::int16_2 &                         value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::int16_3 &                         value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::int16_4 &                         value
            ) const;

    bool get(
            const size_t                              ix,
            uint16_t &                                value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::uint16_2 &                        value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::uint16_3 &                        value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::uint16_4 &                        value
            ) const;

    bool get(
            const size_t                              ix,
            int32_t &                                 value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::int32_2 &                         value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::int32_3 &                         value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::int32_4 &                         value
            ) const;

    bool get(
            const size_t                              ix,
            uint32_t &                                value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::uint32_2 &                        value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::uint32_3 &                        value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::uint32_4 &                        value
            ) const;

    bool get(
            const size_t                              ix,
            int64_t &                                 value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::int64_2 &                         value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::int64_3 &                         value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::int64_4 &                         value
            ) const;

    bool get(
            const size_t                              ix,
            uint64_t &                                value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::uint64_2 &                        value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::uint64_3 &                        value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::uint64_4 &                        value
            ) const;

    bool get(
            const size_t                              ix,
            float &                                   value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::float_2 &                         value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::float_3 &                         value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::float_4 &                         value
            ) const;

    bool get(
            const size_t                              ix,
            double &                                  value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::double_2 &                        value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::double_3 &                        value
            ) const;

    bool get(
            const size_t                              ix,
            Octane::double_4 &                        value
            ) const;

    /// Returned string should be deleted via cleanupString().
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool get(
            const size_t                              ix,
            std::string &                             value
            ) const;

    /// Values should be cleaned up via destroy().
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool getGroup(
            const size_t                              ix,
            ApiBinaryGroupProxy *&                    group
            ) const;

    bool getTable(
            const size_t                              ix,
            ApiBinaryTableProxy *&                    table
            ) const;

    void add(
            const int32_t                             id,
            const bool                                value
            );

    void add(
            const int32_t                             id,
            const int8_t                              value
            );

    void add(
            const int32_t                             id,
            const Octane::int8_2                      value
            );

    void add(
            const int32_t                             id,
            const Octane::int8_3                      value
            );

    void add(
            const int32_t                             id,
            const Octane::int8_4                      value
            );

    void add(
            const int32_t                             id,
            const uint8_t                             value
            );

    void add(
            const int32_t                             id,
            const Octane::uint8_2                     value
            );

    void add(
            const int32_t                             id,
            const Octane::uint8_3                     value
            );

    void add(
            const int32_t                             id,
            const Octane::uint8_4                     value
            );

    void add(
            const int32_t                             id,
            const int16_t                             value
            );

    void add(
            const int32_t                             id,
            const Octane::int16_2                     value
            );

    void add(
            const int32_t                             id,
            const Octane::int16_3                     value
            );

    void add(
            const int32_t                             id,
            const Octane::int16_4                     value
            );

    void add(
            const int32_t                             id,
            const uint16_t                            value
            );

    void add(
            const int32_t                             id,
            const Octane::uint16_2                    value
            );

    void add(
            const int32_t                             id,
            const Octane::uint16_3                    value
            );

    void add(
            const int32_t                             id,
            const Octane::uint16_4                    value
            );

    void add(
            const int32_t                             id,
            const int32_t                             value
            );

    void add(
            const int32_t                             id,
            const Octane::int32_2                     value
            );

    void add(
            const int32_t                             id,
            const Octane::int32_3                     value
            );

    void add(
            const int32_t                             id,
            const Octane::int32_4                     value
            );

    void add(
            const int32_t                             id,
            const uint32_t                            value
            );

    void add(
            const int32_t                             id,
            const Octane::uint32_2                    value
            );

    void add(
            const int32_t                             id,
            const Octane::uint32_3                    value
            );

    void add(
            const int32_t                             id,
            const Octane::uint32_4                    value
            );

    void add(
            const int32_t                             id,
            const int64_t                             value
            );

    void add(
            const int32_t                             id,
            const Octane::int64_2                     value
            );

    void add(
            const int32_t                             id,
            const Octane::int64_3                     value
            );

    void add(
            const int32_t                             id,
            const Octane::int64_4                     value
            );

    void add(
            const int32_t                             id,
            const uint64_t                            value
            );

    void add(
            const int32_t                             id,
            const Octane::uint64_2                    value
            );

    void add(
            const int32_t                             id,
            const Octane::uint64_3                    value
            );

    void add(
            const int32_t                             id,
            const Octane::uint64_4                    value
            );

    void add(
            const int32_t                             id,
            const float                               value
            );

    void add(
            const int32_t                             id,
            const Octane::float_2                     value
            );

    void add(
            const int32_t                             id,
            const Octane::float_3                     value
            );

    void add(
            const int32_t                             id,
            const Octane::float_4                     value
            );

    void add(
            const int32_t                             id,
            const double                              value
            );

    void add(
            const int32_t                             id,
            const Octane::double_2                    value
            );

    void add(
            const int32_t                             id,
            const Octane::double_3                    value
            );

    void add(
            const int32_t                             id,
            const Octane::double_4                    value
            );

    void add(
            const int32_t                             id,
            const char *                              value
            );

    void addGroup(
            const int32_t                             id,
            const ApiBinaryGroupProxy &               group
            );

    void addTable(
            const int32_t                             id,
            const ApiBinaryTableProxy &               table
            );

    /// Dumps the group into the log (use for debugging only).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void dump(
            const uint32_t   indent
            ) const;

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
