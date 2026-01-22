// Copyright (C) 2026 OTOY NZ Ltd.

// system headers
#include <grpcpp/grpcpp.h>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <random>
#include <string>
#include <thread>
// protoc generated headers
#include "apiprojectmanager.grpc.pb.h"
// apiItem
#include "apinodesystem_3.grpc.pb.h"
// apiNode
#include "apinodesystem_7.grpc.pb.h"
#include "apirender.grpc.pb.h"
#include "apichangemanager.grpc.pb.h"
#include "callbackstream.grpc.pb.h"
#include "apirender.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReaderWriter;
using grpc::Status;
using namespace octaneapi;


/// Determines the size of a 1D C array in elements.
#define ARRAY_WIDTH(a)  (sizeof(a) / sizeof(a[0]))

std::string gServerURL = "127.0.0.1:50051";
std::string gImageDumpPath;


#ifdef _WIN32
#include <windows.h>
#elif defined(__linux__)
#include <unistd.h>
#include <limits.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#endif

#pragma once
#include <cmath>
#include <iostream>

#pragma once
#include <cmath>
#include <iostream>

class Float3 {
public:
    float x;
    float y;
    float z;

    // Constructors
    constexpr Float3() : x(0.0f), y(0.0f), z(0.0f) {}

    constexpr Float3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

};


//--------------------------------------------------------------------------------------------------
/// Stores the reference and statistics of a render result, which can be of LDR or HDR. The first
/// pixel in the buffer is of the top-left corner.
struct RenderedImage
{
    //--- Basic image fields ---

    /// The image type of the result. Currently only these types are used:
    ///
    /// - IMAGE_TYPE_LDR_RGBA
    /// - IMAGE_TYPE_HDR_RGBA
    /// - IMAGE_TYPE_HALF_RGBA (macOS/iOS only)
    /// - IMAGE_TYPE_LDR_MONO_ALPHA
    /// - IMAGE_TYPE_HDR_MONO_ALPHA
    /// - IMAGE_TYPE_HALF_MONO_ALPHA (macOS/iOS only)
    octaneapi::ImageType     mType;
    /// The color space of the result.
    octaneapi::NamedColorSpace mColorSpace;
    /// The value of this is implied by mColorSpace unless it's NAMED_COLOR_SPACE_OTHER or
    /// NAMED_COLOR_SPACE_OCIO.
    bool          mIsLinear;
 
    /// The size in pixels, or zero if this image refers to a shared surface.
    uint32_t      mSizeX = 0;
    uint32_t      mSizeY = 0;
    /// The number of pixels allocated on a single image row, or zero if this image refers to a
    /// shared surface.
    uint32_t      mPitch;
    /// The pixel buffer storing the result in row-order, or null if this image refers to a shared
    /// surface.
    ///
    /// The pixel format for each image type is:
    /// - IMAGE_TYPE_LDR_RGBA       : each pixel is stored in 4 bytes  (red, green, blue, alpha)
    /// - IMAGE_TYPE_HDR_RGBA       : each pixel is stored in 4 floats (red, green, blue, alpha)
    /// - IMAGE_TYPE_HALF_RGBA      : each pixel is stored in 4 half-floats (red, green, blue, alpha)
    /// - IMAGE_TYPE_LDR_MONO_ALPHA : each pixel is stored in 2 bytes  (y, alpha)
    /// - IMAGE_TYPE_HDR_MONO_ALPHA : each pixel is stored in 2 floats (y, alpha)
    /// - IMAGE_TYPE_HALF_MONO_ALPHA: each pixel is stored in 2 half-floats (y, alpha)
    const void    *mBuffer;

    //--- Additional render stats ---

    /// The render pass that this result represents.
    RenderPassId  mRenderPassId;
    /// The blended samples per pixel, i.e. the samples you can see in the result.
    float         mTonemappedSamplesPerPixel;
    /// The actually calculated samples per pixel, which can be higher than
    /// mTonemappedSamplesPerPixel, because they haven't been blended or received from the render
    /// nodes yet.
    float         mCalculatedSamplesPerPixel;
    /// The blended samples/px rendered for the current region. 0 when no region is active.
    float         mRegionSamplesPerPixel;
    /// The maximum samples per pixel that has been set in the render target while this result was
    /// rendered.
    float         mMaxSamplesPerPixel;
    /// The render speed in samples per second, which got measured between the last two render
    /// results.
    float         mSamplesPerSecond;
    /// The total render time (in seconds) we have spent since the last restart up to when this
    /// image was blended.
};


static Float3 SPHERE_VERTICES[43] =
{
    { 0.0000f,0.0000f,0.0000f     } ,
    { 0.0000f,0.0000f,1.0000f     } , { 0.5257f,0.0000f,0.8507f    } ,  { 0.1625f,0.5000f,0.8507f    } ,
    { 0.8944f,0.0000f,0.4472f     } , { 0.6882f,0.5000f,0.5257f    } ,  { 0.2764f,0.8507f,0.4472f    } ,
    { -0.4253f,0.3090f,0.8507f    } , { -0.2629f,0.8090f,0.5257f   } ,  { -0.7236f,0.5257f,0.4472f   } ,
    { -0.4253f,-0.3090f,0.8507f   } , { -0.8507f,-0.0000f,0.5257f  } ,  { -0.7236f,-0.5257f,0.4472f  } ,
    { 0.1625f,-0.5000f,0.8507f    } , { -0.2629f,-0.8090f,0.5257f  } ,  { 0.2764f,-0.8507f,0.4472f   } ,
    { 0.6882f,-0.5000f,0.5257f    } , { 0.9511f,-0.3090f,0.0000f   } ,  { 0.9511f,0.3090f,0.0000f    } ,
    { 0.7236f,-0.5257f,-0.4472f   } , { 0.8507f,0.0000f,-0.5257f   } ,  { 0.7236f,0.5257f,-0.4472f   } ,
    { 0.5878f,0.8090f,0.0000f     } , { -0.0000f,1.0000f,0.0000f   } ,  { 0.2629f,0.8090f,-0.5257f   } ,
    { -0.2764f,0.8507f,-0.4472f   } , { -0.5878f,0.8090f,0.0000f   } ,  { -0.9511f,0.3090f,0.0000f   } ,
    { -0.6882f,0.5000f,-0.5257f   } , { -0.8944f,-0.0000f,-0.4472f } ,  { -0.9511f,-0.3090f,0.0000f  } ,
    { -0.5878f,-0.8090f,0.0000f   } , { -0.6882f,-0.5000f,-0.5257f } ,  { -0.2764f,-0.8507f,-0.4472f } ,
    { 0.0000f,-1.0000f,0.0000f    } , { 0.5878f,-0.8090f,0.0000f   } ,  { 0.2629f,-0.8090f,-0.5257f  } ,
    { 0.0000f,0.0000f,-1.0000f    } , { -0.1625f,0.5000f,-0.8507f  } ,  { 0.4253f,0.3090f,-0.8507f   } ,
    { -0.5257f,-0.0000f,-0.8507f  } , { -0.1625f,-0.5000f,-0.8507f } , { 0.4253f,-0.3090f,-0.8507f   }
};


static int32_t SPHERE_FACES[240] =
{
    1,2,3,2,4,5,2,5,3,3,5,6,1,3,7,3,6,8,3,8,7,7,8,9,1,7,10,7,9,11,7,11,10,10,11,12,1,10,13,10,12,14,
    10,14,13,13,14,15,1,13,2,13,15,16,13,16,2,2,16,4,4,17,18,17,19,20,17,20,18,18,20,21,6,22,23,
    22,21,24,22,24,23,23,24,25,9,26,27,26,25,28,26,28,27,27,28,29,12,30,31,30,29,32,30,32,31,
    31,32,33,15,34,35,34,33,36,34,36,35,35,36,19,21,22,18,22,6,5,22,5,18,18,5,4,25,26,23,26,9,8,
    26,8,23,23,8,6,29,30,27,30,12,11,30,11,27,27,11,9,33,34,31,34,15,14,34,14,31,31,14,12,19,17,35,
    17,4,16,17,16,35,35,16,15,37,38,39,38,25,24,38,24,39,39,24,21,37,40,38,40,29,28,40,28,38,
    38,28,25,37,41,40,41,33,32,41,32,40,40,32,29,37,42,41,42,19,36,42,36,41,41,36,33,37,39,42,
    39,21,20,39,20,42,42,20,19
};


static Float3 CUBE_VERTICES[] =
{
    { -0.500000f, 0.000000f,  0.500000f },
    {  0.500000f, 0.000000f,  0.500000f },
    { -0.500000f, 0.000000f, -0.500000f },
    {  0.500000f, 0.000000f, -0.500000f },
    { -0.500000f, 1.000000f,  0.500000f },
    {  0.500000f, 1.000000f,  0.500000f },
    { -0.500000f, 1.000000f, -0.500000f },
    {  0.500000f, 1.000000f, -0.500000f }
};


static int32_t CUBE_FACES[] =
{
    0,2,3,  3,1,0,
    4,5,7,  7,6,4,
    0,1,5,  5,4,0,
    1,3,7,  7,5,1,
    3,2,6,  6,7,3,
    2,0,4,  4,6,2
};


#define OBJECTAMOUNT        100
#define CUBEAMOUNT          1
#define DIFFUSEMATAMOUNT    30
#define GLOSSYMATAMOUNT     30
#define RGBTEXAMOUNT        50
#define IMGTEXAMOUNT        5


static octaneapi::ObjectRef        gImageTextures[IMGTEXAMOUNT];
static octaneapi::ObjectRef        gRgbTextures[RGBTEXAMOUNT];
static octaneapi::ObjectRef        gDiffuseMaterials[DIFFUSEMATAMOUNT];
static octaneapi::ObjectRef        gGlossyMaterials[GLOSSYMATAMOUNT];
static octaneapi::ObjectRef        gMaterialMaps[OBJECTAMOUNT + CUBEAMOUNT];
static octaneapi::ObjectRef        gSphereMesh;
static octaneapi::ObjectRef        gSpinCube;
static octaneapi::ObjectRef        gRenderTarget;
static octaneapi::ObjectRef        gRenderPasses;
static Float3                      gCubeInitTranslate = { 0, -2.2f, 0 };
static octaneapi::ObjectRef        gCubePlacementNode;
static octaneapi::ObjectRef        gCubeMat;

grpc::ServerBuilder  mBuilder;
std::unique_ptr<grpc::Server> mServer;

static const uint32_t INIT_LCG_SEED = 123456789;
static uint32_t       gRandomState = INIT_LCG_SEED;

// Class for receiving events streamed from the server
class GRPCAPIEvents
{
public:
    GRPCAPIEvents(std::shared_ptr<grpc::Channel> channel)
:
    mStub(StreamCallbackService::NewStub(channel)),
    mChannel(channel)  {}

    void initConnection();

    void waitForEvents();

    void shutdown();

private:
    std::shared_ptr<grpc::Channel> & mChannel;
    std::unique_ptr<StreamCallbackService::Stub> mStub;
    std::unique_ptr<grpc::ClientContext> mContext;
    std::unique_ptr<grpc::ClientReader<StreamCallbackRequest>> mStream;
    std::thread mReaderThread;
    std::atomic<bool> mShutdownRequested = false;

    void HandleCallback(
        const StreamCallbackRequest & request);
};


// Calculates a new LCG random number.
static inline void updateLcgRandom()
{
    gRandomState = gRandomState * 1664525 + 1013904223;
}


void resetLcg()
{
    gRandomState = INIT_LCG_SEED;
}


std::tuple<float, float, float> normalized(float x, float y, float z)
{
    float lenSq = x*x + y*y + z*z;
    if (lenSq > 1e-16f) // guard against zero length
    {
        float invLen = 1.0f / std::sqrt(lenSq);
        return { x * invLen, y * invLen, z * invLen };
    }
    return { 0.0f, 0.0f, 0.0f };
}


uint32_t lcgRandom()
{
    updateLcgRandom();

    // return swizzled random number (ab cd ef gh  ->  hg fe dc ba)
    uint32_t result = ((gRandomState & 0xf0f0f0f0) >> 4) |
        ((gRandomState & 0x0f0f0f0f) << 4);
    result = ((result & 0xff000000) >> 24) |
        ((result & 0x00ff0000) >>  8) |
        ((result & 0x0000ff00) <<  8) |
        ((result & 0x000000ff) << 24);
    return result;
}


bool lcgRandomBool()
{
    updateLcgRandom();

    return gRandomState < 0x80000000U;
}


float lcgRandomFloat()
{
    updateLcgRandom();

    // convert random number to float in the range [0 .. 1]
    return 2.32830644e-10f * gRandomState;
}


int lcgRandomRange(
    const int rangeStart,
    const int rangeEnd)
{
    updateLcgRandom();
    const uint64_t range = rangeEnd - rangeStart;
    return rangeStart + (int)((range * gRandomState) >> 32);
}


int lcgRandomRange(
    const int range)
{
    return lcgRandomRange(0, range);
}


void lcgRandomize()
{
    std::random_device rd;
    gRandomState = rd(); // Fully platform-dependent entropy source
}


template <class T>
inline const T* vectorBuffer(
    const std::vector<T> &vec)
{
    return !vec.empty() ? &(vec[0]) : NULL;
}


/// Safe accessor to the buffer of a std::vector.
template <class T>
inline T* vectorBuffer(
    std::vector<T> &vec)
{
    return !vec.empty() ? &(vec[0]) : NULL;
}


static octaneapi::ObjectRef & getRandomRgbTexture()
{
    return gRgbTextures[lcgRandomRange(RGBTEXAMOUNT)];
}


static octaneapi::ObjectRef & getRandomImgTexture()
{
    return gImageTextures[lcgRandomRange(IMGTEXAMOUNT)];
}


static octaneapi::ObjectRef & getRandomTexture()
{
    if (lcgRandomBool())
    {
        return getRandomRgbTexture();
    }
    else
    {
        return getRandomImgTexture();
    }
}


static octaneapi::ObjectRef & getRandomDiffuseMat()
{
    return gDiffuseMaterials[lcgRandomRange(DIFFUSEMATAMOUNT)];
}


static octaneapi::ObjectRef & getRandomGlossyMat()
{
    return gGlossyMaterials[lcgRandomRange(GLOSSYMATAMOUNT)];
}


// Helper function to get the path of the current executable
std::filesystem::path getExecutablePath()
{
#ifdef _WIN32
    char buffer[MAX_PATH];
    DWORD len = GetModuleFileNameA(nullptr, buffer, MAX_PATH);
    return std::filesystem::path(std::string(buffer, len));
#elif defined(__linux__)
    char buffer[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1)
    {
        return std::filesystem::path(std::string(buffer, len));
    }
#elif defined(__APPLE__)
    char buffer[PATH_MAX];
    uint32_t size = sizeof(buffer);
    if (_NSGetExecutablePath(buffer, &size) == 0)
    {
        return std::filesystem::canonical(buffer);
    }
#endif
    throw std::runtime_error("Unable to determine executable path");
}


bool setRenderTargetNode(
            std::shared_ptr<grpc::Channel> & channel,
            octaneapi::ObjectRef &           targetNode
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::setRenderTargetNodeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'targetNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    auto * targetnodeIn = request.mutable_targetnode();
    targetnodeIn->set_type(targetNode.type());
    targetnodeIn->set_handle(targetNode.handle());

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::setRenderTargetNodeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub =
        octaneapi::ApiRenderEngineService::NewStub(channel);
    status = stub->setRenderTargetNode(context.get(), request, &response);
    if (status.ok())
    {
        return response.result(); 
    } 
    return false;
};


octaneapi::ObjectRef createNode(
    std::shared_ptr<grpc::Channel> & channel,
    octaneapi::ObjectRef &           source,
    octaneapi::NodeType              nodeType,
    bool                             configurepinsIn)
{
    octaneapi::ObjectRef newNode;
    octaneapi::ApiNode::createRequest  createRequest;
    octaneapi::ApiNode::createResponse createResponse;
    createRequest.set_type(nodeType);

    auto * ownergraphIn = createRequest.mutable_ownergraph();
    ownergraphIn->set_type(source.type());
    ownergraphIn->set_handle(source.handle());

    createRequest.set_configurepins(configurepinsIn);

    std::shared_ptr<grpc::ClientContext> context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(channel);
    auto status = stub->create(context.get(), createRequest, &createResponse);
    if (status.ok())
    {
        return createResponse.result();
    }
    return newNode;
}


bool connectTo(std::shared_ptr<grpc::Channel> & channel,
               octaneapi::ObjectRef &           thisObject,
               const octaneapi::PinId           pinId,
               octaneapi::ObjectRef &           source,
               bool                             evaluate,
               bool                             doCycleCheck)
{
    octaneapi::ApiNode::connectToRequest connectToRequest;

    auto * objectptrIn = connectToRequest.mutable_objectptr();
    objectptrIn->set_type(thisObject.type());
    objectptrIn->set_handle(thisObject.handle());

    auto * src = connectToRequest.mutable_sourcenode();
    *src = source;
    
    connectToRequest.set_pinid(pinId);
    connectToRequest.set_evaluate(evaluate);
    connectToRequest.set_docyclecheck(doCycleCheck);
    google::protobuf::Empty response;

    std::shared_ptr<grpc::ClientContext> context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub = octaneapi::ApiNodeService::NewStub(channel);
    auto status = stub->connectTo(context.get(), connectToRequest, &response);
    if (status.ok())
    {
        return true;
    }
    return false;
}


bool changeManagerUpdate(
    std::shared_ptr<grpc::Channel> & channel)
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiChangeManager::updateRequest updateRequest;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiChangeManagerService::Stub> stub =
        octaneapi::ApiChangeManagerService::NewStub(channel);
    status = stub->update(context.get(), updateRequest, &response);

    if (status.ok())
    {
        return true;
    }
    return false;
};


bool rootNodeGraph(
    std::shared_ptr<grpc::Channel> & channel,
    octaneapi::ObjectRef &           ref)
{
    octaneapi::ApiProjectManager::rootNodeGraphRequest   rootNodeGraphRequest;
    octaneapi::ApiProjectManager::rootNodeGraphResponse  rootNodeGraphResponse;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiProjectManagerService::Stub> stub =
        octaneapi::ApiProjectManagerService::NewStub(channel);
    auto  status = stub->rootNodeGraph(context.get(), rootNodeGraphRequest, &rootNodeGraphResponse);
    if (status.ok())
    {
         ref = rootNodeGraphResponse.result();
         return true;
    }
    return false;
}


bool resetProject(
    std::shared_ptr<grpc::Channel> & channel )
{
    octaneapi::ApiProjectManager::resetProjectRequest   resetProjectRequest;
    octaneapi::ApiProjectManager::resetProjectResponse  resetProjectResponse;

    resetProjectRequest.set_suppressui(true);
    std::shared_ptr<grpc::ClientContext> context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiProjectManagerService::Stub> stub =
        octaneapi::ApiProjectManagerService::NewStub(channel);
    auto status = stub->resetProject(context.get(), resetProjectRequest, &resetProjectResponse);
    if (status.ok())
    {
        return resetProjectResponse.result();
    }
    return false;
}


bool connectedNode(
            std::shared_ptr<grpc::Channel> & channel,
            const octaneapi::ObjectRef &     thisObject,
            const octaneapi::PinId           pinId,
            const bool                       enterWrapperNode,
            octaneapi::ObjectRef &           refOut
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::connectedNodeRequest connectedNodeRequest;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    auto * objectptrIn = connectedNodeRequest.mutable_objectptr();
    objectptrIn->set_type(thisObject.type());
    objectptrIn->set_handle(thisObject.handle());

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinId' [in] parameter to the request packet.
    octaneapi::PinId pinidIn;
        pinidIn = static_cast<octaneapi::PinId>(pinId);
    connectedNodeRequest.set_pinid(pinidIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'enterWrapperNode' [in] parameter to the request packet.
    bool enterwrappernodeIn;
    enterwrappernodeIn = enterWrapperNode;
    connectedNodeRequest.set_enterwrappernode(enterwrappernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::connectedNodeResponse connectedNodeResponse;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(channel);
    status = stub->connectedNode(context.get(), connectedNodeRequest, &connectedNodeResponse);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        refOut = connectedNodeResponse.result();
        return true;
    }
    return false;
};


bool set(std::shared_ptr<grpc::Channel> &          channel,
         octaneapi::ObjectRef &                    renderTargetNode,
         const octaneapi::AttributeId              id,
         octaneapi::ApiItem::setValueByIDRequest & request,
         bool                                      evaluate)
{
    octaneapi::ApiItem::setValueResponse setValueResponse;

    // make a copy of request with item_ref + attribute_id filled
 
    request.set_evaluate(evaluate);
    auto * ref = request.mutable_item_ref();
    ref->set_type(renderTargetNode.type());
    ref->set_handle(renderTargetNode.handle());

    request.set_attribute_id(static_cast<octaneapi::AttributeId>(id));
    auto stub = octaneapi::ApiItemService::NewStub(channel);
    auto context = std::make_unique<grpc::ClientContext>();
    grpc::Status status = stub->setValueByAttrID(context.get(), request, &setValueResponse);
    if (status.ok())
    {
        return true;
    }
    return false;
}


int staticPinCount(std::shared_ptr<grpc::Channel> & channel,
                   octaneapi::ObjectRef &           thisObject)
{
    octaneapi::ApiNode::staticPinCountRequest request;
    auto * objPtr = request.mutable_objectptr();
    objPtr->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objPtr->set_handle(thisObject.handle());

    octaneapi::ApiNode::staticPinCountResponse response;
    auto context = std::make_unique<grpc::ClientContext>();
    auto stub    = octaneapi::ApiNodeService::NewStub(channel);
    grpc::Status status = stub->staticPinCount(context.get(), request, &response);
    if (!status.ok())
    {
        return -1;
    }
    return response.result();
}


bool setPinValue(
            std::shared_ptr<grpc::Channel> &             channel,
            octaneapi::ObjectRef &                       thisObject,
            const octaneapi::PinId                       id,
            octaneapi::ApiNode::setPinValueByIDRequest & request,
            const bool                                   evaluate
            )
{
    grpc::Status status = grpc::Status::OK; 
    octaneapi::ApiNode::setPinValueResponse response;
    octaneapi::ApiNode::setPinValueByIDRequest req = request;
    req.set_evaluate(evaluate);

    auto* ref = req.mutable_item_ref();
    ref->set_type(thisObject.type());
    ref->set_handle(thisObject.handle());
    req.set_pin_id(id);

    auto stub = octaneapi::ApiNodeService::NewStub(channel);
    auto context = std::make_unique<grpc::ClientContext>();

    status = stub->setPinValueByPinID(context.get(), req, &response);
    if (status.ok())
    {
        return true;
    }

    return false;
};


bool connectToIx(
            std::shared_ptr<grpc::Channel> & channel,
            const octaneapi::ObjectRef &     thisObject,
            const uint32_t                   pinIdx,
            octaneapi::ObjectRef &           sourceNode,
            const bool                       evaluate,
            const bool                       doCycleCheck
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::connectToIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    auto * objectptrIn = request.mutable_objectptr();
    objectptrIn->set_type(thisObject.type());
    objectptrIn->set_handle(thisObject.handle());

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinIdx' [in] parameter to the request packet.
    request.set_pinidx(pinIdx);

    /////////////////////////////////////////////////////////////////////
    // Add the 'sourceNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    auto * sourcenodeIn = request.mutable_sourcenode();
    sourcenodeIn->set_type(sourceNode.type());
    sourcenodeIn->set_handle(sourceNode.handle());

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    request.set_evaluate(evaluate);

    /////////////////////////////////////////////////////////////////////
    // Add the 'doCycleCheck' [in] parameter to the request packet.
    request.set_docyclecheck(doCycleCheck);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(channel);
    status = stub->connectToIx(context.get(), request, &response);

    if (status.ok())
    {
        return true;
    }
    return false;
};


bool evaluate(
            std::shared_ptr<grpc::Channel> &  channel,
            octaneapi::ObjectRef &            thisObject
            )
{
    grpc::Status status = grpc::Status::OK;
    octaneapi::ApiItem::evaluateRequest  request;
    google::protobuf::Empty response;
    auto * ref = request.mutable_objectptr();
    ref->set_type(thisObject.type());
    ref->set_handle(thisObject.handle());

    auto stub = octaneapi::ApiItemService::NewStub(channel);
    auto context = std::make_unique<grpc::ClientContext>();

    status = stub->evaluate(context.get(), request, &response);
    if (status.ok())
    {
        return true;
    }

    return false;
};


bool createInternal(
            std::shared_ptr<grpc::Channel> & channel,
            octaneapi::ObjectRef &           thisObject,
            const octaneapi::PinId           id,
            const octaneapi::NodeType        nodeType,
            const bool                       configurePins,
            const bool                       evaluate
            )
{
    grpc::Status status = grpc::Status::OK; 
    octaneapi::ApiNode::createInternalResponse response;
    octaneapi::ApiNode::createInternalRequest  request;
    request.set_evaluate(evaluate);
    request.set_configurepins(configurePins);
    request.set_pinid(id);
    request.set_type(nodeType);

    auto * ref = request.mutable_objectptr();
    ref->set_type(thisObject.type());
    ref->set_handle(thisObject.handle());
    
    auto stub = octaneapi::ApiNodeService::NewStub(channel);
    auto context = std::make_unique<grpc::ClientContext>();

    status = stub->createInternal(context.get(), request, &response);
    if (status.ok())
    {
        return true;
    }

    return false;
};


octaneapi::MatrixF makeTranslationMatrix(float tx, float ty, float tz)
{
    octaneapi::MatrixF mat;

    // Row 0
    auto* r0 = mat.add_m();
    r0->set_x(1.0f); r0->set_y(0.0f); r0->set_z(0.0f); r0->set_w(tx);

    // Row 1
    auto* r1 = mat.add_m();
    r1->set_x(0.0f); r1->set_y(1.0f); r1->set_z(0.0f); r1->set_w(ty);

    // Row 2
    auto* r2 = mat.add_m();
    r2->set_x(0.0f); r2->set_y(0.0f); r2->set_z(1.0f); r2->set_w(tz);

    return mat;
}


void convertImage(
    const octaneapi::ApiArrayApiRenderImage & in,
    std::vector<RenderedImage> & out)
{

    for (int i = 0; i < in.data_size(); ++i)
    {
        const ::octaneapi::ApiRenderImage & image = in.data(i);
        int imagesize = image.buffer().size();
        const char * imagedata = image.buffer().data().data();
        int imageSizeX = image.size().x();
        int imageSizeY = image.size().y();

        RenderedImage img;

        img.mCalculatedSamplesPerPixel = image.calculatedsamplesperpixel(); 
        img.mType = image.type();
        img.mColorSpace = image.colorspace();
        img.mIsLinear = image.islinear();
        img.mSizeX = image.size().x();
        img.mSizeY = image.size().y();
        img.mPitch = image.pitch();

        //buffer
        img.mBuffer = nullptr;
        size_t imgSize = img.mSizeX * img.mSizeY * img.mPitch;// image.mbuffer().size();
        if (imgSize > 0)
        {
            img.mBuffer = new char[imgSize];
            memcpy((void*)img.mBuffer, (char*)image.buffer().data().data(), image.buffer().size());
        }
        else
        {
            assert(false);
        }

        img.mTonemappedSamplesPerPixel = image.tonemappedsamplesperpixel();
        img.mCalculatedSamplesPerPixel = image.calculatedsamplesperpixel();
        img.mRegionSamplesPerPixel = image.regionsamplesperpixel();
        img.mMaxSamplesPerPixel = image.maxsamplesperpixel();
        img.mSamplesPerSecond = image.samplespersecond();
      
        out.push_back(img);
    }
}


bool grabRenderResult(
            std::shared_ptr<grpc::Channel> &      channel,
            std::vector<RenderedImage> & renderImages
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::grabRenderResultRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::grabRenderResultResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub =
        octaneapi::ApiRenderEngineService::NewStub(channel);
    status = stub->grabRenderResult(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'renderImages' [out] parameter from the gRPC response packet
        octaneapi::ApiArrayApiRenderImage renderImagesOut = response.renderimages();
        convertImage(renderImagesOut, renderImages);
    }
    else
    {
        switch (status.error_code())
        {
            case grpc::StatusCode::INVALID_ARGUMENT:
                throw std::invalid_argument(status.error_message());
            default:
                throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
        } 
    }
    return retVal;
};


bool callSetArrayByAttrID(
        std::shared_ptr<grpc::Channel> &               channel,
        const octaneapi::AttributeId                   id,
        const octaneapi::ApiItem::setArrayByIDRequest & request
        )
{
    octaneapi::ApiItem::setArrayResponse response;

    // copy request so we can fill extra required fields
    octaneapi::ApiItem::setArrayByIDRequest req = request;
    req.set_attribute_id(static_cast<octaneapi::AttributeId>(id));

    auto stub = octaneapi::ApiItemService::NewStub(channel);
    auto context = std::make_unique<grpc::ClientContext>();

    grpc::Status status = stub->setArrayByAttrID(context.get(), req, &response);
    if (status.ok())
    {
        return true;
    }
    return false;
}


void setArray(
            std::shared_ptr<grpc::Channel> &     channel,
            octaneapi::ObjectRef &                    thisObject,
            const octaneapi::AttributeId              id,
            const octaneapi::MatrixF *                arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIDRequest request;
    auto* ref = request.mutable_item_ref();
    ref->set_type(thisObject.type());
    ref->set_handle(thisObject.handle());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_matrix_array();
    for (size_t i = 0; i < size; ++i)
    {
        auto * m = arrMsg->add_data();
        m->CopyFrom(arr[i]);
    }
    auto response = callSetArrayByAttrID(channel, id, request);

};


void setArray(
            std::shared_ptr<grpc::Channel> &     channel,
            octaneapi::ObjectRef &                    thisObject,
            const octaneapi::AttributeId              id,
            const char *const *                       arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIDRequest request;
    auto* ref = request.mutable_item_ref();
    ref->set_type(thisObject.type());
    ref->set_handle(thisObject.handle());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_string_array();
    for (size_t i = 0; i < size; ++i)
    {
        arrMsg->add_data(arr[i] ? arr[i] : "");
    }
    auto response = callSetArrayByAttrID(channel, id, request);
};


void setArray(
            std::shared_ptr<grpc::Channel> &     channel,
            octaneapi::ObjectRef &                    thisObject,
            const octaneapi::AttributeId              id,
            const int32_t *                           arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIDRequest request;
    auto* ref = request.mutable_item_ref();
    ref->set_type(thisObject.type());
    ref->set_handle(thisObject.handle());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_int_array();
    for (size_t i = 0; i < size; ++i)
    {
        arrMsg->add_data(arr[i]);
    }
    auto response = callSetArrayByAttrID(channel, id, request);
};


void setArray(
            std::shared_ptr<grpc::Channel> &     channel,
            octaneapi::ObjectRef &                    thisObject,
            const octaneapi::AttributeId              id,
            const Float3 *                            arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIDRequest request;
    auto* ref = request.mutable_item_ref();
    ref->set_type(thisObject.type());
    ref->set_handle(thisObject.handle());
    request.set_evaluate(evaluate);
    //request.set_attribute_id(octaneapi::AttributeId::float)
    auto * arrMsg = request.mutable_float3_array();
    for (size_t i = 0; i < size; ++i)
    {
        auto * e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
        e->set_z(arr[i].z);
    }
    auto response = callSetArrayByAttrID(channel, id, request);
};


octaneapi::ObjectRef createCube(
    std::shared_ptr<grpc::Channel> &  channel)
{
    octaneapi::ObjectRef projectRoot;
    rootNodeGraph(channel, projectRoot);

    octaneapi::ObjectRef meshNode = createNode(channel,projectRoot,  octaneapi::NT_GEO_MESH, true);

    // set cube geometry
    const std::vector<int32_t> vertsPerPoly(ARRAY_WIDTH(CUBE_FACES) / 3, 3);
    setArray(channel, meshNode, octaneapi::A_VERTICES_PER_POLY,   vectorBuffer(vertsPerPoly), vertsPerPoly.size(),        false);
    setArray(channel, meshNode, octaneapi::A_VERTICES,            CUBE_VERTICES,              ARRAY_WIDTH(CUBE_VERTICES), false);
    setArray(channel, meshNode, octaneapi::A_UVWS,                CUBE_VERTICES,              ARRAY_WIDTH(CUBE_VERTICES), false);
    setArray(channel, meshNode, octaneapi::A_NORMALS,             CUBE_VERTICES,              ARRAY_WIDTH(CUBE_VERTICES), false);
    setArray(channel, meshNode, octaneapi::A_POLY_VERTEX_INDICES, CUBE_FACES,                 ARRAY_WIDTH(CUBE_FACES),    false);
    setArray(channel, meshNode, octaneapi::A_POLY_UVW_INDICES,    CUBE_FACES,                 ARRAY_WIDTH(CUBE_FACES),    false);
    setArray(channel, meshNode, octaneapi::A_POLY_NORMAL_INDICES, CUBE_FACES,                 ARRAY_WIDTH(CUBE_FACES),    false);

    // set material names
    std::vector<const char*> matNames;
    matNames.push_back("Material 1");
    setArray(channel, meshNode, octaneapi::A_MATERIAL_NAMES, vectorBuffer(matNames), 1, false);

    // assign materials to faces
    std::vector<int32_t> polyMatIndices(vertsPerPoly.size());
    for (int32_t i = 0; i < polyMatIndices.size(); ++i)
    {
        polyMatIndices[i] = 0;
    }
    setArray(channel, meshNode, octaneapi::A_POLY_MATERIAL_INDICES, vectorBuffer(polyMatIndices), polyMatIndices.size(), false);

    // evaluate the mesh
    evaluate(channel, meshNode);

    return meshNode;
}


octaneapi::ObjectRef createSphere(
    std::shared_ptr<grpc::Channel> &  channel,
    const unsigned int                matCount)
{
    octaneapi::ObjectRef projectRoot;
    rootNodeGraph(channel, projectRoot);

    // create sphere
    octaneapi::ObjectRef meshNode = createNode(channel, projectRoot, octaneapi::NT_GEO_MESH, true);

    // set sphere geometry
    const std::vector<int32_t> vertsPerPoly(ARRAY_WIDTH(SPHERE_FACES) / 3, 3);
    setArray(channel, meshNode, octaneapi::A_VERTICES_PER_POLY, vectorBuffer(vertsPerPoly), vertsPerPoly.size(), false);
    setArray(channel, meshNode, octaneapi::A_VERTICES, SPHERE_VERTICES, ARRAY_WIDTH(SPHERE_VERTICES), false);
    setArray(channel, meshNode, octaneapi::A_UVWS, SPHERE_VERTICES, ARRAY_WIDTH(SPHERE_VERTICES), false);
    setArray(channel, meshNode, octaneapi::A_NORMALS, SPHERE_VERTICES, ARRAY_WIDTH(SPHERE_VERTICES), false);
    setArray(channel, meshNode, octaneapi::A_POLY_VERTEX_INDICES, SPHERE_FACES, ARRAY_WIDTH(SPHERE_FACES), false);
    setArray(channel, meshNode, octaneapi::A_POLY_UVW_INDICES, SPHERE_FACES, ARRAY_WIDTH(SPHERE_FACES), false);
    setArray(channel, meshNode, octaneapi::A_POLY_NORMAL_INDICES, SPHERE_FACES, ARRAY_WIDTH(SPHERE_FACES), false);

    // set material names
    std::vector<const char*> matNames;
    matNames.push_back("Material 1");
    matNames.push_back("Material 2");
    matNames.push_back("Material 3");
    matNames.push_back("Material 4");
    matNames.push_back("Material 5");
    matNames.push_back("Material 6");
    matNames.push_back("Material 7");
    matNames.push_back("Material 8");
    matNames.push_back("Material 9");
    matNames.push_back("Material 10");
    setArray(channel, meshNode, octaneapi::A_MATERIAL_NAMES, vectorBuffer(matNames), matCount, false);

    // assign materials to faces
    std::vector<int32_t> polyMatIndices(vertsPerPoly.size());
    for (int32_t i=0; i<polyMatIndices.size(); ++i)
    {
        polyMatIndices[i] = i % matCount;
    }
    setArray(channel, meshNode, octaneapi::A_POLY_MATERIAL_INDICES, vectorBuffer(polyMatIndices), polyMatIndices.size(), false);

    // evaluate the mesh
    evaluate(channel, meshNode);

    return meshNode;
}


void initMaterials(
    std::shared_ptr<grpc::Channel >& channel)
{
    std::string texFiles[IMGTEXAMOUNT] =
    {
        "textures/Bokeh2.jpg",
        "textures/Mineral.jpg",
        "textures/MultiScatter8.jpg",
        "textures/OctaneDLDiffuse.jpg",
        "textures/OctaneLogo.png"
    };

    octaneapi::ObjectRef projectRoot;
    rootNodeGraph(channel, projectRoot);

    std::filesystem::path exePath = getExecutablePath();
    std::filesystem::path parentDir = exePath.parent_path().parent_path().parent_path();
    for (int i = 0; i < IMGTEXAMOUNT; ++i)
    {
        gImageTextures[i] = createNode(channel, projectRoot, octaneapi::NT_TEX_IMAGE, true);
        std::filesystem::path texFilePath = parentDir / texFiles[i];
        std::string fullPath = texFilePath.string();
        octaneapi::ApiItem::setValueByIDRequest request; 
        request.set_string_value(fullPath);
        set(channel, gImageTextures[i], octaneapi::A_FILENAME, request, true);
    }

    for (int i = 0; i < RGBTEXAMOUNT; ++i)
    {
        gRgbTextures[i] = createNode(channel, projectRoot, octaneapi::NT_TEX_RGB, true);
        octaneapi::ApiItem::setValueByIDRequest request;
        octaneapi::float_3 * v3 = request.mutable_float3_value();
        float b = lcgRandomFloat();
        float g = lcgRandomFloat();
        float r = lcgRandomFloat();
        v3->set_x(r);
        v3->set_y(g);
        v3->set_z(b);
        set(channel, gRgbTextures[i], octaneapi::A_VALUE, request, true);
    }

    for (int i = 0; i < DIFFUSEMATAMOUNT; ++i)
    {
        gDiffuseMaterials[i] = createNode(channel, projectRoot, octaneapi::NT_MAT_DIFFUSE, true);
        connectTo(channel, gDiffuseMaterials[i], octaneapi::P_DIFFUSE, getRandomTexture(), true, false);
    }

    for (int i = 0; i < GLOSSYMATAMOUNT; ++i)
    {
        gGlossyMaterials[i] = createNode(channel, projectRoot, octaneapi::NT_MAT_DIFFUSE, true);
        connectTo(channel, gGlossyMaterials[i], octaneapi::P_DIFFUSE, getRandomTexture(), true, false);
    }

    if (!gSphereMesh.handle())
    {
        gSphereMesh = createSphere(channel, 2);
        for (int i = 0; i < OBJECTAMOUNT; ++i)
        {
            gMaterialMaps[i] = createNode(channel, projectRoot, octaneapi::NT_MAT_MAP, true);
            connectTo(channel, gMaterialMaps[i], octaneapi::P_GEOMETRY, gSphereMesh, true, false);
        }
    }

    if (!gSpinCube.handle())
    {
        gSpinCube = createCube(channel);
        for (int c = 0; c < CUBEAMOUNT; ++c)
        {
            gMaterialMaps[OBJECTAMOUNT+c] = createNode(channel, projectRoot, octaneapi::NT_MAT_MAP, true);
            connectTo(channel, gMaterialMaps[OBJECTAMOUNT+c], octaneapi::P_GEOMETRY, gSpinCube, true, false);
        }

        gCubePlacementNode = createNode(channel, projectRoot, octaneapi::NT_GEO_PLACEMENT, true);

        octaneapi::ObjectRef cubeTexture = createNode(channel, projectRoot, octaneapi::NT_TEX_RGB, true);
        octaneapi::ApiItem::setValueByIDRequest request;
        octaneapi::float_3 * v3 = request.mutable_float3_value();
        v3->set_x(0);
        v3->set_y(1);
        v3->set_z(0);
        set(channel, cubeTexture, octaneapi::A_VALUE, request, true);
        gCubeMat = createNode(channel, projectRoot, octaneapi::NT_MAT_DIFFUSE, true);
        connectTo(channel, gCubeMat, octaneapi::P_DIFFUSE, cubeTexture, true, false);
    }

    for (int i = 0; i < OBJECTAMOUNT; ++i)
    {
        octaneapi::ObjectRef matMap = gMaterialMaps[i];
        int base = staticPinCount(channel, matMap);
        connectToIx(channel, matMap, base + 0, getRandomDiffuseMat(), true, false);
        connectToIx(channel, matMap, base + 1, getRandomGlossyMat(), true, false);
    }

    for (int c = 0; c < CUBEAMOUNT; ++c)
    {
        octaneapi::ObjectRef matMap = gMaterialMaps[OBJECTAMOUNT+c];
        connectToIx(channel, matMap, staticPinCount(channel, matMap) + 0, gCubeMat, true, false);
    }
}


void makeSimpleScene(
    std::shared_ptr<grpc::Channel> & channel,
    octaneapi::ObjectRef &           renderTargetNode)
{
    octaneapi::ObjectRef projectRoot;
    rootNodeGraph(channel, projectRoot);
    octaneapi::ObjectRef geoGroup;
    if (connectedNode(channel, renderTargetNode, octaneapi::P_MESH, false, geoGroup))
    {
        octaneapi::ApiItem::setValueByIDRequest request;
        request.set_int_value(OBJECTAMOUNT + CUBEAMOUNT);
        set(channel, geoGroup, octaneapi::A_PIN_COUNT, request, true);
    }

    initMaterials(channel);

    // creates instances of the meshes and connects them with the geometry group
    for (int i = 0; i < OBJECTAMOUNT; ++i)
    {
        const float t = sqrtf(i * 0.001f);
        auto scatter = createNode(channel, projectRoot, octaneapi::NT_GEO_SCATTER, true);
        const Float3 translation = { sinf(120.0f * t) * t * 30.0f,
            t * 15.0f,
            cosf(120.0f * t) * t * 30.0f };
        const octaneapi::MatrixF mat = makeTranslationMatrix(translation.x, translation.y, translation.z);
        setArray(channel, scatter, octaneapi::A_TRANSFORMS, &mat, 1, true);
        connectTo(channel, scatter, octaneapi::P_GEOMETRY, gMaterialMaps[i], true, false);
        connectToIx(channel, geoGroup, i, scatter, true, false);
    }

    {
        const octaneapi::MatrixF mat = makeTranslationMatrix(gCubeInitTranslate.x, gCubeInitTranslate.y, gCubeInitTranslate.z);
        octaneapi::ApiNode::setPinValueByIDRequest request;
        auto * v = request.mutable_matrix_value();
        *v = mat;
        setPinValue(channel, gCubePlacementNode, octaneapi::P_TRANSFORM, request, true);
        connectTo(channel, gCubePlacementNode, octaneapi::P_GEOMETRY, gMaterialMaps[OBJECTAMOUNT], true, false);
        connectToIx(channel, geoGroup, OBJECTAMOUNT, gCubePlacementNode, true, false);
    }

    // set up camera
    auto camera = createNode(channel, projectRoot, octaneapi::NT_CAM_THINLENS, true);

    {
        octaneapi::ApiNode::setPinValueByIDRequest request1;
        auto * v = request1.mutable_float3_value();
        v->set_x(0.0f);
        v->set_y(0.0f);
        v->set_z(0.0f);
        setPinValue(channel, camera, octaneapi::P_TARGET, request1, true);
    }

    {
        octaneapi::ApiNode::setPinValueByIDRequest request;
        auto * v = request.mutable_float3_value();
        v->set_x(10.0f);
        v->set_y(-2.0f);
        v->set_z(10.0f);
        setPinValue(channel, camera, octaneapi::P_POSITION, request, true);
    }
    connectTo(channel, renderTargetNode, octaneapi::P_CAMERA, camera, true, false);

    // set up environment
    auto env = createNode(channel, projectRoot, octaneapi::NT_ENV_DAYLIGHT, true);
    createInternal(channel, env, octaneapi::P_SUN_DIR, octaneapi::NT_FLOAT, true, true);

    {
        octaneapi::ApiNode::setPinValueByIDRequest request;
        auto [nx, ny, nz] = normalized(-10.0f, 0.1f, -5.0f);
        auto * v = request.mutable_float3_value();
        v->set_x(nx);
        v->set_y(ny);
        v->set_z(nz);
        setPinValue(channel, env, octaneapi::P_SUN_DIR, request, true);
    }

    {
        octaneapi::ApiNode::setPinValueByIDRequest request;
        request.set_int_value(octaneapi::DAYLIGHTMODEL_OCTANE);
        setPinValue(channel, env, octaneapi::P_MODEL, request, true);
    }
    connectTo(channel, renderTargetNode, octaneapi::P_ENVIRONMENT, env, true, false);

    // set up kernel
    auto kernel = createNode(channel, projectRoot, octaneapi::NT_KERN_PATHTRACING, true);

    {
        octaneapi::ApiNode::setPinValueByIDRequest request;
        request.set_int_value(1000);
        setPinValue(channel, kernel, octaneapi::P_MAX_SAMPLES, request, true);
    }
    connectTo(channel, renderTargetNode, octaneapi::P_KERNEL, kernel, true, false);
}


void saveAsBMP(
    const std::string & filename,
    const uint8_t *     pixelData,
    int                 width,
    int                 height)
{
    const uint32_t rowSize = width * 4; // 4 bytes per pixel (BGRA)
    const uint32_t imageSize = rowSize * height;
    const uint32_t fileSize = 14 + 40 + imageSize;

    std::ofstream out(filename, std::ios::binary);
    if (!out)
    {
        throw std::runtime_error("Unable to open file for writing");
    }

    // BITMAPFILEHEADER
    out.put('B');
    out.put('M');
    out.write(reinterpret_cast<const char*>(&fileSize), 4);
    uint32_t reserved = 0;
    out.write(reinterpret_cast<const char*>(&reserved), 4);
    uint32_t pixelDataOffset = 14 + 40;
    out.write(reinterpret_cast<const char*>(&pixelDataOffset), 4);

    // BITMAPINFOHEADER
    uint32_t infoHeaderSize = 40;
    out.write(reinterpret_cast<const char*>(&infoHeaderSize), 4);
    out.write(reinterpret_cast<const char*>(&width), 4);
    out.write(reinterpret_cast<const char*>(&height), 4);
    uint16_t planes = 1;
    out.write(reinterpret_cast<const char*>(&planes), 2);
    uint16_t bitsPerPixel = 32;
    out.write(reinterpret_cast<const char*>(&bitsPerPixel), 2);
    uint32_t compression = 0;
    out.write(reinterpret_cast<const char*>(&compression), 4);
    out.write(reinterpret_cast<const char*>(&imageSize), 4);
    uint32_t ppm = 2835; // 72 DPI
    out.write(reinterpret_cast<const char*>(&ppm), 4); // x pixels per meter
    out.write(reinterpret_cast<const char*>(&ppm), 4); // y pixels per meter
    uint32_t colorsUsed = 0;
    out.write(reinterpret_cast<const char*>(&colorsUsed), 4);
    uint32_t importantColors = 0;
    out.write(reinterpret_cast<const char*>(&importantColors), 4);

    // Write pixel data — BMP expects BGRA
    for (int y = height - 1; y >= 0; --y) // BMP stores pixels bottom to top
    {
        const uint8_t * rowPtr = pixelData + (y * width * 4);
        for (int x = 0; x < width; ++x)
        {
            uint8_t r = rowPtr[x * 4 + 0];
            uint8_t g = rowPtr[x * 4 + 1];
            uint8_t b = rowPtr[x * 4 + 2];
            uint8_t a = rowPtr[x * 4 + 3];

            out.put(b);
            out.put(g);
            out.put(r);
            out.put(a); // Alpha channel (BGRA format)
        }
    }

    out.close();
}


void renderScene(
    std::shared_ptr<grpc::Channel> & channel)
{
    grpc::Status status = grpc::Status::OK;

    resetProject(channel);

    octaneapi::ObjectRef projectRoot;
    rootNodeGraph(channel, projectRoot);
    octaneapi::ObjectRef renderTarget = createNode(channel, projectRoot, octaneapi::NT_RENDERTARGET, true);
    setRenderTargetNode(channel, renderTarget);

    octaneapi::ObjectRef geoNode = createNode(channel, projectRoot, octaneapi::NT_GEO_GROUP, true);
    connectTo(channel, renderTarget, octaneapi::P_MESH, geoNode, true, false);

    makeSimpleScene(channel, renderTarget);

    octaneapi::ObjectRef renderPasses = createNode(channel, projectRoot, octaneapi::NT_RENDER_PASSES, true); 
    connectTo(channel, renderTarget, octaneapi::P_RENDER_PASSES, renderPasses, true, false);
    changeManagerUpdate(channel);
}


void testApi(std::shared_ptr<grpc::Channel> & channel)
{
    try {

       /* std::string cpuVendor_;
        std::string cpuModel_;
        uint32_t clockSpeedMhz_;
        uint32_t nbCores_;
        ApiInfoProxy::cpuInfo(cpuVendor_, cpuModel_, clockSpeedMhz_, nbCores_);

        std::string  base64test = "base64test";
        Octane::CharArrayT encodedText;
        Octane::CharArrayT decodedText;
        if (ApiBase64Proxy::encode(base64test.c_str(), base64test.length(), encodedText, false))
        {
            ApiBase64Proxy::decode(encodedText.mData, encodedText.mSize, decodedText, false);
        }

        int version = ApiInfoProxy::octaneVersion();
        std::vector<Octane::NodePinType> pinTypes;
        size_t numPinTypes = 0;
        ApiInfoProxy::getPinTypes(pinTypes, numPinTypes);*/
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "General exception: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unknown exception occurred." << std::endl;
    }
}


bool canConnectToServer(const std::string& serverURL)
{
    // Minimal check: create a channel and see if we can connect within a brief timeout
    auto channel = grpc::CreateChannel(serverURL, grpc::InsecureChannelCredentials());
    auto timeout = std::chrono::system_clock::now() + std::chrono::seconds(1);
    if (!channel->WaitForConnected(timeout)) {
        return false;
    }
    return true;
}


int main(int    argc,
         char * argv[])
{
    std::cout << "GRPC API Example render app!\n";
    if (argc < 2 )
    {
        std::cout << "GRPC API Example closing (no args)\n";
        return 1;
    }
 
    gServerURL = std::string(argv[1]);
    if (argc >= 2 && argv[2])
    {
        gImageDumpPath = std::string(argv[2]);
    }

    {
        std::cout << "Attempting to connect to: " << gServerURL << "\n";
        if (!canConnectToServer(gServerURL))
        {
            std::cout << "Failed to connect to gRPC server at " << gServerURL << ". Exiting.\n";
            return 1;
        }

        std::cout << "Connecting to octane.exe on " << gServerURL << "\n";

        auto channel = grpc::CreateChannel(gServerURL, grpc::InsecureChannelCredentials());

        {
            GRPCAPIEvents serverEvents(channel);
            serverEvents.initConnection();
            serverEvents.waitForEvents();

            // call some methods on the API and render a scene
            testApi(channel);

            // render a scene in octane.exe
            renderScene(channel);

            // pause before shutting down events so we can get the last newImage event
            // optionally wait until the render is complete
            std::this_thread::sleep_for(std::chrono::seconds(5));

            serverEvents.shutdown();
        }
        std::cout << "Server stopped. Exiting.\n";
    }
    return 0;
}


void GRPCAPIEvents::initConnection()
{
    //  Important: Keep ClientContext alive for entire stream duration
    mContext = std::make_unique<grpc::ClientContext>();

    google::protobuf::Empty emptyReq;

    // Open bidirectional stream
    mStream = mStub->callbackChannel(mContext.get(), emptyReq);

    std::cout << "[Client] Stream created.\n";
}


void GRPCAPIEvents::waitForEvents()
{
    // Start background thread to handle incoming messages
    mReaderThread = std::thread([this] {
        StreamCallbackRequest request;
        while (!mShutdownRequested && mStream->Read(&request))
        {
            HandleCallback(request);
        }
        std::cout << "[Client] Server closed the stream.\n";
        });
}


void GRPCAPIEvents::shutdown()
{
    mShutdownRequested = true; // Tell threads to stop

    // Optionally close writes and wait for stream to finish
    if (mStream)
    {
        //mStream->WritesDone(); // Let server know we're done writing
        mContext.get()->TryCancel();
        grpc::Status status = mStream->Finish();
        if (!status.ok())
        {
            std::cerr << "[Client] Stream ended with error: " << status.error_message() << "\n";
        }
        else
        {
            std::cout << "[Client] Stream ended cleanly.\n";
        }

        if (mReaderThread.joinable())
        {
            mReaderThread.join();// Wait for reading to stop
        }
    }
}


void GRPCAPIEvents::HandleCallback(
    const octaneapi::StreamCallbackRequest & request)
{
    if (mShutdownRequested)
    {
        std::cerr << "[Client] Shutdown in progress; ignoring callback.\n";
        return;
    }

    switch (request.payload_case())
    {
        case octaneapi::StreamCallbackRequest::kNewStatistics:
        {
            std::cout << "[Client] Received callback of type: kNewStatistics \n";
            auto reqData = request.newstatistics();
         //   CallbackStorage::invokeOnNewStatisticsCallback(0, (void*) reqData.user_data());
            break;
        }
        case octaneapi::StreamCallbackRequest::kRenderFailure:
        {
            std::cout << "[Client] Received callback of type: kRenderFailure \n";
            auto reqData = request.renderfailure();
         //  CallbackStorage::invokeOnRenderFailureCallback(0, (void*) reqData.user_data());
            break;
        }
        case octaneapi::StreamCallbackRequest::kProjectManagerChanged:
        {
            std::cout << "[Client] Received callback of type: kProjectManagerChanged \n";
            auto reqData = request.projectmanagerchanged();
           // CallbackStorage::invokeGRPCProjectManagerObserver(0, (void*) reqData.user_data());
            break;
        }
        case octaneapi::StreamCallbackRequest::kNewImage:
        {
            std::cout << "[Client] Received callback of type: kNewImage \n";
            std::vector<RenderedImage> renderImages;
            if (!grabRenderResult(mChannel, renderImages))
            {
                // call releaseRenderResult on the server inside grabRenderResult and try to change to vector instead of ApiArray
                return;
            }
            // process all the rendered images
            for (size_t i = 0; i < renderImages.size(); ++i)
            {
                const RenderedImage & renderImage = renderImages[i]; 

                // create new ARGB image
                const size_t            dstPitch = renderImage.mSizeX * 4;// imgData.lineStride;
                uint8_t * pixelData = new uint8_t[renderImage.mSizeX * renderImage.mSizeY * 4];
                uint8_t * dst = pixelData;
                switch (renderImage.mType)
                {
                    case  Octane::IMAGE_TYPE_LDR_RGBA:
                    {
                        const unsigned char *src = (const unsigned char*)renderImage.mBuffer;
                        const size_t        srcPitch = renderImage.mPitch * 4;
                        for (unsigned int y=0; y<renderImage.mSizeY; ++y, src+=srcPitch, dst+=dstPitch)
                        {
                            const unsigned char *srcPixel = src;
                            unsigned char       *dstPixel = dst;
                            for (unsigned int x = 0; x < renderImage.mSizeX; ++x, srcPixel += 4, dstPixel += 4)
                            {
                                dstPixel[0] = srcPixel[0];
                                dstPixel[1] = srcPixel[1];
                                dstPixel[2] = srcPixel[2];
                                dstPixel[3] = 0xff;
                            }
                        }
                        break;
                    }
                    case  Octane::IMAGE_TYPE_LDR_MONO_ALPHA:
                    {
                        const unsigned char *src = (const unsigned char*)renderImage.mBuffer;
                        const size_t        srcPitch = renderImage.mPitch * 2;
                        for (unsigned int y=0; y<renderImage.mSizeY; ++y, src+=srcPitch, dst+=dstPitch)
                        {
                            const unsigned char *srcPixel = src;
                            unsigned char       *dstPixel = dst;
                            for (unsigned int x=0; x<renderImage.mSizeX; ++x, srcPixel+=2, dstPixel+=4)
                            {
                                dstPixel[0] = srcPixel[0];
                                dstPixel[1] = srcPixel[0];
                                dstPixel[2] = srcPixel[0];
                                dstPixel[3] = 0xff;
                            }
                        }
                        break;
                    }
                    case  Octane::IMAGE_TYPE_HDR_RGBA:
                    {
                        const float  *src = (const float*)renderImage.mBuffer;
                        const size_t srcPitch = renderImage.mPitch * 4;
                        for (unsigned int y = 0; y < renderImage.mSizeY; ++y, src+=srcPitch, dst+=dstPitch)
                        {
                            const float   *srcPixel = src;
                            unsigned char *dstPixel = dst;
                            for (unsigned int x=0; x<renderImage.mSizeX; ++x, srcPixel+=4, dstPixel+=4)
                            {
                                dstPixel[0] = (unsigned char)std::clamp(srcPixel[0] * 255.f, 0.f, 255.f);
                                dstPixel[1] = (unsigned char)std::clamp(srcPixel[1] * 255.f, 0.f, 255.f);
                                dstPixel[2] = (unsigned char)std::clamp(srcPixel[2] * 255.f, 0.f, 255.f);
                                dstPixel[3] = 0xff;
                            }
                        }
                        break;
                    }
                    case  Octane::IMAGE_TYPE_HDR_MONO_ALPHA:
                    {
                        const float  *src = (const float*)renderImage.mBuffer;
                        const size_t srcPitch = renderImage.mPitch * 2;
                        for (unsigned int y=0; y<renderImage.mSizeY; ++y, src+=srcPitch, dst+=dstPitch)
                        {
                            const float   *srcPixel = src;
                            unsigned char *dstPixel = dst;
                            for (unsigned int x = 0; x < renderImage.mSizeX; ++x, srcPixel += 2, dstPixel += 4)
                            {
                                dstPixel[0] = (unsigned char)std::clamp(srcPixel[0] * 255.f, 0.f, 255.f);
                                dstPixel[1] = (unsigned char)std::clamp(srcPixel[0] * 255.f, 0.f, 255.f);
                                dstPixel[2] = (unsigned char)std::clamp(srcPixel[0] * 255.f, 0.f, 255.f);
                                dstPixel[3] = 0xff;
                            }
                        }
                    }
                }

                if (gImageDumpPath != "")
                {
                    std::string path = gImageDumpPath;
                    path.append("/__test.bmp");
                    saveAsBMP(path, pixelData, renderImage.mSizeX, renderImage.mSizeY);
                }
        
                // delete the data
                if (pixelData)
                {
                    delete[] pixelData;
                }
                if (renderImage.mBuffer)
                {
                    delete[] renderImage.mBuffer;
                }
            }

            break;
        }
        default:
            std::cerr << "[Client] Unknown callback type received.\n"; 
            break;
    }
}