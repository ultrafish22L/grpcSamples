#pragma once

#include "camera_system.h"

namespace SharedUtils {


// Global pointer for GLFW callbacks
CameraController* g_cameraController = nullptr;

// Implementation
void CameraController::initialize(GLFWwindow* window) {
    g_cameraController = this;
    
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetScrollCallback(window, scrollCallback);
    
    // Set initial camera update
    updateCamera();
}

void CameraController::processInput(GLFWwindow* window) {
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

void CameraController::resetCamera() {
    camera.radius = 5.0f;
    camera.theta = 0.0f;
    camera.phi = 0.0f;
    camera.center = glm::vec3(0.0f, 0.0f, 0.0f);
    updateCamera();
}

void CameraController::updateCamera() {
    if (onCameraUpdate) {
        glm::vec3 pos = camera.getPosition();
        onCameraUpdate(pos, camera.center, glm::vec3(0.0f, 1.0f, 0.0f));
    }
}

void CameraController::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
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

void CameraController::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
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
        glm::vec3 pos = g_cameraController->camera.getPosition();
        glm::vec3 forward = glm::normalize(g_cameraController->camera.center - pos);
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

void CameraController::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    (void)window;  // Suppress unused parameter warning
    (void)xoffset; // Suppress unused parameter warning
    if (!g_cameraController) return;
    
    g_cameraController->camera.radius -= yoffset * 0.5f;
    g_cameraController->camera.radius = glm::clamp(g_cameraController->camera.radius, .10f, 1000.0f);
    
    // Update camera
    g_cameraController->updateCamera();
}

} // namespace SharedUtils