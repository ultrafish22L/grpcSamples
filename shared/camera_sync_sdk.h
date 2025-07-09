#ifndef CAMERA_SYNC_SDK_H
#define CAMERA_SYNC_SDK_H

#include <iostream>
#include <string>
#include <memory>
#include <mutex>
#include <thread>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera_sync_base.h"

#ifdef OCTANE_SDK_ENABLED
//#include "octanegrpcwrappers.h"
#include "apirenderengineclient.h"
#include "apinodeinfoclient.h"
#include "apilogmanagerclient.h"
#endif

/**
 * @brief SDK-based camera synchronization with Octane
 * 
 * This class implements direct SDK integration with Octane.
 * It demonstrates how to:
 * - Initialize Octane SDK
 * - Use SDK API calls to control camera
 * - Handle camera synchronization using native SDK objects
 */
class CameraSyncSdk : public CameraSyncBase {
public:
    CameraSyncSdk();
    ~CameraSyncSdk();
    
    // CameraSyncBase interface implementation
    bool connectToServer(const std::string& serverAddress) override;
    void disconnect() override;
    bool isConnected() const override;
    bool setCamera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up, float fov = 0.0f) override;
    bool getCamera(glm::vec3& position, glm::vec3& target, glm::vec3& up, float& fov) override;
    bool setCameraPosition(const glm::vec3& position) override;
    bool setCameraTarget(const glm::vec3& target) override;
    bool setCameraUp(const glm::vec3& up) override;
    bool setCameraFov(float fov) override;
    void initialize() override;
    void updateCamera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up) override;
    
    /**
     * @brief Update Octane camera using view matrix via direct gRPC
     * @param viewMatrix OpenGL view matrix
     * @return true if update successful, false otherwise
     */
    bool updateCameraFromViewMatrix(const glm::mat4& viewMatrix);
    
    /**
     * @brief Check if direct gRPC camera functionality is available
     * @return true if camera can be controlled, false otherwise
     */
    bool isCameraControlAvailable() const;
    
    /**
     * @brief Disconnect from the gRPC server (legacy method)
     */
    void shutdown();
    
    /**
     * @brief Get current camera state from Octane server
     */
    void getCurrentCameraState(glm::vec3& position, glm::vec3& target, glm::vec3& up) const;

    // Direct gRPC interface methods
    void start(const std::string& callbackSource, const bool displayEnglish, const int secondLanguage);
    void stop();
    bool isReady();

private:

    
    /**
     * @brief Log SDK operation status
     */
    void logSdkStatus(const std::string& operation, bool success);
    
    /**
     * @brief Legacy camera update method
     */
    bool updateCameraLegacy(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up);

private:
    bool m_initialized;
    bool m_connected;
    bool m_cameraAvailable;
    std::string m_serverAddress;
    
    // Octane SDK objects
#ifdef OCTANE_SDK_ENABLED
    ApiRenderEngineProxy m_renderEngine;
    ApiNodeProxy m_cameraNode;
#endif

    // Cache for last known camera state
    glm::vec3 m_lastPosition;
    glm::vec3 m_lastTarget;
    glm::vec3 m_lastUp;
    float m_lastFov;
    
    // Module state
    bool m_moduleReady;
    bool m_moduleStarted;
};

#endif // CAMERA_SYNC_SDK_H