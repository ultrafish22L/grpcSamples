#ifndef GRPC_CAMERA_SYNC_H
#define GRPC_CAMERA_SYNC_H

#include <iostream>
#include <string>
#include <memory>
#include <mutex>
#include <thread>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera_sync_base.h"

// Direct gRPC interface - no SDK dependencies

#include <grpcpp/grpcpp.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include "protos/camera_control.grpc.pb.h"

/**
 * @brief Direct gRPC-based camera synchronization with Octane
 * 
 * This class implements a gRPC client that connects to an existing Octane server.
 * It demonstrates how to:
 * - Connect to Octane server via gRPC
 * - Use CameraControl::StubInterface to make API calls
 * - Handle camera synchronization using protobuf messages
 */
class CameraSyncDirect : public CameraSyncBase {
public:
    CameraSyncDirect();
    ~CameraSyncDirect();
    
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
    
    // Legacy methods for backward compatibility
    /**
     * @brief Update Octane camera using direct gRPC calls
     * @param position Camera position in world space
     * @param target Camera target/look-at point
     * @param up Camera up vector
     * @return true if update successful, false otherwise
     */
    bool updateCameraLegacy(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up);
    
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
     * @brief Helper functions to convert between glm::vec3 and octaneapi::Vector3
     */
    static void glmToVector3(const glm::vec3& glmVec, octaneapi::Vector3* protoVec);
    static glm::vec3 vector3ToGlm(const octaneapi::Vector3& protoVec);
    
    /**
     * @brief Convert GLM matrix to protobuf format
     */
    void glmToProtobuf(const glm::mat4& glmMatrix, float* protoMatrix);
    
    /**
     * @brief Log gRPC operation status
     */
    void logGrpcStatus(const std::string& operation, bool success);

private:
    bool m_initialized;
    bool m_connected;
    bool m_cameraAvailable;
    std::string m_serverAddress;
    
    std::shared_ptr<grpc::Channel> m_channel;
    std::unique_ptr<octaneapi::CameraControl::Stub> m_cameraStub;
    
    // Cache for last known camera state
    glm::vec3 m_lastPosition;
    glm::vec3 m_lastTarget;
    glm::vec3 m_lastUp;
    float m_lastFov;
    
    // Module state
    bool m_moduleReady;
    bool m_moduleStarted;
};

#endif // GRPC_CAMERA_SYNC_H