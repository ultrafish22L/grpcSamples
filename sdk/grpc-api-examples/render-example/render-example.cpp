// Copyright (C) 2025 OTOY NZ Ltd.

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
// application headers
#include "grpcsettings.h"
#include "apiinfoclient.h"
#include "apibase64client.h"
#include "apiprojectmanagerclient.h"
#include "apinodeclient.h"
#include "apicontrol.h"
#include "apirenderengineclient.h"
#include "apichangemanagerclient.h"
#include "apirootnodegraphclient.h"
#include "convertapiarrayapirenderimage.h"
#include "callback.grpc.pb.h"  // Generated stub

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReaderWriter;
using grpc::Status;
using namespace octaneapi;

/// Determines the size of a 1D C array in elements.
#define ARRAY_WIDTH(a)  (sizeof(a) / sizeof(a[0]))

std::string gServerURL = "127.0.0.1:50051";
std::string gClientURL = "127.0.0.1:50052";
std::string gImageDumpPath;


#ifdef _WIN32
#include <windows.h>
#elif defined(__linux__)
#include <unistd.h>
#include <limits.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#endif

class GRPCAPIEvents
{
public:
    GRPCAPIEvents(std::shared_ptr<grpc::Channel> channel)
        : mStub(StreamCallbackService::NewStub(channel)) {}

    void initConnection();

    void waitForEvents();

    void shutdown();

private:
    std::unique_ptr<StreamCallbackService::Stub> mStub;
    std::unique_ptr<grpc::ClientContext> mContext;
    std::unique_ptr<grpc::ClientReader<StreamCallbackRequest>> mStream;
    std::thread mReaderThread;
    std::atomic<bool> mShutdownRequested = false;
    void HandleCallback(
        const StreamCallbackRequest & request);
};

static Octane::float_3 SPHERE_VERTICES[43] =
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


static Octane::float_3 CUBE_VERTICES[] =
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


static ApiNodeProxy       gImageTextures[IMGTEXAMOUNT];
static ApiNodeProxy       gRgbTextures[RGBTEXAMOUNT];
static ApiNodeProxy       gDiffuseMaterials[DIFFUSEMATAMOUNT];
static ApiNodeProxy       gGlossyMaterials[GLOSSYMATAMOUNT];
static ApiNodeProxy       gMaterialMaps[OBJECTAMOUNT + CUBEAMOUNT];
static ApiNodeProxy       gSphereMesh;
static ApiNodeProxy       gSpinCube;
static ApiNodeProxy       gRenderTarget;
static ApiNodeProxy       gRenderPasses;
static Octane::float_3    gCubeInitTranslate = { 0, -2.2f, 0 };
static ApiNodeProxy       gCubePlacementNode;
static ApiNodeProxy       gCubeMat;

grpc::ServerBuilder  mBuilder;
std::unique_ptr<grpc::Server> mServer;


static const uint32_t INIT_LCG_SEED = 123456789;
static uint32_t       gRandomState = INIT_LCG_SEED;

// Calculates a new LCG random number.
static inline void updateLcgRandom()
{
    gRandomState = gRandomState * 1664525 + 1013904223;
}


void resetLcg()
{
    gRandomState = INIT_LCG_SEED;
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


// hack required to compile, else we get unresolved external errors
Octane::ApiTextureValueTypeSet::ApiTextureValueTypeSet(uint32_t bitfield)
{

}


Octane::ApiCompatibilityModeInfoSet::ApiCompatibilityModeInfoSet(void)
{

}

static ApiNodeProxy * getRandomRgbTexture()
{
    return &(gRgbTextures[lcgRandomRange(RGBTEXAMOUNT)]);
}


static ApiNodeProxy * getRandomImgTexture()
{
    return &(gImageTextures[lcgRandomRange(IMGTEXAMOUNT)]);
}


static ApiNodeProxy * getRandomTexture()
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


static ApiNodeProxy * getRandomMaterialMap()
{
    return &(gMaterialMaps[lcgRandomRange(OBJECTAMOUNT)]);
}


static ApiNodeProxy * getRandomDiffuseMat()
{
    return &(gDiffuseMaterials[lcgRandomRange(DIFFUSEMATAMOUNT)]);
}


static ApiNodeProxy * getRandomGlossyMat()
{
    return &(gGlossyMaterials[lcgRandomRange(GLOSSYMATAMOUNT)]);
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


ApiNodeProxy createSphere( const unsigned int matCount)
{
    ApiRootNodeGraphProxy  projectRoot = ApiProjectManagerProxy::rootNodeGraph();

    // create sphere
    ApiNodeProxy meshNode = ApiNodeProxy::create(Octane::NT_GEO_MESH, projectRoot, true);
    // set sphere geometry
    const std::vector<int32_t> vertsPerPoly(ARRAY_WIDTH(SPHERE_FACES) / 3, 3);
    meshNode.set(Octane::A_VERTICES_PER_POLY, vectorBuffer(vertsPerPoly), vertsPerPoly.size(), false);
    meshNode.set(Octane::A_VERTICES, SPHERE_VERTICES, ARRAY_WIDTH(SPHERE_VERTICES), false);
    meshNode.set(Octane::A_UVWS, SPHERE_VERTICES, ARRAY_WIDTH(SPHERE_VERTICES), false);
    meshNode.set(Octane::A_NORMALS, SPHERE_VERTICES, ARRAY_WIDTH(SPHERE_VERTICES), false);
    meshNode.set(Octane::A_POLY_VERTEX_INDICES, SPHERE_FACES, ARRAY_WIDTH(SPHERE_FACES), false);
    meshNode.set(Octane::A_POLY_UVW_INDICES, SPHERE_FACES, ARRAY_WIDTH(SPHERE_FACES), false);
    meshNode.set(Octane::A_POLY_NORMAL_INDICES, SPHERE_FACES, ARRAY_WIDTH(SPHERE_FACES), false);

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
    meshNode.set(Octane::A_MATERIAL_NAMES, vectorBuffer(matNames), matCount, false);

    // assign materials to faces
    std::vector<int32_t> polyMatIndices(vertsPerPoly.size());
    for (int32_t i=0; i<polyMatIndices.size(); ++i) { polyMatIndices[i] = i % matCount; }
    meshNode.set(Octane::A_POLY_MATERIAL_INDICES, vectorBuffer(polyMatIndices), polyMatIndices.size(), false);

    // evaluate the mesh
    meshNode.evaluate();

    return meshNode;
}


ApiNodeProxy createCube()
{
    ApiRootNodeGraphProxy projectRoot = ApiProjectManagerProxy::rootNodeGraph();
    ApiNodeProxy meshNode = ApiNodeProxy::create(Octane::NT_GEO_MESH, projectRoot, true);

    // set cube geometry
    const std::vector<int32_t> vertsPerPoly(ARRAY_WIDTH(CUBE_FACES) / 3, 3);
    meshNode.set(Octane::A_VERTICES_PER_POLY,   vectorBuffer(vertsPerPoly), vertsPerPoly.size(),        false);
    meshNode.set(Octane::A_VERTICES,            CUBE_VERTICES,              ARRAY_WIDTH(CUBE_VERTICES), false);
    meshNode.set(Octane::A_UVWS,                CUBE_VERTICES,              ARRAY_WIDTH(CUBE_VERTICES), false);
    meshNode.set(Octane::A_NORMALS,             CUBE_VERTICES,              ARRAY_WIDTH(CUBE_VERTICES), false);
    meshNode.set(Octane::A_POLY_VERTEX_INDICES, CUBE_FACES,                 ARRAY_WIDTH(CUBE_FACES),    false);
    meshNode.set(Octane::A_POLY_UVW_INDICES,    CUBE_FACES,                 ARRAY_WIDTH(CUBE_FACES),    false);
    meshNode.set(Octane::A_POLY_NORMAL_INDICES, CUBE_FACES,                 ARRAY_WIDTH(CUBE_FACES),    false);

    // set material names
    std::vector<const char*> matNames;
    matNames.push_back("Material 1");
    meshNode.set(Octane::A_MATERIAL_NAMES, vectorBuffer(matNames), 1, false);

    // assign materials to faces
    std::vector<int32_t> polyMatIndices(vertsPerPoly.size());
    for (int32_t i = 0; i < polyMatIndices.size(); ++i)
    {
        polyMatIndices[i] = 0;
    }
    meshNode.set(Octane::A_POLY_MATERIAL_INDICES, vectorBuffer(polyMatIndices), polyMatIndices.size(), false);

    // evaluate the mesh
    meshNode.evaluate();

    return meshNode;
}


void initMaterials()
{
    std::string texFiles[IMGTEXAMOUNT] =
    {
        "textures\\Bokeh2.jpg",
        "textures\\Mineral.jpg",
        "textures\\MultiScatter8.jpg",
        "textures\\OctaneDLDiffuse.jpg",
        "textures\\OctaneLogo.png"
    };

    ApiRootNodeGraphProxy projectRoot = ApiProjectManagerProxy::rootNodeGraph();
    
    std::filesystem::path exePath = getExecutablePath();
    std::filesystem::path parentDir = exePath.parent_path().parent_path().parent_path();
    for (int i = 0; i < IMGTEXAMOUNT; ++i)
    {
        gImageTextures[i] = ApiNodeProxy::create(Octane::NT_TEX_IMAGE, projectRoot, true);

        std::filesystem::path texFilePath = parentDir / texFiles[i];
        std::string fullPath = texFilePath.string();  // Converts to platform-native string

        gImageTextures[i].set(Octane::A_FILENAME, fullPath.c_str(), true);
    }

    for (int i = 0; i < RGBTEXAMOUNT; ++i)
    {
        gRgbTextures[i] = ApiNodeProxy::create(Octane::NT_TEX_RGB, projectRoot, true);
        gRgbTextures[i].set(Octane::A_VALUE,
            Octane::float_3::make(lcgRandomFloat(),
                lcgRandomFloat(),
                lcgRandomFloat()), true);
    }

    for (int i = 0; i < DIFFUSEMATAMOUNT; ++i)
    {
        gDiffuseMaterials[i] = ApiNodeProxy::create(Octane::NT_MAT_DIFFUSE, projectRoot, true);
        gDiffuseMaterials[i].connectTo(Octane::P_DIFFUSE, getRandomTexture(), true, false);
    }

    for (int i = 0; i < GLOSSYMATAMOUNT; ++i)
    {
        gGlossyMaterials[i] = ApiNodeProxy::create(Octane::NT_MAT_DIFFUSE, projectRoot, true);
        gGlossyMaterials[i].connectTo(Octane::P_DIFFUSE, getRandomTexture(), true, false);
    }

    if (gSphereMesh.isNull())
    {
        gSphereMesh = createSphere(2);
        for (int i = 0; i < OBJECTAMOUNT; ++i)
        {
            gMaterialMaps[i] = ApiNodeProxy::create(Octane::NT_MAT_MAP, projectRoot, true);
            gMaterialMaps[i].connectTo(Octane::P_GEOMETRY, &gSphereMesh, true, false);
        }
    }

    if (gSpinCube.isNull())
    {
        gSpinCube = createCube();
        for (int c = 0; c < CUBEAMOUNT; ++c)
        {
            gMaterialMaps[OBJECTAMOUNT+c] =  ApiNodeProxy::create(Octane::NT_MAT_MAP, projectRoot, true);
            gMaterialMaps[OBJECTAMOUNT+c].connectTo(Octane::P_GEOMETRY, &gSpinCube, true, false);
        }

        gCubePlacementNode =  ApiNodeProxy::create(Octane::NT_GEO_PLACEMENT,projectRoot, true);

        ApiNodeProxy cubeTexture =  ApiNodeProxy::create(Octane::NT_TEX_RGB, projectRoot, true);
        cubeTexture.set(Octane::A_VALUE, Octane::float_3::make(0, 1, 0), true);
        gCubeMat = ApiNodeProxy::create(Octane::NT_MAT_DIFFUSE, projectRoot, true);
        gCubeMat.connectTo(Octane::P_DIFFUSE, &cubeTexture, true, false);
    }

    for (int i = 0; i < OBJECTAMOUNT; ++i)
    {
        ApiNodeProxy * matMap = &gMaterialMaps[i];
        matMap->connectToIx(matMap->staticPinCount() + 0, getRandomDiffuseMat(), true, false);
        matMap->connectToIx(matMap->staticPinCount() + 1, getRandomGlossyMat(), true, false);
    }

    for (int c = 0; c < CUBEAMOUNT; ++c)
    {
        ApiNodeProxy * matMap = &gMaterialMaps[OBJECTAMOUNT+c];
        matMap->connectToIx(matMap->staticPinCount() + 0, &gCubeMat, true, false);
    }
}


void makeSimpleScene(
    ApiNodeProxy * renderTargetNpde)
{
    ApiRootNodeGraphProxy projectRoot = ApiProjectManagerProxy::rootNodeGraph();
    ApiNodeProxy geoGroup = renderTargetNpde->connectedNode(Octane::P_MESH, false);
    geoGroup.set(Octane::A_PIN_COUNT, OBJECTAMOUNT+CUBEAMOUNT, true);

    try
    {
        initMaterials();
    }
    catch (const std::exception & e)
    {
        std::cerr << "initMaterials exception: " << e.what() << std::endl;
    }

    // creates instances of the meshes and connects them with the geometry group
    for (int i = 0; i < OBJECTAMOUNT; ++i)
    {
        const float t = sqrtf(i * 0.001f);

        ApiNodeProxy scatter = ApiNodeProxy::create(Octane::NT_GEO_SCATTER, projectRoot, true);
        const Octane::float_3 translation = { sinf(120.0f * t) * t * 30.0f,
            t * 15.0f,
            cosf(120.0f * t) * t * 30.0f };

        const OctaneVec::MatrixF mat = Octane::MatrixF::makeTranslation(translation);
        scatter.set(Octane::A_TRANSFORMS, &mat, 1, true);

        scatter.connectTo(Octane::P_GEOMETRY, &(gMaterialMaps[i]), true, false);
        geoGroup.connectToIx(i, &scatter, true, false);
    }
    {
        const Octane::MatrixF mat = Octane::MatrixF::makeTranslation(gCubeInitTranslate);
        gCubePlacementNode.setPinValue(Octane::P_TRANSFORM, mat, true);

        gCubePlacementNode.connectTo(Octane::P_GEOMETRY, &(gMaterialMaps[OBJECTAMOUNT]), true, false);
        geoGroup.connectToIx(OBJECTAMOUNT, &gCubePlacementNode, true, false);
    }

    // set up camera
    ApiNodeProxy camera = ApiNodeProxy::create(Octane::NT_CAM_THINLENS, projectRoot, true);
    camera.setPinValue(Octane::P_TARGET, Octane::float_3::make(0.0f, 0.0f, 0.0f), true);
    camera.setPinValue(Octane::P_POSITION, Octane::float_3::make(10.0f, -2.0f, 10.0f), true);
    renderTargetNpde->connectTo(Octane::P_CAMERA, &camera, true, false);

    // set up environment
    ApiNodeProxy env = ApiNodeProxy::create(Octane::NT_ENV_DAYLIGHT, projectRoot, true);
    env.createInternal(Octane::P_SUN_DIR, Octane::NT_FLOAT, true, true);
    env.setPinValue(Octane::P_SUN_DIR, normalized(Octane::float_3::make(-10.0f, 0.1f, -5.0f)), true);
    env.setPinValue(Octane::P_MODEL, Octane::DAYLIGHTMODEL_OCTANE, true);
    renderTargetNpde->connectTo(Octane::P_ENVIRONMENT, &env, true, false);

    // set up kernel
    ApiNodeProxy kernel = ApiNodeProxy::create(Octane::NT_KERN_PATHTRACING, projectRoot, true);
    kernel.setPinValue(Octane::P_MAX_SAMPLES, 1000, true);
    renderTargetNpde->connectTo(Octane::P_KERNEL, &kernel, true, false);
}

// Assumes pixelData is RGB, 8 bits per channel (i.e., 3 bytes per pixel)
// Total buffer size: width * height * 3

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
    if (!out) {
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


void OnNewImageCallback(
    const  ApiArray<Octane::ApiRenderImage> & renderImages,
    void *                                    userData)
{

    //Octane::ApiArray<Octane::ApiRenderImage> renderImages;
    //if (!ApiRenderEngineProxy::grabRenderResult(renderImages)) 
    //{
    //    // call releaseRenderResult on the server inside grabRenderResult and try to change to vector istnead of ApiArray
    //    return; 
    //}

    // process all the rendered images
    for (size_t i = 0; i < renderImages.mSize; ++i)
    {
        const Octane::ApiRenderImage & renderImage = renderImages.mData[i]; 

        // create new ARGB image
        const size_t            dstPitch = renderImage.mSize.x * 4;// imgData.lineStride;
        uint8_t * pixelData = new uint8_t[renderImage.mSize.x * renderImage.mSize.y * 4];
        uint8_t * dst = pixelData;
        switch (renderImage.mType)
        {
            case  Octane::IMAGE_TYPE_LDR_RGBA:
            {
                const unsigned char *src = (const unsigned char*)renderImage.mBuffer;
                const size_t        srcPitch = renderImage.mPitch * 4;
                for (unsigned int y=0; y<renderImage.mSize.y; ++y, src+=srcPitch, dst+=dstPitch)
                {
                    const unsigned char *srcPixel = src;
                    unsigned char       *dstPixel = dst;
                    for (unsigned int x = 0; x < renderImage.mSize.x; ++x, srcPixel += 4, dstPixel += 4)
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
                for (unsigned int y=0; y<renderImage.mSize.y; ++y, src+=srcPitch, dst+=dstPitch)
                {
                    const unsigned char *srcPixel = src;
                    unsigned char       *dstPixel = dst;
                    for (unsigned int x=0; x<renderImage.mSize.x; ++x, srcPixel+=2, dstPixel+=4)
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
                for (unsigned int y = 0; y < renderImage.mSize.y; ++y, src+=srcPitch, dst+=dstPitch)
                {
                    const float   *srcPixel = src;
                    unsigned char *dstPixel = dst;
                    for (unsigned int x=0; x<renderImage.mSize.x; ++x, srcPixel+=4, dstPixel+=4)
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
                for (unsigned int y=0; y<renderImage.mSize.y; ++y, src+=srcPitch, dst+=dstPitch)
                {
                    const float   *srcPixel = src;
                    unsigned char *dstPixel = dst;
                    for (unsigned int x = 0; x < renderImage.mSize.x; ++x, srcPixel += 2, dstPixel += 4)
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
            saveAsBMP(path, pixelData, renderImage.mSize.x, renderImage.mSize.y);
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
}


void OnNewStatisticsCallback(
    void * userData)
{

}


void OnRenderFailureCallback(
    void * userData)
{

}


void OnApiProjectManagerChange(
    void * userData)
{

}


void renderScene()
{
    try
    {
        // set callback functions.
        // When not running as a module using the modulesdk, then only the following callbacks are supported
        ApiRenderEngineProxy::setOnNewImageCallback(OnNewImageCallback, 0);
        ApiRenderEngineProxy::setOnNewStatisticsCallback(OnNewStatisticsCallback, 0);
        ApiRenderEngineProxy::setOnRenderFailureCallback(OnRenderFailureCallback, 0);
        CallbackStorage::registerGRPCProjectManagerObserver(0, OnApiProjectManagerChange);
        /*  alternateively ,call these instead
        CallbackStorage::registerOnNewImageCallback( 0, OnNewImageCallback);
        CallbackStorage::registerOnNewStatisticsCallback( 0, OnNewStatisticsCallback);
        CallbackStorage::registerOnRenderFailureCallback( 0, OnRenderFailureCallback);
        */

        ApiProjectManagerProxy::resetProject();
        ApiRootNodeGraphProxy projectRoot = ApiProjectManagerProxy::rootNodeGraph();
        gRenderTarget = ApiNodeProxy::create(Octane::NT_RENDERTARGET, projectRoot, true);
        ApiRenderEngineProxy::setRenderTargetNode(&gRenderTarget);
        ApiNodeProxy  geoNode = ApiNodeProxy::create(Octane::NT_GEO_GROUP, projectRoot, true);
        gRenderTarget.connectTo(Octane::P_MESH, &geoNode, true, false);
 
        makeSimpleScene(&gRenderTarget);
        gRenderPasses = ApiNodeProxy::create(Octane::NT_RENDER_PASSES, projectRoot, true);
        gRenderTarget.connectTo(Octane::P_RENDER_PASSES, &gRenderPasses, true, false);
        ApiChangeManagerProxy::update();
    }
    catch (const std::runtime_error & e)
    {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    }
    catch (const std::exception & e)
    {
        std::cerr << "General exception: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unknown exception occurred." << std::endl;
    }
}


void testApi()
{
    try {

        std::string cpuVendor_;
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
        ApiInfoProxy::getPinTypes(pinTypes, numPinTypes);
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
    gImageDumpPath = std::string(argv[2]);

    std::cout << "Connecting to octane.exe on "<<gServerURL<<"\n";
    GRPCSettings::getInstance().setServerAddress(gServerURL);
    auto channel = grpc::CreateChannel(gServerURL, grpc::InsecureChannelCredentials());
    
    // Optionally save debug events to a log
    std::string path = "E:\\grpcdebuglog_rendertest.txt";
    if (path != "")
    {
        try
        {
            ApiControlService::setApiLogPath(true, path);
        }
        catch (const std::exception& e)
        {
            std::cout << "Failed to connect to GRPC server. Exiting.\n";
            return 0;
        }
    }

    GRPCAPIEvents serverEvents(channel);
    serverEvents.initConnection();
    serverEvents.waitForEvents();

    // call some methods on the API and render a scene
    testApi();

    // render a scene in octane.exe
    renderScene();

    // pause before shutting down events so we can get the last newImage event
    // optionally wait until the render is complete
    std::this_thread::sleep_for(std::chrono::seconds(5));

    serverEvents.shutdown();
    std::cout << "Server stopped. Exiting.\n";
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
            CallbackStorage::invokeOnNewStatisticsCallback(0, (void*) reqData.user_data());
            break;
        }
        case octaneapi::StreamCallbackRequest::kRenderFailure:
        {
            std::cout << "[Client] Received callback of type: kRenderFailure \n";
            auto reqData = request.renderfailure();
            CallbackStorage::invokeOnRenderFailureCallback(0, (void*) reqData.user_data());
            break;
        }
        case octaneapi::StreamCallbackRequest::kProjectManagerChanged:
        {
            std::cout << "[Client] Received callback of type: kProjectManagerChanged \n";
            auto reqData = request.projectmanagerchanged();
            CallbackStorage::invokeGRPCProjectManagerObserver(0, (void*) reqData.user_data());
            break;
        }
        case octaneapi::StreamCallbackRequest::kNewImage:
        {
            std::cout << "[Client] Received callback of type: kNewImage \n";

            const OnNewImageRequest & img = request.newimage(); //  use correct field name
            std::vector<Octane::ApiRenderImage> renderedImages;
            ApiArrayApiRenderImageConverter::convert(img.render_images(), renderedImages);
            Octane::ApiArray<Octane::ApiRenderImage> images(renderedImages.data(), renderedImages.size());
            CallbackStorage::invokeOnNewImageCallback(0, images, 0);
            break;
        }
        default:
            std::cerr << "[Client] Unknown callback type received.\n"; 
            break;
    }

    // Send back response
    //stream->Write(response);
}