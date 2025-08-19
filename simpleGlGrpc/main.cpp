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
#include "../shared/camera_system.h"
#include "../shared/model_manager.h"

// Direct gRPC integration (instead of SDK proxy)
#include "camera_sync_direct.h"
#include "camera_sync_livelink.h"

// Window dimensions
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;

// Global objects using shared systems
SharedUtils::CameraController cameraController;
SharedUtils::ModelManager modelManager;
//CameraSyncDirect cameraSync;
CameraSyncLiveLink cameraSync;
SharedUtils::RendererGl renderer;

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
    
    // Create window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "🚀 Shiny 3D Cube Viewer - gRPC Edition", NULL, NULL);
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
        modelManager.updateWindowTitle(window, "3D Model Viewer - gRPC Edition");
    };
    
    cameraController.onResetModel = [&]() {
        modelManager.resetToDefaultCube();
        modelManager.updateWindowTitle(window, "3D Model Viewer - gRPC Edition");
    };
    
    // Set up gRPC camera sync callback
    cameraController.onCameraUpdate = [&](const glm::vec3& position, const glm::vec3& center, const glm::vec3& up) {
        cameraSync.setCamera(position, center, up);
    };
    
    // Set initial camera position in Octane
    glm::vec3 initialPosition = cameraController.camera.getPosition();
    cameraSync.setCamera(initialPosition, cameraController.camera.center, glm::vec3(0.0f, 1.0f, 0.0f));
    
    // Set initial window title
    modelManager.updateWindowTitle(window, "3D Model Viewer - gRPC Edition");
    
    // Print controls
    std::cout << "\n=== 3D Model Viewer - gRPC Edition Controls ===" << std::endl;
    std::cout << "Mouse: Drag to orbit camera (syncs with Octane)" << std::endl;
    std::cout << "Mouse Wheel: Zoom in/out (syncs with Octane)" << std::endl;
    std::cout << "L: Load 3D model file" << std::endl;
    std::cout << "R: Reset to default cube" << std::endl;
    std::cout << "ESC: Exit" << std::endl;
    std::cout << "===============================================\n" << std::endl;
    
    // Main render loop
    while (!glfwWindowShouldClose(window)) 
    {
        // Connect to Octane server and initialize camera sync
        if (!cameraSync.connectToServer("127.0.0.1:51022")) 
        {
//            std::cerr << "Warning: Failed to connect to Octane server" << std::endl;
        }
        cameraSync.initialize();

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
        
        cameraSync.setCamera(viewPos, cameraController.camera.center, glm::vec3(0.0f, 1.0f, 0.0f));

        // Render using modern renderer
        renderer.renderCube(view, projection, viewPos, currentTime);
        
        // Swap buffers
        glfwSwapBuffers(window);
    }
    
    // Cleanup
    renderer.cleanup();
    
    glfwTerminate();
    return 0;
}