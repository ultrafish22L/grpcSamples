#include "octane_camera_sync.h"
#include <iostream>
#include <cstring>

// Include SDK headers
#include "apirender.h"
#include "octanevectypes.h"
#include "octanematrix.h"
#include "octaneenums.h"

// Include gRPC settings and client headers for connection management
#ifdef OCTANE_GRPC_ENABLED
#include "src/api/grpc/grpcsettings.h"
#include "src/api/grpc/client/apirenderengineclient.h"
#include "src/api/grpc/client/apinodeclient.h"
#endif

OctaneCameraSync::OctaneCameraSync()
    : m_initialized(false)
    , m_cameraAvailable(false)
    , m_cameraNode(nullptr)
    , m_lastPosition(0.0f)
    , m_lastTarget(0.0f, 0.0f, -1.0f)
    , m_lastUp(0.0f, 1.0f, 0.0f)
{
}

OctaneCameraSync::~OctaneCameraSync() {
    // Cleanup if needed
}

bool OctaneCameraSync::connectToServer(const std::string& serverAddress) {
    std::cout << "Connecting to Octane server at Unix socket: " << serverAddress << std::endl;
    
#ifdef OCTANE_GRPC_ENABLED
    try {
        // Get the GRPCSettings singleton and set the server address
        // The GRPCSettings expects a "unix:" prefixed address
        std::string unixAddress = "unix:" + serverAddress;
        GRPCSettings& settings = GRPCSettings::getInstance();
        settings.setServerAddress(unixAddress);
        
        // Get the channel to test connection
        auto& channel = settings.getChannel();
        if (channel) {
            std::cout << "Successfully connected to Octane server via Unix socket" << std::endl;
            return true;
        } else {
            std::cout << "Failed to establish gRPC channel to Octane server" << std::endl;
            return false;
        }
    } catch (const std::exception& e) {
        std::cout << "Exception while connecting to Octane server: " << e.what() << std::endl;
        return false;
    }
#else
    std::cout << "gRPC functionality not enabled in build - connection simulation mode" << std::endl;
    std::cout << "Would connect to Unix socket: " << serverAddress << std::endl;
    return true; // Return true for simulation mode
#endif
}

bool OctaneCameraSync::initialize() {
    if (m_initialized) {
        return true;
    }
    
    std::cout << "Initializing Octane Camera Sync..." << std::endl;
    
    // Try to get the render camera node
    m_cameraNode = getRenderCameraNode();
    
    if (m_cameraNode) {
        m_cameraAvailable = true;
        std::cout << "Octane render camera node found and available" << std::endl;
    } else {
        m_cameraAvailable = false;
        std::cout << "Octane render camera node not available (gRPC functionality disabled)" << std::endl;
        std::cout << "Camera sync will operate in simulation mode" << std::endl;
    }
    
    m_initialized = true;
    return true;
}

bool OctaneCameraSync::updateCamera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up) {
    if (!m_initialized) {
        std::cerr << "OctaneCameraSync not initialized" << std::endl;
        return false;
    }
    
    // Cache the camera parameters
    m_lastPosition = position;
    m_lastTarget = target;
    m_lastUp = up;
    
    // Create view matrix and convert to world transform
    glm::mat4 viewMatrix = glm::lookAt(position, target, up);
    glm::mat4 worldMatrix = glm::inverse(viewMatrix);
    
    return updateCameraFromViewMatrix(viewMatrix);
}

bool OctaneCameraSync::updateCameraFromViewMatrix(const glm::mat4& viewMatrix) {
    if (!m_initialized) {
        std::cerr << "OctaneCameraSync not initialized" << std::endl;
        return false;
    }
    
    // Extract camera position and orientation from view matrix
    glm::mat4 worldMatrix = glm::inverse(viewMatrix);
    glm::vec3 position = glm::vec3(worldMatrix[3]);
    glm::vec3 forward = -glm::vec3(worldMatrix[2]);
    glm::vec3 up = glm::vec3(worldMatrix[1]);
    
    std::cout << "Updating Octane camera:" << std::endl;
    std::cout << "  Position: (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;
    std::cout << "  Forward:  (" << forward.x << ", " << forward.y << ", " << forward.z << ")" << std::endl;
    std::cout << "  Up:       (" << up.x << ", " << up.y << ", " << up.z << ")" << std::endl;
    
    if (m_cameraAvailable && m_cameraNode) {
        // Convert to Octane format and set transform
        OctaneVec::float4x4 octaneTransform = glmToOctane(worldMatrix);
        return setCameraTransform(m_cameraNode, octaneTransform);
    } else {
        // Simulation mode - just log the operation
        std::cout << "  [SIMULATION] Camera transform would be applied to Octane" << std::endl;
        return true;
    }
}

bool OctaneCameraSync::isCameraControlAvailable() const {
    return m_initialized && m_cameraAvailable;
}

bool OctaneCameraSync::getCameraPosition(glm::vec3& position) const {
    if (!m_initialized) {
        return false;
    }
    
    if (m_cameraAvailable && m_cameraNode) {
        // TODO: Implement actual SDK call to get camera position
        // For now, return cached position
        position = m_lastPosition;
        return true;
    } else {
        // Simulation mode
        position = m_lastPosition;
        return true;
    }
}

bool OctaneCameraSync::getCameraOrientation(glm::vec3& forward, glm::vec3& up) const {
    if (!m_initialized) {
        return false;
    }
    
    if (m_cameraAvailable && m_cameraNode) {
        // TODO: Implement actual SDK call to get camera orientation
        // For now, calculate from cached data
        forward = glm::normalize(m_lastTarget - m_lastPosition);
        up = m_lastUp;
        return true;
    } else {
        // Simulation mode
        forward = glm::normalize(m_lastTarget - m_lastPosition);
        up = m_lastUp;
        return true;
    }
}

OctaneVec::float3 OctaneCameraSync::glmToOctane(const glm::vec3& v) const {
    OctaneVec::float3 result;
    result.x = v.x;
    result.y = v.y;
    result.z = v.z;
    return result;
}

OctaneVec::float4x4 OctaneCameraSync::glmToOctane(const glm::mat4& m) const {
    OctaneVec::float4x4 result;
    
    // GLM uses column-major order, Octane Matrix stores rows
    // Convert from column-major to row-major
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 4; ++col) {
            result.m[row][col] = m[col][row];
        }
    }
    
    return result;
}

glm::vec3 OctaneCameraSync::octaneToGlm(const OctaneVec::float3& v) const {
    return glm::vec3(v.x, v.y, v.z);
}

Octane::ApiNode* OctaneCameraSync::getRenderCameraNode() {
#ifdef OCTANE_GRPC_ENABLED
    try {
        // Use the actual SDK call when gRPC is enabled
        std::cout << "  Calling Octane::ApiRenderEngine::getRenderCameraNode()" << std::endl;
        return Octane::ApiRenderEngine::getRenderCameraNode();
        
    } catch (const std::exception& e) {
        std::cerr << "Error getting render camera node: " << e.what() << std::endl;
        return nullptr;
    }
#else
    // Simulation mode when gRPC is disabled
    std::cout << "  [SIMULATION] Calling Octane::ApiRenderEngine::getRenderCameraNode()" << std::endl;
    std::cout << "  [SIMULATION] gRPC functionality disabled - returning nullptr" << std::endl;
    return nullptr;
#endif
}

bool OctaneCameraSync::setCameraTransform(Octane::ApiNode* node, const OctaneVec::float4x4& transform) {
    if (!node) {
        return false;
    }
    
    try {
#ifdef OCTANE_GRPC_ENABLED
        // Extract position and target from transform matrix
        // Position is the translation component (last column)
        OctaneVec::float3 position;
        position.x = transform.m[0][3];
        position.y = transform.m[1][3];
        position.z = transform.m[2][3];
        
        // Calculate target point by moving forward from camera position
        // Forward vector is -Z axis of the transform (negative third column)
        OctaneVec::float3 forward;
        forward.x = -transform.m[0][2];
        forward.y = -transform.m[1][2];
        forward.z = -transform.m[2][2];
        
        // Target is position + forward direction (at some distance)
        float targetDistance = 5.0f; // Default target distance
        OctaneVec::float3 target;
        target.x = position.x + forward.x * targetDistance;
        target.y = position.y + forward.y * targetDistance;
        target.z = position.z + forward.z * targetDistance;
        
        std::cout << "  Setting camera position: (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;
        std::cout << "  Setting camera target: (" << target.x << ", " << target.y << ", " << target.z << ")" << std::endl;
        
        // Set camera position and target using SDK calls
        node->setPinValue(Octane::P_POSITION, position, true);
        node->setPinValue(Octane::P_TARGET, target, true);
        
        return true;
#else
        // Simulation mode when gRPC is disabled
        std::cout << "  [SIMULATION] Setting camera transform matrix:" << std::endl;
        for (int row = 0; row < 3; ++row) {
            std::cout << "    [" << transform.m[row][0] << ", " 
                      << transform.m[row][1] << ", " 
                      << transform.m[row][2] << ", " 
                      << transform.m[row][3] << "]" << std::endl;
        }
        
        // Extract and display position and target for simulation
        OctaneVec::float3 position;
        position.x = transform.m[0][3];
        position.y = transform.m[1][3];
        position.z = transform.m[2][3];
        
        OctaneVec::float3 forward;
        forward.x = -transform.m[0][2];
        forward.y = -transform.m[1][2];
        forward.z = -transform.m[2][2];
        
        float targetDistance = 5.0f;
        OctaneVec::float3 target;
        target.x = position.x + forward.x * targetDistance;
        target.y = position.y + forward.y * targetDistance;
        target.z = position.z + forward.z * targetDistance;
        
        std::cout << "  [SIMULATION] Would set camera position: (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;
        std::cout << "  [SIMULATION] Would set camera target: (" << target.x << ", " << target.y << ", " << target.z << ")" << std::endl;
        
        return true;
#endif
        
    } catch (const std::exception& e) {
        std::cerr << "Error setting camera transform: " << e.what() << std::endl;
        return false;
    }
}