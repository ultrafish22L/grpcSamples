#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#include "../shared_rendering.h"

// Modern 3D Cube Viewer with enhanced graphics

// Window dimensions
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;

// Camera parameters
struct Camera {
    float radius = 5.0f;
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

// Mouse state
struct MouseState {
    bool dragging = false;
    double lastX = 0.0;
    double lastY = 0.0;
};

Camera camera;
MouseState mouse;
ModernRendering::ModernRenderer renderer;

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    (void)mods; // Suppress unused parameter warning
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            mouse.dragging = true;
            glfwGetCursorPos(window, &mouse.lastX, &mouse.lastY);
        } else if (action == GLFW_RELEASE) {
            mouse.dragging = false;
        }
    }
}

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    (void)window; // Suppress unused parameter warning
    if (mouse.dragging) {
        double deltaX = xpos - mouse.lastX;
        double deltaY = ypos - mouse.lastY;
        
        // Sensitivity factor
        float sensitivity = 0.01f;
        
        // Update camera angles
        camera.theta += deltaX * sensitivity;
        camera.phi -= deltaY * sensitivity;
        
        // Clamp phi to prevent flipping
        camera.phi = glm::clamp(camera.phi, -1.5f, 1.5f);
        
        // Camera updated (no external sync needed)
        
        mouse.lastX = xpos;
        mouse.lastY = ypos;
    }
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    (void)window;  // Suppress unused parameter warning
    (void)xoffset; // Suppress unused parameter warning
    camera.radius -= yoffset * 0.5f;
    camera.radius = glm::clamp(camera.radius, 1.0f, 20.0f);
    
    // Camera zoom updated (no external sync needed)
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    (void)window; // Suppress unused parameter warning
    glViewport(0, 0, width, height);
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    // Configure GLFW with modern settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x MSAA for anti-aliasing
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
    
    // Create window with modern styling
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "✨ Shiny 3D Cube Viewer - Modern Edition", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    
    // Set callbacks
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetScrollCallback(window, scrollCallback);
    
    // Enable depth testing and other modern OpenGL features
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE); // Anti-aliasing
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Initialize modern renderer
    renderer.initialize();
    
    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        // Process input
        glfwPollEvents();
        
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
        
        // Clear screen with a subtle dark color
        glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        float currentTime = (float)glfwGetTime();
        
        // Create transformation matrices
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 
                                               (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 
                                               0.1f, 100.0f);
        glm::vec3 viewPos = camera.getPosition();
        
        // Render using modern renderer
        renderer.render(view, projection, viewPos, currentTime);
        
        // Swap buffers
        glfwSwapBuffers(window);
    }
    
    // Cleanup
    renderer.cleanup();
    
    glfwTerminate();
    return 0;
}