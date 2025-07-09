/*
 * ✨ Modern 3D Cube Viewer Demo
 * 
 * This is a simplified version showing the key concepts used in the main application.
 * It demonstrates the camera system, modern OpenGL rendering with lighting, and SDK integration.
 */

#include <iostream>
#include <cmath>
#include <glm/glm.hpp>

#include "../shared_rendering.h"

// Direct SDK integration
#include "../shared/camera_sync_sdk.h"

// Simplified Camera class to demonstrate the spherical coordinate system
class Camera {
public:
    float radius = 5.0f;
    float theta = 0.0f;  // horizontal angle (azimuth)
    float phi = 0.0f;    // vertical angle (elevation)
    
    struct Vec3 {
        float x, y, z;
        Vec3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
    };
    
    Vec3 center = Vec3(0.0f, 0.0f, 0.0f);
    
    Vec3 getPosition() const {
        float x = radius * cos(phi) * cos(theta);
        float y = radius * sin(phi);
        float z = radius * cos(phi) * sin(theta);
        return Vec3(center.x + x, center.y + y, center.z + z);
    }
    
    void orbitHorizontal(float deltaAngle) {
        theta += deltaAngle;
    }
    
    void orbitVertical(float deltaAngle) {
        phi += deltaAngle;
        // Clamp to prevent flipping
        if (phi > 1.5f) phi = 1.5f;
        if (phi < -1.5f) phi = -1.5f;
    }
    
    void zoom(float deltaRadius) {
        radius += deltaRadius;
        if (radius < 1.0f) radius = 1.0f;
        if (radius > 20.0f) radius = 20.0f;
    }
    
    void printStatus() const {
        Vec3 pos = getPosition();
        std::cout << "Camera Position: (" << pos.x << ", " << pos.y << ", " << pos.z << ")\n";
        std::cout << "Radius: " << radius << ", Theta: " << theta << ", Phi: " << phi << "\n";
        std::cout << "Looking at: (" << center.x << ", " << center.y << ", " << center.z << ")\n\n";
    }
};

int main() {
    std::cout << "3D Cube Viewer - Camera System Demo\n";
    std::cout << "====================================\n\n";
    
    Camera camera;
    CameraSyncSdk octaneSync;
    
    // Connect to Octane server and initialize camera sync
    std::cout << "Connecting to Octane server...\n";
    if (octaneSync.connectToServer("127.0.0.1:51022")) {
        std::cout << "Connected to Octane server successfully\n";
    } else {
        std::cout << "Warning: Failed to connect to Octane server\n";
    }
    
    std::cout << "Initializing Octane SDK integration...\n";
    if (octaneSync.initialize()) {
        std::cout << "Octane camera sync initialized successfully\n\n";
    } else {
        std::cout << "Warning: Octane camera sync initialization failed\n\n";
    }
    
    std::cout << "Initial camera state:\n";
    camera.printStatus();
    
    std::cout << "Orbiting horizontally (simulating mouse drag left):\n";
    camera.orbitHorizontal(0.5f);
    camera.printStatus();
    
    // Update Octane camera
    Camera::Vec3 pos = camera.getPosition();
    glm::vec3 position(pos.x, pos.y, pos.z);
    glm::vec3 center(camera.center.x, camera.center.y, camera.center.z);
    octaneSync.updateCamera(position, center, glm::vec3(0.0f, 1.0f, 0.0f));
    
    std::cout << "Orbiting vertically (simulating mouse drag up):\n";
    camera.orbitVertical(0.3f);
    camera.printStatus();
    
    // Update Octane camera
    pos = camera.getPosition();
    position = glm::vec3(pos.x, pos.y, pos.z);
    octaneSync.updateCamera(position, center, glm::vec3(0.0f, 1.0f, 0.0f));
    
    std::cout << "Zooming in (simulating mouse wheel scroll):\n";
    camera.zoom(-2.0f);
    camera.printStatus();
    
    // Update Octane camera
    pos = camera.getPosition();
    position = glm::vec3(pos.x, pos.y, pos.z);
    octaneSync.updateCamera(position, center, glm::vec3(0.0f, 1.0f, 0.0f));
    
    std::cout << "Zooming out:\n";
    camera.zoom(4.0f);
    camera.printStatus();
    
    std::cout << "The actual application uses this camera system with OpenGL to:\n";
    std::cout << "- Render a colorful 3D cube\n";
    std::cout << "- Handle mouse input for interactive camera control\n";
    std::cout << "- Apply perspective projection and view transformations\n";
    std::cout << "- Render in real-time with smooth animations\n";
    
    return 0;
}