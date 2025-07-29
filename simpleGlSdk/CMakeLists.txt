cmake_minimum_required(VERSION 3.10)

# Define the simpleGlSdk project
project(simpleGlSdk)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Check for Octane SDK availability (optional for simpleGlSdk)
set(OCTANE_SDK_AVAILABLE FALSE)

# Check for SDK headers
if(EXISTS "${CMAKE_SOURCE_DIR}/sdk/apirender.h")
    set(OCTANE_SDK_AVAILABLE TRUE)
    message(STATUS "Octane SDK headers found - enabling SDK integration")
else()
    message(STATUS "Octane SDK headers not found - building without SDK integration")
endif()

# Assume Octane libraries are available in sdk folder for all platforms

# Create the main executable with SDK integration
add_executable(simpleGlSdk
    main.cpp
)
add_dependencies(simpleGlSdk octane_sdk)

# Function to configure a target
function(configure_simpleGlSdk_target target_name)
    # Include directories
    target_include_directories(${target_name}
        PRIVATE
            ${CMAKE_SOURCE_DIR}/third_party/glew/include
            ${CMAKE_SOURCE_DIR}/third_party/glfw/include
            ${CMAKE_SOURCE_DIR}/third_party/glm
            # Multiplatform SDK headers
            ${CMAKE_SOURCE_DIR}/sdk
            ${CMAKE_SOURCE_DIR}/sdk/src/api/grpc/protodef
            ${CMAKE_SOURCE_DIR}/sdk/src/api/grpc/protoc
            ${CMAKE_SOURCE_DIR}/sdk/src/api/grpc
            ${CMAKE_SOURCE_DIR}/sdk/src/api/grpc/client
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/protos
    )
    
    # Add dependency on protobuf generation
    if(TARGET protobuf_all)
        add_dependencies(${target_name} protobuf_all)
    endif()
    
    # Add dependency on gRPC file generation
    if(TARGET generate_grpc_files_simpleGlSdk)
        add_dependencies(${target_name} generate_grpc_files_simpleGlSdk)
    endif()

    # Add SDK header include paths (required for simpleGlSdk)
    target_include_directories(${target_name}
        PRIVATE
            ${CMAKE_SOURCE_DIR}/sdk
    )

    # Link libraries - use built targets from third_party
    target_link_libraries(${target_name}
        PRIVATE
            shared_lib
            octane_sdk
            glfw
            glew
            glm
            ${OPENGL_LIBRARIES}
    )
    
    # Enable SDK integration for all platforms (using stub implementation)
    target_compile_definitions(${target_name} PRIVATE DO_GRPC_SDK_ENABLED)
    
    # Set working directory for debugging in Visual Studio
    set_target_properties(${target_name} PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
    )

    # Windows MSVC specific configurations
    if(MSVC)
        # Set subsystem to console
        set_target_properties(${target_name} PROPERTIES
            LINK_FLAGS "/SUBSYSTEM:CONSOLE"
        )
        
        # Set runtime library to match third_party libraries (static runtime)
        set_property(TARGET ${target_name} PROPERTY
            MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
        
        # Add /bigobj flag for large object files
        target_compile_options(${target_name} PRIVATE /bigobj)
    endif()
endfunction()

# Configure all targets
configure_simpleGlSdk_target(simpleGlSdk)

#[[

# Create a demo executable
add_executable(simpleGlSdk_demo
    demo.cpp
)

# Create a test executable
add_executable(simpleGlSdk_test
    test_gl.cpp
)
configure_simpleGlSdk_target(simpleGlSdk_demo)
configure_simpleGlSdk_target(simpleGlSdk_test)
]]

# gRPC functionality is provided by third_party libraries only
# No system gRPC dependencies
