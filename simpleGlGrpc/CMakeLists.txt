cmake_minimum_required(VERSION 3.10)

# Define the simpleGlGrpc project
project(simpleGlGrpc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generated protobuf files
set(PROTOBUF_SOURCES
    generated/camera_control.pb.cc
    generated/camera_control.grpc.pb.cc
)

# gRPC source files (simplified implementations)
set(GRPC_SOURCES
    ${PROTOBUF_SOURCES}
)

# gRPC header files
set(GRPC_HEADERS
    grpcmaininterface.h
    grpcmodulebase.h
    callbackservice.h
    apicontrol.h
    apinodepinInfohelper.h
    grpc_stubs.h
    grpc_camera_sync.h
)

# Create the main executable with direct gRPC integration
add_executable(simpleGlGrpc
    main.cpp
    grpc_camera_sync.cpp
    ${GRPC_SOURCES}
)

# Include directories
target_include_directories(simpleGlGrpc
    PRIVATE
        ${CMAKE_SOURCE_DIR}/third_party/glew/include
        ${CMAKE_SOURCE_DIR}/third_party/glfw/include
        ${CMAKE_SOURCE_DIR}/third_party/glm
        ${CMAKE_SOURCE_DIR}/sdk
        ${CMAKE_SOURCE_DIR}/sdk/src/api/grpc/protodef
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/generated
)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Link libraries for main executable
target_link_libraries(simpleGlGrpc
    PRIVATE
        octane_sdk
        glew
        glfw
        glm
        ${OPENGL_LIBRARIES}
)

# Add gRPC libraries if available
if(TARGET grpc++)
    target_link_libraries(simpleGlGrpc
        PRIVATE
            grpc++
            grpc
    )
    target_compile_definitions(simpleGlGrpc
        PRIVATE
            OCTANE_GRPC_ENABLED
    )
else()
    # Use system gRPC libraries
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GRPC REQUIRED grpc++)
    pkg_check_modules(PROTOBUF REQUIRED protobuf)
    
    target_link_libraries(simpleGlGrpc
        PRIVATE
            ${GRPC_LIBRARIES}
            ${PROTOBUF_LIBRARIES}
    )
    target_include_directories(simpleGlGrpc
        PRIVATE
            ${GRPC_INCLUDE_DIRS}
            ${PROTOBUF_INCLUDE_DIRS}
    )
    target_compile_definitions(simpleGlGrpc
        PRIVATE
            OCTANE_GRPC_ENABLED
    )
endif()

# Set working directory for debugging in Visual Studio
set_target_properties(simpleGlGrpc PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)
