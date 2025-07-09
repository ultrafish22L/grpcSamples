#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <functional>

namespace SharedUtils {

/**
 * Camera parameters and controls
 */
struct Camera {
    float radius = 22.0f;
    float theta = 0.0f;  // horizontal angle
    float phi = 0.0f;    // vertical angle
    glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
    
    glm::vec3 getPosition() const {
        float x = radius * cos(phi) * cos(theta);
        float y = radius * sin(phi);
        float z = radius * cos(phi) * sin(theta);
        return center + glm::vec3(x, y, z);
    }
    
    glm::mat4 getViewMatrix() const {
        glm::vec3 position = getPosition();
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        return glm::lookAt(position, center, up);
    }
};

/**
 * Mouse state tracking
 */
struct MouseState {
    bool dragging = false;
    bool panning = false;  // Right mouse button for panning
    double lastX = 0.0;
    double lastY = 0.0;
};

/**
 * Keyboard state tracking for model loading
 */
struct KeyboardState {
    bool lKeyPressed = false;
    bool rKeyPressed = false;
};

/**
 * Camera and input controller
 */
class CameraController {
public:
    Camera camera;
    MouseState mouse;
    KeyboardState keyboard;
    
    // Callbacks for model loading
    std::function<void()> onLoadModel;
    std::function<void()> onResetModel;
    std::function<void(const glm::vec3&, const glm::vec3&, const glm::vec3&)> onCameraUpdate;
    
    /**
     * Initialize camera controller with GLFW window
     */
    void initialize(GLFWwindow* window);
    
    /**
     * Process keyboard input for model loading
     */
    void processInput(GLFWwindow* window);
    
    /**
     * Reset camera to default position
     */
    void resetCamera();

private:
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    
    void updateCamera();
};

// Global pointer for GLFW callbacks
static CameraController* g_cameraController = nullptr;

// Implementation
inline void CameraController::initialize(GLFWwindow* window) {
    g_cameraController = this;
    
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetScrollCallback(window, scrollCallback);
    
    // Set initial camera update
    updateCamera();
}

inline void CameraController::processInput(GLFWwindow* window) {
    // Handle file loading (L key)
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        if (!keyboard.lKeyPressed) {
            keyboard.lKeyPressed = true;
            if (onLoadModel) {
                onLoadModel();
            }
        }
    } else {
        keyboard.lKeyPressed = false;
    }
    
    // Handle reset to cube (R key)
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        if (!keyboard.rKeyPressed) {
            keyboard.rKeyPressed = true;
            if (onResetModel) {
                onResetModel();
            }
        }
    } else {
        keyboard.rKeyPressed = false;
    }
}

inline void CameraController::resetCamera() {
    camera.radius = 5.0f;
    camera.theta = 0.0f;
    camera.phi = 0.0f;
    camera.center = glm::vec3(0.0f, 0.0f, 0.0f);
    updateCamera();
}

inline void CameraController::updateCamera() {
    if (onCameraUpdate) {
        glm::vec3 position = camera.getPosition();
        onCameraUpdate(position, camera.center, glm::vec3(0.0f, 1.0f, 0.0f));
    }
}

inline void CameraController::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    (void)mods; // Suppress unused parameter warning
    if (!g_cameraController) return;
    
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            g_cameraController->mouse.dragging = true;
            glfwGetCursorPos(window, &g_cameraController->mouse.lastX, &g_cameraController->mouse.lastY);
        } else if (action == GLFW_RELEASE) {
            g_cameraController->mouse.dragging = false;
        }
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            g_cameraController->mouse.panning = true;
            glfwGetCursorPos(window, &g_cameraController->mouse.lastX, &g_cameraController->mouse.lastY);
        } else if (action == GLFW_RELEASE) {
            g_cameraController->mouse.panning = false;
        }
    }
}

inline void CameraController::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    (void)window; // Suppress unused parameter warning
    if (!g_cameraController) return;
    
    if (g_cameraController->mouse.dragging) {
        // Left mouse button: orbit camera
        double deltaX = xpos - g_cameraController->mouse.lastX;
        double deltaY = ypos - g_cameraController->mouse.lastY;
        
        // Sensitivity factor
        float sensitivity = 0.01f;
        
        // Update camera angles
        g_cameraController->camera.theta += deltaX * sensitivity;
        g_cameraController->camera.phi -= deltaY * sensitivity;
        
        // Clamp phi to prevent flipping
        g_cameraController->camera.phi = glm::clamp(g_cameraController->camera.phi, -1.5f, 1.5f);
        
        // Update camera
        g_cameraController->updateCamera();
        
        g_cameraController->mouse.lastX = xpos;
        g_cameraController->mouse.lastY = ypos;
    } else if (g_cameraController->mouse.panning) {
        // Right mouse button: pan camera center
        double deltaX = xpos - g_cameraController->mouse.lastX;
        double deltaY = ypos - g_cameraController->mouse.lastY;
        
        // Pan sensitivity (smaller for more precise control)
        float panSensitivity = 0.005f;
        
        // Get camera's right and up vectors for proper panning
        glm::vec3 position = g_cameraController->camera.getPosition();
        glm::vec3 forward = glm::normalize(g_cameraController->camera.center - position);
        glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));
        glm::vec3 up = glm::normalize(glm::cross(right, forward));
        
        // Apply panning to camera center
        g_cameraController->camera.center -= right * (float)deltaX * panSensitivity * g_cameraController->camera.radius;
        g_cameraController->camera.center += up * (float)deltaY * panSensitivity * g_cameraController->camera.radius;
        
        // Update camera
        g_cameraController->updateCamera();
        
        g_cameraController->mouse.lastX = xpos;
        g_cameraController->mouse.lastY = ypos;
    }
}

inline void CameraController::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    (void)window;  // Suppress unused parameter warning
    (void)xoffset; // Suppress unused parameter warning
    if (!g_cameraController) return;
    
    g_cameraController->camera.radius -= yoffset * 0.5f;
    g_cameraController->camera.radius = glm::clamp(g_cameraController->camera.radius, 1.0f, 20.0f);
    
    // Update camera
    g_cameraController->updateCamera();
}

} // namespace SharedUtils