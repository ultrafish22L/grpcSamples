// Copyright (C) 2025 OTOY NZ Ltd.



#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)

#include "convertmatrix.h"
namespace OctaneGRPC
{

    void MatrixConverter::convertMatrixToOctane(
        const octaneapi::MatrixF& in,
        OctaneVec::MatrixF& out)
    {
        // Ensure the Protobuf repeated field contains exactly 3 rows (as required for 3x4 matrix)
        if (in.m_size() != 3)
        {
            throw std::runtime_error("Invalid input MatrixF: Expected 3 rows, but got " + std::to_string(in.m_size()));
        }

        // Iterate over the Protobuf repeated float_4 and populate the C++ MatrixF
        for (int i = 0; i < 3; ++i)
        {
            // Access the i-th float_4 vector in Protobuf
            const auto& protoVec = in.m(i);

            // Populate the corresponding Vec4<float> in the C++ Matrix
            out.m[i] = {
                protoVec.x(),
                protoVec.y(),
                protoVec.z(),
                protoVec.w()
            };
        }
    }


    void MatrixConverter::convertMatrixToProto(
        const OctaneVec::MatrixF& in,
        octaneapi::MatrixF& out)
    {
        // Clear any pre-existing data in the Protobuf message
        out.clear_m();

        // Iterate over each row in the C++ Matrix
        for (int i = 0; i < 3; ++i)
        {
            const auto& cppVec = in.m[i]; // Access the i-th Vec4

                                          // Add a new float_4 entry to the Protobuf repeated field
            auto* protoVec = out.add_m();

            // Set the components of the float_4 message
            protoVec->set_x(cppVec.x);
            protoVec->set_y(cppVec.y);
            protoVec->set_z(cppVec.z);
            protoVec->set_w(cppVec.w);
        }
    }
} //namespace OctaneGRPC
#endif //#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)