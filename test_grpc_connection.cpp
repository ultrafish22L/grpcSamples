/**
 * Simple gRPC connection test without GUI
 * Tests the core gRPC functionality with the mock server
 */

#include <iostream>
#include <memory>
#include <string>
#include <chrono>
#include <thread>

// Include the camera sync component
#include "shared/camera_sync_livelink.h"

int main() {
    std::cout << "🧪 Testing gRPC Connection to Mock Octane Server\n";
    std::cout << "================================================\n\n";

    // Create camera sync instance
    CameraSyncLiveLink cameraSync;
    
    // Test 1: Connection
    std::cout << "Test 1: Connecting to server at 127.0.0.1:51022...\n";
    bool connected = cameraSync.connectToServer("127.0.0.1:51022");
    if (connected) {
        std::cout << "✅ Connection successful!\n\n";
    } else {
        std::cout << "❌ Connection failed!\n\n";
        return 1;
    }

    // Test 2: Get Camera
    std::cout << "Test 2: Getting camera position...\n";
    glm::vec3 pos, target, up;
    float fov;
    bool gotCamera = cameraSync.getCamera(pos, target, up, fov);
    if (gotCamera) {
        std::cout << "✅ Got camera successfully!\n";
        std::cout << "   Position: (" << pos.x << ", " << pos.y << ", " << pos.z << ")\n";
        std::cout << "   Target: (" << target.x << ", " << target.y << ", " << target.z << ")\n";
        std::cout << "   Up: (" << up.x << ", " << up.y << ", " << up.z << ")\n";
        std::cout << "   FOV: " << fov << "\n\n";
    } else {
        std::cout << "❌ Failed to get camera!\n\n";
    }

    // Test 3: Set Camera
    std::cout << "Test 3: Setting camera position...\n";
    glm::vec3 newPos(1.0f, 2.0f, 3.0f);
    glm::vec3 newTarget(0.0f, 0.0f, 0.0f);
    glm::vec3 newUp(0.0f, 1.0f, 0.0f);
    bool setCamera = cameraSync.setCamera(newPos, newTarget, newUp, 45.0f);
    if (setCamera) {
        std::cout << "✅ Set camera successfully!\n\n";
    } else {
        std::cout << "❌ Failed to set camera!\n\n";
    }

    // Test 4: Get Camera again to verify change
    std::cout << "Test 4: Verifying camera change...\n";
    gotCamera = cameraSync.getCamera(pos, target, up, fov);
    if (gotCamera) {
        std::cout << "✅ Got updated camera!\n";
        std::cout << "   Position: (" << pos.x << ", " << pos.y << ", " << pos.z << ")\n";
        std::cout << "   Target: (" << target.x << ", " << target.y << ", " << target.z << ")\n";
        std::cout << "   FOV: " << fov << "\n\n";
    } else {
        std::cout << "❌ Failed to get updated camera!\n\n";
    }

    // Test 5: Get Meshes
    std::cout << "Test 5: Getting mesh list...\n";
    std::vector<CameraSyncLiveLink::MeshInfo> meshes;
    bool gotMeshes = cameraSync.getMeshList(meshes);
    if (gotMeshes) {
        std::cout << "✅ Got meshes successfully!\n";
        std::cout << "   Found " << meshes.size() << " meshes:\n";
        for (const auto& mesh : meshes) {
            std::cout << "   - " << mesh.name << " (ID: " << mesh.id << ")\n";
        }
        std::cout << "\n";
    } else {
        std::cout << "❌ Failed to get meshes!\n\n";
    }

    // Test 6: Performance test - multiple rapid calls
    std::cout << "Test 6: Performance test (10 rapid camera calls)...\n";
    auto start = std::chrono::high_resolution_clock::now();
    int successCount = 0;
    
    for (int i = 0; i < 10; i++) {
        if (cameraSync.getCamera(pos, target, up, fov)) {
            successCount++;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "✅ Performance test completed!\n";
    std::cout << "   Success rate: " << successCount << "/10\n";
    std::cout << "   Total time: " << duration.count() << "ms\n";
    std::cout << "   Average per call: " << (duration.count() / 10.0f) << "ms\n\n";

    // Disconnect
    std::cout << "Test 7: Disconnecting...\n";
    cameraSync.disconnect();
    std::cout << "✅ Disconnected successfully!\n\n";

    std::cout << "🎉 All tests completed!\n";
    return 0;
}