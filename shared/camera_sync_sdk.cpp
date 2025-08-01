#include "camera_sync_sdk.h"
#include <iostream>
#include <cstring>

#ifdef DO_GRPC_SDK_ENABLED
#include "grpcsettings.h"
#include "apirenderengineclient.h"
#include "apiprojectmanagerclient.h"
#include "apirootnodegraphclient.h"
#include "apinodegraphclient.h"
#include "apinodeclient.h"
#include "apiitemarrayclient.h"
#include "apinodeinfoclient.h"
#include "octaneids.h"
#include "octanevectypes.h"
using namespace OctaneVec;
#endif
#define UPDATE_DELTA_POSITION .001f
#define UPDATE_DELTA_TARGET   .001f
#define UPDATE_DELTA_UP       .001f
#define UPDATE_DELTA_FOV      .01f

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
    std::cout << "CameraSyncSdk created" << std::endl;
}

CameraSyncSdk::~CameraSyncSdk() {
    shutdown();
    std::cout << "CameraSyncSdk destroyed" << std::endl;
}

bool CameraSyncSdk::connectToServer(const std::string& serverAddress) {
    if (m_connected) {
        return true;
    }
    
    m_serverAddress = serverAddress;
    std::cout << "Initializing Octane SDK connection..." << std::endl;
    
#ifdef DO_GRPC_SDK_ENABLED
    try {
        // Note: In a real implementation, ApiRenderEngine would be a singleton
        // or obtained through a factory method. For now, we'll assume it's already initialized.
//        m_renderEngine = new ApiRenderEngineProxy(); // Hypothetical singleton access
		GRPCSettings::getInstance().setServerAddress(serverAddress);
        
        std::cout << "Octane SDK connection established" << std::endl;
        m_connected = true;
        m_cameraAvailable = false;
        logSdkStatus("ConnectToServer", true);
        return true;
        
    } catch (const std::exception& e) {
        std::cout << "Exception during SDK connection: " << e.what() << std::endl;
        logSdkStatus("ConnectToServer", false);
        return false;
    }
#else
    // Simulation mode when SDK is not available
    std::cout << "Octane SDK not available - using simulation mode" << std::endl;
    std::cout << "Simulating connection to Octane at: " << serverAddress << std::endl;
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
        std::cout << "Cannot initialize: not connected to Octane" << std::endl;
        return;
    }
    
    std::cout << "Initializing camera control..." << std::endl;
    
#ifdef DO_GRPC_SDK_ENABLED
    try {
        // Get the current camera node from the render engine
        m_cameraNode = ::ApiRenderEngineProxy::getRenderCameraNode();
        
        if (!m_cameraNode.isNull()) {
            m_cameraAvailable = true;
            m_initialized = true;
            std::cout << "Camera control initialized successfully" << std::endl;
            logSdkStatus("Initialize", true);

            testConnection();
        } else {
            std::cout << "No camera node found in current render target" << std::endl;
            m_cameraAvailable = false;
            logSdkStatus("Initialize", false);
        }
        
    } catch (const std::exception& e) {
        std::cout << "Exception during camera initialization: " << e.what() << std::endl;
        m_cameraAvailable = false;
        logSdkStatus("Initialize", false);
    }
#else
    // Simulation mode
    m_cameraAvailable = true;
    m_initialized = true;
    std::cout << "Camera control initialized (simulation mode)" << std::endl;
    logSdkStatus("Initialize (Simulation)", true);
#endif
}
static char sIndent[129];
static const char* Indent(int i)
{
    int ii = i * 2;
    if (ii > 128)
        ii = 128;

    memset(sIndent, ' ', ii);
	sIndent[ii] = 0;
    return sIndent;
}

static bool recurseNodeTest(ApiItemProxy& item, int indent = 0)
{
    if (item.isNull())
    {
        std::cout << "recurseNodes: item == null" << std::endl;
        return false;
    }
    std::cout << Indent(indent) << "item.name = " << item.name() << std::endl;

    if (item.isGraph())
    {
        ApiItemArrayProxy items;
        item.toGraph().getOwnedItems(items);
        indent++;

        for (int i = 0; i < items.size(); i++)
        {
            auto item = items.get(i);

            if (item.isNull())
                continue;

            recurseNodeTest(item, indent + 2);
        }
        return true;
    }
    // node
	ApiNodeProxy& node = item.toNode();
	int pinCount = node.pinCount();
    for (int i = 0; i < pinCount; i++)
    {
        ApiNodeProxy n = node.connectedNodeIx(i, false);
        ApiNodePinInfoProxy info = node.info();

        if (n.isNull())
            continue;

        recurseNodeTest(n, indent + 2);
    }
    return true;
}

bool CameraSyncSdk::testConnection() {
    if (!m_initialized || m_cameraNode.isNull()) {
        return false;
    }
    std::cout << "octane camera.name = " << m_cameraNode.name() << std::endl;

    auto root = ApiProjectManagerProxy::rootNodeGraph();
    if (root.isNull())
    {
        std::cout << "ApiProjectManager::rootNodeGraph() == null" << std::endl;
        return false;
    }
    recurseNodeTest(root);

    return true;
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
        std::cout << "Shutting down Octane SDK connection..." << std::endl;
        
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
            std::cout << "Exception getting camera state: " << e.what() << std::endl;
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
    std::cout << "Module started with callback source: " << callbackSource << std::endl;
    m_moduleStarted = true;
}

void CameraSyncSdk::stop() {
    std::cout << "Module stopped" << std::endl;
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
        return false;
    }
    glm::vec3 d = pos - m_lastPosition;
    if (glm::length(d) < UPDATE_DELTA_POSITION) {
		// No significant change in position
        return false;
    }
#ifdef DO_GRPC_SDK_ENABLED
    try {
        // Set camera pos via SDK using pin values
        float_3 p = {pos.x, pos.y, pos.z};
        m_cameraNode.setPinValue(Octane::P_POSITION, p, true);
        
        logSdkStatus("SetCameraPosition", true);
        
    } catch (const std::exception& e) {
        std::cout << "Exception in setCameraPosition: " << e.what() << std::endl;
        logSdkStatus("SetCameraPosition", false);
        return false;
    }
#endif
    m_lastPosition = pos;
    return true;
}

bool CameraSyncSdk::setCameraTarget(const glm::vec3& target, bool evaluate) {
    if (!m_initialized) {
        m_lastTarget = target;
        return false;
    }
    glm::vec3 d = target - m_lastTarget;
    if (glm::length(d) < UPDATE_DELTA_TARGET) {
        // No significant change in target
        return false;
    }
#ifdef DO_GRPC_SDK_ENABLED
    try {
        // Set camera target via SDK using pin values
        float_3 tgt = {target.x, target.y, target.z};
        m_cameraNode.setPinValue(Octane::P_TARGET, tgt, evaluate);
        
        logSdkStatus("SetCameraTarget", true);
        
    } catch (const std::exception& e) {
        std::cout << "Exception in setCameraTarget: " << e.what() << std::endl;
        logSdkStatus("SetCameraTarget", false);
        return false;
    }
#endif
    m_lastTarget = target;
    return true;
}

bool CameraSyncSdk::setCameraUp(const glm::vec3& up, bool evaluate) {
    if (!m_initialized) {
        m_lastUp = up;
        return false;
    }
    glm::vec3 d = up - m_lastUp;
    if (glm::length(d) < UPDATE_DELTA_UP) {
        // No significant change in up
        return false;
    }
#ifdef DO_GRPC_SDK_ENABLED
    try {
        // Set camera up vector via SDK using pin values
        float_3 upVec = {up.x, up.y, up.z};
        m_cameraNode.setPinValue(Octane::P_UP, upVec, true);
        
        logSdkStatus("SetCameraUp", true);
        
    } catch (const std::exception& e) {
        std::cout << "Exception in setCameraUp: " << e.what() << std::endl;
        logSdkStatus("SetCameraUp", false);
        return false;
    }
#endif
    m_lastUp = up;
    return true;
}

bool CameraSyncSdk::setCameraFov(float fov, bool evaluate) {
    float d = fov - m_lastFov;
    
    if (d < UPDATE_DELTA_FOV) {
        // No significant change in fov
        return false;
    }
#ifdef DO_GRPC_SDK_ENABLED
    try {
        // Set camera FOV via SDK using pin values
        m_cameraNode.setPinValue(Octane::P_FOV, fov, true);
        
        logSdkStatus("SetCameraFov", true);
        
    } catch (const std::exception& e) {
        std::cout << "Exception in setCameraFov: " << e.what() << std::endl;
        logSdkStatus("SetCameraFov", false);
        return false;
    }
#endif
    m_lastFov = fov;
    return true;
}

// Helper functions

void CameraSyncSdk::logSdkStatus(const std::string& operation, bool success) {
    if (success) {
        std::cout << "" << operation << " - SUCCESS" << std::endl;
    } else {
        std::cout << "" << operation << " - FAILED" << std::endl;
    }
}
