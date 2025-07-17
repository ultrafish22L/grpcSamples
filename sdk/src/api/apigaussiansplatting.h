// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _API_GAUSSIAN_SPLATTING_H
#define _API_GAUSSIAN_SPLATTING_H 1

#include "apinodesystem.h"
#include "octanetypes.h"


namespace Octane
{

class OCTANEAPI_DECL ApiGaussianSplatCloudNode : public ApiNode
{
    OCTANEAPI_NO_COPY(ApiGaussianSplatCloudNode);

public:

    /// Creates a new node of the NT_GEO_GAUSSIAN_SPLAT type.
    ///
    /// @param[in]  ownerGraph 
    ///     Graph that will own the new ApiGaussianSplatCloudNode.
    /// @return
    ///     Pointer to the created node or NULL if creation failed.
    static ApiGaussianSplatCloudNode * create(
        ApiNodeGraph & ownerGraph);

    /// Returns ApiGaussianSplatCloudNode interface for the ApiNode of NT_GEO_GAUSSIAN_SPLAT type
    /// 
    /// @param[in] node
    ///     The node to obtain API for.
    /// @return 
    ///     The ApiGaussianSplatCloudNode object pointer if node type is NT_GEO_GAUSSIAN_SPLAT.
    ///     NULL otherwise.
    static ApiGaussianSplatCloudNode * obtain(
        ApiNode * node);

    /// Writes the Gaussian splat PLY attribute arrays into the node attributes.
    /// Can be used to assign in-memory data to NT_GEO_GAUSSIAN_SPLAT without specifying a .PLY file.
    ///
    /// @param[in] numberOfPoints
    ///     The number of points in the Gaussian splat cloud. If 0, the Gaussian splat
    ///     attributes will be cleared.
    /// @param[in] x,y,z,opacity,scale0,scale1,scale2,rot0,rot1,rot2,rot3,dc0,dc1,dc2
    ///     The pointers to the corresponding PLY Gaussian splat attribute buffers.
    ///     These buffers contain 1 floating point value per each point in the cloud, so each buffer
    ///     size must be at least sizeof(float) * numberOfPoints.
    ///     These pointers can't be NULL when numberOfPoints is non-zero.
    /// @param[in] numberOfRestAttributes
    ///     The number of elements in restAttributePointers buffer. If more than 45 provided, the
    ///     extra values will be ignored.
    /// @param[in] restAttributePointers
    ///     The buffer that contains pointers to the extra spherical harmonics data buffers.
    ///     Can't be NULL when numberOfRestAttributes is non-zero.
    ///     Each buffer element is a pointer to the corresponding PLY attribute buffer (f_rest_0,
    ///     f_rest_1, f_rest_2... etc)
    ///     The buffer size must be at least sizeof(float*) * numberOfRestAttributes.
    ///     The requirements for extra spherical harmonics data buffers are the same as for the
    ///     other attributes: size must be at least sizeof(float) * numberOfPoints.
    /// @param[in] evaluate
    ///     TRUE to re-evaluate the node, FALSE otherwise.
    /// @return
    ///     TRUE if attributes were set successfully, FALSE otherwise
    bool setAttributesFromPly(
        const uint32_t       numberOfPoints,
        const float *        x,
        const float *        y,
        const float *        z,
        const float *        opacity,
        const float *        scale0,
        const float *        scale1,
        const float *        scale2,
        const float *        rot0,
        const float *        rot1,
        const float *        rot2,
        const float *        rot3,
        const float *        dc0,
        const float *        dc1,
        const float *        dc2,
        const uint32_t       numberOfRestAttributes,
        const float *const * restAttributePointers,
        const bool           evaluate = true);
};

}

#endif
