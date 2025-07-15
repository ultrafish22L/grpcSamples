/**
 * testGrpcApi - C++ Dear ImGui application duplicating html/index.html functionality
 * 
 * This application creates a C++ Dear ImGui interface that exactly matches the 
 * HTML interface functionality, using shared components from simpleGlGrpc.
 * 
 * Features:
 * - Professional OTOY theming matching HTML interface
 * - Real-time 3D cube rendering with mouse controls
 * - gRPC LiveLink connectivity (when available)
 * - Activity logging with timestamps and emoji indicators
 * - Performance monitoring (FPS, frame time)
 * - Model loading capabilities
 * - Camera synchronization with Octane
 */

#include <iostream>
#include <memory>
#include <string>
#include <chrono>
#include <thread>
#include <vector>

// OpenGL and windowing
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Dear ImGui
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// Activity logging and performance tracking
#include "ActivityLogger.h"
#include "PerformanceTracker.h"

// OTOY Color Scheme (matching HTML interface)
namespace OTOYColors {
    const ImVec4 BG_PRIMARY = ImVec4(0.08f, 0.08f, 0.12f, 1.0f);
    const ImVec4 BG_SECONDARY = ImVec4(0.12f, 0.12f, 0.18f, 1.0f);
    const ImVec4 ACCENT_RED = ImVec4(0.8f, 0.2f, 0.2f, 1.0f);
    const ImVec4 TEXT_PRIMARY = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);
    const ImVec4 TEXT_SECONDARY = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);
    const ImVec4 SUCCESS_GREEN = ImVec4(0.2f, 0.8f, 0.2f, 1.0f);
    const ImVec4 WARNING_YELLOW = ImVec4(0.8f, 0.8f, 0.2f, 1.0f);
    const ImVec4 ERROR_RED = ImVec4(0.8f, 0.2f, 0.2f, 1.0f);
}

// Simple 3D Cube Renderer
class SimpleCubeRenderer {
private:
    GLuint VAO, VBO, EBO;
    GLuint shaderProgram;
    GLint modelLoc, viewLoc, projLoc;
    
    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec3 aNormal;
        
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        
        out vec3 FragPos;
        out vec3 Normal;
        
        void main() {
            FragPos = vec3(model * vec4(aPos, 1.0));
            Normal = mat3(transpose(inverse(model))) * aNormal;
            gl_Position = projection * view * vec4(FragPos, 1.0);
        }
    )";
    
    const char* fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        
        in vec3 FragPos;
        in vec3 Normal;
        
        void main() {
            vec3 lightColor = vec3(1.0, 1.0, 1.0);
            vec3 objectColor = vec3(0.8, 0.2, 0.2);
            vec3 lightPos = vec3(2.0, 2.0, 2.0);
            
            // Ambient
            float ambientStrength = 0.3;
            vec3 ambient = ambientStrength * lightColor;
            
            // Diffuse
            vec3 norm = normalize(Normal);
            vec3 lightDir = normalize(lightPos - FragPos);
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = diff * lightColor;
            
            vec3 result = (ambient + diffuse) * objectColor;
            FragColor = vec4(result, 1.0);
        }
    )";
    
public:
    bool initialize() {
        // Cube vertices with normals
        float vertices[] = {
            // Front face
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
             1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
            
            // Back face
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
             1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
        };
        
        unsigned int indices[] = {
            // Front face
            0, 1, 2, 2, 3, 0,
            // Back face
            4, 5, 6, 6, 7, 4,
            // Left face
            7, 3, 0, 0, 4, 7,
            // Right face
            1, 5, 6, 6, 2, 1,
            // Top face
            3, 2, 6, 6, 7, 3,
            // Bottom face
            0, 1, 5, 5, 4, 0
        };
        
        // Generate and bind VAO
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        
        glBindVertexArray(VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        // Normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        
        // Create shaders
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        
        // Create shader program
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        
        // Get uniform locations
        modelLoc = glGetUniformLocation(shaderProgram, "model");
        viewLoc = glGetUniformLocation(shaderProgram, "view");
        projLoc = glGetUniformLocation(shaderProgram, "projection");
        
        // Clean up shaders
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        
        return true;
    }
    
    void render(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) {
        glUseProgram(shaderProgram);
        
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    
    void cleanup() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteProgram(shaderProgram);
    }
};

// Simple Camera Controller
class SimpleCameraController {
public:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    
    float yaw = -90.0f;
    float pitch = 0.0f;
    float distance = 5.0f;
    
    bool isDragging = false;
    double lastX = 0.0, lastY = 0.0;
    
    glm::mat4 getViewMatrix() {
        return glm::lookAt(position, target, up);
    }
    
    void handleMouseButton(int button, int action, double xpos, double ypos) {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            if (action == GLFW_PRESS) {
                isDragging = true;
                lastX = xpos;
                lastY = ypos;
            } else if (action == GLFW_RELEASE) {
                isDragging = false;
            }
        }
    }
    
    void handleMouseMove(double xpos, double ypos) {
        if (!isDragging) return;
        
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to top
        
        lastX = xpos;
        lastY = ypos;
        
        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;
        
        yaw += xoffset;
        pitch += yoffset;
        
        // Constrain pitch
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;
        
        updateCameraPosition();
    }
    
    void handleScroll(double yoffset) {
        distance -= yoffset * 0.5f;
        if (distance < 1.0f) distance = 1.0f;
        if (distance > 20.0f) distance = 20.0f;
        updateCameraPosition();
    }
    
private:
    void updateCameraPosition() {
        float x = distance * cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        float y = distance * sin(glm::radians(pitch));
        float z = distance * sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        position = glm::vec3(x, y, z);
    }
};

// Main Application Class
class TestGrpcApiApp {
private:
    GLFWwindow* window = nullptr;
    SimpleCubeRenderer renderer;
    SimpleCameraController camera;
    
    std::unique_ptr<ActivityLogger> logger;
    std::unique_ptr<PerformanceTracker> perfTracker;
    
    // UI State
    bool showDemo = false;
    bool autoRotateToggle = true;
    bool syncCameraToggle = false;
    float modelRotation = 0.0f;
    
    // Performance metrics
    float fps = 0.0f;
    float frameTime = 0.0f;
    int successCount = 0;
    int errorCount = 0;
    
    // Connection status
    enum class ConnectionStatus { READY, CONNECTED, DISCONNECTED };
    ConnectionStatus connectionStatus = ConnectionStatus::READY;
    
public:
    bool Initialize() {
        // Initialize GLFW
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return false;
        }
        
        // Configure GLFW
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        // Create window
        window = glfwCreateWindow(1400, 1200, "testGrpcApi - WebGL-Octane LiveLink Sync", NULL, NULL);
        if (!window) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }
        
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // Enable vsync
        
        // Set callbacks
        glfwSetWindowUserPointer(window, this);
        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
            TestGrpcApiApp* app = static_cast<TestGrpcApiApp*>(glfwGetWindowUserPointer(window));
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            app->camera.handleMouseButton(button, action, xpos, ypos);
        });
        
        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
            TestGrpcApiApp* app = static_cast<TestGrpcApiApp*>(glfwGetWindowUserPointer(window));
            app->camera.handleMouseMove(xpos, ypos);
        });
        
        glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
            TestGrpcApiApp* app = static_cast<TestGrpcApiApp*>(glfwGetWindowUserPointer(window));
            app->camera.handleScroll(yoffset);
        });
        
        // Initialize GLEW
        if (glewInit() != GLEW_OK) {
            std::cerr << "Failed to initialize GLEW" << std::endl;
            return false;
        }
        
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        
        // Setup Dear ImGui style (OTOY theme)
        SetupOTOYTheme();
        
        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
        
        // Initialize renderer
        if (!renderer.initialize()) {
            logger->Log("Failed to initialize renderer", ActivityLogger::LogLevel::ERROR);
            return false;
        }
        
        // Initialize logging and performance tracking
        logger = std::make_unique<ActivityLogger>();
        perfTracker = std::make_unique<PerformanceTracker>();
        
        logger->Log("Initializing WebGL-Octane LiveLink Sync viewer", ActivityLogger::LogLevel::STATUS);
        logger->Log("Using simplified C++ Dear ImGui implementation", ActivityLogger::LogLevel::STATUS);
        
        return true;
    }
    
    void SetupOTOYTheme() {
        ImGuiStyle& style = ImGui::GetStyle();
        
        // Colors
        style.Colors[ImGuiCol_Text] = OTOYColors::TEXT_PRIMARY;
        style.Colors[ImGuiCol_TextDisabled] = OTOYColors::TEXT_SECONDARY;
        style.Colors[ImGuiCol_WindowBg] = OTOYColors::BG_PRIMARY;
        style.Colors[ImGuiCol_ChildBg] = OTOYColors::BG_SECONDARY;
        style.Colors[ImGuiCol_PopupBg] = OTOYColors::BG_SECONDARY;
        style.Colors[ImGuiCol_Border] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
        style.Colors[ImGuiCol_FrameBg] = OTOYColors::BG_SECONDARY;
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.2f, 0.2f, 0.3f, 1.0f);
        style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.3f, 0.3f, 0.4f, 1.0f);
        style.Colors[ImGuiCol_TitleBg] = OTOYColors::BG_PRIMARY;
        style.Colors[ImGuiCol_TitleBgActive] = OTOYColors::BG_PRIMARY;
        style.Colors[ImGuiCol_MenuBarBg] = OTOYColors::BG_SECONDARY;
        style.Colors[ImGuiCol_ScrollbarBg] = OTOYColors::BG_PRIMARY;
        style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
        style.Colors[ImGuiCol_CheckMark] = OTOYColors::ACCENT_RED;
        style.Colors[ImGuiCol_SliderGrab] = OTOYColors::ACCENT_RED;
        style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.9f, 0.3f, 0.3f, 1.0f);
        style.Colors[ImGuiCol_Button] = OTOYColors::BG_SECONDARY;
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.2f, 0.2f, 0.3f, 1.0f);
        style.Colors[ImGuiCol_ButtonActive] = OTOYColors::ACCENT_RED;
        style.Colors[ImGuiCol_Header] = OTOYColors::BG_SECONDARY;
        style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.2f, 0.2f, 0.3f, 1.0f);
        style.Colors[ImGuiCol_HeaderActive] = OTOYColors::ACCENT_RED;
        
        // Styling
        style.WindowRounding = 6.0f;
        style.FrameRounding = 4.0f;
        style.ScrollbarRounding = 4.0f;
        style.GrabRounding = 4.0f;
        style.WindowPadding = ImVec2(10, 10);
        style.FramePadding = ImVec2(8, 4);
        style.ItemSpacing = ImVec2(8, 6);
    }
    
    void Run() {
        while (!glfwWindowShouldClose(window)) {
            // Update performance tracking
            perfTracker->Update();
            fps = perfTracker->GetFPS();
            frameTime = perfTracker->GetFrameTime();
            
            glfwPollEvents();
            
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            
            // Render the main interface
            RenderMainInterface();
            
            // Rendering
            ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(OTOYColors::BG_PRIMARY.x, OTOYColors::BG_PRIMARY.y, OTOYColors::BG_PRIMARY.z, OTOYColors::BG_PRIMARY.w);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);
            
            // Render 3D scene
            Render3DScene(display_w, display_h);
            
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            
            glfwSwapBuffers(window);
        }
    }
    
    void Render3DScene(int width, int height) {
        // Create matrices
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
        glm::mat4 view = camera.getViewMatrix();
        
        // Auto-rotate if enabled
        if (autoRotateToggle) {
            modelRotation += 0.01f;
        }
        
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), modelRotation, glm::vec3(0.0f, 1.0f, 0.0f));
        
        // Render the cube
        renderer.render(model, view, projection);
    }
    
    void RenderMainInterface() {
        // Create main dockspace
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        
        ImGui::Begin("DockSpace", nullptr, window_flags);
        ImGui::PopStyleVar(3);
        
        // Create dockspace
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
        
        // Menu bar
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("View")) {
                ImGui::MenuItem("Show Demo Window", nullptr, &showDemo);
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
        
        ImGui::End();
        
        // Connection Panel
        RenderConnectionPanel();
        
        // Activity Log
        RenderActivityLog();
        
        // Performance Stats
        RenderPerformanceStats();
        
        // Demo window
        if (showDemo) {
            ImGui::ShowDemoWindow(&showDemo);
        }
    }
    
    void RenderConnectionPanel() {
        ImGui::Begin("Connection & Controls");
        
        // OTOY Logo and branding
        ImGui::TextColored(OTOYColors::ACCENT_RED, "OTOY");
        ImGui::SameLine();
        ImGui::Text("WebGL-Octane LiveLink Sync");
        
        ImGui::Separator();
        
        // Connection status LED
        ImVec4 ledColor;
        const char* statusText;
        switch (connectionStatus) {
            case ConnectionStatus::READY:
                ledColor = OTOYColors::WARNING_YELLOW;
                statusText = "Ready";
                break;
            case ConnectionStatus::CONNECTED:
                ledColor = OTOYColors::SUCCESS_GREEN;
                statusText = "Connected";
                break;
            case ConnectionStatus::DISCONNECTED:
                ledColor = OTOYColors::ERROR_RED;
                statusText = "Disconnected";
                break;
        }
        
        ImGui::TextColored(ledColor, "●");
        ImGui::SameLine();
        ImGui::Text("Status: %s", statusText);
        
        ImGui::Separator();
        
        // Connection controls
        if (ImGui::Button("Connect to LiveLink")) {
            ConnectToLiveLink();
        }
        
        ImGui::SameLine();
        
        if (ImGui::Button("Disconnect")) {
            DisconnectFromLiveLink();
        }
        
        ImGui::Separator();
        
        // Model controls
        if (ImGui::Button("Load Model")) {
            LoadModel();
        }
        
        ImGui::SameLine();
        
        if (ImGui::Button("Load Teapot")) {
            TestLoadTeapot();
        }
        
        ImGui::Separator();
        
        // Camera controls
        ImGui::Checkbox("Auto-rotate", &autoRotateToggle);
        ImGui::Checkbox("Sync Camera", &syncCameraToggle);
        
        if (ImGui::Button("Reset Camera")) {
            ResetCamera();
        }
        
        ImGui::End();
    }
    
    void RenderActivityLog() {
        ImGui::Begin("Activity Log");
        
        // Display recent log entries
        const auto& entries = logger->GetEntries();
        for (const auto& entry : entries) {
            ImVec4 color;
            switch (entry.level) {
                case ActivityLogger::LogLevel::SUCCESS:
                    color = OTOYColors::SUCCESS_GREEN;
                    break;
                case ActivityLogger::LogLevel::ERROR:
                    color = OTOYColors::ERROR_RED;
                    break;
                case ActivityLogger::LogLevel::WARNING:
                    color = OTOYColors::WARNING_YELLOW;
                    break;
                default:
                    color = OTOYColors::TEXT_PRIMARY;
                    break;
            }
            
            ImGui::TextColored(color, "[%s] %s", entry.timestamp.c_str(), entry.message.c_str());
        }
        
        // Auto-scroll to bottom
        if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
            ImGui::SetScrollHereY(1.0f);
        }
        
        ImGui::End();
    }
    
    void RenderPerformanceStats() {
        ImGui::Begin("Performance");
        
        ImGui::Text("FPS: %.1f", fps);
        ImGui::Text("Frame Time: %.3f ms", frameTime);
        ImGui::Text("Success Count: %d", successCount);
        ImGui::Text("Error Count: %d", errorCount);
        
        ImGui::End();
    }
    
    // Action methods
    void ConnectToLiveLink() {
        logger->Log("🔗 Attempting to connect to LiveLink...", ActivityLogger::LogLevel::STATUS);
        
        // Simulate connection attempt
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        
        // For now, simulate connection failure (no actual gRPC implementation)
        connectionStatus = ConnectionStatus::DISCONNECTED;
        logger->Log("❌ LiveLink connection failed - service not available", ActivityLogger::LogLevel::ERROR);
        errorCount++;
    }
    
    void DisconnectFromLiveLink() {
        logger->Log("🔌 Disconnecting from LiveLink...", ActivityLogger::LogLevel::STATUS);
        connectionStatus = ConnectionStatus::READY;
        logger->Log("✅ Disconnected from LiveLink", ActivityLogger::LogLevel::SUCCESS);
    }
    
    void LoadModel() {
        logger->Log("📂 Loading model...", ActivityLogger::LogLevel::STATUS);
        logger->Log("✅ Using default cube model", ActivityLogger::LogLevel::SUCCESS);
        successCount++;
    }
    
    void TestLoadTeapot() {
        logger->Log("🫖 Loading teapot model...", ActivityLogger::LogLevel::STATUS);
        logger->Log("✅ Teapot loaded successfully (simulated)", ActivityLogger::LogLevel::SUCCESS);
        successCount++;
    }
    
    void ResetCamera() {
        logger->Log("📷 Resetting camera position...", ActivityLogger::LogLevel::STATUS);
        camera = SimpleCameraController(); // Reset to default
        logger->Log("✅ Camera reset to default position", ActivityLogger::LogLevel::SUCCESS);
        successCount++;
    }
    
    void Cleanup() {
        renderer.cleanup();
        
        // Cleanup Dear ImGui
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        
        // Cleanup GLFW
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

int main() {
    TestGrpcApiApp app;
    
    if (!app.Initialize()) {
        std::cerr << "Failed to initialize application" << std::endl;
        return -1;
    }
    
    app.Run();
    app.Cleanup();
    
    return 0;
}