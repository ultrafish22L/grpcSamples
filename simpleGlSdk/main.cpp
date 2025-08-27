#ifdef _WIN32
#include <windows.h>  // Include Windows headers first to define LONGLONG
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>
#include <mutex>
#include <atomic>
#include <vector>

#include "shared_rendering.h"
#include "../shared/camera_system.h"
#include "../shared/model_manager.h"

// SDK integration (using actual SDK calls)
#include "../shared/camera_sync_livelink.h"
#include "../shared/camera_sync_sdk.h"

#ifdef DO_GRPC_SDK_ENABLED
#include "grpcsettings.h"
#include "apirenderengineclient.h"
#include "apinodeclient.h"
#include "octaneids.h"
#include "octanevectypes.h"
#include "apirender.h"
#include "apisharedsurface.h"
using namespace OctaneVec;
#endif

// Windows-specific includes for shared surface implementation
#ifdef _WIN32
#include <d3d11.h>
#include <dxgi1_2.h>
#include <GL/wglext.h>
#include <comdef.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#endif

// Window dimensions
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;

// Global objects using shared systems
SharedUtils::CameraController cameraController;
SharedUtils::ModelManager modelManager;
SharedUtils::RendererGl renderer;
CameraSyncSdk cameraSync;
//CameraSyncLiveLink cameraSync; 
GLuint mTextureNameGL = 0;
bool showTestQuad = true;

// Rendering mode enumeration
enum RenderMode {
    RENDER_MODE_CALLBACK,      // Cross-platform callback approach
    RENDER_MODE_SHARED_SURFACE // Windows-only high-performance shared surface
};

// Global variables for callback-based rendering
#ifdef DO_GRPC_SDK_ENABLED
std::mutex g_renderImageMutex;
std::vector<Octane::ApiRenderImage> g_latestRenderImages;
bool g_hasNewRenderData = false;
bool g_hasSharedSurfaceData = false;
std::atomic<int> g_callbackCount{0};
bool g_callbackRegistered = false;
RenderMode g_renderMode = RENDER_MODE_CALLBACK;
#endif

// Windows-specific shared surface variables
#ifdef _WIN32
// D3D11 device and context
ID3D11Device* g_d3d11Device = nullptr;
ID3D11DeviceContext* g_d3d11Context = nullptr;
ID3D11Texture2D* g_sharedTexture = nullptr;
HANDLE g_sharedHandle = nullptr;
uint64_t g_adapterLuid = 0;

// OpenGL interop
HANDLE g_glD3DDevice = nullptr;
HANDLE g_glSharedTexture = nullptr;
GLuint g_sharedTextureGL = 0;

// WGL extension function pointers
PFNWGLDXOPENDEVICENVPROC wglDXOpenDeviceNV = nullptr;
PFNWGLDXCLOSEDEVICENVPROC wglDXCloseDeviceNV = nullptr;
PFNWGLDXREGISTEROBJECTNVPROC wglDXRegisterObjectNV = nullptr;
PFNWGLDXUNREGISTEROBJECTNVPROC wglDXUnregisterObjectNV = nullptr;
PFNWGLDXLOCKOBJECTSNVPROC wglDXLockObjectsNV = nullptr;
PFNWGLDXUNLOCKOBJECTSNVPROC wglDXUnlockObjectsNV = nullptr;

// Octane shared surface
//const Octane::ApiSharedSurface* g_octaneSharedSurface = nullptr;
int64_t g_sharedSurfaceId = 0;
#endif

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    (void)window; // Suppress unused parameter warning
    glViewport(0, 0, width, height);
}

void setupTexture(const ApiRenderImage& image)
{
#if defined(DO_OCTANE_SHARED_SURFACE) && defined(WIN32)
    if (image->mSharedSurface != nullptr)
    {
        if ((uint64_t)image->mSharedSurface != mSharedSurfaceId)
        {
            // only when changed
            mSharedSurfaceId = (uint64_t)image->mSharedSurface;

            // octane gpu texture
            ID3D11Device1* d3d = (ID3D11Device1*)CommonD3D::GetD3DDevice();
            ID3D11Texture2D* octaneTex = nullptr;
            HRESULT res = d3d->OpenSharedResource1((HANDLE)mSharedSurfaceId, __uuidof(ID3D11Texture2D), (void**)&octaneTex);

            D3D11_TEXTURE2D_DESC desc;
            octaneTex->GetDesc(&desc);
            // D3D11 surface always has a pitch that is a multiple of 32
            int wid = (desc.Width + 31) & ~31;
            int hgt = (desc.Height + 31) & ~31;

            // for debugging, this works   
//						CommonD3D::SaveSharedTextureToBitmap(octaneTex);

                        // get the shared handle
            HANDLE sharedHandle = 0;
            IDXGIResource1* resource;
            if (S_OK != octaneTex->QueryInterface(__uuidof(IDXGIResource1), (void**)&resource))
            {
                API_LOG("ERROR: Failed to retrieve IDXGIResource from shared texture.");
            }
            if (S_OK != resource->CreateSharedHandle(nullptr, DXGI_SHARED_RESOURCE_READ, nullptr, &sharedHandle))
            {
                API_LOG("ERROR: Failed to created shared handle.");
            }
            // rebuild gltexture
            if (mTextureNameGL != 0)
                glDeleteTextures(1, &mTextureNameGL);
            glGenTextures(1, &mTextureNameGL);
            glBindTexture(GL_TEXTURE_2D, mTextureNameGL);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glBindTexture(GL_TEXTURE_2D, 0);
            GL_CHECK_ERROR(__FILE__, __LINE__);

            // rebuild memobject
            GLuint memObjGL = 0;
            glCreateMemoryObjectsEXT(1, &memObjGL);
            GL_CHECK_ERROR(__FILE__, __LINE__);

            // import shared surface to memobject
            glImportMemoryWin32HandleEXT(memObjGL, wid * hgt * 4, GL_HANDLE_TYPE_D3D11_IMAGE_EXT, (void*)sharedHandle);
            GL_CHECK_ERROR(__FILE__, __LINE__);
            // attach memobject to texture
            if (glAcquireKeyedMutexWin32EXT(memObjGL, 0, 500))
            {
                glTextureStorageMem2DEXT(mTextureNameGL, 1, GL_RGBA8, desc.Width, desc.Height, memObjGL, 0);
                GL_CHECK_ERROR(__FILE__, __LINE__);
                glReleaseKeyedMutexWin32EXT(memObjGL, 0);
            }
            glDeleteMemoryObjectsEXT(1, &memObjGL);
            GL_CHECK_ERROR(__FILE__, __LINE__);
        }
    }
    else
#endif
        if (image.mBuffer)
        {
            std::cout << " Processing new render data..." << std::endl;
            std::cout << "   Image: " << image.mSize.x << "x" << image.mSize.y 
                      << ", Type: " << image.mType << std::endl;
            
            // Determine OpenGL format and type based on Octane image type
            GLenum internalFormat = GL_RGBA8;
            GLenum format = GL_RGBA;
            GLenum type = GL_UNSIGNED_BYTE;
            
            switch (image.mType)
            {
            case Octane::IMAGE_TYPE_LDR_MONO:
                internalFormat = GL_R8;
                format = GL_RED;
                type = GL_UNSIGNED_BYTE;
                break;
            case Octane::IMAGE_TYPE_HDR_MONO:
                internalFormat = GL_R32F;
                format = GL_RED;
                type = GL_FLOAT;
                break;
            case Octane::IMAGE_TYPE_LDR_MONO_ALPHA:
                internalFormat = GL_RG8;
                format = GL_RG;
                type = GL_UNSIGNED_BYTE;
                break;
            case Octane::IMAGE_TYPE_HDR_MONO_ALPHA:
                internalFormat = GL_RG32F;
                format = GL_RG;
                type = GL_FLOAT;
                break;
            case Octane::IMAGE_TYPE_LDR_RGBA:
                internalFormat = GL_RGBA8;
                format = GL_RGBA;
                type = GL_UNSIGNED_BYTE;
                break;
            case Octane::IMAGE_TYPE_HDR_RGBA:
                internalFormat = GL_RGBA32F;
                format = GL_RGBA;
                type = GL_FLOAT;
                break;
            default:
                std::cout << "  Unknown image type " << image.mType << ", using RGBA8" << std::endl;
                break;
            }

            const void* bufferData = image.mBuffer;
            int width = image.mSize.x;
            int height = image.mSize.y;

            // Recreate texture if dimensions changed
            static int lastWidth = 0, lastHeight = 0;
            if (width != lastWidth || height != lastHeight) {
                std::cout << "   Recreating texture for new dimensions: " << width << "x" << height << std::endl;
                if (mTextureNameGL != 0) {
                    glDeleteTextures(1, &mTextureNameGL);
                }
                glGenTextures(1, &mTextureNameGL);
                lastWidth = width;
                lastHeight = height;
            }

            glBindTexture(GL_TEXTURE_2D, mTextureNameGL);
            
            // Set texture parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            
            // Upload texture data with correct dimensions and format
            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, bufferData);
            
            GLenum error = glGetError();
            if (error != GL_NO_ERROR) {
                std::cout << " OpenGL error during texture upload: 0x" << std::hex << error << std::dec << std::endl;
            } else {
                std::cout << " Texture updated successfully!" << std::endl;
            }
            
            glBindTexture(GL_TEXTURE_2D, 0);
        }
}

#ifdef _WIN32
// Helper function to get HRESULT error description
std::string GetHRESULTErrorDescription(HRESULT hr) {
    _com_error err(hr);
    std::string ws(err.ErrorMessage());
    return std::string(ws.begin(), ws.end());
}

// Initialize D3D11 device and context
bool initializeD3D11() {
    std::cout << " Initializing D3D11 device..." << std::endl;
    
    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    
    D3D_FEATURE_LEVEL featureLevels[] = {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
    
    D3D_FEATURE_LEVEL featureLevel;
    HRESULT hr = D3D11CreateDevice(
        nullptr,                    // Use default adapter
        D3D_DRIVER_TYPE_HARDWARE,   // Hardware acceleration
        nullptr,                    // No software module
        createDeviceFlags,          // Device flags
        featureLevels,              // Feature levels
        ARRAYSIZE(featureLevels),   // Number of feature levels
        D3D11_SDK_VERSION,          // SDK version
        &g_d3d11Device,             // Device output
        &featureLevel,              // Feature level output
        &g_d3d11Context             // Context output
    );
    
    if (FAILED(hr)) {
        std::cout << " Failed to create D3D11 device: " << GetHRESULTErrorDescription(hr) << std::endl;
        return false;
    }
    
    std::cout << " D3D11 device created successfully" << std::endl;
    std::cout << "   Feature level: " << std::hex << featureLevel << std::dec << std::endl;
    
    // Get adapter LUID for shared surface compatibility
    IDXGIDevice* dxgiDevice = nullptr;
    hr = g_d3d11Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
    if (SUCCEEDED(hr)) {
        IDXGIAdapter* adapter = nullptr;
        hr = dxgiDevice->GetAdapter(&adapter);
        if (SUCCEEDED(hr)) {
            DXGI_ADAPTER_DESC desc;
            hr = adapter->GetDesc(&desc);
            if (SUCCEEDED(hr)) {
                g_adapterLuid = (static_cast<uint64_t>(desc.AdapterLuid.HighPart) << 32) | desc.AdapterLuid.LowPart;
                std::cout << "   Adapter LUID: 0x" << std::hex << g_adapterLuid << std::dec << std::endl;
            }
            adapter->Release();
        }
        dxgiDevice->Release();
    }
    
    return true;
}

// Load WGL extension function pointers
bool loadWGLExtensions() {
    std::cout << " Loading WGL extensions..." << std::endl;
    
    // Check if WGL_NV_DX_interop extension is supported
    const char* extensions = (const char*)glGetString(GL_EXTENSIONS);
    if (!extensions || !strstr(extensions, "WGL_NV_DX_interop")) {
        std::cout << " WGL_NV_DX_interop extension not supported" << std::endl;
        return false;
    }
    
    // Load extension function pointers
    wglDXOpenDeviceNV = (PFNWGLDXOPENDEVICENVPROC)wglGetProcAddress("wglDXOpenDeviceNV");
    wglDXCloseDeviceNV = (PFNWGLDXCLOSEDEVICENVPROC)wglGetProcAddress("wglDXCloseDeviceNV");
    wglDXRegisterObjectNV = (PFNWGLDXREGISTEROBJECTNVPROC)wglGetProcAddress("wglDXRegisterObjectNV");
    wglDXUnregisterObjectNV = (PFNWGLDXUNREGISTEROBJECTNVPROC)wglGetProcAddress("wglDXUnregisterObjectNV");
    wglDXLockObjectsNV = (PFNWGLDXLOCKOBJECTSNVPROC)wglGetProcAddress("wglDXLockObjectsNV");
    wglDXUnlockObjectsNV = (PFNWGLDXUNLOCKOBJECTSNVPROC)wglGetProcAddress("wglDXUnlockObjectsNV");
    
    if (!wglDXOpenDeviceNV || !wglDXCloseDeviceNV || !wglDXRegisterObjectNV || 
        !wglDXUnregisterObjectNV || !wglDXLockObjectsNV || !wglDXUnlockObjectsNV) {
        std::cout << " Failed to load WGL extension functions" << std::endl;
        return false;
    }
    
    std::cout << " WGL extensions loaded successfully" << std::endl;
    return true;
}

// Create shared D3D11 texture
bool createSharedTexture(int width, int height) {
    std::cout << " Creating shared D3D11 texture (" << width << "x" << height << ")..." << std::endl;
    
    // Create shared texture descriptor
    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // sRGB format for proper color space
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX; // Enable keyed mutex for synchronization
    
    HRESULT hr = g_d3d11Device->CreateTexture2D(&desc, nullptr, &g_sharedTexture);
    if (FAILED(hr)) {
        std::cout << " Failed to create shared texture: " << GetHRESULTErrorDescription(hr) << std::endl;
        return false;
    }
    
    // Get shared handle for the texture
    IDXGIResource1* dxgiResource = nullptr;
    hr = g_sharedTexture->QueryInterface(__uuidof(IDXGIResource1), (void**)&dxgiResource);
    if (FAILED(hr)) {
        std::cout << " Failed to query DXGI resource: " << GetHRESULTErrorDescription(hr) << std::endl;
        return false;
    }
    
    hr = dxgiResource->CreateSharedHandle(
        nullptr,                        // Default security attributes
        DXGI_SHARED_RESOURCE_READ,      // Read access for OpenGL
        nullptr,                        // No name
        &g_sharedHandle
    );
    dxgiResource->Release();
    
    if (FAILED(hr)) {
        std::cout << " Failed to create shared handle: " << GetHRESULTErrorDescription(hr) << std::endl;
        return false;
    }
    
    std::cout << " Shared D3D11 texture created successfully" << std::endl;
    std::cout << "   Handle: 0x" << std::hex << g_sharedHandle << std::dec << std::endl;
    return true;
}

// Setup OpenGL interop with D3D11
bool setupOpenGLInterop() {
    std::cout << " Setting up OpenGL/D3D11 interop..." << std::endl;
    
    // Open D3D11 device for OpenGL interop
    g_glD3DDevice = wglDXOpenDeviceNV(g_d3d11Device);
    if (!g_glD3DDevice) {
        std::cout << " Failed to open D3D11 device for OpenGL interop" << std::endl;
        return false;
    }
    
    // Generate OpenGL texture
    glGenTextures(1, &g_sharedTextureGL);
    if (g_sharedTextureGL == 0) {
        std::cout << " Failed to generate OpenGL texture" << std::endl;
        return false;
    }
    
    // Register shared texture with OpenGL
    g_glSharedTexture = wglDXRegisterObjectNV(
        g_glD3DDevice,              // D3D device handle
        g_sharedTexture,            // D3D resource
        g_sharedTextureGL,          // OpenGL texture name
        GL_TEXTURE_2D,              // OpenGL target
        WGL_ACCESS_READ_ONLY_NV     // Access type
    );
    
    if (!g_glSharedTexture) {
        std::cout << " Failed to register shared texture with OpenGL" << std::endl;
        return false;
    }
    
    std::cout << " OpenGL/D3D11 interop setup successfully" << std::endl;
    std::cout << "   OpenGL texture ID: " << g_sharedTextureGL << std::endl;
    return true;
}

// Register shared surface with Octane
bool registerWithOctane() {
    std::cout << " Registering shared surface with Octane..." << std::endl;
/*
    // Check if current device supports shared surfaces
    ApiDeviceSharedSurfaceInfo sharedInfo = OctaneGRPC::ApiRenderEngineProxy::deviceSharedSurfaceInfo(0);
    if (!sharedInfo.mD3D11.mSupported) {
        std::cout << " Current Octane device doesn't support D3D11 shared surfaces" << std::endl;
        return false;
    }
    
    if (sharedInfo.mD3D11.mAdapterLuid != g_adapterLuid) {
        std::cout << " Adapter LUID mismatch:" << std::endl;
        std::cout << "   Octane: 0x" << std::hex << sharedInfo.mD3D11.mAdapterLuid << std::dec << std::endl;
        std::cout << "   D3D11:  0x" << std::hex << g_adapterLuid << std::dec << std::endl;
        return false;
    }
    
    std::cout << " Octane device supports D3D11 shared surfaces" << std::endl;
    std::cout << "   Adapter LUID: 0x" << std::hex << sharedInfo.mD3D11.mAdapterLuid << std::dec << std::endl;
    
    // Create Octane shared surface
    g_octaneSharedSurface = ApiSharedSurface::createD3D11(g_adapterLuid, g_sharedHandle);
    if (!g_octaneSharedSurface) {
        std::cout << " Failed to create Octane shared surface" << std::endl;
        return false;
    }
    
    // Enable shared surface output in Octane
    OctaneGRPC::ApiRenderEngineProxy::setSharedSurfaceOutputType(SHARED_SURFACE_TYPE_D3D11, true);
    
    std::cout << " Shared surface registered with Octane successfully" << std::endl;
    std::cout << "   Real-time mode enabled" << std::endl;
*/
    return true;
}

// Cleanup shared surface resources
void cleanupSharedSurface() {
    std::cout << " Cleaning up shared surface resources..." << std::endl;
    
    // Disable shared surface output
//    if (g_octaneSharedSurface) {
//        OctaneGRPC::ApiRenderEngineProxy::setSharedSurfaceOutputType(SHARED_SURFACE_TYPE_NONE, false);
//    }
    
    // Unregister OpenGL object
    if (g_glSharedTexture && wglDXUnregisterObjectNV) {
        wglDXUnregisterObjectNV(g_glD3DDevice, g_glSharedTexture);
        g_glSharedTexture = nullptr;
    }
    
    // Close OpenGL/D3D11 interop device
    if (g_glD3DDevice && wglDXCloseDeviceNV) {
        wglDXCloseDeviceNV(g_glD3DDevice);
        g_glD3DDevice = nullptr;
    }
    
    // Release OpenGL texture
    if (g_sharedTextureGL != 0) {
        glDeleteTextures(1, &g_sharedTextureGL);
        g_sharedTextureGL = 0;
    }
    
    // Release Octane shared surface
//    if (g_octaneSharedSurface) {
//        g_octaneSharedSurface = nullptr;
//    }
    
    // Close shared handle
    if (g_sharedHandle) {
        CloseHandle(g_sharedHandle);
        g_sharedHandle = nullptr;
    }
    
    // Release D3D11 resources
    if (g_sharedTexture) {
        g_sharedTexture->Release();
        g_sharedTexture = nullptr;
    }
    
    if (g_d3d11Context) {
        g_d3d11Context->Release();
        g_d3d11Context = nullptr;
    }
    
    if (g_d3d11Device) {
        g_d3d11Device->Release();
        g_d3d11Device = nullptr;
    }
    
    std::cout << " Shared surface cleanup complete" << std::endl;
}
#endif

#ifdef DO_GRPC_SDK_ENABLED
// Enhanced callback function that handles both shared surfaces and regular buffers
void OnNewImageCallback(const Octane::ApiArray<Octane::ApiRenderImage>& renderImages, void* userData)
{
    (void)userData; // Suppress unused parameter warning
    
    std::lock_guard<std::mutex> lock(g_renderImageMutex);
    
    g_callbackCount++;
    bool foundSharedSurface = false;
    bool foundRegularBuffer = false;
    
    for (size_t i = 0; i < renderImages.mSize; ++i) {
        const auto& img = renderImages.mData[i];
/*
        // Check if this image uses shared surface (highest priority)
        if (img.mSharedSurface != nullptr) {
            foundSharedSurface = true;
            g_hasSharedSurfaceData = true;
            
            std::cout << " Received shared surface callback #" << g_callbackCount.load() << std::endl;
            std::cout << "   Surface type: " << img.mSharedSurface->getType() << std::endl;
            std::cout << "   Pass: " << img.mRenderPassId 
                      << ", Samples: " << img.mTonemappedSamplesPerPixel << std::endl;
            
            // No need to copy data - it's already in shared GPU memory!
            break; // Prioritize shared surface over regular buffers
            
        } else */
        if (img.mBuffer != nullptr) {
            foundRegularBuffer = true;
            // Store regular buffer as fallback
            if (i == 0) { // Only store the first image to avoid excessive copying
                g_latestRenderImages.clear();
                g_latestRenderImages.push_back(img);
            }
        }
    }
    
    if (foundSharedSurface) {
        // Shared surface takes priority - no buffer copying needed
        g_hasNewRenderData = false; // Clear regular buffer flag
    } else if (foundRegularBuffer) {
        // Use regular buffer callback approach
        g_hasNewRenderData = true;
        g_hasSharedSurfaceData = false;
        
        std::cout << " Received render callback #" << g_callbackCount.load() 
                  << " with " << renderImages.mSize << " images" << std::endl;
        
        if (renderImages.mSize > 0) {
            const auto& img = renderImages.mData[0];
            std::cout << "   Image: " << img.mSize.x << "x" << img.mSize.y 
                      << ", Type: " << img.mType 
                      << ", Pass: " << img.mRenderPassId
                      << ", Samples: " << img.mTonemappedSamplesPerPixel << std::endl;
        }
    } else {
        std::cout << "  Received callback #" << g_callbackCount.load() 
                  << " with no usable image data" << std::endl;
    }
}
#endif

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    // Configure GLFW with modern settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x MSAA for anti-aliasing
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
    
    // Create window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, " Shiny 3D Cube Viewer - SDK Edition", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    
    // Set callbacks
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    
    // Initialize systems
    renderer.initialize();
    modelManager.initialize(&renderer);
    cameraController.initialize(window);
    
    // Set up model manager callbacks
    cameraController.onLoadModel = [&]() {
        modelManager.loadModelFromDialog();
        modelManager.updateWindowTitle(window, "3D Model Viewer - SDK Edition");
    };
    
    cameraController.onResetModel = [&]() {
        modelManager.resetToDefaultCube();
        modelManager.updateWindowTitle(window, "3D Model Viewer - SDK Edition");
    };
    
    // Set up SDK camera sync callback
    cameraController.onCameraUpdate = [&](const glm::vec3& position, const glm::vec3& center, const glm::vec3& up) {
        cameraSync.setCamera(position, center, up);
    };
    const char* serverAddress = "127.0.0.1:51022";
    OctaneGRPC::GRPCSettings::getInstance().setServerAddress(serverAddress);
    OctaneGRPC::GRPCSettings::getInstance().setUniqueString("grpc");

#ifdef DO_GRPC_SDK_ENABLED
    // Callback will be registered after successful connection in main loop

#ifdef _WIN32X
    // Attempt to initialize shared surface rendering (Windows only)
    std::cout << "\n Attempting shared surface initialization..." << std::endl;
    
    bool sharedSurfaceSuccess = false;
    if (initializeD3D11()) {
        if (loadWGLExtensions()) {
            if (createSharedTexture(WINDOW_WIDTH, WINDOW_HEIGHT)) {
                if (setupOpenGLInterop()) {
                    if (registerWithOctane()) {
                        g_renderMode = RENDER_MODE_SHARED_SURFACE;
                        sharedSurfaceSuccess = true;
                        std::cout << " Shared surface rendering enabled!" << std::endl;
                        std::cout << "   Mode: MAXIMUM PERFORMANCE (Zero-copy GPU sharing)" << std::endl;
                    }
                }
            }
        }
    }
    
    if (!sharedSurfaceSuccess) {
        std::cout << "  Shared surface initialization failed - using callback mode" << std::endl;
        g_renderMode = RENDER_MODE_CALLBACK;
        
        // Clean up any partial initialization
        cleanupSharedSurface();
    }
#else
    std::cout << "  Shared surfaces only available on Windows - using callback mode" << std::endl;
    g_renderMode = RENDER_MODE_CALLBACK;
#endif
#endif

    // Set initial camera position in Octane
    glm::vec3 initialPosition = cameraController.camera.getPosition();
    cameraSync.setCamera(initialPosition, cameraController.camera.center, glm::vec3(0.0f, 1.0f, 0.0f));
    
    // Set initial window title
    modelManager.updateWindowTitle(window, "3D Model Viewer - SDK Edition");
    
    // Print controls with current rendering mode
#ifdef DO_GRPC_SDK_ENABLED
    if (g_renderMode == RENDER_MODE_SHARED_SURFACE) {
        std::cout << "\n=== 3D Model Viewer - SDK Edition (Shared Surface Mode) ===" << std::endl;
        std::cout << " MAXIMUM PERFORMANCE: Zero-copy GPU sharing with Octane" << std::endl;
    } else {
        std::cout << "\n=== 3D Model Viewer - SDK Edition (Callback Mode) ===" << std::endl;
        std::cout << " Cross-platform callback system for Octane rendering" << std::endl;
    }
#else
    std::cout << "\n=== 3D Model Viewer - SDK Edition ===" << std::endl;
#endif
    
    std::cout << "Mouse: Drag to orbit camera (syncs with Octane via SDK)" << std::endl;
    std::cout << "Mouse Wheel: Zoom in/out (syncs with Octane via SDK)" << std::endl;
    std::cout << "L: Load 3D model file" << std::endl;
    std::cout << "R: Reset to default cube" << std::endl;
    std::cout << "Q: Toggle between Octane render and local cube" << std::endl;
    std::cout << "ESC: Exit" << std::endl;
    std::cout << "===============================================\n" << std::endl;
    
    // Create a test texture with a visible pattern
    glGenTextures(1, &mTextureNameGL);
    glBindTexture(GL_TEXTURE_2D, mTextureNameGL);
    GL_CHECK_ERROR(__FILE__, __LINE__);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Create a checkerboard pattern for testing
    unsigned char* testData = new unsigned char[WINDOW_WIDTH * WINDOW_HEIGHT * 4];
    for (int y = 0; y < WINDOW_HEIGHT; y++) {
        for (int x = 0; x < WINDOW_WIDTH; x++) {
            int index = (y * WINDOW_WIDTH + x) * 4;
            bool checker = ((x / 64) + (y / 64)) % 2;
            if (checker) {
                testData[index + 0] = 255; // R
                testData[index + 1] = 100; // G
                testData[index + 2] = 100; // B
            } else {
                testData[index + 0] = 100; // R
                testData[index + 1] = 255; // G
                testData[index + 2] = 100; // B
            }
            testData[index + 3] = 255; // A
        }
    }
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, testData);
    GL_CHECK_ERROR(__FILE__, __LINE__);
    glBindTexture(GL_TEXTURE_2D, 0);
    delete[] testData;
    
    std::cout << "Created test texture with checkerboard pattern" << std::endl;

    // Main render loop
    while (!glfwWindowShouldClose(window)) 
    {
        // Connect to Octane server and initialize camera sync
        if (cameraSync.connectToServer(serverAddress))
        {
            cameraSync.initialize();
            
            // Register callback after successful connection (only once)
            if (!g_callbackRegistered) {
                std::cout << " Registering render image callback..." << std::endl;
                try {
                    OctaneGRPC::ApiRenderEngineProxy::setOnNewImageCallback(OnNewImageCallback, nullptr);
                    std::cout << " Render image callback registered successfully" << std::endl;
                    g_callbackRegistered = true;
                } catch (const std::exception& e) {
                    std::cout << " Failed to register render image callback: " << e.what() << std::endl;
                }
            }
        }

        // Process input
        glfwPollEvents();
        
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
        
        // Toggle between Octane render and local cube
        static bool qKeyPressed = false;
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS && !qKeyPressed) {
            showTestQuad = !showTestQuad;
#ifdef DO_GRPC_SDK_ENABLED
            if (showTestQuad) {
                if (g_renderMode == RENDER_MODE_SHARED_SURFACE) {
                    std::cout << "Display mode:  Octane render (shared surface - maximum performance)" << std::endl;
                } else {
                    std::cout << "Display mode:  Octane render (callback)" << std::endl;
                }
            } else {
                std::cout << "Display mode:  Local cube" << std::endl;
            }
#else
            std::cout << "Display mode: " << (showTestQuad ? " Octane render" : " Local cube") << std::endl;
#endif
            qKeyPressed = true;
        } else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE) {
            qKeyPressed = false;
        }
        
        // Process camera and model input
        cameraController.processInput(window);
        
        // Clear screen with a subtle dark color
        glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        float currentTime = (float)glfwGetTime();
        
        // Create transformation matrices using shared camera
        glm::mat4 view = cameraController.camera.getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 
                                               (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 
                                               0.1f, 100.0f);
        glm::vec3 viewPos = cameraController.camera.getPosition();
        
        cameraSync.setCamera(viewPos, cameraController.camera.center, glm::vec3(0.0f, 1.0f, 0.0f));

#ifdef DO_GRPC_SDK_ENABLED
        // Handle rendering based on current mode
        if (g_renderMode == RENDER_MODE_SHARED_SURFACE) {
#ifdef _WIN32
            // Shared surface rendering - check if we have new data
            {
                std::lock_guard<std::mutex> lock(g_renderImageMutex);
                if (g_hasSharedSurfaceData) {
                    // Data is already in shared GPU memory - just use the shared texture
                    // No CPU-GPU transfer needed!
                    g_hasSharedSurfaceData = false; // Mark as processed
                }
            }
#endif
        } else {
            // Callback mode rendering - check for new buffer data
            std::lock_guard<std::mutex> lock(g_renderImageMutex);
            if (g_hasNewRenderData && !g_latestRenderImages.empty()) {
                setupTexture(g_latestRenderImages[0]);
                g_hasNewRenderData = false; // Mark as processed
            }
        }
#else
        // Fallback: try the old grabRenderResult method (likely to fail)
        std::vector<ApiRenderImage> images;
        ApiRenderEngineProxy::grabRenderResult(images);
        if (images.size() > 0)
        {
            setupTexture(images[0]);
        }
#endif
        if (showTestQuad) {
#ifdef DO_GRPC_SDK_ENABLED
            if (g_renderMode == RENDER_MODE_SHARED_SURFACE) {
#ifdef _WIN32
                // Use shared surface texture with D3D11/OpenGL interop
                if (g_glSharedTexture && wglDXLockObjectsNV) {
                    // Lock shared texture for OpenGL access
                    if (wglDXLockObjectsNV(g_glD3DDevice, 1, &g_glSharedTexture)) {
                        // Render with shared texture (zero-copy!)
                        renderer.renderQuad(g_sharedTextureGL);
                        
                        // Unlock shared texture
                        wglDXUnlockObjectsNV(g_glD3DDevice, 1, &g_glSharedTexture);
                    } else {
                        // Fallback to regular texture if lock fails
                        renderer.renderQuad(mTextureNameGL);
                    }
                } else {
                    // Fallback to regular texture if shared surface not available
                    renderer.renderQuad(mTextureNameGL);
                }
#endif
            } else {
                // Use regular callback texture
                renderer.renderQuad(mTextureNameGL);
            }
#else
            // Use regular texture (no SDK)
            renderer.renderQuad(mTextureNameGL);
#endif
        }
        else
        {
            // Render cube as fallback
            renderer.renderCube(view, projection, viewPos, currentTime);
        }
        // Swap buffers
        glfwSwapBuffers(window);
    }
    
    // Cleanup
#ifdef DO_GRPC_SDK_ENABLED
    // Unregister the callback if it was registered
    if (g_callbackRegistered) {
        std::cout << " Unregistering render image callback..." << std::endl;
        try {
            // !!! only works with module sdk 
            OctaneGRPC::ApiRenderEngineProxy::setOnNewImageCallback(nullptr, nullptr);
            std::cout << " Render image callback unregistered" << std::endl;
        } catch (const std::exception& e) {
            std::cout << " Failed to unregister render image callback: " << e.what() << std::endl;
        }
    }
    
    std::cout << " Total callbacks received: " << g_callbackCount.load() << std::endl;

#ifdef _WIN32
    // Cleanup shared surface resources
    if (g_renderMode == RENDER_MODE_SHARED_SURFACE) {
        cleanupSharedSurface();
    }
#endif
#endif
    
    if (mTextureNameGL != 0) {
        glDeleteTextures(1, &mTextureNameGL);
    }
    renderer.cleanup();
    
    glfwTerminate();
    return 0;
}
