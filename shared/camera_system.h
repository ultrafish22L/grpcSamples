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
        glm::vec3 pos = getPosition();
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        return glm::lookAt(pos, center, up);
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
     * Reset camera to default pos
     */
    void resetCamera();

private:
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    
    void updateCamera();
};

// Global pointer for GLFW callbacks
extern CameraController* g_cameraController;


} // namespace SharedUtils