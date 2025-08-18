/**
 * Octane Callback Testbed - Debug callback registration and image reception
 * 
 * This is a minimal test program to isolate and debug the OnNewImageCallback
 * functionality without requiring a full OpenGL context or GUI.
 */

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <mutex>
#include <atomic>
#include <vector>
#include <thread>
#include <chrono>
#include <cstring>

// Mock OpenGL types for testing without actual OpenGL
typedef unsigned int GLuint;
typedef unsigned int GLenum;
typedef unsigned char GLubyte;

#define GL_TEXTURE_2D 0x0DE1
#define GL_RGBA 0x1908
#define GL_UNSIGNED_BYTE 0x1401
#define GL_LINEAR 0x2601
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_WRAP_S 0x2802
#define GL_TEXTURE_WRAP_T 0x2803

// Mock OpenGL functions for testing
void glGenTextures(int n, GLuint* textures) { 
    static GLuint counter = 1;
    for(int i = 0; i < n; i++) textures[i] = counter++;
    std::cout << "Mock: glGenTextures(" << n << ") -> " << textures[0] << std::endl;
}

void glBindTexture(GLenum target, GLuint texture) {
    std::cout << "Mock: glBindTexture(" << target << ", " << texture << ")" << std::endl;
}

void glTexParameteri(GLenum target, GLenum pname, int param) {
    std::cout << "Mock: glTexParameteri(" << target << ", " << pname << ", " << param << ")" << std::endl;
}

void glTexImage2D(GLenum target, int level, int internalformat, int width, int height, 
                  int border, GLenum format, GLenum type, const void* pixels) {
    std::cout << "Mock: glTexImage2D(" << width << "x" << height << ", format=" << format 
              << ", pixels=" << (pixels ? "valid" : "null") << ")" << std::endl;
}

// Include SDK headers if available
#ifdef DO_GRPC_SDK_ENABLED
#include "grpcsettings.h"
#include "apirenderengineclient.h"
#include "apinodeclient.h"
#include "octaneids.h"
#include "octanevectypes.h"
#include "apirender.h"
using namespace OctaneVec;
#endif

// Global variables for callback testing
#ifdef DO_GRPC_SDK_ENABLED
std::mutex g_renderImageMutex;
std::vector<Octane::ApiRenderImage> g_latestRenderImages;
bool g_hasNewRenderData = false;
std::atomic<int> g_callbackCount{0};
std::atomic<bool> g_testRunning{true};
#endif

GLuint g_testTexture = 0;

// Test texture setup function
void setupTestTexture(const Octane::ApiRenderImage& image) {
    std::cout << "\n🔧 Setting up texture from callback image..." << std::endl;
    
    if (!image.mBuffer) {
        std::cout << "❌ No buffer data in image!" << std::endl;
        return;
    }
    
    std::cout << "✅ Image buffer found:" << std::endl;
    std::cout << "   Size: " << image.mSize.x << "x" << image.mSize.y << std::endl;
    std::cout << "   Type: " << image.mType << std::endl;
    std::cout << "   Pass ID: " << image.mRenderPassId << std::endl;
    std::cout << "   Samples: " << image.mTonemappedSamplesPerPixel << std::endl;
    
    // Generate texture if needed
    if (g_testTexture == 0) {
        glGenTextures(1, &g_testTexture);
        std::cout << "   Generated texture ID: " << g_testTexture << std::endl;
    }
    
    // Bind and configure texture
    glBindTexture(GL_TEXTURE_2D, g_testTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    // Upload image data
    const char* buffer = (const char*)image.mBuffer;
    
    // Determine format based on image type
    GLenum format = GL_RGBA;
    GLenum type = GL_UNSIGNED_BYTE;
    
    switch (image.mType) {
        case Octane::IMAGE_TYPE_LDR_RGBA:
            format = GL_RGBA;
            type = GL_UNSIGNED_BYTE;
            std::cout << "   Format: LDR RGBA (8-bit)" << std::endl;
            break;
        case Octane::IMAGE_TYPE_HDR_RGBA:
            format = GL_RGBA;
            type = GL_UNSIGNED_BYTE; // Will need proper float handling in real implementation
            std::cout << "   Format: HDR RGBA (float)" << std::endl;
            break;
        default:
            std::cout << "   Format: Unknown (" << image.mType << ")" << std::endl;
            break;
    }
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.mSize.x, image.mSize.y, 
                 0, format, type, buffer);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    std::cout << "✅ Texture setup complete! Ready for rendering." << std::endl;
}

#ifdef DO_GRPC_SDK_ENABLED
// Enhanced callback function for testing
void OnNewImageCallbackTest(const Octane::ApiArray<Octane::ApiRenderImage>& renderImages, void* userData)
{
    (void)userData; // Suppress unused parameter warning
    
    std::lock_guard<std::mutex> lock(g_renderImageMutex);
    
    g_callbackCount++;
    
    std::cout << "\n🎉 CALLBACK RECEIVED #" << g_callbackCount.load() << std::endl;
    std::cout << "   Images in array: " << renderImages.mSize << std::endl;
    
    bool foundUsableImage = false;
    
    for (size_t i = 0; i < renderImages.mSize; ++i) {
        const auto& img = renderImages.mData[i];
        
        std::cout << "   Image[" << i << "]:" << std::endl;
        std::cout << "     Buffer: " << (img.mBuffer ? "✅ Present" : "❌ Null") << std::endl;
        std::cout << "     SharedSurface: " << (img.mSharedSurface ? "✅ Present" : "❌ Null") << std::endl;
        
        if (img.mBuffer) {
            std::cout << "     Size: " << img.mSize.x << "x" << img.mSize.y << std::endl;
            std::cout << "     Type: " << img.mType << std::endl;
            std::cout << "     Pass: " << img.mRenderPassId << std::endl;
            std::cout << "     Samples: " << img.mTonemappedSamplesPerPixel << std::endl;
            
            // Store the first usable image
            if (!foundUsableImage) {
                g_latestRenderImages.clear();
                g_latestRenderImages.push_back(img);
                g_hasNewRenderData = true;
                foundUsableImage = true;
                
                std::cout << "     ✅ Stored as latest render image" << std::endl;
            }
        }
        
        if (img.mSharedSurface) {
            std::cout << "     SharedSurface Type: " << img.mSharedSurface->getType() << std::endl;
        }
    }
    
    if (!foundUsableImage) {
        std::cout << "   ⚠️  No usable image data found in callback!" << std::endl;
    }
    
    std::cout << "   Total callbacks received: " << g_callbackCount.load() << std::endl;
}
#endif

// Test connection and callback registration
bool testCallbackRegistration() {
    std::cout << "\n🔗 Testing callback registration..." << std::endl;
    
#ifdef DO_GRPC_SDK_ENABLED
    try {
        // Set server address
        const char* serverAddress = "127.0.0.1:51022";
        GRPCSettings::getInstance().setServerAddress(serverAddress);
        std::cout << "✅ Server address set to: " << serverAddress << std::endl;
        
        // Register callback
        ApiRenderEngineProxy::setOnNewImageCallback(OnNewImageCallbackTest, nullptr);
        std::cout << "✅ Callback registered successfully" << std::endl;
        
        return true;
        
    } catch (const std::exception& e) {
        std::cout << "❌ Exception during callback registration: " << e.what() << std::endl;
        return false;
    }
#else
    std::cout << "❌ SDK not enabled - cannot test callbacks" << std::endl;
    return false;
#endif
}

// Test basic connection to Octane
bool testOctaneConnection() {
    std::cout << "\n🔌 Testing Octane connection..." << std::endl;
    
#ifdef DO_GRPC_SDK_ENABLED
    try {
        // Try to get render camera node as a connection test
        auto cameraNode = ApiRenderEngineProxy::getRenderCameraNode();
        
        if (!cameraNode.isNull()) {
            std::cout << "✅ Connected to Octane successfully" << std::endl;
            std::cout << "   Camera node: " << cameraNode.name() << std::endl;
            return true;
        } else {
            std::cout << "⚠️  Connected but no camera node found" << std::endl;
            std::cout << "   This might be normal if no scene is loaded" << std::endl;
            return true; // Connection is working, just no scene
        }
        
    } catch (const std::exception& e) {
        std::cout << "❌ Connection failed: " << e.what() << std::endl;
        return false;
    }
#else
    std::cout << "❌ SDK not enabled - cannot test connection" << std::endl;
    return false;
#endif
}

// Monitor callback activity
void monitorCallbacks(int durationSeconds) {
    std::cout << "\n👀 Monitoring callbacks for " << durationSeconds << " seconds..." << std::endl;
    std::cout << "   (Make sure Octane is rendering something!)" << std::endl;
    
    int lastCallbackCount = 0;
    
    for (int i = 0; i < durationSeconds; i++) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        int currentCount = g_callbackCount.load();
        int newCallbacks = currentCount - lastCallbackCount;
        
        std::cout << "   [" << (i+1) << "s] Callbacks: " << currentCount 
                  << " (+" << newCallbacks << " this second)" << std::endl;
        
        // Process any new render data
        {
            std::lock_guard<std::mutex> lock(g_renderImageMutex);
            if (g_hasNewRenderData && !g_latestRenderImages.empty()) {
                std::cout << "   🎨 Processing new render data..." << std::endl;
                setupTestTexture(g_latestRenderImages[0]);
                g_hasNewRenderData = false;
            }
        }
        
        lastCallbackCount = currentCount;
    }
    
    std::cout << "\n📊 Monitoring complete:" << std::endl;
    std::cout << "   Total callbacks: " << g_callbackCount.load() << std::endl;
    std::cout << "   Average rate: " << (float)g_callbackCount.load() / durationSeconds << " callbacks/sec" << std::endl;
}

// Cleanup function
void cleanup() {
    std::cout << "\n🧹 Cleaning up..." << std::endl;
    
#ifdef DO_GRPC_SDK_ENABLED
    try {
        ApiRenderEngineProxy::setOnNewImageCallback(nullptr, nullptr);
        std::cout << "✅ Callback unregistered" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "⚠️  Error during cleanup: " << e.what() << std::endl;
    }
#endif
    
    g_testRunning = false;
}

int main() {
    std::cout << "🧪 Octane Callback Testbed" << std::endl;
    std::cout << "=========================" << std::endl;
    std::cout << "This test will:" << std::endl;
    std::cout << "1. Connect to Octane at 127.0.0.1:51022" << std::endl;
    std::cout << "2. Register OnNewImageCallback" << std::endl;
    std::cout << "3. Monitor for incoming render callbacks" << std::endl;
    std::cout << "4. Process image data and setup GL textures" << std::endl;
    std::cout << std::endl;
    
    // Test sequence
    bool success = true;
    
    // Test 1: Connection
    if (!testOctaneConnection()) {
        std::cout << "\n❌ Connection test failed - is Octane running with LiveLink enabled?" << std::endl;
        success = false;
    }
    
    // Test 2: Callback registration
    if (success && !testCallbackRegistration()) {
        std::cout << "\n❌ Callback registration failed" << std::endl;
        success = false;
    }
    
    // Test 3: Monitor callbacks
    if (success) {
        std::cout << "\n✅ Setup complete - monitoring callbacks..." << std::endl;
        std::cout << "💡 TIP: Start rendering in Octane to see callbacks!" << std::endl;
        
        monitorCallbacks(30); // Monitor for 30 seconds
    }
    
    // Cleanup
    cleanup();
    
    std::cout << "\n" << (success ? "✅" : "❌") << " Test " << (success ? "completed" : "failed") << std::endl;
    
    if (success && g_callbackCount.load() > 0) {
        std::cout << "🎉 SUCCESS: Callbacks are working!" << std::endl;
        std::cout << "   The callback system is functional and ready for integration." << std::endl;
    } else if (success) {
        std::cout << "⚠️  No callbacks received - check if Octane is actively rendering" << std::endl;
    }
    
    return success ? 0 : 1;
}