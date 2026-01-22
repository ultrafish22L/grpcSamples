// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _OCTANEVOLUME_H_
#define _OCTANEVOLUME_H_


// library includes
#include "octaneids.h"
#include "octanetypes.h"
#include "octanevectypes.h"
#include "octanematrix.h"



namespace Octane
{


class OCTANEAPI_DECL VdbGridSampler
{
    OCTANEAPI_NO_COPY(VdbGridSampler);

    friend class VdbInfo;

public:

    /// Returns the voxel value at the given location of the current grid.
    ///
    /// @param [in] x
    ///     The x coordinate of the sample point in world/local space based on how the sampler has been created
    /// @param [in] y
    ///     The y coordinate of the sample point in world/local space based on how the sampler has been created
    /// @param [in] z
    ///     The z coordinate of the sample point in world/local space based on how the sampler has been created
    /// @return
    ///     The sampled value at the given coordinate, if succeeded. OR zero on failure
    float getValue(
        const float x,
        const float y,
        const float z) const;

private:

    /// The pointer to the grid data
    void *const mDataPtr;
    /// The flag indicating if we can ignore the grid transform
    const bool  mIgnoreTransform;

    VdbGridSampler(
        void *const dataPtr,
        const bool  ignoreVdbTransform);

    ~VdbGridSampler();
};



/// Provides information about one VDB grid.
class OCTANEAPI_DECL VdbGridInfo
{
    OCTANEAPI_NO_COPY(VdbGridInfo);

    friend class VdbInfo;

public:

    /// Returns the name of this grid. Don't deallocate this, it is owned by VdbGridInfo, which 
    /// takes care of deallocating it.
    const char* name() const;
    /// Returns the type of this grid.
    const char* type() const;
    /// Returns the width, height and depth of the grid in voxels.
    uint32_3    resolution() const;
    /// Returns the minimum active voxel bounding box of the grid.
    int32_3     minBound() const;
    /// Returns the maximum active voxel bounding box of the grid.
    int32_3     maxBound() const;
    /// Returns the _transposed_ transform from the VDB, excluding the perspective projection. This
    /// is to match with how transforms are stored by Octane.
    MatrixF     transform() const;

private:
    
    /// The name of this particular grid.
    const char *const mName;
    /// The type of this grid.
    const char *const mType;
    /// The resolution of this grid.
    const uint32_3    mResolution;
    /// The active voxel axis-aligned bounding box.
    const int32_3     mMinBounds;
    /// The active voxel axis-aligned bounding box.
    const int32_3     mMaxBounds;
    /// The grid's transform. This transform is transposed from the ones stored in VDBs so that
    /// it matches with Octane.
    const MatrixF     mTransform;


    /// This class owns the name and type ptrs.
    VdbGridInfo(
        const char *const name,
        const char *const type,
        const uint32_3    resolution,
        const int32_3     bounds[2],
        const MatrixF     transform);
    
    ~VdbGridInfo();
};



/// Provides information about an OpenVDB file.
class OCTANEAPI_DECL VdbInfo
{
    OCTANEAPI_NO_COPY(VdbInfo);


public:

    /// Constructs a new VdbInfo object with the VDB at the given path
    /// 
    /// @param[in] path
    ///     Absolute path to the VDB file.
    VdbInfo(
        const char *const path);
    
    /// Destroys the instance.
    ~VdbInfo();

    /// If the VDB information was loaded successfully, this will return TRUE, otherwise FALSE.
    bool valid() const;

    /// Returns the number of grids stored in the VDB file.
    uint32_t gridCount() const;

    /// Returns a pointer to the VdbGridInfo of the specified index or NULL if the index is invalid
    /// or the VdbInfo wasn't loaded correctly.
    /// 
    /// @param[in] index
    ///     The index of the grid in the VDB file.
    /// @returns if index < gridCount() then this returns a pointer to a VdbGridInfo. Otherwise
    ///     NULL.
    const VdbGridInfo* grid(
        const uint32_t index) const;

    /// Returns a pointer to the VdbGridSampler of the specified index or NULL if the index is invalid
    /// , the current grid is not a float grid or the VdbInfo wasn't loaded correctly.
    /// 
    /// @param[in] index
    ///     The index of the grid in the VDB file.
    /// @param[in] ignoreVdbTransform
    ///     The flag indicating if we will apply the world transform
    /// @returns if index < gridCount() and the expecting grid is a float grid then this returns
    ///     a pointer to a VdbGridSampler. Otherwise NULL.
    VdbGridSampler* sampler(
        const uint32_t index,
        const bool     ignoreVdbTransform = true);

    /// Destroys the single sampler if any
    void destroySampler();

    /// Convenience function to check whether a grid a) exists, b) is of a suitable type for the 
    /// channel specified. If not, then it will find one that is suitable. If there are none, then
    /// it will return NULL.
    ///
    /// @param[in] channelAttributeId
    ///     One of: A_VOLUME_ABSORPTION_ID,         float grid
    ///             A_VOLUME_EMISSION_ID,           float grid
    ///             A_VOLUME_SCATTER_ID,            float grid
    ///             A_VOLUME_VELOCITY_ID,           float3 grid
    ///             A_VOLUME_VELOCITY_ID_X,         float grid
    ///             A_VOLUME_VELOCITY_ID_Y or       float grid
    ///             A_VOLUME_VELOCITY_ID_Z.         float grid
    /// @param[in] gridName
    ///     Preferred grid name, perhaps as specified by the end-user. This grid name may be 
    ///     invalid, or specify a name that does not exist in this VDB.
    /// @returns 
    ///     If gridName specifies a grid that exists in this VDB, and it is of the correct type for
    ///     the channel specified in channelAttributeId, then the name will be returned unchanged. 
    ///     If not, the name of the first grid in the VDB that matches the correct type will be 
    ///     returned. In the case that there are none suitable, then this function will return
    ///     NULL.
    const char *const findGrid(
        const Octane::AttributeId channelAttributeId,
        const char *const         gridName) const;

private:

    /// The openvdb file name
    const char* const mFileName;
    /// The file stream. Will be NULL if the construction failed and this instance is in an invalid
    /// state.
    void *            mFileStream;
    /// The OpenVDB stream. Will be NULL if the construction failed and this instance is in an
    /// invalid state.
    void *            mVdbStream;
    /// the number of VdbGridInfo pointers we have in mGrids
    uint32_t          mGridCount;
    /// an array of pointers to VdbGridInfo's. Check valid() and mGridCount before accessing.
    VdbGridInfo       **mGrids;
    /// the grid index of the current sampler.
    uint32_t          mSamplerIndex;
    /// The single grid sampler instance pointer is NULL if there is no a single sampler.
    VdbGridSampler    *mSampler;
};



} // namespace Octane

#endif // _OCTANEVOLUME_H_
