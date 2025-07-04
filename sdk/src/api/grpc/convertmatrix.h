// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)

#include "protoc/common.grpc.pb.h"
#include "octanematrix.h"

class MatrixConverter
{
public:
    /// Converts a matrix from the Protobuf format (octaneapi::MatrixF) to the Octane type
    /// (OctaneVec::MatrixF).
    ///
    /// @param[in] in
    ///     The input matrix in octaneapi::MatrixF format.
    /// @param[out] out
    ///     The output matrix converted to OctaneVec::MatrixF format.
    static void convertMatrixToOctane(
        const octaneapi::MatrixF & in,
        OctaneVec::MatrixF &       out);

    /// Converts a matrix from the Octane type (OctaneVec::MatrixF) format to the protobuf format
    /// (octaneapi::MatrixF).
    ///
    /// @param[in] in
    ///     The input matrix in OctaneVec::MatrixF format.
    /// @param[out] out
    ///     The output matrix converted to octaneapi::MatrixF format.
    static void convertMatrixToProto(
        const OctaneVec::MatrixF & in,
        octaneapi::MatrixF &       out);
};

#endif //#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)