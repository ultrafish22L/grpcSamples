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
class ApiNodeProxy;
class ApiNodeGraphProxy;
class ApiOutputColorSpaceInfoProxy;
class ApiSharedSurfaceProxy;


#include "apirender.h"


class Convert;

class GRPCSettings;

#include "apinodeclient.h"

/// Stores the information about one intersection along the picking ray.
struct GRPCPickIntersection : public GRPCBase
{
    ApiNodeProxy           mNode;
    unsigned int          mMaterialPinIx;
    float                 mDepth;
    OctaneVec::float_3    mPosition;
    OctaneVec::float_3    mGeometricNormal;
    OctaneVec::float_3    mSmoothedNormal;
    Octane::PrimitiveType mPrimitiveType;
    OctaneVec::float_3    mPrimitiveVertices[3];
    OctaneVec::float_3    mPositionOnPrimitive;
};

/// Proxy class for ApiRenderEngine
class ApiRenderEngineProxy : public GRPCBase
{
public:
    /// Sets the render target node that should be rendered. All scene information for rendering is
    /// retrieved via its input nodes. This will always render something using various fallback
    /// mechanisms even if the render target node has no connections to its input pins at all.
    ///
    /// Only if @ref targetNode is NULL, rendering is halted, all render data is released from GPU
    /// memory and the render threads start idling. I.e. restarting rendering with a valid render
    /// target will quicker from this state than after rendering was stopped completely via @ref
    /// stopRendering().
    ///
    /// To emulate the behaviour in the Standalone for previewing geometry or materials and textures
    /// you can also specify a geometry, material or texture node instead of a render target node
    /// (see below).
    ///
    /// NOTE: This will immediately update the render engine and restart rendering and not wait until
    ///       ApiChangeManager::update() has been called.
    ///
    /// @param  targetNode
    ///     In the regular use case you specify a render target node or NULL. If NULL is provided
    ///     rendering halts, render data is released from the GPUs and the render threads idle.
    ///
    ///     It can also be a linker node in which case the render target is fetched from the end of
    ///     the linker chain.
    ///
    ///     The other use cases is to do preview rendering of a geometry, material or texture node
    ///     as in the Octane Standalone. For that you specify a geometry, material or texture node
    ///     as @ref renderTarget. In those cases, the preview render target is used, which can be
    ///     queried via @ref ApiProjectManager::previewRenderTarget(). If you specify a material or
    ///     texture node, the material ball geometry will be rendered in combination with the
    ///     preview render target. The material ball geometry is the same as the one you can fetch
    ///     view @ref ApiProjectManager::materialBall().
    ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     FALSE if the specified node wasn't NULL or had an incorrect output type, i.e. its
    ///     output type was not PT_RENDERTARGET, PT_GEOMETRY, PT_MATERIAL or PT_TEXTURE.
    static bool setRenderTargetNode(
            ApiNodeProxy *   targetNode
            );

    /// Returns render target node that's currently being rendered (can be NULL).
    ///
    /// NOTE: If you set a geometry / material / texture node in @ref setRenderTargetNode(), then
    ///       the preview render target node will be returned
    ///       (@ref ApiProjectManager::previewRenderTarget()).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static ApiNodeProxy getRenderTargetNode();

    /// Returns the geometry root node that's currently being rendered (can be NULL).
    ///
    /// Usually that will be the node that is connecte to the geometry pin of the current render
    /// target node, with the following exceptions:
    ///
    /// - If you specified a geometry node in @ref setRenderTargetNode(), this node will be returned.
    /// - If you set a material or texture node in @ref setRenderTargetNode(), then the material
    ///   ball mesh node will be returned (@ref ApiProjectManager::materialBall()).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static ApiNodeProxy getRenderGeometryNode();

    /// Returns the camera node that's currently being rendered (can be NULL).
    ///
    /// Usually that will be the node that is connected to the camera pin of the current render
    /// target node, with the following exception:
    ///
    /// - If you set a material or texture node in @ref setRenderTargetNode(), then the material
    ///   ball camera node will be returned, since Octane Standalone uses a different camera for the
    ///   material ball scene than for the geometry preview.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static ApiNodeProxy getRenderCameraNode();

    /// Sets the render region. Both min and max will be clamped at the actual resolution, when the
    /// render data is passed to the render threads. The coordinate system is the same as for render
    /// results.
    ///
    /// @param[in]  active
    ///     If set to TRUE, the specified render region will be activated otherwise it will be
    ///     de-activated and the full image will be used as render region.
    /// @param[in]  regionMin
    ///     The minimum coordinate of the render region, excluding the feather border.
    /// @param[in]  regionMax
    ///     The maximum coordinate of the render region, excluding the feather border.
    /// @param[in]  featherWidth
    ///     The width of the additional feather border.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void setRenderRegion(
            const bool                                active,
            const OctaneVec::uint32_2                 regionMin,
            const OctaneVec::uint32_2                 regionMax,
            const uint32_t                            featherWidth
            );

    /// Fetches the current render region settings. The coordinate system is the same as for render
    /// results.
    ///
    /// @param[out]  active
    ///     If set to TRUE, the specified render region will be activated otherwise it will be
    ///     de-activated and the full image will be used as render region.
    /// @param[out]  regionMin
    ///     The currently set render region minimum (inclusive).
    /// @param[out]  regionMax
    ///     The currently set render region maximum (inclusive).
    /// @param[out]  featherWidth
    ///     The currently set width of the additional feather border.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void getRenderRegion(
            bool &                                    active,
            OctaneVec::uint32_2 &                     regionMin,
            OctaneVec::uint32_2 &                     regionMax,
            uint32_t &                                featherWidth
            );

    /// Sets parameters for asynchronous tonemapping. These are used for the intermediate results of
    /// the progressive rendering. The render flow using asynchronous minimizes the overhead of
    /// tonemapping and makes sure that the GPUs spend the maximum amount of time integrating.
    ///
    /// @param bufferType
    ///     The format of the result buffers. The initial value before this function is called is
    ///     TONEMAP_BUFFER_TYPE_LDR.
    /// @param cryptomatteFalseColor
    ///     Whether to apply false color to cryptomatte passes (if there are any) for viewing as an
    ///     image. If this is false, actual cryptomatte data (non-image data) will be produced for
    ///     cryptomatte passes and bufferType must be TONEMAP_BUFFER_TYPE_HDR_FLOAT. This should be
    ///     true if the result is going to be displayed on the screen or saved to a human-viewable
    ///     image file, and false if the result is going to be saved to a 32-bit EXR file to be used
    ///     for cryptomatte compositing. The initial value before this function is called is true.
    /// @param colorSpaceInfo
    ///     The color space info for the results. Must not be null. This pointer only needs to
    ///     remain valid for the duration of this call. The initial value before this function is
    ///     called is equivalent to the info created by
    ///     ApiOutputColorSpaceInfo::createUseImagerSettings(NAMED_COLOR_SPACE_SRGB).
    /// @param premultipliedAlphaType
    ///     The type of premultiplied alpha for the results to have. The initial value before this
    ///     function is called is PREMULTIPLIED_ALPHA_TYPE_LINEARIZED.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void setAsyncTonemapParams(
            Octane::TonemapBufferType                 bufferType,
            bool                                      cryptomatteFalseColor,
            const ApiOutputColorSpaceInfoProxy *      colorSpaceInfo,
            Octane::PremultipliedAlphaType            premultipliedAlphaType
            );

    /// Convenience overload that does the same thing as:
    ///
    ///     auto info = ApiOutputColorSpaceInfo::createKnownColorSpace(colorSpace, false);
    ///     setAsyncTonemapParams(..., info, ...);
    ///     info->destroy();
    ///
    /// @param colorSpace
    ///     Must not be NAMED_COLOR_SPACE_OCIO or NAMED_COLOR_SPACE_OTHER.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void setAsyncTonemapParams(
            Octane::TonemapBufferType                 bufferType,
            bool                                      cryptomatteFalseColor,
            Octane::NamedColorSpace                   colorSpace,
            Octane::PremultipliedAlphaType            premultipliedAlphaType
            );

    /// Returns the current asynchronous tonemap buffer type.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::TonemapBufferType asyncTonemapBufferType();

    /// Returns the current value of whether to apply false color to cryptomatte passes for
    /// asynchronous tonemapping.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool asyncTonemapCryptomatteFalseColor();

    /// Returns the current asynchronous tonemap output color space info.
    ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Will not be null. This pointer will remain valid until the next time a method is called
    ///     on this class. To use the information longer than that, clone() the result (and make
    ///     sure to destroy() the clone when done).
    static ApiOutputColorSpaceInfoProxy asyncTonemapOutputColorSpaceInfo();

    /// Returns the current asynchronous tonemap output color space. This depends on the type of the
    /// current asynchronous tonemap output color space info:
    ///     - Known color space -> that known color space.
    ///     - OCIO color space -> NAMED_COLOR_SPACE_OCIO.
    ///     - OCIO view -> NAMED_COLOR_SPACE_OCIO.
    ///     - Use imager settings -> NAMED_COLOR_SPACE_OTHER.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::NamedColorSpace asyncTonemapColorSpace();

    /// Returns the current asynchronous tonemap premultiplied alpha type.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::PremultipliedAlphaType asyncTonemapPremultipliedAlphaType();

    /// Sets the render passes that are tonemapped all the time. We TRY to have a tonemapped
    /// result available for each pass in this set on the image callback. You can get the
    /// result via grabRenderResult(). If you never use this function the only async tonemap pass
    /// is RENDER_PASS_BEAUTY.
    ///
    /// NOTE: To avoid confusion, there's a difference between enabled passes and
    /// async tonemap passes. The former are which we render behind the scene and the latter are
    /// the ones which we also tonemap immediately. This means that you can have immediately a
    /// result for the async tonemap passes. You don't get a result for async tonemap passes that
    /// aren't enabled in the node.
    ///
    /// WARNING: requesting more tonemap passes incurs a performance penalty. Ideally this
    /// functionality should only by used by plugins that composite render results real time.
    ///
    /// @param[in]  tonemapPasses
    ///     Set of tonemap passes.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE on success, FALSE on failure. This function will fail if the set is empty.
    static bool setAsyncTonemapRenderPasses(
            const Octane::ApiArray<Octane::RenderPassId> &   tonemapPasses
            );

    /// Returns the set of tonemap render passes.
    /// NOTE: The returned list must be freed with a call to @ref freeTonemapPasses().
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void asyncTonemapRenderPasses(
            Octane::ApiArray<Octane::RenderPassId> &   tonemapPasses
            );

    /// Returns the render AOVs and output AOVs that are enabled in the specified render target
    /// node as a set of render pass IDs.
    /// NOTE: The returned list must be freed with a call to @ref freeTonemapPasses().
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void getEnabledAovs(
            const ApiNodeProxy *const                 renderTargetNode,
            std::vector<Octane::RenderPassId> &       aovIds
            );

    /// Frees the set of tonemap passes returned by @ref asyncTonemapRenderPasses() and @ref
    /// getEnabledAovs().
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void freeTonemapPasses(
            Octane::ApiArray<Octane::RenderPassId> &   tonemapPasses
            );

    /// Returns the display pass in the current render. The display pass is the first async
    /// tonemap pass that is actually being rendered or the main pass if the intersection
    /// between the async tonemap passes and the enabled render passes is the empty set.
    ///
    /// This is probably only relevant for the Standalone.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::RenderPassId displayRenderPassId();

    /// Sets the sub-sampling mode.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void setSubSampleMode(
            const Octane::SubSampleMode   mode
            );

    /// Returns the current sub-sampling mode.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::SubSampleMode getSubSampleMode();

    /// Sets the current clay render mode.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void setClayMode(
            const Octane::ClayMode   mode
            );

    /// Returns the current clay mode.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::ClayMode clayMode();

    /// Returns the current fps.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static float fps();

    /// Sets the current fps.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void setFps(
            const float   fps
            );

    /// Returns TRUE if the render engine is currently running a compilation job.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool isCompiling();

    /// Deprecated, this returns the same value as hasPendingRenderData()
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool isCompressingTextures();

    /// Returns TRUE if there is render data that has not finished compiling.
    /// You may receive render results while this is true, the associated statistics
    /// will have mHasPendingUpdates set to true.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool hasPendingRenderData();

    /// Returns the change level after the last update. There are currently 5 methods that can
    /// change a change level:
    ///     ApiProjectManager::resetProject()
    ///     / ApiProjectManager::loadProject()
    ///     / ApiRenderEngine::stopRendering():
    ///         will reset render target -> change level will be 0
    ///     ApiRenderEngine::setRenderTargetNode():
    ///         immediately a new render target node -> the change level will be incremented
    ///     ApiChangeManager::update():
    ///         if some changes accumulated the change level be incremented
    /// You can check if the latest data is renderable via lastUpdateWasRenderable().
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::CLevelT getCurrentChangeLevel();

    /// Returns the change level of the last rendered image, which can be lower than
    /// getCurrentChangeLevel(). This way you can quickly check if the last rendered image
    /// already includes the latest changes.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::CLevelT getRenderImageChangeLevel();

    /// Returns the change level of the last time the rendering was restarted. This can be lower
    /// than the change level of the last rendered image if the post processing or tone mapping
    /// settings change
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::CLevelT getRenderRestartedChangeLevel();

    /// Registers an asynchronous update callback. When a callback is registered, updates to the
    /// render engine will not block. This callback is called when the render engine was updated.
    /// This means that the change level only increments after the callback.
    /// Setting the callback to NULL will make updates synchronous again.
    ///
    /// This callback is called on a different thread than the main thread so the plugin must
    /// take care of all the thread synchronization.
    ///
    /// @param[in]  callback
    ///     Function called every time an update is finished.
    /// @param[in]  userData
    ///     Opaque user data pointer passed as an argument to the callback.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void setAsyncUpdateCallback(
            Octane::ApiRenderEngine::AsyncUpdateCallbackT callback,
            void *                                    userData
            );

    /// Checks if updates are done asynchronously.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool updatesAreAsync();

    /// @deprecated Use the callback mechanism instead.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool isImageReady();

    static void resetImageReady();

    static bool isRenderFailure();

    static void resetRenderFailure();

    /// Registers a callback with the render target that is called when a tile was blended in one
    /// of the two render films and the render statistics did not change.
    ///
    /// @param[in]  callback
    ///     User provided callback funcion or NULL to unset the callback.
    /// @param[in]  userData
    ///     Opaque pointer to userdata. This pointer is not touched by Octane. Can be a NULL pointer.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void setOnTileBlendedCallback(
            Octane::ApiRenderEngine::OnTileBlendedCallbackT callback,
            void *                                    userData
            );

    /// Registers a callback with the render target that is called when the statistics in the
    /// render target changed.
    ///
    /// @param[in]  callback
    ///     User provided callback funcion or NULL to unset the callback.
    /// @param[in]  userData
    ///     Opaque pointer to userdata. This pointer is not touched by Octane. Can be a NULL pointer.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void setOnNewStatisticsCallback(
            Octane::ApiRenderEngine::OnNewStatisticsCallbackT callback,
            void *                                    userData
            );

    /// Registers a callback with the render target that is called when a new tonemapped result
    /// is available.
    ///
    /// @param[in]  callback
    ///     User provided callback funcion or NULL to unset the callback.
    /// @param[in]  userData
    ///     Opaque pointer to userdata. This pointer is not touched by Octane. Can be a NULL pointer.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void setOnNewImageCallback(
            Octane::ApiRenderEngine::OnNewImageCallbackT callback,
            void *                                    userData
            );

    /// Registers a callback with the render target that is called when OCIO errors are encountered
    /// when updating render data.
    ///
    /// @param callback
    ///     User provided callback function or null to unset the callback.
    /// @param userData
    ///     Opaque pointer to user data. This pointer is not touched by Octane. Can be null.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void setOnOcioErrorCallback(
            Octane::ApiRenderEngine::OnOcioErrorCallbackT callback,
            void *                                    userData
            );

    /// Registers a callback with the render target that is called when rendering fails.
    ///
    /// @param[in]  callback
    ///     User provided callback function or NULL to unset the callback.
    /// @param[in]  userData
    ///     Opaque pointer to userdata. This pointer is not touched by
    ///     Octane. Can be a NULL pointer.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void setOnRenderFailureCallback(
            Octane::ApiRenderEngine::OnRenderFailureCallbackT callback,
            void *                                    userData
            );

    /// Forces render engine callbacks to be made in render threads instead of the main message
    /// thread. Some plugins may want to do this, because in some circumstances messages may not get
    /// processed.
    ///
    /// @param[in]
    ///     If set to TRUE, the callbacks will be executed immediately in whatever
    ///     thread they occur. If set to FALSE, the callbacks will be executed in
    ///     the main thread (default).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void setForceCallbacksInRenderThreads(
            const bool   enabled
            );

    /// Grabs the latest render result in the passed in array. A result has several images, 1 for
    /// each asynchronously tonemapped render pass. These results are still owned by Octane and
    /// valid until releaseRenderResult() is called. The plugin must try to release the result
    /// as soon as possible.
    ///
    /// We TRY to return an image for each render pass that was set via
    /// setAsyncTonemapRenderPasses() but it can be that there are fewer images available than
    /// initially requested. After some time the engine should have all results available.
    ///
    /// @param[out]  renderImages
    ///     Array of render images - 1 for each tonemapped render pass. These must be freed with
    ///     freeRenderImages().
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if there is a list of non-empty render results available. If this function
    ///     returns FALSE you don't have to call releaseRenderResult().
    static bool grabRenderResult(
            std::vector<Octane::ApiRenderImage> &   renderImages
            );

    /// Releases the results again so that the engine can reuse it.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void releaseRenderResult();

    /// Runs a synchronous tonemap and returns the result. This function is fairly invasive and
    /// blocks the render threads until all results have been collected, i.e. adds a lot of
    /// overhead.
    ///
    /// @param passes
    ///     The render passes for which we like a tonemapped result. All the render passes in
    ///     the passed in array MUST be enabled! For the old behaviour use RENDER_PASS_BEAUTY
    ///     which is always enabled.
    /// @param passesLength
    ///     The length of the passes array.
    /// @param bufferType
    ///     The format of the result buffers.
    /// @param cryptomatteFalseColor
    ///     Whether to apply false color to cryptomatte passes (if there are any) for viewing as an
    ///     image. If this is false, actual cryptomatte data (non-image data) will be produced for
    ///     cryptomatte passes and bufferType must be TONEMAP_BUFFER_TYPE_HDR_FLOAT. This should be
    ///     true if the result is going to be displayed on the screen or saved to a human-viewable
    ///     image file, and false if the result is going to be saved to a 32-bit EXR file to be used
    ///     for cryptomatte compositing.
    /// @param colorSpaceInfo
    ///     The color space info for the results. Must not be null.
    /// @param premultipliedAlphaType
    ///     The type of premultiplied alpha for the results to have.
    /// @param[out] results
    ///     The result images will be stored here if the function returns TRUE. These images must
    ///     be freed via freeRenderImages().
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if the result is not empty and FALSE if it is.
    static bool synchronousTonemap(
            const Octane::RenderPassId *              passes,
            size_t                                    passesLength,
            Octane::TonemapBufferType                 bufferType,
            bool                                      cryptomatteFalseColor,
            const ApiOutputColorSpaceInfoProxy *      colorSpaceInfo,
            Octane::PremultipliedAlphaType            premultipliedAlphaType,
            std::vector<Octane::ApiRenderImage> & results
            );

    /// Convenience overload that does the same thing as:
    ///
    ///     auto info = ApiOutputColorSpaceInfo::createKnownColorSpace(colorSpace, false);
    ///     auto result = synchronousTonemap(..., info, ...);
    ///     info->destroy();
    ///     return result;
    ///
    /// @param colorSpace
    ///     Must not be NAMED_COLOR_SPACE_OCIO or NAMED_COLOR_SPACE_OTHER.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool synchronousTonemap(
            const Octane::RenderPassId *              passes,
            size_t                                    passesLength,
            Octane::TonemapBufferType                 bufferType,
            bool                                      cryptomatteFalseColor,
            Octane::NamedColorSpace                   colorSpace,
            Octane::PremultipliedAlphaType            premultipliedAlphaType,
            std::vector<Octane::ApiRenderImage> & results
            );

    /// Runs a synchronous tonemap for all render passes that are already started by the render
    /// engine and returns the results. This is EXTREMELY invasive and can block for a VERY long
    /// time. The preferred method is to use the results returned by incremental rendering and
    /// leave the other passes alone (this is the same behaviour as in the Standalone where only a
    /// single pass is displayed to the user although most passes run in parallel).
    ///
    /// Render passes that aren't started yet or are not enabled are not in the result.
    ///
    /// @param bufferType
    ///     The format of the result buffers.
    /// @param cryptomatteFalseColor
    ///     Whether to apply false color to cryptomatte passes (if there are any) for viewing as an
    ///     image. If this is false, actual cryptomatte data (non-image data) will be produced for
    ///     cryptomatte passes and bufferType must be TONEMAP_BUFFER_TYPE_HDR_FLOAT. This should be
    ///     true if the result is going to be displayed on the screen or saved to a human-viewable
    ///     image file, and false if the result is going to be saved to a 32-bit EXR file to be used
    ///     for cryptomatte compositing.
    /// @param colorSpaceInfo
    ///     The output color space info to use. Must not be null.
    /// @param premultipliedAlphaType
    ///     The type of premultiplied alpha for the results to have.
    /// @param[out] results
    ///     Array of render results. This array is allocated by the API and should
    ///     be freed by calling freeRenderImages().
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if we came back with results, FALSE otherwise.
    static bool synchronousTonemapAllRenderPasses(
            Octane::TonemapBufferType                 bufferType,
            bool                                      cryptomatteFalseColor,
            const ApiOutputColorSpaceInfoProxy *      colorSpaceInfo,
            Octane::PremultipliedAlphaType            premultipliedAlphaType,
            std::vector<Octane::ApiRenderImage> & results
            );

    /// Convenience overload that does the same thing as:
    ///
    ///     auto info = ApiOutputColorSpaceInfo::createKnownColorSpace(colorSpace, false);
    ///     auto result = synchronousTonemapAllRenderPasses(..., info, ...);
    ///     info->destroy();
    ///     return result;
    ///
    /// @param colorSpace
    ///     Must not be NAMED_COLOR_SPACE_OCIO or NAMED_COLOR_SPACE_OTHER.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool synchronousTonemapAllRenderPasses(
            Octane::TonemapBufferType                 bufferType,
            bool                                      cryptomatteFalseColor,
            Octane::NamedColorSpace                   colorSpace,
            Octane::PremultipliedAlphaType            premultipliedAlphaType,
            std::vector<Octane::ApiRenderImage> & results
            );

    /// Returns the statistics for the current render progress. This may be a bit ahead of the
    /// values returned by getRenderResultStatistics.
    ///
    /// @param[out] statistics
    ///     statistics fetched from the latest render progress
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void getRenderStatistics(
            Octane::RenderResultStatistics &   statistics
            );

    /// Returns the statistics for the render results. When no image was rendered yet, the
    /// statistics struct is all zeros.
    ///
    /// @param[out] statistics
    ///     statistics fetched from the latest asynchronous tomemap result
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void getRenderResultStatistics(
            Octane::RenderResultStatistics &   statistics
            );

    /// Saves the current result of the render target to the specified file.
    ///
    /// @param renderPassId
    ///     The render pass to save out. This render pass MUST be enabled.
    /// @param fullPath
    ///     The full path to the file name where the image will be stored. When the filename in the
    ///     path doesn't have the correct extension, we'll add it.
    /// @param imageSaveFormat
    ///     The format of the image file that should be saved.
    /// @param colorSpaceInfo
    ///     The output color space info to use. Must not be null.
    /// @param premultipliedAlphaType
    ///     The type of premultiplied alpha for the image file to have. This should be
    ///     PREMULTIPLIED_ALPHA_TYPE_NONE when saving a PNG file, because PNG files are never
    ///     premultiplied according to the PNG specification.
    /// @param exrCompressionType
    ///     Compression type of the OpenEXR file. Ignored if imageSaveFormat implies PNG.
    /// @param exrCompressionLevel
    ///     Compression factor if using OpenEXR with DWA compression. Default value is 45,
    ///     usable range is 0 (highest quality) to about 2000 (high compression).
    /// @param asynchronous
    ///     If true, then the image will be saved on a background thread, and this call always
    ///     immediately returns true.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if the current result was saved successfully and FALSE if not.
    static bool saveImage(
            Octane::RenderPassId                      renderPassId,
            const char *                              fullPath,
            Octane::ImageSaveFormat                   imageSaveFormat,
            const ApiOutputColorSpaceInfoProxy *      colorSpaceInfo,
            Octane::PremultipliedAlphaType            premultipliedAlphaType,
            Octane::ExrCompressionType                exrCompressionType,
            float                                     exrCompressionLevel,
            bool                                      asynchronous
            );

    /// Convenience overload that does the same thing as:
    ///
    ///     auto info = ApiOutputColorSpaceInfo::createKnownColorSpace(colorSpace, false);
    ///     auto result = saveImage(..., info, ...);
    ///     info->destroy();
    ///     return result;
    ///
    /// @param colorSpace
    ///     Must not be NAMED_COLOR_SPACE_OCIO or NAMED_COLOR_SPACE_OTHER.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool saveImage(
            Octane::RenderPassId                      renderPassId,
            const char *                              fullPath,
            Octane::ImageSaveFormat                   imageSaveFormat,
            Octane::NamedColorSpace                   colorSpace,
            Octane::PremultipliedAlphaType            premultipliedAlphaType,
            Octane::ExrCompressionType                exrCompressionType,
            float                                     exrCompressionLevel,
            bool                                      asynchronous
            );

    /// Saves the current result of the render target to the specified file using provided export settings
    ///
    /// @param renderPassId
    ///     The render pass to save out. This render pass MUST be enabled.
    /// @param fullPath
    ///     The full path to the file name where the image will be stored
    /// @param colorSpaceInfo
    ///     The output color space info to use. Must not be null.
    /// @param exportSettings
    ///     The settings that describe the output format and other parameters like compression or quality
    /// @param asynchronous
    ///     If true, then the image will be saved on a background thread, and this call always
    ///     immediately returns true.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if the current result was saved successfully and FALSE if not.
    static bool saveImage(
            Octane::RenderPassId                      renderPassId,
            const char *                              fullPath,
            const ApiOutputColorSpaceInfoProxy *      colorSpaceInfo,
            const Octane::ImageExportSettings &       exportSettings,
            bool                                      asynchronous
            );

    /// Saves the render passes as discrete files in the provided output directory.
    ///
    /// @param outputDirectory
    ///     The full path to the output directory.
    /// @param passesToExport
    ///     Array with an export object for each pass to export. Passes that aren't enabled or
    ///     haven't been started yet by the render engine are skipped. Each image will receive the
    ///     filename as defined in the export object. If the filename doesn't have the corrrect
    ///     extension, we'll add it.
    /// @param passesToExportLength
    ///     Length of the passesToExport array.
    /// @param imageSaveFormat
    ///     The format of the image files that should be saved.
    /// @param colorSpaceInfo
    ///     The output color space info to use. Must not be null.
    /// @param premultipliedAlphaType
    ///     The type of premultiplied alpha for the image files to have. This should be
    ///     PREMULTIPLIED_ALPHA_TYPE_NONE when saving PNG files, because PNG files are never
    ///     premultiplied according to the PNG specification.
    /// @param exrCompressionType
    ///     Compression type of the OpenEXR file. Ignored if imageSaveFormat implies PNG.
    /// @param exrCompressionLevel
    ///     Compression factor if using OpenEXR with DWA compression. Default value is 45,
    ///     usable range is 0 (highest quality) to about 2000 (high compression).
    /// @param metadata
    ///     Metadata for the file header. This is an array of consecutive key/value pairs.
    ///     Can be NULL if you don't want any metadata in the file header.
    /// @param metadataLength
    ///     Length of the meta data array.
    /// @param asynchronous
    ///     If TRUE, then the image will be saved on a background thread, and this call returns TRUE
    ///     immediately.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if all the passes could be saved successfully, FALSE if not.
    static bool saveRenderPasses(
            const char *                              outputDirectory,
            const Octane::RenderPassExport *          passesToExport,
            size_t                                    passesToExportLength,
            Octane::ImageSaveFormat                   imageSaveFormat,
            const ApiOutputColorSpaceInfoProxy *      colorSpaceInfo,
            Octane::PremultipliedAlphaType            premultipliedAlphaType,
            Octane::ExrCompressionType                exrCompressionType,
            float                                     exrCompressionLevel,
            const char *const *                       metadata,
            size_t                                    metadataLength,
            bool                                      asynchronous
            );

    /// Convenience overload that does the same thing as:
    ///
    ///     auto info = ApiOutputColorSpaceInfo::createKnownColorSpace(colorSpace, false);
    ///     auto result = saveRenderPasses(..., info, ...);
    ///     info->destroy();
    ///     return result;
    ///
    /// @param colorSpace
    ///     Must not be NAMED_COLOR_SPACE_OCIO or NAMED_COLOR_SPACE_OTHER.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool saveRenderPasses(
            const char *                              outputDirectory,
            const Octane::RenderPassExport *          passesToExport,
            size_t                                    passesToExportLength,
            Octane::ImageSaveFormat                   imageSaveFormat,
            Octane::NamedColorSpace                   colorSpace,
            Octane::PremultipliedAlphaType            premultipliedAlphaType,
            Octane::ExrCompressionType                exrCompressionType,
            float                                     exrCompressionLevel,
            const char *const *                       metadata,
            size_t                                    metadataLength,
            bool                                      asynchronous
            );

    /// Saves the render passes as discrete files in the provided output directory.
    ///
    /// @param outputDirectory
    ///     The full path to the output directory.
    /// @param passesToExport
    ///     Array with an export object for each pass to export. Passes that aren't enabled or
    ///     haven't been started yet by the render engine are skipped. Each image will receive the
    ///     filename as defined in the export object. If the filename doesn't have the corrrect
    ///     extension, we'll add it.
    /// @param passesToExportLength
    ///     Length of the passesToExport array.
    /// @param colorSpaceInfo
    ///     The output color space info to use. Must not be null.
    /// @param exportSettings
    ///     The settings that describe the output format and other parameters like compression or
    ///     quality.
    /// @param metadata
    ///     Metadata for the file header. This is an array of consecutive key/value pairs.
    ///     Can be NULL if you don't want any metadata in the file header.
    /// @param metadataLength
    ///     Length of the meta data array.
    /// @param asynchronous
    ///     If TRUE, then the image will be saved on a background thread, and this call returns TRUE
    ///     immediately.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if all the passes could be saved successfully, FALSE if not.
    static bool saveRenderPasses(
            const char *                              outputDirectory,
            const Octane::RenderPassExport *          passesToExport,
            size_t                                    passesToExportLength,
            const ApiOutputColorSpaceInfoProxy *      colorSpaceInfo,
            const Octane::ImageExportSettings &       exportSettings,
            const char *const *                       metadata,
            size_t                                    metadataLength,
            bool                                      asynchronous
            );

    /// Saves the render passes in a multi layer EXR file.
    ///
    /// @param fullPath
    ///     The full path to the file name where the image will be stored.
    /// @param passesToExport
    ///     Array with an export object for each pass to export. Passes that aren't enabled or
    ///     haven't been started yet by the render engine are skipped in the output file.
    /// @param passesToExportLength
    ///     Length of the passesToExport array.
    /// @param useHalf
    ///     Whether to save a 16-bit EXR instead of 32-bit.
    /// @param colorSpaceInfo
    ///     The output color space info to use. Must not be null.
    /// @param premultipliedAlpha
    ///     Whether the image should have premultiplied alpha.
    /// @param compressionType
    ///     Compression type of the OpenEXR file.
    /// @param exrCompressionLevel
    ///     Compression factor if using OpenEXR with DWA compression. Default value is 45,
    ///     usable range is 0 (highest quality) to about 2000 (high compression).
    /// @param metadata
    ///     Meta data for the file header. This is an array of consecutive key/value pairs.
    ///     Can be NULL if you don't want any metadata in the file header.
    /// @param metadataLength
    ///     Length of the meta data array.
    /// @param asynchronous
    ///     If TRUE, then the image will be saved on a background thread, and this call returns TRUE
    ///     immediately.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if the current result was saved successfully and FALSE if not.
    static bool saveRenderPassesMultiExr(
            const char *                              fullPath,
            const Octane::RenderPassExport *          passesToExport,
            const size_t                              passesToExportLength,
            bool                                      useHalf,
            const ApiOutputColorSpaceInfoProxy *      colorSpaceInfo,
            bool                                      premultipliedAlpha,
            const Octane::ExrCompressionType          compressionType,
            const float                               exrCompressionLevel,
            const char *const *                       metadata,
            const size_t                              metadataLength,
            const bool                                asynchronous
            );

    /// Convenience overload that does the same thing as:
    ///
    ///     auto info = ApiOutputColorSpaceInfo::createKnownColorSpace(colorSpace, false);
    ///     auto result = saveRenderPassesMultiExr(..., info, ...);
    ///     info->destroy();
    ///     return result;
    ///
    /// @param colorSpace
    ///     Must not be NAMED_COLOR_SPACE_OCIO or NAMED_COLOR_SPACE_OTHER.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool saveRenderPassesMultiExr(
            const char *                              fullPath,
            const Octane::RenderPassExport *          passesToExport,
            const size_t                              passesToExportLength,
            bool                                      useHalf,
            Octane::NamedColorSpace                   colorSpace,
            bool                                      premultipliedAlpha,
            const Octane::ExrCompressionType          compressionType,
            const float                               exrCompressionLevel,
            const char *const *                       metadata,
            const size_t                              metadataLength,
            const bool                                asynchronous
            );

    /// Saves the render passes in a deep image EXR file. This only succeeds if deep image is
    /// enabled in the kernel settings.
    ///
    /// @param fullPath
    ///     The full path to the file name where the image will be stored.
    /// @param passesToExport
    ///     Array with an export object for each pass to export. Passes that aren't enabled, haven't
    ///     been started yet by the render engine or don't support deep image output are skipped in
    ///     the output file. If deep image render passes is not enabled in the kernel settings, only
    ///     the beauty pass (RENDER_PASS_BEAUTY) can be exported. If none of the given passes are
    ///     available, this call fails and returns false.
    /// @param passesToExportLength
    ///     Length of the passesToExport array.
    /// @param colorSpace
    ///     The output color space to use. Must not be NAMED_COLOR_SPACE_SRGB,
    ///     NAMED_COLOR_SPACE_OCIO or NAMED_COLOR_SPACE_OTHER.
    /// @param compressionType
    ///     Compression type of the OpenEXR file.
    /// @param metadata
    ///     Meta data for the file header. This is an array of consecutive key/value pairs.
    ///     Can be NULL if you don't want any metadata in the file header.
    /// @param metadataLength
    ///     Length of the meta data array.
    /// @param asynchronous
    ///     If TRUE, then the image will be saved on a background thread, and this call returns TRUE
    ///     immediately.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if the current result was saved successfully and FALSE if not.
    static bool saveRenderPassesDeepExr(
            const char *                              fullPath,
            const Octane::RenderPassExport *          passesToExport,
            const size_t                              passesToExportLength,
            Octane::NamedColorSpace                   colorSpace,
            const Octane::ExrCompressionType          compressionType,
            const char *const *                       metadata,
            const size_t                              metadataLength,
            const bool                                asynchronous
            );

    /// Checks whether the provided render target both supports and has enabled deep pixel rendering.
    /// This is equivalent to checking whether its P_KERNEL pin has a P_DEEP_ENABLE pin set to TRUE.
    ///
    /// @param[in]  renderTargetNode
    ///     The render target node which settings will be returned.
    /// @param[out]  maxDepthSamples
    ///     It will be set to the maximum number of depth samples as specified in the kernel's
    ///     P_MAX_DEPTH_SAMPLES if deep pixel is enabled or zero otherwise.
    /// @param[out]  samplesBeforeCanSave
    ///     It will be set to the minimum number of samples required before the deep image can be
    ///     saved if deep pixel is enabled or zero otherwise.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool deepImageEnabled(
            const ApiNodeProxy *                      renderTargetNode,
            uint32_t &                                maxDepthSamples,
            uint32_t &                                samplesBeforeCanSave
            );

    /// Checks if deep image rendering is enabled for the current render task.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool deepImageEnabled();

    /// Checks if deep image rendering and deep render AOVs are enabled for the current render task.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool deepPassesEnabled();

    /// Checks if we can save a deep image. Impossible when deep image rendering is disabled or when
    /// we have not collected enough "seed" samples/px.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool canSaveDeepImage();

    /// Saves the current render as a deep image. The only supported file format for deep images
    /// is OpenEXR.
    ///
    /// The OpenEXR standard defines that OpenEXR images have pre-multiplied alpha so all the values
    /// saved out in the deep image are pre-multiplied.
    ///
    /// @param fullPath
    ///     Absolute path to the destination file.
    /// @param colorSpace
    ///     The output color space to use. Must not be NAMED_COLOR_SPACE_SRGB,
    ///     NAMED_COLOR_SPACE_OCIO or NAMED_COLOR_SPACE_OTHER.
    /// @param saveAsync
    ///     TRUE to save the image on a background thread.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE on if the image was saved sucessfully, FALSE otherwise.
    static bool saveDeepImage(
            const char *                              fullPath,
            Octane::NamedColorSpace                   colorSpace,
            const bool                                saveAsync
            );

    /// Saves the current render state plus a reference to the project file. Since the render data
    /// may come from either a Standalone project or some 3D host project, the interface is kind of
    /// generic. All the custom fields can be filled with arbitrary data. The reason why they are
    /// separate fields is because it's expected that the plugins will need to store similar data.
    ///
    /// @note States stored with this version can only be loaded by Octane instances of the same
    ///       version.
    /// @note This function is not supported by all SDK flavours
    ///
    /// @param[in]  renderStateFileName
    ///     The file name of the render state file.
    /// @param[in]  customProjectFileName
    ///     The file name of the project that provided the render data that is currently being
    ///     rendered. (can be empty but must not be NULL)
    /// @param[in]  customProjectTime
    ///     The current time in the project, which may be needed to restore the state in an animated
    ///     project.
    /// @param[in]  customVersion
    ///     The version of the project in case there is additional versioning on the plugin side.
    /// @param[in]  customData
    ///     A pointer to some custom data that will be stored in the render state file. It can be
    ///     used by plugins to store additional information that is required to restore the
    ///     host scene. (can be NULL)
    /// @param[in]  customDataSize
    ///     The size of the custom data. (can be zero)
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if the render state was saved successfully, FALSE if not in which case there
    ///     should have been additional error messages on the log.
    static bool saveRenderState(
            const char *const                         renderStateFileName,
            const char *const                         customProjectFileName,
            const float                               customProjectTime,
            const uint32_t                            customVersion,
            const void *const                         customData,
            const uint32_t                            customDataSize
            );

    /// Loads an Octane render state file. This will block the render target until the loading has
    /// been finished and only then the function returns. If the loading failed, rendering will be
    /// stopped and the render target reset.
    ///
    /// @note Only render states that have been stored with the same version can be loaded.
    ///
    /// @note If any region rendering was enabled, it will be disabled afterwards.
    ///
    /// @note This function is not supported by all SDK flavours
    ///
    /// @param[in]  renderStateFileName
    ///     The name of the render state file.
    /// @param[in]  loadProjectCallback
    ///     The callback that will restore the project and return the render target node that should
    ///     be rendered. (must not be NULL)
    /// @param[in]  privateCallbackData
    ///     Private data that will be passed to the callback function. (can be NULL)
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if the render state and its referenced project have been loaded correctly, FALSE if
    ///     not. There should be additional information in the log.
    static bool loadRenderState(
            const char *const                         renderStateFileName,
            GRPCLoadRenderStateProjectT              loadProjectCallback,
            void *const                               privateCallbackData
            );

    /// Renders a preview image of a texture / material node. The rendering is done synchronously
    /// and the function will block until the material has been rendered.
    ///
    /// @param[in]  node
    ///     Pointer to the material or texture node that should be rendered (must not be NULL).
    /// @param[in]  sizeX
    ///     The width in pixels the preview image should have.
    /// @param[in]  sizeY
    ///     The height in pixels the preview image should have.
    /// @param[in]  maxSamples
    ///     The maximum samples per pixel that should be rendered in the preview.
    /// @param[in]  objectSize
    ///     The size of the object that will have the material in the preview image (useful for
    ///     procedural nodes).
    /// @param[in]  type
    ///     The type of the object that should rendered.
    /// @param[out]  buffer
    ///     Pointer to the RGBA buffer where the result will be stored (must not be NULL).
    ///     Its capacity must be >= 4*sizeX*sizeY bytes. The channel order is red, green, blue, alpha.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if the preview was rendered successfully, FALSE if not.
    static bool previewMaterial(
            const ApiNodeProxy *                      node,
            const unsigned int                        sizeX,
            const unsigned int                        sizeY,
            const unsigned int                        maxSamples,
            const float                               objectSize,
            const Octane::PreviewType                 type,
            unsigned char *                           buffer
            );

    /// Same as above but return HDR buffer
    ///
    /// @param[in]  node
    ///     Pointer to the material or texture node that should be rendered (must not be NULL).
    /// @param[in]  sizeX
    ///     The width in pixels the preview image should have.
    /// @param[in]  sizeY
    ///     The height in pixels the preview image should have.
    /// @param[in]  maxSamples
    ///     The maximum samples per pixel that should be rendered in the preview.
    /// @param[in]  objectSize
    ///     The size of the object that will have the material in the preview image (useful for
    ///     procedural nodes).
    /// @param[in]  type
    ///     The type of the object that should rendered.
    /// @param[out]  buffer
    ///     Pointer to the RGBA buffer where the result will be stored (must not be NULL).
    ///     Its capacity must be 16*sizeX*sizeY bytes. The channel order is red, green, blue, alpha.
    /// @param[out]  linear
    ///     if TRUE the values will be linear and if FALSE  gamma correction for a gamma of 2.2
    ///     will be applied to the result values.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if the preview was rendered successfully, FALSE if not.
    static bool previewMaterialHdr(
            const ApiNodeProxy *const                 node,
            const uint32_t                            sizeX,
            const uint32_t                            sizeY,
            const uint32_t                            maxSamples,
            const float                               objectSize,
            const Octane::PreviewType                 type,
            float *const                              buffer,
            const bool                                linear
            );

    /// Preview a material or texture node
    ///
    /// @param node
    ///     Pointer to the material or texture node that should be rendered (must not be NULL).
    /// @param size
    ///     The width and height in pixels for the returned image
    /// @param crop
    ///     The cropping to apply to the film plane. Given as {X, Y, width, height}, and as
    ///     proportion of the entire image size. {0, 0, 1, 1} will render the entire image.
    ///     (0, 0) is the top left corner of the image.
    /// @param maxSamples
    ///     The maximum samples per pixel that should be rendered in the preview.
    /// @param objectSize
    ///     The size in meters of the object that will have the material in the preview image
    ///     (useful for procedural nodes).
    /// @param type
    ///     The type of the object that should rendered.
    /// @param bufferType
    ///     The format of the result buffer.
    /// @param colorSpace
    ///     The output color space. Must not be NAMED_COLOR_SPACE_OCIO or NAMED_COLOR_SPACE_OTHER.
    /// @param[out]  buffer
    ///     Pointer to the RGBA buffer where the result will be stored (must not be NULL).
    ///     The topmost line is stored first (Y down).
    ///     The channel order is red, green, blue, alpha. The size of the buffer is given by
    ///     (isHDR ? 16 : 4) * size.x * size.y
    ///     For HDR images the buffer must be aligned to 4 bytes.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if the preview was rendered successfully, FALSE if not.
    static bool previewMaterial(
            const ApiNodeProxy *const                 node,
            const OctaneVec::uint32_2                 size,
            const OctaneVec::float_4                  crop,
            const uint32_t                            maxSamples,
            const float                               objectSize,
            const Octane::PreviewType                 type,
            Octane::TonemapBufferType                 bufferType,
            Octane::NamedColorSpace                   colorSpace,
            void *const                               buffer
            );

    /// Returns the overall memory usage of a device.
    ///
    /// @param[in] deviceIx
    ///     THe device id
    /// @param[out]  memUsage
    ///     Returns the memory usage of the device for the current scene. Returns all zero memory usage,
    /// If rendering has not started or the device not used of rendering.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void getMemoryUsage(
            const uint32_t                            deviceIx,
            Octane::ApiDeviceMemoryUsage &            memUsage
            );

    /// Returns memory usage statistics for a device
    ///
    /// @param[in] deviceIx
    ///     The device id
    /// @param[in] memoryLocation
    ///     The location of the memory
    /// @param[out]  resourceStats
    ///     Returns the resource statistics of the device for the current scene. Returns all zero resource
    ///     statistics, If rendering has not started or the device not used of rendering.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void getResourceStatistics(
            const unsigned int                        deviceIx,
            const Octane::MemoryLocation              memoryLocation,
            Octane::ApiDeviceResourceStatistics &     resourceStats
            );

    /// Returns the geometry statistics of the current scene. Returns all zero stats if rendering
    /// has not started.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void getGeometryStatistics(
            Octane::ApiGeometryStatistics &   stats
            );

    /// Returns the texture usage. Returns all zero stats if rendering
    /// has not started.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void getTexturesStatistics(
            Octane::ApiTextureStatistics &   textureStats
            );

    /// If the currently rendered scene contains geometry, its bounding box is stored in the
    /// provided vectors and TRUE is returned.
    ///
    /// If the scene contains no geometry or we are not rendering, FALSE is returned and the
    /// provided vectors are not changed.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool getSceneBounds(
            Octane::float_3 &                         bboxMin,
            Octane::float_3 &                         bboxMax
            );

    /// Returns the number of render devices (GPUs) in this machine.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static unsigned int getDeviceCount();

    /// Returns the compute model of the device.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static int getDeviceComputeModel(
            const uint32_t   index
            );

    /// Returns the name of the device
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static std::string getDeviceName(
            const uint32_t   index
            );

    /// Returns TRUE if the device with the provided index is supported by Octane, i.e. can render,
    /// tone-map and/or de-noise.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool isSupportedDevice(
            const uint32_t   index
            );

    /// Returns TRUE if the device with the provided index can be used for rendering.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool deviceCanRender(
            const uint32_t   index
            );

    /// Returns TRUE if the device with the provided index can be used for denoising.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool deviceCanDenoise(
            const uint32_t   index
            );

    /// Returns TRUE if the device with the provided index supports hardware ray-tracing.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool deviceSupportsHardwareRayTracing(
            const uint32_t   index
            );

    /// Returns details of the shared surface capabilities of the device with the provided index.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::ApiDeviceSharedSurfaceInfo deviceSharedSurfaceInfo(
            uint32_t   index
            );

    /// Returns an array of available peer-to-peer (NVlink) pairs.
    ///
    /// @param[out]  count
    ///     The number of available pairs that is stored in the returned array.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     An array of available peer-to-peer groups or NULL if none are available.
    static std::vector<OctaneVec::uint32_2> getAvailablePeerToPeerPairs(
            uint32_t &   count
            );

    /// List of devices to enable for rendering and denoising. All other
    /// devices which are not in the list and was previously enabled will get disabled.
    ///
    /// Priority: Previously enabled devices either for rendering and/or denoising have
    /// high precedence over new devices.
    ///
    /// This function will silently ignore any invalid device indexes passed in the lists.
    ///
    /// @param renderDeviceIxs
    ///     Indices for those devices that should be enabled for rendering.
    /// @param renderDeviceCount
    ///     Total number of elements to be used from @ref renderDeviceIxs.
    /// @param deviceIxsUsingPriority
    ///     Indices for those devices for which render priority should be enabled.
    /// @param deviceCountUsingPriority
    ///     Total number of elements to be used from @ref deviceIxsUsingPriority.
    /// @param imageDeviceIx
    ///     Index of the device to use for imaging. Use -1 to automatically select the first capable
    ///     device. The device selected for imaging will also be the real-time device if the
    ///     real-time mode is enabled. And the device selected for imaging will also always be used
    ///     for rendering whether it is present in @ref renderDeviceIxs or not.
    /// @param denoiseDeviceIxs
    ///     Indices for those devices that should be enabled for denoising.
    /// @param denoiseDeviceCount
    ///     Total number of elements to be used from @ref denoiseDeviceIxs.
    /// @param peerToPeerGroups
    ///     Pointer to an array of peer-to-peer groups (NVLink) that should be used or NULL if
    ///     the current peer-to-peer setup should not be changed or if no peer-to-peer groups should
    ///     be used.
    /// @param peerToPeerGroupCount
    ///     The number of peer-to-peer groups in @ref peerToPeerGroups. If set to
    ///     @ref DONT_CHANGE_PEER_TO_PEER, @ref peerToPeerGroups will be ignored and the setup not
    ///     changed.
    /// @param useMetalRayTracing
    ///     Whether to use the Metal ray tracing backend on devices with support for it.
    ///     This does not affect NVIDIA devices
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if all the devices enabled. FALSE if failed able to enable one or more devices
    ///     due to the maximum GPU limit, in this case, Please use get functions to update the UI
    ///     to latest and inform the user about failure.
    static bool setDevicesActivity(
            const uint32_t *const                     renderDeviceIxs,
            const uint32_t                            renderDeviceCount,
            const uint32_t *const                     deviceIxsUsingPriority,
            const uint32_t                            deviceCountUsingPriority,
            const int32_t                             imageDeviceIx,
            const uint32_t *const                     denoiseDeviceIxs,
            const uint32_t                            denoiseDeviceCount,
            const Octane::uint32_2 *const             peerToPeerGroups,
            const uint32_t                            peerToPeerGroupCount,
            const bool                                useMetalRayTracing
            );

    /// Returns TRUE if the device is used for rendering.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool isDeviceUsedForRendering(
            const uint32_t   index
            );

    /// Returns TRUE if the device with index uses render priority.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool deviceUsesPriority(
            const uint32_t   index
            );

    /// Returns TRUE if the device at the provided index is using hardware ray-tracing
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool deviceUsesHardwareRayTracing(
            const uint32_t   index
            );

    /// Returns the index of the device used for imaging, or -1 if no device is capable. The image
    /// device is also the device used in the real-time mode.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static int32_t imageDeviceIndex();

    /// Returns TRUE if the device is used for denoising.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool isDeviceUsedForDenoising(
            const uint32_t   index
            );

    /// Returns the current render priority.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::ApiRenderEngine::RenderPriority renderPriority();

    /// Sets the current render priority.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void setRenderPriority(
            const Octane::ApiRenderEngine::RenderPriority   priority
            );

    /// Returns the current peer-to-peer configuration. The returned array is owned by Octane and
    /// stays valid until shutdown or the next call of this function.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static std::vector<OctaneVec::uint32_2> currentPeerToPeerGroups(
            uint32_t &   groupCount
            );

    /// Returns TRUE if hardware raytracing is currently enabled for all devices with support for it
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool hardwareRayTracingEnabled();

    /// Opens a modal dialog to allow the user to set devices configuration. When the
    /// the function returns, the dialog has been closed already and the settings have been stored
    /// in the Octane application preferences.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void openDeviceSettings();

    /// Returns the state of the device.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::RenderDeviceState renderDeviceState(
            const unsigned int   deviceIx
            );

    /// Returns the error state of a device or RENDER_ERROR_NONE if the device has not failed or
    /// is not active.
    ///
    /// NOTE: The error types currently supported on the high level are:
    ///       - RENDER_ERROR_NONE
    ///       - RENDER_ERROR_KERNEL_FAILED
    ///       - RENDER_ERROR_ACTIVATION_REQUIRED
    ///       - RENDER_ERROR_UNSPECIFIED
    ///       Until we have improved the high-level error management other error types will be
    ///       reported as RENDER_ERROR_UNSPECIFIED.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::RenderError renderDeviceErrorCode(
            const unsigned int   deviceIx
            );

    /// Returns the error state of a device as string or an empty string if the device is not in an
    /// error state or is not active.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static std::string errorcodeToString(
            const Octane::RenderError   code
            );

    /// Returns the (low-level) error message that triggered the device to fail or an empty string
    /// if it hasn't failed or isn't active.
    ///
    /// NOTE: This function is not thread-safe and the returned pointer stays valid until the next
    ///       call of this function.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static std::string renderDeviceErrorMessage(
            const unsigned int   deviceIx
            );

    /// Saves the current render device configuration (device activity and priority usage in the
    /// Octane preferences, which are shared between Octane Standalone and all plugins).
    ///
    /// The preferences are automatically loaded when Octane is started.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void saveRenderDeviceConfig();

    /// Returns true if out-of-core textures are enabled
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool outOfCoreEnabled();

    /// Enable out-of-core textures and geometry, or update the maximum amount of system memory
    /// to allow for use.
    ///
    /// Out-of-core textures and geometry are stored in pinned memory, i.e. memory that the
    /// operating system can't page out. This effectively makes it unavailable to other
    /// applications. Beware that some OSs do not allow more than 50% of system RAM to be
    /// page locked, and on Windows it is not consistent between versions, and whether the
    /// CUDA device is in TCC mode or WDDM mode also makes a difference.
    ///
    /// @param limit
    ///     Maximum number of bytes to be used by out-of-core textures and geometry.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void enableOutOfCore(
            uint64_t   limit
            );

    /// Disables out-of-core.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void disableOutOfCore();

    /// Returns RAM usage by out-of-core textures. All amounts are expressed in bytes. Some values
    /// are estimated by the operating system.
    ///
    /// @param[out] usedOutOfCore
    ///     Out-of-core memory used by Octane.
    /// @param[out] maxOutOfCore
    ///     Out-of-core memory limit, as set up via the preferences. Will be set to the previous
    ///     setting if out-of-core textures are disabled.
    /// @param[out] usedByOctane
    ///     Estimate of how much memory is currently in use by Octane (including the out-of-core
    ///     memory).
    /// @param[out] totalUsed
    ///     Estimate of the total amount of RAM in use.
    /// @param[out] totalRam
    ///     Total RAM size.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void getOutOfCoreMemoryUsage(
            uint64_t &                                usedOutOfCore,
            uint64_t &                                maxOutOfCore,
            uint64_t &                                usedByOctane,
            uint64_t &                                totalUsed,
            uint64_t &                                totalRam
            );

    /// To run the render kernels successfully, there needs to be some amount of free GPU memory.
    /// This setting determines how much GPU memory the render engine will leave available when
    /// uploading images and meshes. This only has an effect when device peering or out-of-core is
    /// enabled.
    ///
    /// There is no easy way to guess the minimum amount required. The default value should work
    /// for most scenes.
    ///
    /// @param gpuHeadroom
    ///     GPU headroom size in bytes.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void setGpuHeadroom(
            uint64_t   gpuHeadroom
            );

    /// Gets the GPU headroom value.
    ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     GPU headroom size in bytes.
    static uint64_t getGpuHeadroom();

    /// Sets the maximum number of system cores to use for the following subsystems:
    /// 1. VDB operations
    /// 2. Geometry processing
    /// 3. Bone deformation
    /// 4. AI light processing
    ///
    /// @params[in] maxCores
    ///     Giving 0 will make Octane use all cores. If you provide a number larger than 0, the
    ///     number of cores used will be the minimum of maxCores and the number of actual cores
    ///     your system has.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void setCoreLimit(
            const uint32_t   maxCores
            );

    /// Disables the core limit, meaning Octane will use all cores available for the subsystems
    /// listed in the comments above on setCoreLimit(). This is equivalent to calling
    /// setCoreLimit(0);
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void disableCoreLimit();

    /// Registers a shared surface to be used for compositor input.
    ///
    /// At all times when the given shared surface is registered (i.e. from before this function is
    /// called until after the corresponding call to unregisterInputSharedSurface returns), it must
    /// be the case that the current image device supports it. Use deviceSharedSurfaceInfo to check
    /// which devices (if any) support the shared surface, and setDevicesActivity to set the image
    /// device accordingly.
    ///
    /// @param surface
    ///     Details of the surface to register. This function increments the reference count of the
    ///     underlying shared surface object but doesn't take ownership of this instance; you still
    ///     need to release it.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     An nonzero ID for the shared surface, or zero if surface is null. This ID can be stored
    ///     in A_SHARED_SURFACE_ID node attributes to be used during rendering. IDs are never
    ///     reused, even after being unregistered, so this ID will always refer to this surface.
    static int64_t registerInputSharedSurface(
            const ApiSharedSurfaceProxy *   surface
            );

    /// Unregisters an input shared surface that was registered with registerInputSharedSurface.
    ///
    /// The surface will not be destroyed until there are no other references to it. Continued use
    /// of this ID may or may not continue to read from the shared surface (if it still exists). If
    /// it does not, it will work as if the surface had 0x0 size.
    ///
    /// @param id
    ///     The ID that was returned when the shared surface was registered. It's safe to pass zero
    ///     or an ID that has already been unregistered; this will do nothing.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void unregisterInputSharedSurface(
            int64_t   id
            );

    /// Causes an asynchronous tonemap operation to run even if one wouldn't otherwise have been
    /// run. This should be called when the contents of an input shared surface have changed
    /// externally, but there might not have been any actual render data changes that Octane knows
    /// about. Without calling this, the compositor may never be run again (e.g. if rendering has
    /// finished) or it may be run after some time (e.g. if tonemap frequency has reduced as
    /// rendering progresses). Calling this ensures updates to input shared surfaces are reflected
    /// in render output eventually (and as soon as possible).
    ///
    /// @param force
    ///     If this is true, any updates made in the past are guaranteed to be reflected in output
    ///     in the future. If this is false, a new asynchronous tonemap operation will not be
    ///     started if one is already running (in that case, the output will eventually reflect the
    ///     very recent state of input shared surfaces, but not necessarily the current state). For
    ///     best performance, if calling this function frequently (e.g. 10+ times per second) prefer
    ///     to pass false where possible. This only needs to be true if this function may not be
    ///     called again for some time.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void triggerAsyncTonemap(
            bool   force
            );

    /// Sets the shared surface output type and whether to use real time mode.
    ///
    /// At all times when shared surface output is enabled (i.e. from before this function is called
    /// to enable shared surface output until after it returns having disabled shared surface
    /// output), it must be the case that the current image device supports the desired type of
    /// shared surface. Use deviceSharedSurfaceInfo to check which devices (if any) support the
    /// desired type of shared surface, and setDevicesActivity to set the image device accordingly.
    ///
    /// At all times when real time mode is enabled (i.e. from before this function is called to
    /// enable real time mode until after it returns having disabled real time mode), there must be
    /// exactly one render pass enabled for async tonemapping. Use setAsyncTonemapRenderPasses to
    /// set the render passes that are enabled for async tonemapping.
    ///
    /// Changing this is expensive as all render threads will be destroyed and recreated, so should
    /// not be done frequently.
    ///
    /// The format of the output shared surface(s) is determined by setAsyncTonemapParams.
    ///
    /// @param type
    ///     The desired shared surface output type, or SHARED_SURFACE_TYPE_NONE to disable shared
    ///     surface output. Shared surface output is intially disabled.
    /// @param realTime
    ///     True to enable real time mode, false to disable real time mode. Real time mode is
    ///     initially disabled.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void setSharedSurfaceOutputType(
            Octane::SharedSurfaceType                 type,
            bool                                      realTime
            );

    /// Gets the current shared surface output type.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::SharedSurfaceType getSharedSurfaceOutputType();

    /// Gets whether the renderer is in real time mode.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool getRealTime();

    /// Pauses rendering. During pausing the render threads are just spinning and waiting for
    /// new work, i.e. for rendering to continue. All resources and the film buffer on the GPU stay
    /// alive. All changes in the render target are not passed through to the render threads, with
    /// the exception of changes in the imager and post-pro nodes.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void pauseRendering();

    /// Continues rendering. All changes not passed to the render threads yet, will be passed on
    /// after continuation.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void continueRendering();

    /// Returns TRUE if rendering is currently paused.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool isRenderingPaused();

    /// Restarts the rendering, i.e. wipes the film buffer and starts from scratch. If rendering
    /// was paused, it will implicitely continued.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void restartRendering();

    /// Stops the rendering completely, i.e. releases all allocated GPU resources, stops the
    /// render threads and deletes the render target. This is a fairly expensive operation, but
    /// could be useful if you want to completely stop rendering, but don't want to destroy your
    /// node graph.
    ///
    /// getRenderTargetNode() will return NULL afterwards.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void stopRendering();

    /// Shoots a viewing ray from the camera through the specified pixel and records all
    /// intersections with the scene ordered by distance from camera.
    ///
    /// @param[in]  x
    ///     The X coordinate of the picking ray (in image space).
    /// @param[in]  y
    ///     The Y coordinate of the picking ray (in image space).
    /// @param[in]  filterDuplicateMaterialPins
    ///     If set to TRUE and there are several intersections with polygons mapping to the same
    ///     material pin, only the first intersection (closest to the camera) will be recorded.
    /// @param[out]  intersections
    ///     Pointer to a C array where the intersections will be stored (must not be NULL).
    /// @param[in]  intersectionsSize
    ///     The maximum number of intersections that can be stored in "intersections".
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The number of intersections stored in "intersections".
    static unsigned int pick(
            const unsigned int                        x,
            const unsigned int                        y,
            const bool                                filterDuplicateMaterialPins,
            GRPCPickIntersection &                   intersections,
            const unsigned int                        intersectionsSize
            );

    /// @deprecated Equivalent to pickImagerWhitePoint(uint32_2{x, y}, whitePoint); use that
    /// instead.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool pickWhitePoint(
            const unsigned int                        x,
            const unsigned int                        y,
            OctaneVec::float_3 &                      whitePoint
            );

    /// Determines the average color around a specified location in the main beauty pass and
    /// calculates the required color to white balance those pixels, i.e. the white point to set in
    /// the imager node to make that location end up neutral after tonemapping.
    ///
    /// @param position
    ///     The coordinates of the pixel to sample near.
    /// @param[out] whitePoint
    ///     Will be set to the picked white point (in the linear sRGB color space) if this function
    ///     returns true. Will not be modified if this function returns false.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     True if the operation succeeded. False if there was an error.
    static bool pickImagerWhitePoint(
            OctaneVec::uint32_2                       position,
            OctaneVec::float_3 &                      whitePoint
            );

    /// Checks whether a white point is pickable for a given output AOV and "Adjust white balance"
    /// output AOV layer node. This can be used to determine whether to enable picking for a given
    /// node depending on the currently displayed AOV and current render data.
    ///
    /// @param outputAovIndex
    ///     The index of the output AOV to check.
    /// @param nodeUniqueId
    ///     The unique ID (as returned by ApiNode::uniqueId()) of the "Adjust white balance" output
    ///     AOV layer node to check.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     True if the output AOV uses the pickable node identified by nodeUniqueId. False
    ///     otherwise.
    static bool isOutputAovWhitePointPickable(
            uint32_t                                  outputAovIndex,
            uint32_t                                  nodeUniqueId
            );

    /// Determines the average color around a specified location before applying an "Adjust white
    /// balance" output AOV layer while compositing an output AOV, and calculates the required white
    /// point to use for the layer so that it will make that location neutral.
    ///
    /// @param position
    ///     The coordinates of the pixel to sample near.
    /// @param outputAovIndex
    ///     The pick is done in the context of the output AOV with this index.
    /// @param nodeUniqueId
    ///     The unique ID (as returned by ApiNode::uniqueId()) of the "Adjust white balance" output
    ///     AOV layer node for which the white point is being picked. If the output AOV uses this
    ///     node in multiple places, the white point will be picked based on the first time the
    ///     layer is applied during compositing (depth first traversal, bottom layer first).
    /// @param[out] whitePoint
    ///     If this function returns true: will be set to the picked white point (in the linear sRGB
    ///     color space), or (0, 0, 0) if the output AOV doesn't use the pickable node identified by
    ///     nodeUniqueId. If this function returns false: will not be modified.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     True if the operation succeeded. False if there was an error.
    static bool pickOutputAovWhitePoint(
            OctaneVec::uint32_2                       position,
            uint32_t                                  outputAovIndex,
            uint32_t                                  nodeUniqueId,
            OctaneVec::float_3 &                      whitePoint
            );

    /// Gets the name of the cryptomatte matte with the most coverage at a given position.
    ///
    /// @param x
    ///     The X coordinate of the pixel to sample.
    /// @param y
    ///     The Y coordinate of the pixel to sample.
    /// @param pass
    ///     The cryptomatte pass for which to pick the matte. This must be one of the
    ///     RENDER_PASS_CRYPTOMATTE_* values.
    /// @param[out] matteName
    ///     If this function returns true, the matte name that was picked will be written here. If
    ///     this function returns false, this will not be modified. This may be null if
    ///     matteNameBufferSize is zero.
    /// @param[in,out] matteNameBufferSize
    ///     On input, the size of the buffer pointed to by matteName (including space for a
    ///     terminating null character).
    ///
    ///     On output, this will be set to:
    ///         (If this function returns true):
    ///             The number of bytes written to matteName (including the terminating null
    ///             character). This will always be greater than zero and less than or equal to the
    ///             input value.
    ///         (If this function returns false because the input value was not large enough):
    ///             The minimum input value required for a future call to this function to succeed.
    ///             This will always be greater than the input value.
    ///         (If this function returns false for some other reason):
    ///             Zero.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     True if a matte was picked. False if no mattes had coverage for the given pixel, or the
    ///     given pass has not been rendered, or matteNameBufferSize was not large enough to hold
    ///     the picked matte name, or some other error occurred.
    static bool pickCryptomatteMatte(
            unsigned int                              x,
            unsigned int                              y,
            Octane::RenderPassId                      pass,
            std::string &                             matteName,
            unsigned int &                            matteNameBufferSize
            );

    /// Modifies a cryptomatte matte selection string (e.g. the value of the P_CRYPTOMATTE_MATTES
    /// pin of a NT_OUTPUT_AOV_LAYER_BLEND_CRYPTOMATTE_MASK node) to ensure a specific matte name is
    /// or is not included. This could be used to modify the matte selection for a cryptomatte mask
    /// after picking a matte to add or remove with pickCryptomatteMatte.
    ///
    /// If the original matte selection string already includes or does not include the matte name
    /// as requested, the "modified" matte selection will be the same as the original.
    ///
    /// @param inputText
    ///     The original value of the matte selection string. Must not be null.
    /// @param matteName
    ///     The matte name to add to or remove from the selection. Must not be null.
    /// @param add
    ///     True to ensure the matte name is included in the selection. False to ensure it is not
    ///     included in the selection.
    /// @param[out] outputText
    ///     If this function returns true, the modified matte selection string will be written here.
    ///     If this function returns false, this will not be modified. This may be null if
    ///     outputTextBufferSize is zero. This may point to the same buffer as inputText to do the
    ///     modification in place.
    /// @param[in,out] outputTextBufferSize
    ///     On input, the size of the buffer pointed to by outputText (including space for a
    ///     terminating null character).
    ///
    ///     On output, this will be set to:
    ///         (If this function returns true):
    ///             The number of bytes written to outputText (including the terminating null
    ///             character). This will always be greater than zero and less than or equal to the
    ///             input value.
    ///         (If this function returns false):
    ///             The minimum input value required for a future call to this function to succeed.
    ///             This will always be greater than the input value.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     True if the operation succeeded. False if the operation failed because
    ///     outputTextBufferSize was not large enough to hold the resulting string.
    static bool modifyCryptomatteMatteSelection(
            const char *                              inputText,
            const char *                              matteName,
            bool                                      add,
            std::string &                             outputText,
            unsigned int &                            outputTextBufferSize
            );

    /// Returns a human readable string for a render priority.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static std::string toString(
            const Octane::ApiRenderEngine::RenderPriority   priority
            );

    /// Returns PCI bus and device ids of the device
    ///
    /// @param[in] deviceIx
    ///     device id
    /// @param[out] pciBusId
    ///     PCI bus id of the device
    /// @param[out] pciDeviceId
    ///     PCI device id of the device
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void getDevicePciIds(
            const unsigned int                        deviceIx,
            uint64_t &                                pciBusId,
            uint64_t &                                pciDeviceId
            );

private:
    static GRPCSettings & getGRPCSettings();
};
