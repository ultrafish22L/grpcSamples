cmake_minimum_required(VERSION 3.16)
project(testGrpcApi)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../shared)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../shared/protos)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../third_party/imgui)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../third_party/imgui/backends)
include_directories(/usr/include/glm)

# Dear ImGui sources
set(IMGUI_SOURCES
    ../third_party/imgui/imgui.cpp
    ../third_party/imgui/imgui_demo.cpp
    ../third_party/imgui/imgui_draw.cpp
    ../third_party/imgui/imgui_tables.cpp
    ../third_party/imgui/imgui_widgets.cpp
    ../third_party/imgui/backends/imgui_impl_glfw.cpp
    ../third_party/imgui/backends/imgui_impl_opengl3.cpp
)

# Use existing generated protobuf files from shared/protos
set(PROTO_SOURCES
    ../shared/protos/livelink.pb.cc
    ../shared/protos/livelink.grpc.pb.cc
    ../shared/protos/camera_control.pb.cc
    ../shared/protos/camera_control.grpc.pb.cc
)

# Shared component sources
set(SHARED_SOURCES
    ../shared/camera_sync_livelink.cpp
    ../shared/camera_sync_direct.cpp
)

# Application sources
set(APP_SOURCES
    main.cpp
    ActivityLogger.cpp
    PerformanceTracker.cpp
)

# Create executable
add_executable(${PROJECT_NAME} 
    ${APP_SOURCES}
    ${SHARED_SOURCES}
    ${IMGUI_SOURCES}
    ${PROTO_SOURCES}
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
    OpenGL::GL
    glfw
    GLEW
    ${GRPC_LIBRARIES}
    ${PROTOBUF_LIBRARIES}
    ${CMAKE_DL_LIBS}
)

# Compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall -Wextra -Wpedantic
    ${GRPC_CFLAGS_OTHER}
    ${PROTOBUF_CFLAGS_OTHER}
)

# Copy resources
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/imgui.ini ${CMAKE_CURRENT_BINARY_DIR}/imgui.ini COPYONLY)