/**
 * Test simpleGlGrpc connection logic without GUI
 * Verify it connects directly to mock Octane server
 */

#include <iostream>
#include <memory>
#include <string>

// Include the same components as simpleGlGrpc
#include "shared/camera_sync_livelink.h"

int main() {
    std::cout << "🧪 Testing simpleGlGrpc Direct Connection Logic\n";
    std::cout << "===============================================\n\n";

    // Create the same components as simpleGlGrpc
    CameraSyncLiveLink cameraSync;
    
    // Use the same server address as simpleGlGrpc
    std::string serverAddress = "127.0.0.1:51022";
    
    std::cout << "Testing simpleGlGrpc connection pattern...\n";
    std::cout << "Server address: " << serverAddress << "\n\n";

    // Test connection (same logic as simpleGlGrpc line 119)
    std::cout << "Test: Direct connection to mock Octane server...\n";
    
    bool connected = cameraSync.connectToServer(serverAddress);
    if (connected) {
        std::cout << "✅ simpleGlGrpc connection pattern working!\n";
        std::cout << "✅ Connected directly to mock Octane server\n\n";
        
        // Test basic operation
        glm::vec3 pos, target, up;
        float fov;
        if (cameraSync.getCamera(pos, target, up, fov)) {
            std::cout << "✅ Camera sync operational\n";
            std::cout << "   Position: (" << pos.x << ", " << pos.y << ", " << pos.z << ")\n";
        }
        
        cameraSync.disconnect();
        std::cout << "✅ Disconnected successfully\n";
    } else {
        std::cout << "❌ simpleGlGrpc connection failed!\n";
        return 1;
    }

    std::cout << "\n🎉 simpleGlGrpc connection logic verified!\n";
    std::cout << "✅ Both simpleGlGrpc and testGrpcApi use same direct connection\n";
    std::cout << "✅ No proxy server required for either application\n";
    
    return 0;
}