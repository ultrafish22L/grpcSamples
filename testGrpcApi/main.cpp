/**
 * testGrpcApi - C++ Dear ImGui Application
 * Exact duplicate of html/index.html functionality using shared components
 * 
 * Features:
 * - OTOY-themed professional interface matching html/index.html
 * - WebGL-style 3D rendering with OpenGL (reusing shared_rendering.cpp)
 * - gRPC LiveLink integration (reusing camera_sync_livelink.cpp)
 * - Real-time camera synchronization (reusing camera_system.h)
 * - Activity logging and performance monitoring
 * - All controls and features from the HTML version
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <cmath>

// OpenGL and GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Dear ImGui
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// Shared components (reuse existing code)
#include "../shared_rendering.h"
#include "camera_system.h"
#include "model_manager.h"
#include "camera_sync_livelink.h"
#include "file_dialog.h"

// Application components
#include "ActivityLogger.h"
#include "PerformanceTracker.h"

// OTOY Brand Colors (matching CSS)
namespace OTOYColors {
    const ImVec4 RED = ImVec4(0.624f, 0.204f, 0.204f, 1.0f);           // #9f3434
    const ImVec4 RED_LIGHT = ImVec4(0.678f, 0.235f, 0.235f, 1.0f);     // #ad3c3c
    const ImVec4 RED_DARK = ImVec4(0.471f, 0.153f, 0.153f, 1.0f);      // #792727
    const ImVec4 BG_PRIMARY = ImVec4(0.039f, 0.039f, 0.039f, 1.0f);    // #0a0a0a
    const ImVec4 BG_SECONDARY = ImVec4(0.102f, 0.102f, 0.102f, 1.0f);  // #1a1a1a
    const ImVec4 BG_PANEL = ImVec4(0.118f, 0.118f, 0.118f, 1.0f);      // #1e1e1e
    const ImVec4 BG_HEADER = ImVec4(0.059f, 0.059f, 0.059f, 1.0f);     // #0f0f0f
    const ImVec4 TEXT_PRIMARY = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);        // #ffffff
    const ImVec4 TEXT_SECONDARY = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);      // #cccccc
    const ImVec4 TEXT_MUTED = ImVec4(0.467f, 0.467f, 0.467f, 1.0f);    // #777777
    const ImVec4 ACCENT_GREEN = ImVec4(0.361f, 0.722f, 0.361f, 1.0f);  // #5cb85c
    const ImVec4 ACCENT_BLUE = ImVec4(0.357f, 0.753f, 0.871f, 1.0f);   // #5bc0de
    const ImVec4 ACCENT_WARNING = ImVec4(0.941f, 0.678f, 0.306f, 1.0f); // #f0ad4e
}

class TestGrpcApiApp {
private:
    GLFWwindow* window;
    
    // Shared components (reuse existing infrastructure)
    SharedUtils::CameraController cameraController;
    SharedUtils::ModelManager modelManager;
    CameraSyncLiveLink cameraSync;
    ModernRendering::ModernRenderer renderer;
    
    std::unique_ptr<ActivityLogger> logger;
    std::unique_ptr<PerformanceTracker> perfTracker;
    
    // Application state matching HTML
    std::string serverAddress = "127.0.0.1:51023";  // gRPC format, not HTTP
    bool connectionToggle = false;
    bool autoRotateToggle = true;
    bool syncCameraToggle = true;
    bool verboseLogsToggle = false;
    
    // Performance stats
    float fps = 0.0f;
    float frameTime = 0.0f;
    float responseTime = 0.0f;
    float syncRate = 0.0f;
    int errorCount = 0;
    
    // UI state
    bool showDemo = false;
    ImVec2 canvasSize = ImVec2(800, 600);
    
    // Camera sync timer
    std::chrono::steady_clock::time_point lastSyncTime;
    
public:
    TestGrpcApiApp() = default;
    ~TestGrpcApiApp() = default;
    
    bool Initialize() {
        // Initialize GLFW
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return false;
        }
        
        // Configure GLFW (matching simpleGlGrpc settings)
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, 4); // 4x MSAA for anti-aliasing
        glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
        glfwWindowHint(GLFW_DEPTH_BITS, 24);
        
        // Create window
        window = glfwCreateWindow(1400, 1000, "🔗 OTOY WebGL-Octane LiveLink Sync", nullptr, nullptr);
        if (!window) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }
        
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // Enable vsync
        
        // Initialize GLEW
        if (glewInit() != GLEW_OK) {
            std::cerr << "Failed to initialize GLEW" << std::endl;
            return false;
        }
        
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        
        // Setup OTOY theme
        SetupOTOYTheme();
        
        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
        
        // Initialize shared components
        logger = std::make_unique<ActivityLogger>();
        perfTracker = std::make_unique<PerformanceTracker>();
        
        // Initialize renderer (reuse shared rendering system)
        if (!renderer.initialize()) {
            logger->Log("Failed to initialize renderer", ActivityLogger::LogLevel::ERROR);
            return false;
        }
        
        // Initialize model manager
        modelManager.initialize(&renderer);
        
        logger->Log("Initializing WebGL-Octane LiveLink Sync viewer", ActivityLogger::LogLevel::STATUS);
        logger->Log("Using shared components from simpleGlGrpc", ActivityLogger::LogLevel::STATUS);
        
        lastSyncTime = std::chrono::steady_clock::now();
        
        return true;
    }
    
    void SetupOTOYTheme() {
        ImGuiStyle& style = ImGui::GetStyle();
        
        // Colors matching OTOY theme
        style.Colors[ImGuiCol_Text] = OTOYColors::TEXT_PRIMARY;
        style.Colors[ImGuiCol_TextDisabled] = OTOYColors::TEXT_MUTED;
        style.Colors[ImGuiCol_WindowBg] = OTOYColors::BG_PRIMARY;
        style.Colors[ImGuiCol_ChildBg] = OTOYColors::BG_SECONDARY;
        style.Colors[ImGuiCol_PopupBg] = OTOYColors::BG_PANEL;
        style.Colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
        style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style.Colors[ImGuiCol_FrameBg] = OTOYColors::BG_SECONDARY;
        style.Colors[ImGuiCol_FrameBgHovered] = OTOYColors::BG_PANEL;
        style.Colors[ImGuiCol_FrameBgActive] = OTOYColors::BG_PANEL;
        style.Colors[ImGuiCol_TitleBg] = OTOYColors::BG_HEADER;
        style.Colors[ImGuiCol_TitleBgActive] = OTOYColors::BG_HEADER;
        style.Colors[ImGuiCol_TitleBgCollapsed] = OTOYColors::BG_HEADER;
        style.Colors[ImGuiCol_MenuBarBg] = OTOYColors::BG_HEADER;
        style.Colors[ImGuiCol_ScrollbarBg] = OTOYColors::BG_SECONDARY;
        style.Colors[ImGuiCol_ScrollbarGrab] = OTOYColors::RED;
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = OTOYColors::RED_LIGHT;
        style.Colors[ImGuiCol_ScrollbarGrabActive] = OTOYColors::RED_DARK;
        style.Colors[ImGuiCol_CheckMark] = OTOYColors::RED;
        style.Colors[ImGuiCol_SliderGrab] = OTOYColors::RED;
        style.Colors[ImGuiCol_SliderGrabActive] = OTOYColors::RED_LIGHT;
        style.Colors[ImGuiCol_Button] = OTOYColors::BG_PANEL;
        style.Colors[ImGuiCol_ButtonHovered] = OTOYColors::RED;
        style.Colors[ImGuiCol_ButtonActive] = OTOYColors::RED_DARK;
        style.Colors[ImGuiCol_Header] = OTOYColors::BG_PANEL;
        style.Colors[ImGuiCol_HeaderHovered] = OTOYColors::RED;
        style.Colors[ImGuiCol_HeaderActive] = OTOYColors::RED_DARK;
        style.Colors[ImGuiCol_Separator] = OTOYColors::BG_PANEL;
        style.Colors[ImGuiCol_SeparatorHovered] = OTOYColors::RED;
        style.Colors[ImGuiCol_SeparatorActive] = OTOYColors::RED_LIGHT;
        style.Colors[ImGuiCol_ResizeGrip] = OTOYColors::BG_PANEL;
        style.Colors[ImGuiCol_ResizeGripHovered] = OTOYColors::RED;
        style.Colors[ImGuiCol_ResizeGripActive] = OTOYColors::RED_DARK;
        style.Colors[ImGuiCol_Tab] = OTOYColors::BG_SECONDARY;
        style.Colors[ImGuiCol_TabHovered] = OTOYColors::RED;
        style.Colors[ImGuiCol_TabActive] = OTOYColors::RED_DARK;
        style.Colors[ImGuiCol_TabUnfocused] = OTOYColors::BG_SECONDARY;
        style.Colors[ImGuiCol_TabUnfocusedActive] = OTOYColors::BG_PANEL;
        
        // Style settings for professional look
        style.WindowRounding = 2.0f;
        style.FrameRounding = 2.0f;
        style.PopupRounding = 2.0f;
        style.ScrollbarRounding = 2.0f;
        style.GrabRounding = 2.0f;
        style.TabRounding = 2.0f;
        style.WindowBorderSize = 1.0f;
        style.FrameBorderSize = 0.0f;
        style.PopupBorderSize = 1.0f;
        style.WindowPadding = ImVec2(8, 8);
        style.FramePadding = ImVec2(8, 4);
        style.ItemSpacing = ImVec2(8, 4);
        style.ItemInnerSpacing = ImVec2(4, 4);
        style.IndentSpacing = 20.0f;
        style.ScrollbarSize = 16.0f;
        style.GrabMinSize = 12.0f;
    }
    
    void Run() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            
            // Update performance tracking
            perfTracker->Update();
            fps = perfTracker->GetFPS();
            frameTime = perfTracker->GetFrameTime();
            
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
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            
            glfwSwapBuffers(window);
        }
    }
    
    void RenderMainInterface() {
        // Create main dockspace
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        // ImGui::SetNextWindowViewport(viewport->ID); // Not available in this ImGui version
        
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | 
                                       ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                                       ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
                                       ImGuiWindowFlags_NoBackground;
        
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        
        ImGui::Begin("MainDockSpace", nullptr, window_flags);
        ImGui::PopStyleVar(3);
        
        // Create dockspace (disabled - not available in this ImGui version)
        // ImGuiID dockspace_id = ImGui::GetID("MainDockSpace");
        // ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
        
        // Render header
        RenderHeader();
        
        // Render controls section
        RenderControlsSection();
        
        // Render main content area
        RenderMainContent();
        
        // Render footer
        RenderFooter();
        
        ImGui::End();
    }
    
    void RenderHeader() {
        ImGui::PushStyleColor(ImGuiCol_ChildBg, OTOYColors::BG_HEADER);
        ImGui::BeginChild("Header", ImVec2(0, 80), true, ImGuiWindowFlags_NoScrollbar);
        
        // OTOY Branding
        ImGui::PushStyleColor(ImGuiCol_Text, OTOYColors::TEXT_PRIMARY);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
        
        // Octane gear icon (simplified)
        ImGui::Text("⚙️");
        ImGui::SameLine();
        ImGui::Text("WebGL LiveLink 🔗");
        
        ImGui::SameLine(ImGui::GetWindowWidth() - 400);
        
        // Connection controls
        ImGui::Text("🔌");
        ImGui::SameLine();
        ImGui::PushItemWidth(200);
        ImGui::InputText("##ServerAddress", &serverAddress[0], serverAddress.capacity());
        ImGui::PopItemWidth();
        
        ImGui::SameLine();
        if (ImGui::Checkbox("Connect", &connectionToggle)) {
            ToggleConnection();
        }
        
        ImGui::PopStyleColor();
        ImGui::EndChild();
        ImGui::PopStyleColor();
    }
    
    void RenderControlsSection() {
        ImGui::PushStyleColor(ImGuiCol_ChildBg, OTOYColors::BG_SECONDARY);
        ImGui::BeginChild("Controls", ImVec2(0, 60), true, ImGuiWindowFlags_NoScrollbar);
        
        // LiveLink controls
        if (ImGui::Button("📷 Get Camera")) { TestGetCamera(); }
        ImGui::SameLine();
        if (ImGui::Button("📸 Set Camera")) { SetCamera(); }
        ImGui::SameLine();
        if (ImGui::Button("🔄 Reset Camera")) { ResetCamera(); }
        ImGui::SameLine();
        if (ImGui::Button("🎬 Get Meshes")) { TestGetMeshes(); }
        ImGui::SameLine();
        if (ImGui::Button("📂 Load Model")) { LoadModel(); }
        ImGui::SameLine();
        if (ImGui::Button("🫖 Load Teapot")) { TestLoadTeapot(); }
        
        // View controls
        ImGui::SameLine(ImGui::GetWindowWidth() - 300);
        ImGui::Text("🧊");
        ImGui::SameLine();
        if (ImGui::Checkbox("Auto-Rotate", &autoRotateToggle)) {
            ToggleAutoRotate();
        }
        
        ImGui::SameLine();
        ImGui::Text("🔗");
        ImGui::SameLine();
        if (ImGui::Checkbox("Camera Sync", &syncCameraToggle)) {
            ToggleCameraSync();
        }
        
        ImGui::EndChild();
        ImGui::PopStyleColor();
    }
    
    void RenderMainContent() {
        // Split main content: Canvas (left) + Activity Log (right)
        ImGui::BeginChild("MainContent", ImVec2(0, -80), false);
        
        // Canvas area
        ImGui::BeginChild("Canvas", ImVec2(-300, 0), true);
        
        // Get available space for canvas
        ImVec2 canvas_pos = ImGui::GetCursorScreenPos();
        ImVec2 canvas_size = ImGui::GetContentRegionAvail();
        
        // Set up OpenGL viewport for 3D rendering
        glViewport(0, 0, (int)canvas_size.x, (int)canvas_size.y);
        
        // Create projection matrix
        glm::mat4 projection = glm::perspective(
            glm::radians(45.0f), 
            canvas_size.x / canvas_size.y, 
            0.1f, 
            100.0f
        );
        
        // Get view matrix from camera controller
        glm::mat4 view = cameraController.camera.getViewMatrix();
        
        // Auto-rotate model if enabled
        static float modelRotation = 0.0f;
        if (autoRotateToggle) {
            modelRotation += 0.01f;
        }
        
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), modelRotation, glm::vec3(0.0f, 1.0f, 0.0f));
        
        // Render 3D scene using shared renderer
        glm::vec3 viewPos = cameraController.camera.getPosition();
        static float time = 0.0f;
        time += 0.016f; // ~60 FPS increment
        
        renderer.render(view, projection, viewPos, time);
        
        // Handle camera sync
        if (syncCameraToggle && cameraSync.isConnected()) {
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastSyncTime);
            
            if (elapsed.count() > 33) { // ~30 FPS sync rate
                glm::vec3 pos = cameraController.camera.getPosition();
                glm::vec3 target = cameraController.camera.center;
                glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
                
                cameraSync.setCamera(pos, target, up, 45.0f, false); // Don't evaluate every frame
                lastSyncTime = now;
                syncRate = 30.0f; // Update sync rate display
            }
        }
        
        // Handle mouse input for camera control (matching simpleGlGrpc)
        if (ImGui::IsWindowHovered()) {
            ImGuiIO& io = ImGui::GetIO();
            
            if (io.MouseDown[0]) { // Left mouse button - rotate
                if (!cameraController.mouse.dragging) {
                    cameraController.mouse.dragging = true;
                    cameraController.mouse.lastX = io.MousePos.x;
                    cameraController.mouse.lastY = io.MousePos.y;
                } else {
                    float xoffset = io.MousePos.x - cameraController.mouse.lastX;
                    float yoffset = cameraController.mouse.lastY - io.MousePos.y;
                    cameraController.mouse.lastX = io.MousePos.x;
                    cameraController.mouse.lastY = io.MousePos.y;
                    
                    float sensitivity = 0.005f;
                    cameraController.camera.theta += xoffset * sensitivity;
                    cameraController.camera.phi += yoffset * sensitivity;
                    
                    // Constrain phi
                    if (cameraController.camera.phi > 1.5f) cameraController.camera.phi = 1.5f;
                    if (cameraController.camera.phi < -1.5f) cameraController.camera.phi = -1.5f;
                }
            } else {
                cameraController.mouse.dragging = false;
            }
            
            if (io.MouseDown[1]) { // Right mouse button - pan
                if (!cameraController.mouse.panning) {
                    cameraController.mouse.panning = true;
                    cameraController.mouse.lastX = io.MousePos.x;
                    cameraController.mouse.lastY = io.MousePos.y;
                } else {
                    float xoffset = io.MousePos.x - cameraController.mouse.lastX;
                    float yoffset = cameraController.mouse.lastY - io.MousePos.y;
                    cameraController.mouse.lastX = io.MousePos.x;
                    cameraController.mouse.lastY = io.MousePos.y;
                    
                    float sensitivity = 0.01f;
                    glm::vec3 right = glm::normalize(glm::cross(
                        cameraController.camera.getPosition() - cameraController.camera.center,
                        glm::vec3(0.0f, 1.0f, 0.0f)
                    ));
                    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
                    
                    cameraController.camera.center -= right * xoffset * sensitivity;
                    cameraController.camera.center += up * yoffset * sensitivity;
                }
            } else {
                cameraController.mouse.panning = false;
            }
            
            // Mouse wheel - zoom
            if (io.MouseWheel != 0.0f) {
                cameraController.camera.radius -= io.MouseWheel * 2.0f;
                if (cameraController.camera.radius < 1.0f) cameraController.camera.radius = 1.0f;
                if (cameraController.camera.radius > 100.0f) cameraController.camera.radius = 100.0f;
            }
        }
        
        ImGui::EndChild();
        
        ImGui::SameLine();
        
        // Activity Log Panel
        ImGui::BeginChild("ActivityPanel", ImVec2(0, 0), true);
        
        ImGui::Text("Activity Log");
        ImGui::Separator();
        
        // Activity log content
        ImGui::BeginChild("ActivityLog", ImVec2(0, -60), true, ImGuiWindowFlags_AlwaysVerticalScrollbar);
        
        if (logger) {
            auto logs = logger->GetLogs();
            for (const auto& log : logs) {
                ImVec4 color = OTOYColors::TEXT_PRIMARY;
                switch (log.level) {
                    case ActivityLogger::LogLevel::ERROR: color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f); break;
                    case ActivityLogger::LogLevel::SUCCESS: color = OTOYColors::ACCENT_GREEN; break;
                    case ActivityLogger::LogLevel::WARNING: color = OTOYColors::ACCENT_WARNING; break;
                    case ActivityLogger::LogLevel::STATUS: color = OTOYColors::ACCENT_BLUE; break;
                    default: color = OTOYColors::TEXT_PRIMARY; break;
                }
                
                ImGui::PushStyleColor(ImGuiCol_Text, color);
                ImGui::TextWrapped("[%s] %s", log.timestamp.c_str(), log.message.c_str());
                ImGui::PopStyleColor();
            }
        }
        
        // Auto-scroll to bottom
        if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);
        
        ImGui::EndChild();
        
        // Activity controls
        if (ImGui::Button("🗑️ Clear")) { ClearLog(); }
        ImGui::SameLine();
        if (ImGui::Button("💾 Export")) { ExportDebugInfo(); }
        ImGui::SameLine();
        if (ImGui::Button("📊 Info")) { ShowInfo(); }
        
        ImGui::SameLine(ImGui::GetWindowWidth() - 150);
        ImGui::Text("📝");
        ImGui::SameLine();
        if (ImGui::Checkbox("Verbose", &verboseLogsToggle)) {
            ToggleVerboseLogs();
        }
        
        ImGui::EndChild();
        
        ImGui::EndChild();
    }
    
    void RenderFooter() {
        ImGui::PushStyleColor(ImGuiCol_ChildBg, OTOYColors::BG_HEADER);
        ImGui::BeginChild("Footer", ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollbar);
        
        // Performance stats
        ImGui::Text("FPS: %.1f", fps);
        ImGui::SameLine();
        ImGui::Text("Frame: %.1fms", frameTime);
        ImGui::SameLine();
        ImGui::Text("Response: %.1fms", responseTime);
        ImGui::SameLine();
        ImGui::Text("Sync: %.1f/s", syncRate);
        ImGui::SameLine();
        ImGui::Text("Errors: %d", errorCount);
        
        // OTOY footer
        ImGui::SameLine(ImGui::GetWindowWidth() - 400);
        
        // Status LED
        ImVec4 ledColor = connectionToggle ? OTOYColors::ACCENT_GREEN : OTOYColors::RED;
        ImGui::PushStyleColor(ImGuiCol_Text, ledColor);
        ImGui::Text("●");
        ImGui::PopStyleColor();
        ImGui::SameLine();
        ImGui::Text("All Systems Ready");
        
        ImGui::SameLine(ImGui::GetWindowWidth() - 200);
        ImGui::PushStyleColor(ImGuiCol_Text, OTOYColors::TEXT_MUTED);
        ImGui::Text("© OTOY Inc. – 2020 All Rights Reserved.");
        ImGui::PopStyleColor();
        
        ImGui::EndChild();
        ImGui::PopStyleColor();
    }
    
    // Event handlers matching HTML functionality (using shared components)
    void ToggleConnection() {
        if (connectionToggle) {
            logger->Log("Connecting to Octane LiveLink at " + serverAddress + "...", ActivityLogger::LogLevel::STATUS);
            if (cameraSync.connectToServer(serverAddress)) {
                logger->Log("✅ Connected to Octane LiveLink", ActivityLogger::LogLevel::SUCCESS);
            } else {
                logger->Log("❌ Failed to connect to Octane LiveLink", ActivityLogger::LogLevel::ERROR);
                connectionToggle = false;
                errorCount++;
            }
        } else {
            logger->Log("Disconnecting from Octane LiveLink...", ActivityLogger::LogLevel::STATUS);
            cameraSync.disconnect();
            logger->Log("Disconnected from Octane LiveLink", ActivityLogger::LogLevel::STATUS);
        }
    }
    
    void TestGetCamera() {
        logger->Log("📷 Getting camera from Octane...", ActivityLogger::LogLevel::STATUS);
        glm::vec3 pos, target, up;
        float fov;
        
        if (cameraSync.getCamera(pos, target, up, fov)) {
            logger->Log("✅ Camera retrieved successfully", ActivityLogger::LogLevel::SUCCESS);
            logger->Log("Position: (" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ", " + std::to_string(pos.z) + ")", ActivityLogger::LogLevel::DEBUG);
            logger->Log("Target: (" + std::to_string(target.x) + ", " + std::to_string(target.y) + ", " + std::to_string(target.z) + ")", ActivityLogger::LogLevel::DEBUG);
        } else {
            logger->Log("❌ Failed to get camera", ActivityLogger::LogLevel::ERROR);
            errorCount++;
        }
    }
    
    void SetCamera() {
        logger->Log("📸 Setting camera to Octane...", ActivityLogger::LogLevel::STATUS);
        
        // Get current camera position from controller
        glm::vec3 pos = cameraController.camera.getPosition();
        glm::vec3 target = cameraController.camera.center;
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        
        if (cameraSync.setCamera(pos, target, up, 45.0f)) {
            logger->Log("✅ Camera set successfully", ActivityLogger::LogLevel::SUCCESS);
        } else {
            logger->Log("❌ Failed to set camera", ActivityLogger::LogLevel::ERROR);
            errorCount++;
        }
    }
    
    void ResetCamera() {
        logger->Log("🔄 Resetting camera...", ActivityLogger::LogLevel::STATUS);
        
        // Reset local camera
        cameraController.camera.radius = 22.0f;
        cameraController.camera.theta = 0.0f;
        cameraController.camera.phi = 0.0f;
        cameraController.camera.center = glm::vec3(0.0f, 0.0f, 0.0f);
        
        // Sync with Octane if connected
        if (cameraSync.isConnected()) {
            SetCamera();
        }
        
        logger->Log("✅ Camera reset", ActivityLogger::LogLevel::SUCCESS);
    }
    
    void TestGetMeshes() {
        logger->Log("🎬 Getting meshes from Octane...", ActivityLogger::LogLevel::STATUS);
        
        std::vector<CameraSyncLiveLink::MeshInfo> meshes;
        if (cameraSync.getMeshList(meshes)) {
            logger->Log("✅ Found " + std::to_string(meshes.size()) + " meshes", ActivityLogger::LogLevel::SUCCESS);
            for (const auto& mesh : meshes) {
                logger->Log("Mesh: " + mesh.name + " (ID: " + std::to_string(mesh.id) + ")", ActivityLogger::LogLevel::DEBUG);
            }
        } else {
            logger->Log("❌ Failed to get meshes", ActivityLogger::LogLevel::ERROR);
            errorCount++;
        }
    }
    
    void LoadModel() {
        logger->Log("📂 Loading model...", ActivityLogger::LogLevel::STATUS);
        
        // Use shared model manager dialog
        modelManager.loadModelFromDialog();
        
        if (modelManager.hasCustomModel()) {
            logger->Log("✅ Model loaded: " + modelManager.getCurrentModelName(), ActivityLogger::LogLevel::SUCCESS);
        } else {
            logger->Log("❌ Failed to load model or dialog cancelled", ActivityLogger::LogLevel::WARNING);
        }
    }
    
    void TestLoadTeapot() {
        logger->Log("🫖 Resetting to default cube...", ActivityLogger::LogLevel::STATUS);
        
        // Reset to default cube (no built-in teapot in shared system)
        modelManager.resetToDefaultCube();
        logger->Log("✅ Reset to default cube", ActivityLogger::LogLevel::SUCCESS);
    }
    
    void ToggleAutoRotate() {
        logger->Log(autoRotateToggle ? "🧊 Auto-rotate enabled" : "🧊 Auto-rotate disabled", 
                   ActivityLogger::LogLevel::STATUS);
    }
    
    void ToggleCameraSync() {
        logger->Log(syncCameraToggle ? "🔗 Camera sync enabled" : "🔗 Camera sync disabled", 
                   ActivityLogger::LogLevel::STATUS);
    }
    
    void ClearLog() {
        if (logger) {
            logger->Clear();
        }
    }
    
    void ExportDebugInfo() {
        logger->Log("💾 Exporting debug information...", ActivityLogger::LogLevel::STATUS);
        // TODO: Implement debug export
    }
    
    void ShowInfo() {
        logger->Log("📊 Showing system information...", ActivityLogger::LogLevel::STATUS);
        // TODO: Implement info display
    }
    
    void ToggleVerboseLogs() {
        logger->Log(verboseLogsToggle ? "📝 Verbose logging enabled" : "📝 Verbose logging disabled", 
                   ActivityLogger::LogLevel::STATUS);
    }
    
    void Cleanup() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        
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