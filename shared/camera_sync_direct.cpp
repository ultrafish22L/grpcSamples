#include "camera_sync_direct.h"
#include <iostream>
#include <cstring>

#include <google/protobuf/empty.pb.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

CameraSyncDirect::CameraSyncDirect()
    : m_initialized(false)
    , m_connected(false)
    , m_cameraAvailable(false)
    , m_lastPosition(0.0f)
    , m_lastTarget(0.0f, 0.0f, -1.0f)
    , m_lastUp(0.0f, 1.0f, 0.0f)
    , m_lastFov(45.0f)
    , m_moduleReady(true)
    , m_moduleStarted(false)
{
}

CameraSyncDirect::~CameraSyncDirect() {
    shutdown();
}

bool CameraSyncDirect::connectToServer(const std::string& serverAddress) {
    
    try {
        if (!m_cameraStub)
        {
            std::cout << "Connecting to Octane gRPC server at: " << serverAddress << std::endl;
            m_serverAddress = serverAddress;

            // Create gRPC channel
            m_channel = grpc::CreateChannel(serverAddress, grpc::InsecureChannelCredentials());

            if (!m_channel) {
                std::cout << "Failed to create gRPC channel" << std::endl;
                return false;
            }

            // Create CameraControl stub
            m_cameraStub = octaneapi::CameraControl::NewStub(m_channel);

            if (!m_cameraStub) {
                std::cout << "Failed to create CameraControl stub" << std::endl;
                return false;
            }
        }
        // Test connection by checking channel state
        auto state = m_channel->GetState(true);
        if (state == GRPC_CHANNEL_READY || state == GRPC_CHANNEL_CONNECTING) {
            if (!m_connected)
            {
                std::cout << "Successfully connected to Octane gRPC server at " << serverAddress << std::endl;
                m_connected = true;
            }
            return true;
        } else {
//            std::cout << "Failed to connect to Octane gRPC server (channel state: " << state << ")" << std::endl;
            return false;
        }
        
    } catch (const std::exception& e) {
        std::cout << "Exception while connecting to gRPC server: " << e.what() << std::endl;
        return false;
    }
    return true;
}

void CameraSyncDirect::initialize() {
    if (!m_connected) {
 //       std::cout << "Cannot initialize: not connected to server" << std::endl;
        return;
    }
    if (!m_initialized)
    {
//        std::cout << "Initializing gRPC camera control client..." << std::endl;

        try {
            // Check if channel and stub are ready
            if (m_channel && m_cameraStub) {
                // Test the connection with a simple call
                grpc::ClientContext context;
                google::protobuf::Empty request;
                octaneapi::CameraPositionResponse response;
                
                auto status = m_cameraStub->GetCameraPosition(&context, request, &response);
                
                if (status.ok()) {
                    m_cameraAvailable = true;
                    m_initialized = true;
                    std::cout << "gRPC camera control client initialized successfully" << std::endl;
                    return;
                } else {
                    std::cout << "Failed to communicate with Octane server: " << status.error_message() << std::endl;
                    m_cameraAvailable = false;
                    m_initialized = true; // Still initialized, but camera not available
                    return;
                }
            }
            else {
                std::cout << "Failed to initialize gRPC camera control client" << std::endl;
                return;
            }
        }
        catch (const std::exception& e) {
            std::cout << "Exception during gRPC camera initialization: " << e.what() << std::endl;
            return;
        }
    }
}

bool CameraSyncDirect::updateCameraLegacy(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up) {

    if (!m_initialized) {
        return false;
    }
    
    if (m_initialized) {
        
        try {
            if (!m_cameraAvailable) {
                grpc::ClientContext context;
                google::protobuf::Empty request;
                octaneapi::CameraPositionResponse response;

                auto status = m_cameraStub->GetCameraPosition(&context, request, &response);

                if (status.ok()) {
                    m_cameraAvailable = true;
                    std::cout << "gRPC camera control client initialized successfully" << std::endl;
                    return true;
                }
                m_cameraAvailable = false;
                return false;
            }
            // Update camera pos
            {
                grpc::ClientContext context;
                octaneapi::CameraPositionRequest request;
                google::protobuf::Empty response;
                
                glmToVector3(pos, request.mutable_position());
                auto status = m_cameraStub->SetCameraPosition(&context, request, &response);
                
                if (!status.ok()) {
                    std::cout << "Failed to set camera pos: " << status.error_message() << std::endl;
                    return false;
                }
            }
            
            // Update camera target
            {
                grpc::ClientContext context;
                octaneapi::CameraTargetRequest request;
                google::protobuf::Empty response;
                
                glmToVector3(target, request.mutable_target());
                auto status = m_cameraStub->SetCameraTarget(&context, request, &response);
                
                if (!status.ok()) {
                    std::cout << "Failed to set camera target: " << status.error_message() << std::endl;
                    return false;
                }
            }
            
            // Update camera up vector
            {
                grpc::ClientContext context;
                octaneapi::CameraUpRequest request;
                google::protobuf::Empty response;
                
                glmToVector3(up, request.mutable_up());
                auto status = m_cameraStub->SetCameraUp(&context, request, &response);
                
                if (!status.ok()) {
                    std::cout << "Failed to set camera up vector: " << status.error_message() << std::endl;
                    return false;
                }
            }
            
            // Cache the values
            m_lastPosition = pos;
            m_lastTarget = target;
            m_lastUp = up;
            
            std::cout << "Camera updated via gRPC - Position(" << pos.x << "," << pos.y << "," << pos.z << ")" 
                      << " Target(" << target.x << "," << target.y << "," << target.z << ")"
                      << " Up(" << up.x << "," << up.y << "," << up.z << ")" << std::endl;

//            ApiChangeManagerProxy::update();

            return true;
            
        } catch (const std::exception& e) {
            std::cout << "Exception during camera update: " << e.what() << std::endl;
            return false;
        }
    }
/*
    // Simulation mode or gRPC not available
    m_lastPosition = pos;
    m_lastTarget = target;
    m_lastUp = up;
    std::cout << "Simulation: Camera updated - Position(" << pos.x << "," << pos.y << "," << pos.z << ")" << std::endl;
*/

    return true;
}

bool CameraSyncDirect::updateCameraFromViewMatrix(const glm::mat4& viewMatrix) {
    if (!m_initialized) {
        return false;
    }
    
    // Extract camera pos, target, and up vector from view matrix
    // View matrix is the inverse of the camera's world transform
    glm::mat4 cameraTransform = glm::inverse(viewMatrix);
    
    // Extract pos from the 4th column
    glm::vec3 pos = glm::vec3(cameraTransform[3]);
    
    // Extract forward direction (negative Z axis in camera space)
    glm::vec3 forward = -glm::vec3(cameraTransform[2]);
    
    // Extract up direction (Y axis in camera space)
    glm::vec3 up = glm::vec3(cameraTransform[1]);
    
    // Calculate target point (pos + forward direction)
    glm::vec3 target = pos + forward;
    
    // Use the existing updateCameraLegacy method
    return updateCameraLegacy(pos, target, up);
}

bool CameraSyncDirect::isCameraControlAvailable() const {
    return m_initialized && m_cameraAvailable;
}

void CameraSyncDirect::shutdown() {
    if (m_connected) {
        std::cout << "Disconnecting from gRPC server..." << std::endl;
        
        // Clean up client resources
        m_cameraStub.reset();
        m_channel.reset();
        
        m_connected = false;
        m_initialized = false;
        m_cameraAvailable = false;
    }
}

void CameraSyncDirect::getCurrentCameraState(glm::vec3& pos, glm::vec3& target, glm::vec3& up) const {
    if (m_cameraAvailable && m_cameraStub) {
        try {
            // Get camera pos
            {
                grpc::ClientContext context;
                google::protobuf::Empty request;
                octaneapi::CameraPositionResponse response;
                
                auto status = m_cameraStub->GetCameraPosition(&context, request, &response);
                if (status.ok() && response.has_position()) {
                    pos = vector3ToGlm(response.position());
                } else {
                    pos = m_lastPosition;
                }
            }
            
            // Get camera target
            {
                grpc::ClientContext context;
                google::protobuf::Empty request;
                octaneapi::CameraTargetResponse response;
                
                auto status = m_cameraStub->GetCameraTarget(&context, request, &response);
                if (status.ok() && response.has_target()) {
                    target = vector3ToGlm(response.target());
                } else {
                    target = m_lastTarget;
                }
            }
            
            // Get camera up vector
            {
                grpc::ClientContext context;
                google::protobuf::Empty request;
                octaneapi::CameraUpResponse response;
                
                auto status = m_cameraStub->GetCameraUp(&context, request, &response);
                if (status.ok() && response.has_up()) {
                    up = vector3ToGlm(response.up());
                } else {
                    up = m_lastUp;
                }
            }
        } catch (const std::exception& e) {
            std::cout << "Exception getting camera state: " << e.what() << std::endl;
            // Fallback to cached values
            pos = m_lastPosition;
            target = m_lastTarget;
            up = m_lastUp;
        }
    } else {
        // Fallback to cached values
        pos = m_lastPosition;
        target = m_lastTarget;
        up = m_lastUp;
    }

}

// GRPCMainInterface implementation
void CameraSyncDirect::start(const std::string& callbackSource, const bool displayEnglish, const int secondLanguage) {
    std::cout << "gRPC Module started with callback source: " << callbackSource << std::endl;
    m_moduleStarted = true;
}

void CameraSyncDirect::stop() {
    std::cout << "gRPC Module stopped" << std::endl;
    m_moduleStarted = false;
}

bool CameraSyncDirect::isReady() {
    return m_moduleReady;
}

// CameraSyncBase interface implementation
void CameraSyncDirect::disconnect() {
    shutdown();
}

bool CameraSyncDirect::isConnected() const {
    return m_connected;
}

bool CameraSyncDirect::setCamera(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up, float fov, bool evaluate) {
    bool result = updateCameraLegacy(pos, target, up);
    if (result && fov > 0.0f) {
        m_lastFov = fov;
        // Note: FOV setting not implemented in octaneapi::CameraControl
        // This would need to be added to the proto definition
    }
    return result;
}

bool CameraSyncDirect::getCamera(glm::vec3& pos, glm::vec3& target, glm::vec3& up, float& fov) {
    if (!m_initialized) {
        pos = m_lastPosition;
        target = m_lastTarget;
        up = m_lastUp;
        fov = m_lastFov;
        return false;
    }
    try {
        // Get camera pos
        {
            grpc::ClientContext context;
            google::protobuf::Empty request;
            octaneapi::CameraPositionResponse response;
            
            auto status = m_cameraStub->GetCameraPosition(&context, request, &response);
            if (status.ok()) {
                pos = vector3ToGlm(response.position());
                m_lastPosition = pos;
            } else {
                pos = m_lastPosition;
            }
        }
        
        // Get camera target
        {
            grpc::ClientContext context;
            google::protobuf::Empty request;
            octaneapi::CameraTargetResponse response;
            
            auto status = m_cameraStub->GetCameraTarget(&context, request, &response);
            if (status.ok()) {
                target = vector3ToGlm(response.target());
                m_lastTarget = target;
            } else {
                target = m_lastTarget;
            }
        }
        
        // Get camera up
        {
            grpc::ClientContext context;
            google::protobuf::Empty request;
            octaneapi::CameraUpResponse response;
            
            auto status = m_cameraStub->GetCameraUp(&context, request, &response);
            if (status.ok()) {
                up = vector3ToGlm(response.up());
                m_lastUp = up;
            } else {
                up = m_lastUp;
            }
        }
        
        fov = m_lastFov; // FOV not available in current proto
        return true;
        
    } catch (const std::exception& e) {
        std::cout << "Exception during getCamera: " << e.what() << std::endl;
        pos = m_lastPosition;
        target = m_lastTarget;
        up = m_lastUp;
        fov = m_lastFov;
        return false;
    }
}

bool CameraSyncDirect::setCameraPosition(const glm::vec3& pos, bool evaluate) {
    if (!m_initialized) {
        m_lastPosition = pos;
        return false;
    }
    try {
        grpc::ClientContext context;
        octaneapi::CameraPositionRequest request;
        google::protobuf::Empty response;
        
        glmToVector3(pos, request.mutable_position());
        auto status = m_cameraStub->SetCameraPosition(&context, request, &response);
        
        if (status.ok()) {
            m_lastPosition = pos;
//            logGrpcStatus("SetCameraPosition", true);
            return true;
        } else {
            logGrpcStatus("SetCameraPosition", false);
            return false;
        }
    } catch (const std::exception& e) {
        std::cout << "Exception in setCameraPosition: " << e.what() << std::endl;
        return false;
    }
}

bool CameraSyncDirect::setCameraTarget(const glm::vec3& target, bool evaluate) {
    if (!m_initialized) {
        m_lastTarget = target;
        return false;
    }

    try {
        grpc::ClientContext context;
        octaneapi::CameraTargetRequest request;
        google::protobuf::Empty response;
        
        glmToVector3(target, request.mutable_target());
        auto status = m_cameraStub->SetCameraTarget(&context, request, &response);
        
        if (status.ok()) {
            m_lastTarget = target;
            logGrpcStatus("SetCameraTarget", true);
            return true;
        } else {
            logGrpcStatus("SetCameraTarget", false);
            return false;
        }
    } catch (const std::exception& e) {
        std::cout << "Exception in setCameraTarget: " << e.what() << std::endl;
        return false;
    }
}

bool CameraSyncDirect::setCameraUp(const glm::vec3& up, bool evaluate) {
    if (!m_initialized) {
        m_lastUp = up;
        return false;
    }

    try {
        grpc::ClientContext context;
        octaneapi::CameraUpRequest request;
        google::protobuf::Empty response;
        
        glmToVector3(up, request.mutable_up());
        auto status = m_cameraStub->SetCameraUp(&context, request, &response);
        
        if (status.ok()) {
            m_lastUp = up;
            logGrpcStatus("SetCameraUp", true);
            return true;
        } else {
            logGrpcStatus("SetCameraUp", false);
            return false;
        }
    } catch (const std::exception& e) {
        std::cout << "Exception in setCameraUp: " << e.what() << std::endl;
        return false;
    }

}

bool CameraSyncDirect::setCameraFov(float fov, bool evaluate) {
    // FOV setting not implemented in octaneapi::CameraControl
    // This would need to be added to the proto definition
    m_lastFov = fov;
    std::cout << "FOV setting not implemented in octaneapi::CameraControl protocol" << std::endl;
    return false;
}

// Helper functions
void CameraSyncDirect::glmToVector3(const glm::vec3& glmVec, octaneapi::Vector3* protoVec) {
    protoVec->set_x(glmVec.x);
    protoVec->set_y(glmVec.y);
    protoVec->set_z(glmVec.z);
}

glm::vec3 CameraSyncDirect::vector3ToGlm(const octaneapi::Vector3& protoVec) {
    return glm::vec3(protoVec.x(), protoVec.y(), protoVec.z());
}

void CameraSyncDirect::glmToProtobuf(const glm::mat4& glmMatrix, float* protoMatrix) {
    // GLM matrices are column-major, copy directly
    const float* src = glm::value_ptr(glmMatrix);
    for (int i = 0; i < 16; ++i) {
        protoMatrix[i] = src[i];
    }
}

void CameraSyncDirect::logGrpcStatus(const std::string& operation, bool success) {
    if (success) {
        std::cout << "Direct gRPC: " << operation << " - SUCCESS" << std::endl;
    } else {
        std::cout << "Direct gRPC: " << operation << " - FAILED" << std::endl;
    }
}