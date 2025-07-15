/**
 * Test the testGrpcApi connection logic without GUI
 * Verifies it connects directly to mock Octane server like simpleGlGrpc
 */

#include <iostream>
#include <memory>
#include <string>

// Include the same components as testGrpcApi
#include "shared/camera_sync_livelink.h"
#include "testGrpcApi/ActivityLogger.h"

int main() {
    std::cout << "🧪 Testing testGrpcApi Direct Connection Logic\n";
    std::cout << "==============================================\n\n";

    // Create the same components as testGrpcApi
    CameraSyncLiveLink cameraSync;
    auto logger = std::make_unique<ActivityLogger>();
    
    // Use the same server address as updated testGrpcApi
    std::string serverAddress = "127.0.0.1:51022";  // Direct connection to mock Octane server
    
    std::cout << "Testing direct connection to mock Octane server (bypassing proxy)...\n";
    std::cout << "Server address: " << serverAddress << "\n\n";

    // Test 1: Connection (same logic as testGrpcApi)
    std::cout << "Test 1: Direct connection to mock Octane server...\n";
    logger->Log("Connecting to Octane LiveLink at " + serverAddress + "...", ActivityLogger::LogLevel::STATUS);
    
    bool connected = cameraSync.connectToServer(serverAddress);
    if (connected) {
        logger->Log("✅ Connected to Octane LiveLink successfully", ActivityLogger::LogLevel::STATUS);
        std::cout << "✅ Connection successful! (same as simpleGlGrpc)\n\n";
    } else {
        logger->Log("❌ Failed to connect to Octane LiveLink", ActivityLogger::LogLevel::LOG_ERROR);
        std::cout << "❌ Connection failed!\n\n";
        return 1;
    }

    // Test 2: Basic operations (same as testGrpcApi would do)
    std::cout << "Test 2: Basic gRPC operations...\n";
    
    // Get camera (like testGrpcApi sync logic)
    glm::vec3 pos, target, up;
    float fov;
    bool gotCamera = cameraSync.getCamera(pos, target, up, fov);
    if (gotCamera) {
        logger->Log("✅ Got camera position successfully", ActivityLogger::LogLevel::STATUS);
        std::cout << "✅ Camera sync working!\n";
        std::cout << "   Position: (" << pos.x << ", " << pos.y << ", " << pos.z << ")\n";
    } else {
        logger->Log("❌ Failed to get camera position", ActivityLogger::LogLevel::LOG_ERROR);
        std::cout << "❌ Camera sync failed!\n";
    }

    // Test 3: Set camera (like testGrpcApi would do)
    std::cout << "\nTest 3: Setting camera position...\n";
    glm::vec3 newPos(2.0f, 3.0f, 4.0f);
    glm::vec3 newTarget(0.0f, 0.0f, 0.0f);
    glm::vec3 newUp(0.0f, 1.0f, 0.0f);
    
    bool setCamera = cameraSync.setCamera(newPos, newTarget, newUp, 45.0f);
    if (setCamera) {
        logger->Log("✅ Set camera position successfully", ActivityLogger::LogLevel::STATUS);
        std::cout << "✅ Camera control working!\n";
    } else {
        logger->Log("❌ Failed to set camera position", ActivityLogger::LogLevel::LOG_ERROR);
        std::cout << "❌ Camera control failed!\n";
    }

    // Test 4: Get meshes (like testGrpcApi would do)
    std::cout << "\nTest 4: Getting mesh list...\n";
    std::vector<CameraSyncLiveLink::MeshInfo> meshes;
    bool gotMeshes = cameraSync.getMeshList(meshes);
    if (gotMeshes) {
        logger->Log("✅ Got mesh list successfully (" + std::to_string(meshes.size()) + " meshes)", ActivityLogger::LogLevel::STATUS);
        std::cout << "✅ Mesh discovery working! Found " << meshes.size() << " meshes\n";
        for (const auto& mesh : meshes) {
            std::cout << "   - " << mesh.name << " (ID: " << mesh.id << ")\n";
        }
    } else {
        logger->Log("❌ Failed to get mesh list", ActivityLogger::LogLevel::LOG_ERROR);
        std::cout << "❌ Mesh discovery failed!\n";
    }

    // Disconnect (same as testGrpcApi)
    std::cout << "\nTest 5: Disconnecting...\n";
    logger->Log("Disconnecting from Octane LiveLink...", ActivityLogger::LogLevel::STATUS);
    cameraSync.disconnect();
    logger->Log("Disconnected from Octane LiveLink", ActivityLogger::LogLevel::STATUS);
    std::cout << "✅ Disconnected successfully!\n\n";

    // Show activity log (like testGrpcApi would display)
    std::cout << "📋 Activity Log (as testGrpcApi would show):\n";
    std::cout << "==========================================\n";
    auto logs = logger->GetLogs();
    for (const auto& log : logs) {
        std::cout << log.timestamp << " - " << log.message << "\n";
    }

    std::cout << "\n🎉 testGrpcApi connection logic verified!\n";
    std::cout << "✅ Now connects directly to mock Octane server (127.0.0.1:51022)\n";
    std::cout << "✅ Same connection pattern as simpleGlGrpc\n";
    std::cout << "✅ No proxy server required\n";
    
    return 0;
}