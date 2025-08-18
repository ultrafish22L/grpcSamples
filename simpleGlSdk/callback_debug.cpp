/**
 * Focused Octane Callback Debug Tool
 * 
 * This tool isolates the callback registration and tests it step by step
 * to identify why callbacks aren't being received.
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

// Mock OpenGL for testing
typedef unsigned int GLuint;
typedef unsigned int GLenum;
#define GL_TEXTURE_2D 0x0DE1
#define GL_RGBA 0x1908
#define GL_UNSIGNED_BYTE 0x1401

// Include SDK headers
#ifdef DO_GRPC_SDK_ENABLED
#include "grpcsettings.h"
#include "apirenderengineclient.h"
#include "apiprojectmanagerclient.h"
#include "apinodeclient.h"
#include "octaneids.h"
#include "octanevectypes.h"
#include "apirender.h"
using namespace OctaneVec;
#endif

// Global test state
std::atomic<int> g_callbackCount{0};
std::atomic<bool> g_receivedCallback{false};
std::mutex g_outputMutex;

#ifdef DO_GRPC_SDK_ENABLED
// Simple callback for testing
void TestCallback(const Octane::ApiArray<Octane::ApiRenderImage>& renderImages, void* userData)
{
    std::lock_guard<std::mutex> lock(g_outputMutex);
    
    g_callbackCount++;
    g_receivedCallback = true;
    
    std::cout << "\n🎉 CALLBACK #" << g_callbackCount.load() << " RECEIVED!" << std::endl;
    std::cout << "   Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count() << "ms" << std::endl;
    std::cout << "   Images: " << renderImages.mSize << std::endl;
    std::cout << "   UserData: " << userData << std::endl;
    
    for (size_t i = 0; i < renderImages.mSize; ++i) {
        const auto& img = renderImages.mData[i];
        std::cout << "   Image[" << i << "]: " << img.mSize.x << "x" << img.mSize.y 
                  << ", Buffer=" << (img.mBuffer ? "YES" : "NO")
                  << ", SharedSurface=" << (img.mSharedSurface ? "YES" : "NO") << std::endl;
    }
}
#endif

// Test 1: Basic connection
bool testConnection() {
    std::cout << "\n🔌 Test 1: Basic Connection" << std::endl;
    std::cout << "================================" << std::endl;
    
#ifdef DO_GRPC_SDK_ENABLED
    try {
        // Set server address
        GRPCSettings::getInstance().setServerAddress("127.0.0.1:51022");
        std::cout << "✅ Server address set" << std::endl;
        
        // Try to get project info as a connection test
        auto rootGraph = ApiProjectManagerProxy::rootNodeGraph();
        if (!rootGraph.isNull()) {
            std::cout << "✅ Connected to Octane successfully" << std::endl;
            std::cout << "   Root graph: " << rootGraph.name() << std::endl;
            return true;
        } else {
            std::cout << "⚠️  Connected but no root graph found" << std::endl;
            return true; // Still connected, just no project loaded
        }
        
    } catch (const std::exception& e) {
        std::cout << "❌ Connection failed: " << e.what() << std::endl;
        return false;
    }
#else
    std::cout << "❌ SDK not enabled" << std::endl;
    return false;
#endif
}

// Test 2: Render target status
bool testRenderTarget() {
    std::cout << "\n🎯 Test 2: Render Target Status" << std::endl;
    std::cout << "=================================" << std::endl;
    
#ifdef DO_GRPC_SDK_ENABLED
    try {
        auto renderTarget = ApiRenderEngineProxy::getRenderTargetNode();
        if (!renderTarget.isNull()) {
            std::cout << "✅ Render target found: " << renderTarget.name() << std::endl;
            return true;
        } else {
            std::cout << "⚠️  No render target set" << std::endl;
            std::cout << "   This might be why callbacks aren't working!" << std::endl;
            return false;
        }
        
    } catch (const std::exception& e) {
        std::cout << "❌ Error checking render target: " << e.what() << std::endl;
        return false;
    }
#else
    std::cout << "❌ SDK not enabled" << std::endl;
    return false;
#endif
}

// Test 3: Camera node status
bool testCameraNode() {
    std::cout << "\n📷 Test 3: Camera Node Status" << std::endl;
    std::cout << "===============================" << std::endl;
    
#ifdef DO_GRPC_SDK_ENABLED
    try {
        auto cameraNode = ApiRenderEngineProxy::getRenderCameraNode();
        if (!cameraNode.isNull()) {
            std::cout << "✅ Camera node found: " << cameraNode.name() << std::endl;
            return true;
        } else {
            std::cout << "⚠️  No camera node found" << std::endl;
            return false;
        }
        
    } catch (const std::exception& e) {
        std::cout << "❌ Error checking camera node: " << e.what() << std::endl;
        return false;
    }
#else
    std::cout << "❌ SDK not enabled" << std::endl;
    return false;
#endif
}

// Test 4: Callback registration
bool testCallbackRegistration() {
    std::cout << "\n📞 Test 4: Callback Registration" << std::endl;
    std::cout << "=================================" << std::endl;
    
#ifdef DO_GRPC_SDK_ENABLED
    try {
        // Register callback
        ApiRenderEngineProxy::setOnNewImageCallback(TestCallback, (void*)0x12345678);
        std::cout << "✅ Callback registered successfully" << std::endl;
        return true;
        
    } catch (const std::exception& e) {
        std::cout << "❌ Callback registration failed: " << e.what() << std::endl;
        return false;
    }
#else
    std::cout << "❌ SDK not enabled" << std::endl;
    return false;
#endif
}

// Test 5: Force rendering start
bool testStartRendering() {
    std::cout << "\n🚀 Test 5: Start Rendering" << std::endl;
    std::cout << "===========================" << std::endl;
    
#ifdef DO_GRPC_SDK_ENABLED
    try {
        // Try to get current render target
        auto renderTarget = ApiRenderEngineProxy::getRenderTargetNode();
        
        if (renderTarget.isNull()) {
            std::cout << "⚠️  No render target - trying to set one from project" << std::endl;
            
            // Try to find a render target in the project
            auto rootGraph = ApiProjectManagerProxy::rootNodeGraph();
            if (!rootGraph.isNull()) {
                // This is a simplified approach - in reality you'd need to traverse the graph
                std::cout << "   Found root graph, but need to implement render target search" << std::endl;
                return false;
            }
        } else {
            std::cout << "✅ Render target exists: " << renderTarget.name() << std::endl;
            
            // Try to restart rendering by setting the same render target
            bool result = ApiRenderEngineProxy::setRenderTargetNode(&renderTarget);
            if (result) {
                std::cout << "✅ Rendering restarted" << std::endl;
                return true;
            } else {
                std::cout << "❌ Failed to restart rendering" << std::endl;
                return false;
            }
        }
        
    } catch (const std::exception& e) {
        std::cout << "❌ Error starting rendering: " << e.what() << std::endl;
        return false;
    }
#endif
    
    return false;
}

// Test 6: Monitor for callbacks
void testMonitorCallbacks(int seconds) {
    std::cout << "\n👀 Test 6: Monitor Callbacks (" << seconds << "s)" << std::endl;
    std::cout << "===============================" << std::endl;
    std::cout << "Waiting for callbacks..." << std::endl;
    std::cout << "(Make sure Octane is actively rendering!)" << std::endl;
    
    auto startTime = std::chrono::steady_clock::now();
    int lastCount = 0;
    
    for (int i = 0; i < seconds; i++) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        int currentCount = g_callbackCount.load();
        int newCallbacks = currentCount - lastCount;
        
        {
            std::lock_guard<std::mutex> lock(g_outputMutex);
            std::cout << "[" << (i+1) << "s] Total: " << currentCount 
                      << ", New: " << newCallbacks << std::endl;
        }
        
        lastCount = currentCount;
    }
    
    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    
    std::cout << "\n📊 Monitoring Results:" << std::endl;
    std::cout << "   Duration: " << duration.count() << "ms" << std::endl;
    std::cout << "   Total callbacks: " << g_callbackCount.load() << std::endl;
    std::cout << "   Rate: " << (float)g_callbackCount.load() / seconds << " callbacks/sec" << std::endl;
}

// Cleanup
void cleanup() {
    std::cout << "\n🧹 Cleanup" << std::endl;
    std::cout << "==========" << std::endl;
    
#ifdef DO_GRPC_SDK_ENABLED
    try {
        ApiRenderEngineProxy::setOnNewImageCallback(nullptr, nullptr);
        std::cout << "✅ Callback unregistered" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "⚠️  Cleanup error: " << e.what() << std::endl;
    }
#endif
}

int main() {
    std::cout << "🔍 Octane Callback Debug Tool" << std::endl;
    std::cout << "=============================" << std::endl;
    std::cout << "This tool will systematically test callback functionality." << std::endl;
    std::cout << "Make sure Octane is running on 127.0.0.1:51022 with a scene loaded!" << std::endl;
    
    bool allTestsPassed = true;
    
    // Run tests in sequence
    if (!testConnection()) {
        std::cout << "\n❌ CRITICAL: Connection failed - check if Octane is running" << std::endl;
        return 1;
    }
    
    bool hasRenderTarget = testRenderTarget();
    bool hasCameraNode = testCameraNode();
    
    if (!hasRenderTarget) {
        std::cout << "\n⚠️  WARNING: No render target - callbacks may not work" << std::endl;
        std::cout << "   Solution: Load a scene in Octane or set a render target" << std::endl;
        allTestsPassed = false;
    }
    
    if (!hasCameraNode) {
        std::cout << "\n⚠️  WARNING: No camera node - this might be normal" << std::endl;
    }
    
    if (!testCallbackRegistration()) {
        std::cout << "\n❌ CRITICAL: Callback registration failed" << std::endl;
        return 1;
    }
    
    // Try to start rendering if we have a render target
    if (hasRenderTarget) {
        testStartRendering();
    }
    
    // Monitor for callbacks
    testMonitorCallbacks(15);
    
    // Final results
    std::cout << "\n" << "=" * 50 << std::endl;
    std::cout << "📋 FINAL RESULTS" << std::endl;
    std::cout << "=" * 50 << std::endl;
    
    if (g_receivedCallback.load()) {
        std::cout << "🎉 SUCCESS: Callbacks are working!" << std::endl;
        std::cout << "   Total callbacks received: " << g_callbackCount.load() << std::endl;
        std::cout << "   The callback system is functional." << std::endl;
    } else if (allTestsPassed) {
        std::cout << "⚠️  NO CALLBACKS: System appears functional but no callbacks received" << std::endl;
        std::cout << "   Possible causes:" << std::endl;
        std::cout << "   1. Octane is not actively rendering" << std::endl;
        std::cout << "   2. No render target is set in Octane" << std::endl;
        std::cout << "   3. Rendering is paused or stopped" << std::endl;
        std::cout << "   4. Scene has no geometry to render" << std::endl;
        std::cout << "\n   Try:" << std::endl;
        std::cout << "   - Load a scene in Octane" << std::endl;
        std::cout << "   - Start rendering (press F5 or click render)" << std::endl;
        std::cout << "   - Check that LiveLink is enabled" << std::endl;
    } else {
        std::cout << "❌ FAILURE: System has issues that prevent callbacks" << std::endl;
        std::cout << "   Check the test results above for specific problems" << std::endl;
    }
    
    cleanup();
    
    return g_receivedCallback.load() ? 0 : 1;
}