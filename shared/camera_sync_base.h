#pragma once

#include <string>
#include <glm/glm.hpp>

/**
 * Abstract base class for camera synchronization implementations
 * Provides a common interface for different gRPC camera sync protocols
 */
class CameraSyncBase {
public:
    virtual ~CameraSyncBase() = default;

    // Connection management
    virtual bool connectToServer(const std::string& serverAddress) = 0;
    virtual void disconnect() = 0;
    virtual bool isConnected() const = 0;

    // Basic camera operations
    virtual bool setCamera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up, float fov = 0.0f) = 0;
    virtual bool getCamera(glm::vec3& position, glm::vec3& target, glm::vec3& up, float& fov) = 0;

    // Individual camera component setters
    virtual bool setCameraPosition(const glm::vec3& position) = 0;
    virtual bool setCameraTarget(const glm::vec3& target) = 0;
    virtual bool setCameraUp(const glm::vec3& up) = 0;
    virtual bool setCameraFov(float fov) = 0;

    // Update camera from view matrix (for compatibility with existing code)
    virtual void updateCamera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up) {
        setCamera(position, target, up);
    }

    // Initialize (for compatibility with existing code)
    virtual void initialize() {}
};