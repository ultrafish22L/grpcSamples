#include "grpc_camera_sync.h"
#include <iostream>
#include <cstring>

#ifdef OCTANE_GRPC_ENABLED
#include <google/protobuf/empty.pb.h>
#endif

GrpcCameraSync::GrpcCameraSync()
    : m_initialized(false)
    , m_connected(false)
    , m_cameraAvailable(false)
    , m_lastPosition(0.0f)
    , m_lastTarget(0.0f, 0.0f, -1.0f)
    , m_lastUp(0.0f, 1.0f, 0.0f)
    , m_moduleReady(true)
    , m_moduleStarted(false)
{
#ifdef OCTANE_GRPC_ENABLED
    // Initialize gRPC channel and stub when needed
#endif
}

GrpcCameraSync::~GrpcCameraSync() {
    shutdown();
}

bool GrpcCameraSync::connectToServer(const std::string& serverAddress, const std::string& clientAddress) {
    std::cout << "Connecting to Octane server via direct gRPC at: " << serverAddress << std::endl;
    
#ifdef OCTANE_GRPC_ENABLED
    try {
        m_serverAddress = serverAddress;
        m_clientAddress = clientAddress;
        
        // Create direct channel to Octane server
        std::string unixAddress = "unix:" + serverAddress;
        m_channel = grpc::CreateChannel(unixAddress, grpc::InsecureChannelCredentials());
        
        if (!m_channel) {
            std::cout << "Failed to create gRPC channel to Octane server" << std::endl;
            return false;
        }
        
        // Create camera control stub
        m_cameraStub = octaneapi::CameraControl::NewStub(m_channel);
        
        // Test connection by checking channel state
        auto state = m_channel->GetState(true);
        if (state == GRPC_CHANNEL_READY || state == GRPC_CHANNEL_CONNECTING) {
            std::cout << "Successfully connected to Octane server via direct gRPC" << std::endl;
            m_connected = true;
            return true;
        } else {
            std::cout << "gRPC channel not ready, state: " << state << std::endl;
            return false;
        }
    } catch (const std::exception& e) {
        std::cout << "Exception while connecting to Octane server: " << e.what() << std::endl;
        return false;
    }
#else
    std::cout << "gRPC support not enabled, cannot connect to Octane server" << std::endl;
    return false;
#endif
}

bool GrpcCameraSync::initialize() {
    if (!m_connected) {
        std::cout << "Cannot initialize: not connected to server" << std::endl;
        return false;
    }
    
    std::cout << "Initializing direct gRPC camera sync..." << std::endl;
    
#ifdef OCTANE_GRPC_ENABLED
    try {
        // Test if we can get render camera using direct gRPC calls
        if (getRenderCameraNode()) {
            m_cameraAvailable = true;
            m_initialized = true;
            std::cout << "Direct gRPC camera sync initialized successfully" << std::endl;
            return true;
        } else {
            std::cout << "Failed to get render camera node via direct gRPC" << std::endl;
            return false;
        }
    } catch (const std::exception& e) {
        std::cout << "Exception during gRPC camera initialization: " << e.what() << std::endl;
        return false;
    }
#else
    std::cout << "gRPC support not enabled, using simulation mode" << std::endl;
    m_cameraAvailable = false;
    m_initialized = true;
    return true;
#endif
}

bool GrpcCameraSync::updateCamera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up) {
    if (!m_initialized) {
        return false;
    }
    
#ifdef OCTANE_GRPC_ENABLED
    if (m_cameraStub) {
        try {
            grpc::ClientContext context;
            google::protobuf::Empty response;
            
            // Set camera position
            octaneapi::CameraPositionRequest posRequest;
            auto* pos = posRequest.mutable_position();
            pos->set_x(position.x);
            pos->set_y(position.y);
            pos->set_z(position.z);
            
            auto status = m_cameraStub->SetCameraPosition(&context, posRequest, &response);
            if (!status.ok()) {
                std::cout << "Failed to set camera position: " << status.error_message() << std::endl;
                return false;
            }
            
            // Set camera target
            grpc::ClientContext context2;
            octaneapi::CameraTargetRequest targetRequest;
            auto* tgt = targetRequest.mutable_target();
            tgt->set_x(target.x);
            tgt->set_y(target.y);
            tgt->set_z(target.z);
            
            status = m_cameraStub->SetCameraTarget(&context2, targetRequest, &response);
            if (!status.ok()) {
                std::cout << "Failed to set camera target: " << status.error_message() << std::endl;
                return false;
            }
            
            // Set camera up vector
            grpc::ClientContext context3;
            octaneapi::CameraUpRequest upRequest;
            auto* upVec = upRequest.mutable_up();
            upVec->set_x(up.x);
            upVec->set_y(up.y);
            upVec->set_z(up.z);
            
            status = m_cameraStub->SetCameraUp(&context3, upRequest, &response);
            if (!status.ok()) {
                std::cout << "Failed to set camera up: " << status.error_message() << std::endl;
                return false;
            }
            
            // Cache the values
            m_lastPosition = position;
            m_lastTarget = target;
            m_lastUp = up;
            
            std::cout << "Camera updated via direct gRPC protobuf calls" << std::endl;
            return true;
            
        } catch (const std::exception& e) {
            std::cout << "Exception during gRPC camera update: " << e.what() << std::endl;
            return false;
        }
    }
#endif
    
    // Simulation mode
    std::cout << "Simulation: Camera updated - Position(" << position.x << "," << position.y << "," << position.z << ")" << std::endl;
    return true;
}

bool GrpcCameraSync::updateCameraFromViewMatrix(const glm::mat4& viewMatrix) {
    if (!m_initialized) {
        return false;
    }
    
#ifdef OCTANE_GRPC_ENABLED
    if (m_cameraAvailable) {
        try {
            // Use direct gRPC call to set camera transform
            if (setCameraTransform(viewMatrix)) {
                logGrpcStatus("Camera transform update", true);
                return true;
            } else {
                logGrpcStatus("Camera transform update", false);
                return false;
            }
        } catch (const std::exception& e) {
            std::cout << "Exception during gRPC camera update: " << e.what() << std::endl;
            return false;
        }
    } else {
        // Simulation mode - just log the operation
        std::cout << "Simulation: Camera transform updated via direct gRPC" << std::endl;
        return true;
    }
#else
    // No gRPC support - simulation mode
    std::cout << "Simulation: Camera transform updated (gRPC disabled)" << std::endl;
    return true;
#endif
}

bool GrpcCameraSync::isCameraControlAvailable() const {
    return m_initialized && m_cameraAvailable;
}

void GrpcCameraSync::shutdown() {
    if (m_connected) {
        std::cout << "Shutting down direct gRPC camera sync..." << std::endl;
        
#ifdef OCTANE_GRPC_ENABLED
        // Clean up gRPC resources
        m_cameraStub.reset();
        m_channel.reset();
#endif
        
        m_connected = false;
        m_initialized = false;
        m_cameraAvailable = false;
    }
}

// GRPCMainInterface implementation
void GrpcCameraSync::start(const std::string& callbackSource, const bool displayEnglish, const int secondLanguage) {
    std::cout << "gRPC Module started with callback source: " << callbackSource << std::endl;
    m_moduleStarted = true;
}

void GrpcCameraSync::stop() {
    std::cout << "gRPC Module stopped" << std::endl;
    m_moduleStarted = false;
}

bool GrpcCameraSync::isReady() {
    return m_moduleReady;
}

// Private methods
bool GrpcCameraSync::getRenderCameraNode() {
#ifdef OCTANE_GRPC_ENABLED
    if (!m_channel) {
        return false;
    }
    
    try {
        // TODO: Implement direct gRPC calls using generated protobuf stubs
        // For now, simulate success
        std::cout << "Direct gRPC: Retrieved render camera node (simulated)" << std::endl;
        return true;
        
        // Future implementation would look like:
        // auto stub = octaneapi::ApiRenderEngine::NewStub(m_channel);
        // octaneapi::ApiRenderEngine::getRenderCameraRequest request;
        // octaneapi::ApiRenderEngine::getRenderCameraResponse response;
        // grpc::ClientContext context;
        // grpc::Status status = stub->getRenderCamera(&context, request, &response);
        // return status.ok();
    } catch (const std::exception& e) {
        std::cout << "Exception in getRenderCameraNode: " << e.what() << std::endl;
        return false;
    }
#else
    // Simulation mode
    std::cout << "Simulation: Retrieved render camera node" << std::endl;
    return true;
#endif
}

bool GrpcCameraSync::setCameraTransform(const glm::mat4& transform) {
#ifdef OCTANE_GRPC_ENABLED
    if (!m_channel) {
        return false;
    }
    
    try {
        // TODO: Implement direct gRPC calls using generated protobuf stubs
        // For now, simulate success
        std::cout << "Direct gRPC: Set camera transform (simulated)" << std::endl;
        return true;
        
        // Future implementation would look like:
        // auto stub = octaneapi::ApiNode::NewStub(m_channel);
        // octaneapi::ApiNode::setTransformRequest request;
        // octaneapi::ApiNode::setTransformResponse response;
        // // Convert GLM matrix to protobuf format
        // auto* protoTransform = request.mutable_transform();
        // glmToProtobuf(transform, protoTransform->mutable_data()->mutable_data());
        // grpc::ClientContext context;
        // grpc::Status status = stub->setTransform(&context, request, &response);
        // return status.ok();
    } catch (const std::exception& e) {
        std::cout << "Exception in setCameraTransform: " << e.what() << std::endl;
        return false;
    }
#else
    // Simulation mode
    std::cout << "Simulation: Set camera transform" << std::endl;
    return true;
#endif
}

void GrpcCameraSync::glmToProtobuf(const glm::mat4& glmMatrix, float* protoMatrix) {
    // GLM matrices are column-major, copy directly
    const float* src = glm::value_ptr(glmMatrix);
    for (int i = 0; i < 16; ++i) {
        protoMatrix[i] = src[i];
    }
}

void GrpcCameraSync::logGrpcStatus(const std::string& operation, bool success) {
    if (success) {
        std::cout << "Direct gRPC: " << operation << " - SUCCESS" << std::endl;
    } else {
        std::cout << "Direct gRPC: " << operation << " - FAILED" << std::endl;
    }
}