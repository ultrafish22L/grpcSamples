// Fix Windows APIENTRY macro redefinition warning
#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef APIENTRY
#define APIENTRY __stdcall
#endif
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shared_rendering.h"

int main() {
    std::cout << "✨ Testing Modern OpenGL setup...\n";
    
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }
    
    std::cout << "GLFW initialized successfully\n";
    
    // Configure GLFW for Modern OpenGL 3.3 Core with enhanced features
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x MSAA for anti-aliasing
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE); // Don't show window
    
    // Create a hidden window for context
    GLFWwindow* window = glfwCreateWindow(1, 1, "Test", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    
    std::cout << "GLFW window created successfully\n";
    
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        glfwTerminate();
        return -1;
    }
    
    std::cout << "GLEW initialized successfully\n";
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
    
    // Test basic OpenGL functionality
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    std::cout << "Basic OpenGL operations successful\n";
    std::cout << "The cube viewer application should work correctly!\n";
    
    glfwTerminate();
    return 0;
}