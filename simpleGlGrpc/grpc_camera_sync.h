#ifndef GRPC_CAMERA_SYNC_H
#define GRPC_CAMERA_SYNC_H

#include <iostream>
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Direct gRPC interface - no SDK dependencies

#ifdef OCTANE_GRPC_ENABLED
#include <grpcpp/grpcpp.h>
#include "camera_control.grpc.pb.h"
#endif

/**
 * @brief Direct gRPC-based camera synchronization with Octane
 * 
 * This class implements direct gRPC communication with Octane instead of
 * using the SDK proxy classes. It demonstrates how to:
 * - Establish direct gRPC connections
 * - Make direct API calls using protobuf messages
 * - Handle camera synchronization without SDK wrappers
 */
class GrpcCameraSync {
public:
    GrpcCameraSync();
    ~GrpcCameraSync();
    
    /**
     * @brief Connect to Octane server using direct gRPC
     * @param serverAddress Server address (Unix socket path)
     * @param clientAddress Client callback address
     * @return true if connection successful, false otherwise
     */
    bool connectToServer(const std::string& serverAddress = "/tmp/octane_server.sock",
                        const std::string& clientAddress = "/tmp/grpc_client.sock");
    
    /**
     * @brief Initialize the gRPC camera sync system
     * @return true if initialization successful, false otherwise
     */
    bool initialize();
    
    /**
     * @brief Update Octane camera using direct gRPC calls
     * @param position Camera position in world space
     * @param target Camera target/look-at point
     * @param up Camera up vector
     * @return true if update successful, false otherwise
     */
    bool updateCamera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up);
    
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
     * @brief Shutdown the gRPC connection
     */
    void shutdown();

    // Direct gRPC interface methods
    void start(const std::string& callbackSource, const bool displayEnglish, const int secondLanguage);
    void stop();
    bool isReady();

private:
    /**
     * @brief Make a direct gRPC call to get render camera
     * @return true if successful, false otherwise
     */
    bool getRenderCameraNode();
    
    /**
     * @brief Make a direct gRPC call to set camera transform
     * @param transform Transform matrix
     * @return true if successful, false otherwise
     */
    bool setCameraTransform(const glm::mat4& transform);
    
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
    std::string m_clientAddress;
    
#ifdef OCTANE_GRPC_ENABLED
    std::shared_ptr<grpc::Channel> m_channel;
    std::unique_ptr<octaneapi::CameraControl::Stub> m_cameraStub;
#endif
    
    // Cache for last known camera state
    glm::vec3 m_lastPosition;
    glm::vec3 m_lastTarget;
    glm::vec3 m_lastUp;
    
    // Module state
    bool m_moduleReady;
    bool m_moduleStarted;
};

#endif // GRPC_CAMERA_SYNC_H