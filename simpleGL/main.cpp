#ifdef _WIN32
#include <windows.h>  // Include Windows headers first to define LONGLONG
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>

#include "shared_rendering.h"
#include "camera_system.h"
#include "model_manager.h"

// Modern 3D Cube Viewer with enhanced graphics

// Window dimensions
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;

// Global objects using shared systems
SharedUtils::CameraController cameraController;
SharedUtils::ModelManager modelManager;
SharedUtils::RendererGl renderer;
GLFWwindow* g_window = nullptr;

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
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "✨ 3D Model Viewer - cube (Default Cube)", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    g_window = window;
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    
    // Set callbacks
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    
    // Enable depth testing and other modern OpenGL features
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE); // Anti-aliasing
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Initialize systems
    renderer.initialize();
    modelManager.initialize(&renderer);
    cameraController.initialize(window);
    
    // Set up model manager callbacks
    cameraController.onLoadModel = [&]() {
        modelManager.loadModelFromDialog();
        modelManager.updateWindowTitle(window, "3D Model Viewer");
    };
    
    cameraController.onResetModel = [&]() {
        modelManager.resetToDefaultCube();
        modelManager.updateWindowTitle(window, "3D Model Viewer");
    };
    
    // Set initial window title
    modelManager.updateWindowTitle(window, "3D Model Viewer");
    
    // Print controls
    std::cout << "\n=== 3D Model Viewer Controls ===" << std::endl;
    std::cout << "Mouse: Drag to orbit camera" << std::endl;
    std::cout << "Mouse Wheel: Zoom in/out" << std::endl;
    std::cout << "L: Load 3D model file" << std::endl;
    std::cout << "R: Reset to default cube" << std::endl;
    std::cout << "ESC: Exit" << std::endl;
    std::cout << "================================\n" << std::endl;
    
    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        // Process input
        glfwPollEvents();
        
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
        
        // Process camera and model input
        cameraController.processInput(window);
        
        // Clear screen with a subtle dark color
        glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        float currentTime = (float)glfwGetTime();
        
        // Create transformation matrices using shared camera
        glm::mat4 view = cameraController.camera.getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 
                                               (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 
                                               0.1f, 100.0f);
        glm::vec3 viewPos = cameraController.camera.getPosition();
        
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