#include "camera_sync_sdk.h"
#include <iostream>
#include <cstring>

#ifdef DO_GRPC_SDK_ENABLED
#include "apirender.h"
#include "apinodesystem.h"
#include "octaneids.h"
#include "octanevectypes.h"
using namespace OctaneVec;
#endif

CameraSyncSdk::CameraSyncSdk()
    : m_initialized(false)
    , m_connected(false)
    , m_cameraAvailable(false)
    , m_lastPosition(0.0f, 0.0f, 5.0f)
    , m_lastTarget(0.0f, 0.0f, 0.0f)
    , m_lastUp(0.0f, 1.0f, 0.0f)
    , m_lastFov(45.0f)
    , m_moduleReady(true)
    , m_moduleStarted(false)
{
    std::cout << "[SDK] CameraSyncSdk created" << std::endl;
}

CameraSyncSdk::~CameraSyncSdk() {
    shutdown();
    std::cout << "[SDK] CameraSyncSdk destroyed" << std::endl;
}

bool CameraSyncSdk::connectToServer(const std::string& serverAddress) {
    if (m_connected) {
        return true;
    }
    
    m_serverAddress = serverAddress;
    std::cout << "[SDK] Initializing Octane SDK connection..." << std::endl;
    
#ifdef DO_GRPC_SDK_ENABLED
    try {
        // Note: In a real implementation, ApiRenderEngine would be a singleton
        // or obtained through a factory method. For now, we'll assume it's already initialized.
        // m_renderEngine = ApiRenderEngine::getInstance(); // Hypothetical singleton access
        
        std::cout << "[SDK] Octane SDK connection established" << std::endl;
        m_connected = true;
        m_cameraAvailable = false;
        logSdkStatus("ConnectToServer", true);
        return true;
        
    } catch (const std::exception& e) {
        std::cout << "[SDK] Exception during SDK connection: " << e.what() << std::endl;
        logSdkStatus("ConnectToServer", false);
        return false;
    }
#else
    // Simulation mode when SDK is not available
    std::cout << "[SDK] Octane SDK not available - using simulation mode" << std::endl;
    std::cout << "[SDK] Simulating connection to Octane at: " << serverAddress << std::endl;
    m_connected = true;
    m_cameraAvailable = true;
    logSdkStatus("ConnectToServer (Simulation)", true);
    return true;
#endif
}

void CameraSyncSdk::initialize() {
    if (m_initialized) {
        return;
    }
    
    if (!m_connected) {
        std::cout << "[SDK] Cannot initialize: not connected to Octane" << std::endl;
        return;
    }
    
    std::cout << "[SDK] Initializing camera control..." << std::endl;
    
#ifdef DO_GRPC_SDK_ENABLED
    try {
        // Get the current camera node from the render engine
        m_cameraNode = ::ApiRenderEngineProxy::getRenderCameraNode();
        
        if (!m_cameraNode.isNull()) {
            m_cameraAvailable = true;
            m_initialized = true;
            std::cout << "[SDK] Camera control initialized successfully" << std::endl;
            logSdkStatus("Initialize", true);
        } else {
            std::cout << "[SDK] No camera node found in current render target" << std::endl;
            m_cameraAvailable = false;
            logSdkStatus("Initialize", false);
        }
        
    } catch (const std::exception& e) {
        std::cout << "[SDK] Exception during camera initialization: " << e.what() << std::endl;
        m_cameraAvailable = false;
        logSdkStatus("Initialize", false);
    }
#else
    // Simulation mode
    m_cameraAvailable = true;
    m_initialized = true;
    std::cout << "[SDK] Camera control initialized (simulation mode)" << std::endl;
    logSdkStatus("Initialize (Simulation)", true);
#endif
}

bool CameraSyncSdk::updateCameraFromViewMatrix(const glm::mat4& viewMatrix) {
    if (!m_initialized) {
        return false;
    }
    
    // Extract camera pos, target, and up vector from view matrix
    glm::mat4 cameraTransform = glm::inverse(viewMatrix);
    
    // Extract pos from the 4th column
    glm::vec3 pos = glm::vec3(cameraTransform[3]);
    
    // Extract forward direction (negative Z axis in camera space)
    glm::vec3 forward = -glm::vec3(cameraTransform[2]);
    
    // Extract up direction (Y axis in camera space)
    glm::vec3 up = glm::vec3(cameraTransform[1]);
    
    // Calculate target point (pos + forward direction)
    glm::vec3 target = pos + forward;
    
    return setCamera(pos, target, up);
}

bool CameraSyncSdk::isCameraControlAvailable() const {
    return m_initialized && m_cameraAvailable;
}

void CameraSyncSdk::shutdown() {
    if (m_connected) {
        std::cout << "[SDK] Shutting down Octane SDK connection..." << std::endl;
        
        m_connected = false;
        m_initialized = false;
        m_cameraAvailable = false;
        
        logSdkStatus("Shutdown", true);
    }
}

void CameraSyncSdk::getCurrentCameraState(glm::vec3& pos, glm::vec3& target, glm::vec3& up) const {
#ifdef DO_GRPC_SDK_ENABLED
    if (m_cameraAvailable && !m_cameraNode.isNull()) {
        try {
            // Get current camera state from SDK using pin values
            float_3 p, t, u;
            m_cameraNode.getPinValue(Octane::P_POSITION, p);
            m_cameraNode.getPinValue(Octane::P_TARGET, t);
            m_cameraNode.getPinValue(Octane::P_UP, u);
            
            pos = glm::vec3(p.x, p.y, p.z);
            target = glm::vec3(t.x, t.y, t.z);
            up = glm::vec3(u.x, u.y, u.z);
            
        } catch (const std::exception& e) {
            std::cout << "[SDK] Exception getting camera state: " << e.what() << std::endl;
            pos = m_lastPosition;
            target = m_lastTarget;
            up = m_lastUp;
        }
    } else {
        pos = m_lastPosition;
        target = m_lastTarget;
        up = m_lastUp;
    }
#else
    // Simulation mode - return cached values
    pos = m_lastPosition;
    target = m_lastTarget;
    up = m_lastUp;
#endif
}

// Module interface implementation
void CameraSyncSdk::start(const std::string& callbackSource, const bool displayEnglish, const int secondLanguage) {
    std::cout << "[SDK] Module started with callback source: " << callbackSource << std::endl;
    m_moduleStarted = true;
}

void CameraSyncSdk::stop() {
    std::cout << "[SDK] Module stopped" << std::endl;
    m_moduleStarted = false;
}

bool CameraSyncSdk::isReady() {
    return m_moduleReady;
}

// CameraSyncBase interface implementation
void CameraSyncSdk::disconnect() {
    shutdown();
}

bool CameraSyncSdk::isConnected() const {
    return m_connected;
}

bool CameraSyncSdk::setCamera(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up, float fov, bool evaluate)
{
    bool result = true;
    result &= setCameraPosition(pos, false);
    result &= setCameraTarget(target, false);
    result &= setCameraUp(up, false);

    if (result && fov > 0.0f) {
        setCameraFov(fov);
    }
    if (!evaluate)
    {
#ifdef DO_GRPC_SDK_ENABLED
        m_cameraNode.evaluate();
#endif
    }
    return result;
}

bool CameraSyncSdk::getCamera(glm::vec3& pos, glm::vec3& target, glm::vec3& up, float& fov) {
    if (!m_initialized) {
        pos = m_lastPosition;
        target = m_lastTarget;
        up = m_lastUp;
        fov = m_lastFov;
        return false;
    }

    getCurrentCameraState(pos, target, up);
    fov = m_lastFov;
    return true;
}

bool CameraSyncSdk::setCameraPosition(const glm::vec3& pos, bool evaluate) {
    if (!m_initialized) {
        m_lastPosition = pos;
        return false;
    }

#ifdef DO_GRPC_SDK_ENABLED
    try {
        // Set camera pos via SDK using pin values
        float_3 p = {pos.x, pos.y, pos.z};
        m_cameraNode.setPinValue(Octane::P_POSITION, p, true);
        
        m_lastPosition = pos;
        logSdkStatus("SetCameraPosition", true);
        return true;
        
    } catch (const std::exception& e) {
        std::cout << "[SDK] Exception in setCameraPosition: " << e.what() << std::endl;
        logSdkStatus("SetCameraPosition", false);
        return false;
    }
#else
    // Simulation mode
    m_lastPosition = pos;
    std::cout << "[SDK] Simulation: Camera pos set to (" << pos.x << "," << pos.y << "," << pos.z << ")" << std::endl;
    logSdkStatus("SetCameraPosition (Simulation)", true);
    return true;
#endif
}

bool CameraSyncSdk::setCameraTarget(const glm::vec3& target, bool evaluate) {
    if (!m_initialized) {
        m_lastTarget = target;
        return false;
    }

#ifdef DO_GRPC_SDK_ENABLED
    try {
        // Set camera target via SDK using pin values
        float_3 tgt = {target.x, target.y, target.z};
        m_cameraNode.setPinValue(Octane::P_TARGET, tgt, evaluate);
        
        m_lastTarget = target;
        logSdkStatus("SetCameraTarget", true);
        return true;
        
    } catch (const std::exception& e) {
        std::cout << "[SDK] Exception in setCameraTarget: " << e.what() << std::endl;
        logSdkStatus("SetCameraTarget", false);
        return false;
    }
#else
    // Simulation mode
    m_lastTarget = target;
    std::cout << "[SDK] Simulation: Camera target set to (" << target.x << "," << target.y << "," << target.z << ")" << std::endl;
    logSdkStatus("SetCameraTarget (Simulation)", true);
    return true;
#endif
}

bool CameraSyncSdk::setCameraUp(const glm::vec3& up, bool evaluate) {
    if (!m_initialized) {
        m_lastUp = up;
        return false;
    }

#ifdef DO_GRPC_SDK_ENABLED
    try {
        // Set camera up vector via SDK using pin values
        float_3 upVec = {up.x, up.y, up.z};
        m_cameraNode.setPinValue(Octane::P_UP, upVec, true);
        
        m_lastUp = up;
        logSdkStatus("SetCameraUp", true);
        return true;
        
    } catch (const std::exception& e) {
        std::cout << "[SDK] Exception in setCameraUp: " << e.what() << std::endl;
        logSdkStatus("SetCameraUp", false);
        return false;
    }
#else
    // Simulation mode
    m_lastUp = up;
    std::cout << "[SDK] Simulation: Camera up vector set to (" << up.x << "," << up.y << "," << up.z << ")" << std::endl;
    logSdkStatus("SetCameraUp (Simulation)", true);
    return true;
#endif
}

bool CameraSyncSdk::setCameraFov(float fov, bool evaluate) {
#ifdef DO_GRPC_SDK_ENABLED
    try {
        // Set camera FOV via SDK using pin values
        m_cameraNode.setPinValue(Octane::P_FOV, fov, true);
        
        m_lastFov = fov;
        logSdkStatus("SetCameraFov", true);
        return true;
        
    } catch (const std::exception& e) {
        std::cout << "[SDK] Exception in setCameraFov: " << e.what() << std::endl;
        logSdkStatus("SetCameraFov", false);
        return false;
    }
#else
    // Simulation mode
    m_lastFov = fov;
    std::cout << "[SDK] Simulation: Camera FOV set to " << fov << " degrees" << std::endl;
    logSdkStatus("SetCameraFov (Simulation)", true);
    return true;
#endif
}

// Helper functions

void CameraSyncSdk::logSdkStatus(const std::string& operation, bool success) {
    if (success) {
        std::cout << "[SDK] " << operation << " - SUCCESS" << std::endl;
    } else {
        std::cout << "[SDK] " << operation << " - FAILED" << std::endl;
    }
}
