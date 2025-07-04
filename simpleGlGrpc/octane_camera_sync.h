#ifndef OCTANE_CAMERA_SYNC_H
#define OCTANE_CAMERA_SYNC_H

#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Forward declarations for SDK types
namespace Octane {
    class ApiNode;
    class ApiRenderEngine;
}

namespace OctaneVec {
    template<class ST> struct Vec3;
    template<class ST> struct Matrix;
    typedef Vec3<float> float3;
    typedef Matrix<float> float4x4;
}

/**
 * @brief Manages synchronization between OpenGL camera and Octane SDK camera
 * 
 * This class provides functionality to:
 * - Get the current render camera node from Octane
 * - Convert OpenGL camera parameters to Octane format
 * - Update Octane camera position and orientation
 */
class OctaneCameraSync {
public:
    OctaneCameraSync();
    ~OctaneCameraSync();
    
    /**
     * @brief Connect to Octane server
     * @param serverAddress Server address (Unix socket path, e.g., "/tmp/octane_server.sock")
     * @return true if connection successful, false otherwise
     */
    bool connectToServer(const std::string& serverAddress = "/tmp/octane_server.sock");
    
    /**
     * @brief Initialize the camera sync system
     * @return true if initialization successful, false otherwise
     */
    bool initialize();
    
    /**
     * @brief Update Octane camera to match OpenGL camera
     * @param position Camera position in world space
     * @param target Camera target/look-at point
     * @param up Camera up vector
     * @return true if update successful, false otherwise
     */
    bool updateCamera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up);
    
    /**
     * @brief Update Octane camera using view matrix
     * @param viewMatrix OpenGL view matrix
     * @return true if update successful, false otherwise
     */
    bool updateCameraFromViewMatrix(const glm::mat4& viewMatrix);
    
    /**
     * @brief Check if SDK camera functionality is available
     * @return true if camera can be controlled, false otherwise
     */
    bool isCameraControlAvailable() const;
    
    /**
     * @brief Get current camera position from Octane
     * @param position Output camera position
     * @return true if successful, false otherwise
     */
    bool getCameraPosition(glm::vec3& position) const;
    
    /**
     * @brief Get current camera orientation from Octane
     * @param forward Output forward vector
     * @param up Output up vector
     * @return true if successful, false otherwise
     */
    bool getCameraOrientation(glm::vec3& forward, glm::vec3& up) const;

private:
    /**
     * @brief Convert GLM vector to Octane vector
     */
    OctaneVec::float3 glmToOctane(const glm::vec3& v) const;
    
    /**
     * @brief Convert GLM matrix to Octane matrix
     */
    OctaneVec::float4x4 glmToOctane(const glm::mat4& m) const;
    
    /**
     * @brief Convert Octane vector to GLM vector
     */
    glm::vec3 octaneToGlm(const OctaneVec::float3& v) const;
    
    /**
     * @brief Get the render camera node from Octane
     * @return Pointer to camera node, or nullptr if not available
     */
    Octane::ApiNode* getRenderCameraNode();
    
    /**
     * @brief Set camera transform matrix
     * @param node Camera node
     * @param transform Transform matrix
     * @return true if successful, false otherwise
     */
    bool setCameraTransform(Octane::ApiNode* node, const OctaneVec::float4x4& transform);

private:
    bool m_initialized;
    bool m_cameraAvailable;
    Octane::ApiNode* m_cameraNode;
    
    // Cache for last known camera state
    glm::vec3 m_lastPosition;
    glm::vec3 m_lastTarget;
    glm::vec3 m_lastUp;
};

#endif // OCTANE_CAMERA_SYNC_H