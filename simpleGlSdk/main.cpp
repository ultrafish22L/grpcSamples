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
using namespace OctaneVec;
#endif

// Window dimensions
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;

// Global objects using shared systems
SharedUtils::CameraController cameraController;
SharedUtils::ModelManager modelManager;
SharedUtils::RendererGl renderer;
//CameraSyncSdk cameraSync;
CameraSyncLiveLink cameraSync; 
GLuint mTextureNameGL = 0;
bool showTestQuad = false;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    (void)window; // Suppress unused parameter warning
    glViewport(0, 0, width, height);
}

void renderQuad(const ApiRenderImage& image)
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
//        if (image.mBuffer)
        {
/*
            uint8_t pixsize = 0;
            switch (image.mType)
            {
            case Octane::IMAGE_TYPE_LDR_MONO:
                pixsize = sizeof(char);
                break;
            case Octane::IMAGE_TYPE_HDR_MONO:
                pixsize = sizeof(float);
                break;
            case Octane::IMAGE_TYPE_LDR_MONO_ALPHA:
                pixsize = sizeof(char) * 2;
                break;
            case Octane::IMAGE_TYPE_HDR_MONO_ALPHA:
                pixsize = sizeof(float) * 2;
                break;
            case Octane::IMAGE_TYPE_LDR_RGBA:
                pixsize = sizeof(char) * 4;
                break;
            case Octane::IMAGE_TYPE_HDR_RGBA:
                pixsize = sizeof(float) * 4;
                break;
            }
            uint64_t bytesize = image.mSize[0] * pixsize * (uint64_t)image.mSize[1];

//            const char* b = (const char*)image.mBuffer;

            glBindTexture(GL_TEXTURE_2D, mTextureNameGL);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, b);
            glBindTexture(GL_TEXTURE_2D, 0);
*/

            renderer.renderQuad(mTextureNameGL);
        }
}

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
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "🚀 Shiny 3D Cube Viewer - SDK Edition", NULL, NULL);
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
    GRPCSettings::getInstance().setServerAddress(serverAddress);

    // Set initial camera position in Octane
    glm::vec3 initialPosition = cameraController.camera.getPosition();
    cameraSync.setCamera(initialPosition, cameraController.camera.center, glm::vec3(0.0f, 1.0f, 0.0f));
    
    // Set initial window title
    modelManager.updateWindowTitle(window, "3D Model Viewer - SDK Edition");
    
    // Print controls
    std::cout << "\n=== 3D Model Viewer - SDK Edition Controls ===" << std::endl;
    std::cout << "Mouse: Drag to orbit camera (syncs with Octane via SDK)" << std::endl;
    std::cout << "Mouse Wheel: Zoom in/out (syncs with Octane via SDK)" << std::endl;
    std::cout << "L: Load 3D model file" << std::endl;
    std::cout << "R: Reset to default cube" << std::endl;
    std::cout << "Q: Toggle test quad rendering" << std::endl;
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
        }

        // Process input
        glfwPollEvents();
        
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
        
        // Toggle test quad rendering
        static bool qKeyPressed = false;
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS && !qKeyPressed) {
            showTestQuad = !showTestQuad;
            std::cout << "Test quad rendering: " << (showTestQuad ? "ON" : "OFF") << std::endl;
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

        if (showTestQuad) {
            // Force show test quad for debugging
            if (mTextureNameGL != 0) {
                renderer.renderQuad(mTextureNameGL);
            }
        } else {
            std::vector<ApiRenderImage> images;
            ApiRenderEngineProxy::grabRenderResult(images);

            if (images.size() > 0)
            {
                // Render the Octane image if available
                renderQuad(images[0]);
            }
            else
            {
                // Render cube as fallback
                renderer.renderCube(view, projection, viewPos, currentTime);
            }
        }
        // Swap buffers
        glfwSwapBuffers(window);
    }
    
    // Cleanup
    if (mTextureNameGL != 0) {
        glDeleteTextures(1, &mTextureNameGL);
    }
    renderer.cleanup();
    
    glfwTerminate();
    return 0;
}
