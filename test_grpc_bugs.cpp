/**
 * Comprehensive gRPC bug testing
 * Tests edge cases, error conditions, and potential issues
 */

#include <iostream>
#include <memory>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <random>

// Include the camera sync component
#include "shared/camera_sync_livelink.h"

void testConnectionErrors() {
    std::cout << "🔍 Testing Connection Error Handling\n";
    std::cout << "====================================\n";

    CameraSyncLiveLink cameraSync;
    
    // Test 1: Invalid server address
    std::cout << "Test 1: Invalid server address...\n";
    bool connected = cameraSync.connectToServer("invalid.server:12345");
    if (!connected) {
        std::cout << "✅ Correctly failed to connect to invalid server\n";
    } else {
        std::cout << "❌ BUG: Connected to invalid server!\n";
    }

    // Test 2: Empty server address
    std::cout << "Test 2: Empty server address...\n";
    connected = cameraSync.connectToServer("");
    if (!connected) {
        std::cout << "✅ Correctly failed with empty server address\n";
    } else {
        std::cout << "❌ BUG: Connected with empty server address!\n";
    }

    // Test 3: Operations without connection
    std::cout << "Test 3: Operations without connection...\n";
    glm::vec3 pos, target, up;
    float fov;
    bool result = cameraSync.getCamera(pos, target, up, fov);
    if (!result) {
        std::cout << "✅ Correctly failed getCamera without connection\n";
    } else {
        std::cout << "❌ BUG: getCamera succeeded without connection!\n";
    }

    result = cameraSync.setCamera(glm::vec3(1,2,3), glm::vec3(0,0,0), glm::vec3(0,1,0), 45.0f);
    if (!result) {
        std::cout << "✅ Correctly failed setCamera without connection\n";
    } else {
        std::cout << "❌ BUG: setCamera succeeded without connection!\n";
    }

    std::vector<CameraSyncLiveLink::MeshInfo> meshes;
    result = cameraSync.getMeshList(meshes);
    if (!result) {
        std::cout << "✅ Correctly failed getMeshList without connection\n";
    } else {
        std::cout << "❌ BUG: getMeshList succeeded without connection!\n";
    }

    std::cout << "\n";
}

void testExtremeValues() {
    std::cout << "🔍 Testing Extreme Values\n";
    std::cout << "=========================\n";

    CameraSyncLiveLink cameraSync;
    
    // Connect to server first
    if (!cameraSync.connectToServer("127.0.0.1:51022")) {
        std::cout << "❌ Failed to connect to server for extreme value tests\n";
        return;
    }

    // Test 1: Very large position values
    std::cout << "Test 1: Very large position values...\n";
    glm::vec3 extremePos(1e6f, 1e6f, 1e6f);
    glm::vec3 target(0, 0, 0);
    glm::vec3 up(0, 1, 0);
    bool result = cameraSync.setCamera(extremePos, target, up, 45.0f);
    if (result) {
        std::cout << "✅ Handled large position values\n";
    } else {
        std::cout << "⚠️  Failed with large position values\n";
    }

    // Test 2: Very small position values
    std::cout << "Test 2: Very small position values...\n";
    glm::vec3 tinyPos(1e-6f, 1e-6f, 1e-6f);
    result = cameraSync.setCamera(tinyPos, target, up, 45.0f);
    if (result) {
        std::cout << "✅ Handled small position values\n";
    } else {
        std::cout << "⚠️  Failed with small position values\n";
    }

    // Test 3: Negative values
    std::cout << "Test 3: Negative position values...\n";
    glm::vec3 negPos(-100.0f, -200.0f, -300.0f);
    result = cameraSync.setCamera(negPos, target, up, 45.0f);
    if (result) {
        std::cout << "✅ Handled negative position values\n";
    } else {
        std::cout << "⚠️  Failed with negative position values\n";
    }

    // Test 4: Zero FOV
    std::cout << "Test 4: Zero FOV...\n";
    result = cameraSync.setCamera(glm::vec3(1,2,3), target, up, 0.0f);
    if (result) {
        std::cout << "✅ Handled zero FOV\n";
    } else {
        std::cout << "⚠️  Failed with zero FOV\n";
    }

    // Test 5: Very large FOV
    std::cout << "Test 5: Very large FOV...\n";
    result = cameraSync.setCamera(glm::vec3(1,2,3), target, up, 179.0f);
    if (result) {
        std::cout << "✅ Handled large FOV\n";
    } else {
        std::cout << "⚠️  Failed with large FOV\n";
    }

    // Test 6: Invalid up vector (zero length)
    std::cout << "Test 6: Zero-length up vector...\n";
    glm::vec3 zeroUp(0, 0, 0);
    result = cameraSync.setCamera(glm::vec3(1,2,3), target, zeroUp, 45.0f);
    if (result) {
        std::cout << "⚠️  Accepted zero-length up vector (might be a bug)\n";
    } else {
        std::cout << "✅ Correctly rejected zero-length up vector\n";
    }

    cameraSync.disconnect();
    std::cout << "\n";
}

void testConcurrency() {
    std::cout << "🔍 Testing Concurrency Issues\n";
    std::cout << "=============================\n";

    CameraSyncLiveLink cameraSync;
    
    if (!cameraSync.connectToServer("127.0.0.1:51022")) {
        std::cout << "❌ Failed to connect to server for concurrency tests\n";
        return;
    }

    // Test rapid-fire requests
    std::cout << "Test 1: Rapid-fire requests (100 calls in quick succession)...\n";
    auto start = std::chrono::high_resolution_clock::now();
    int successCount = 0;
    int failCount = 0;

    for (int i = 0; i < 100; i++) {
        glm::vec3 pos, target, up;
        float fov;
        if (cameraSync.getCamera(pos, target, up, fov)) {
            successCount++;
        } else {
            failCount++;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "   Success: " << successCount << ", Failed: " << failCount << "\n";
    std::cout << "   Total time: " << duration.count() << "ms\n";
    std::cout << "   Average per call: " << (duration.count() / 100.0f) << "ms\n";

    if (failCount == 0) {
        std::cout << "✅ All rapid requests succeeded\n";
    } else {
        std::cout << "⚠️  Some rapid requests failed - possible concurrency issue\n";
    }

    cameraSync.disconnect();
    std::cout << "\n";
}

void testMemoryLeaks() {
    std::cout << "🔍 Testing Memory Management\n";
    std::cout << "============================\n";

    // Test repeated connect/disconnect cycles
    std::cout << "Test 1: Repeated connect/disconnect cycles...\n";
    
    for (int i = 0; i < 10; i++) {
        CameraSyncLiveLink cameraSync;
        
        bool connected = cameraSync.connectToServer("127.0.0.1:51022");
        if (connected) {
            // Do some operations
            glm::vec3 pos, target, up;
            float fov;
            cameraSync.getCamera(pos, target, up, fov);
            cameraSync.setCamera(glm::vec3(i, i, i), glm::vec3(0,0,0), glm::vec3(0,1,0), 45.0f);
            
            std::vector<CameraSyncLiveLink::MeshInfo> meshes;
            cameraSync.getMeshList(meshes);
        }
        
        cameraSync.disconnect();
        
        if (i % 2 == 0) {
            std::cout << "   Cycle " << (i+1) << "/10 completed\n";
        }
    }
    
    std::cout << "✅ Completed 10 connect/disconnect cycles\n";
    std::cout << "\n";
}

void testDataIntegrity() {
    std::cout << "🔍 Testing Data Integrity\n";
    std::cout << "=========================\n";

    CameraSyncLiveLink cameraSync;
    
    if (!cameraSync.connectToServer("127.0.0.1:51022")) {
        std::cout << "❌ Failed to connect to server for data integrity tests\n";
        return;
    }

    // Test 1: Set and verify camera positions
    std::cout << "Test 1: Camera position round-trip accuracy...\n";
    
    std::vector<glm::vec3> testPositions = {
        glm::vec3(1.0f, 2.0f, 3.0f),
        glm::vec3(-5.5f, 10.25f, -15.75f),
        glm::vec3(0.001f, 0.002f, 0.003f),
        glm::vec3(100.0f, 200.0f, 300.0f)
    };

    for (size_t i = 0; i < testPositions.size(); i++) {
        glm::vec3 setPos = testPositions[i];
        glm::vec3 target(0, 0, 0);
        glm::vec3 up(0, 1, 0);
        
        // Set camera
        bool setResult = cameraSync.setCamera(setPos, target, up, 45.0f);
        if (!setResult) {
            std::cout << "❌ Failed to set camera position " << i << "\n";
            continue;
        }

        // Get camera back
        glm::vec3 getPos, getTarget, getUp;
        float getFov;
        bool getResult = cameraSync.getCamera(getPos, getTarget, getUp, getFov);
        if (!getResult) {
            std::cout << "❌ Failed to get camera position " << i << "\n";
            continue;
        }

        // Check accuracy (allowing for small floating point errors)
        float tolerance = 0.01f;
        glm::vec3 diff = getPos - setPos;
        float distance = glm::length(diff);
        
        if (distance < tolerance) {
            std::cout << "✅ Position " << i << " accurate (error: " << distance << ")\n";
        } else {
            std::cout << "⚠️  Position " << i << " inaccurate (error: " << distance << ")\n";
            std::cout << "   Set: (" << setPos.x << ", " << setPos.y << ", " << setPos.z << ")\n";
            std::cout << "   Got: (" << getPos.x << ", " << getPos.y << ", " << getPos.z << ")\n";
        }
    }

    cameraSync.disconnect();
    std::cout << "\n";
}

int main() {
    std::cout << "🐛 Comprehensive gRPC Bug Testing\n";
    std::cout << "==================================\n\n";

    testConnectionErrors();
    testExtremeValues();
    testConcurrency();
    testMemoryLeaks();
    testDataIntegrity();

    std::cout << "🎉 Bug testing completed!\n";
    std::cout << "Check output above for any ❌ or ⚠️  indicators\n";
    
    return 0;
}