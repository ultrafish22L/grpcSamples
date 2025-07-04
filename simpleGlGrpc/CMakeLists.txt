cmake_minimum_required(VERSION 3.10)

# Define the simpleGlGrpc project
project(simpleGlGrpc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Check for gRPC availability - prefer third_party, fallback to system
set(GRPC_AVAILABLE OFF)

# Try to use third_party gRPC libraries for Windows
if(WIN32)
    set(GRPC_LIB_DIR "${CMAKE_SOURCE_DIR}/third_party/grpc/windows/$<IF:$<CONFIG:Debug>,debug_64,release_64>")
    set(GRPC_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/third_party/grpc/windows/include")
    
    if(EXISTS "${CMAKE_SOURCE_DIR}/third_party/grpc/windows/include")
        set(GRPC_AVAILABLE ON)
        set(GRPC_LIBRARIES
            "${GRPC_LIB_DIR}/grpc++.lib"
            "${GRPC_LIB_DIR}/grpc.lib"
            "${GRPC_LIB_DIR}/gpr.lib"
            "${GRPC_LIB_DIR}/address_sorting.lib"
            "${GRPC_LIB_DIR}/upb_base_lib.lib"
            "${GRPC_LIB_DIR}/upb_message_lib.lib"
            "${GRPC_LIB_DIR}/upb_mem_lib.lib"
            "${GRPC_LIB_DIR}/upb_textformat_lib.lib"
            "${GRPC_LIB_DIR}/upb_json_lib.lib"
            "${GRPC_LIB_DIR}/upb_wire_lib.lib"
            "${GRPC_LIB_DIR}/upb_mini_descriptor_lib.lib"
            "${GRPC_LIB_DIR}/utf8_range_lib.lib"
        )
        message(STATUS "simpleGlGrpc: Using third_party gRPC libraries")
    endif()
endif()

# Fallback to system gRPC
if(NOT GRPC_AVAILABLE)
    find_package(PkgConfig QUIET)
    if(PkgConfig_FOUND)
        pkg_check_modules(GRPC QUIET grpc++)
        if(GRPC_FOUND)
            set(GRPC_AVAILABLE ON)
            set(GRPC_LIBRARIES ${GRPC_LIBRARIES})
            set(GRPC_INCLUDE_DIR ${GRPC_INCLUDE_DIRS})
            message(STATUS "simpleGlGrpc: Using system gRPC libraries")
        endif()
    endif()
endif()

if(GRPC_AVAILABLE)
    message(STATUS "simpleGlGrpc: gRPC functionality enabled")
else()
    message(STATUS "simpleGlGrpc: gRPC functionality disabled (libraries not found)")
endif()

# gRPC header files (simplified - removed problematic SDK-dependent files)
set(GRPC_HEADERS
    grpc_camera_sync.h
    octane_camera_sync.h
)

# Source files for all executables (simplified - removed problematic SDK-dependent files)
set(COMMON_SOURCES
    grpc_camera_sync.cpp
    octane_camera_sync.cpp
    grpc_settings.cpp
    # Add generated protobuf files for camera control
    generated/camera_control.pb.cc
    generated/camera_control.grpc.pb.cc
)

# Create the main executable with direct gRPC integration
add_executable(simpleGlGrpc
    main.cpp
    ${COMMON_SOURCES}
)

# Create a demo executable
add_executable(simpleGlGrpc_demo
    demo.cpp
    ${COMMON_SOURCES}
)

# Create a test executable
add_executable(simpleGlGrpc_test
    test_gl.cpp
    ${COMMON_SOURCES}
)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Function to configure a target
function(configure_simpleGlGrpc_target target_name)
    # Include directories
    target_include_directories(${target_name}
        PRIVATE
            ${CMAKE_SOURCE_DIR}/third_party/glew/include
            ${CMAKE_SOURCE_DIR}/third_party/glfw/include
            ${CMAKE_SOURCE_DIR}/third_party/glm
            ${CMAKE_SOURCE_DIR}/sdk
            ${CMAKE_SOURCE_DIR}/sdk/src/api/grpc/protodef
            ${CMAKE_SOURCE_DIR}/sdk/src/api/grpc/protoc
            ${CMAKE_SOURCE_DIR}/sdk/src/api/grpc
            ${CMAKE_SOURCE_DIR}/sdk/src/api/grpc/client
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/generated
            # Add third_party protobuf, gRPC, and absl headers for all platforms
            ${CMAKE_SOURCE_DIR}/third_party/protobuf/windows/include
            ${CMAKE_SOURCE_DIR}/third_party/grpc/windows/include
            ${CMAKE_SOURCE_DIR}/third_party/absl/windows/include
    )
    
    # Add dependency on protobuf generation
    if(TARGET protobuf_all)
        add_dependencies(${target_name} protobuf_all)
    endif()

    # Add gRPC include directories if available
    if(GRPC_AVAILABLE)
        target_include_directories(${target_name}
            PRIVATE
                ${GRPC_INCLUDE_DIR}
        )
        
        # Add compile definition for gRPC support
        target_compile_definitions(${target_name}
            PRIVATE
                GRPC_ENABLED
        )
    endif()

    # Link libraries
    target_link_libraries(${target_name}
        PRIVATE
            octane_sdk
            glew
            glfw
            glm
            ${OPENGL_LIBRARIES}
            # Windows-specific system libraries
            $<$<PLATFORM_ID:Windows>:user32>
            $<$<PLATFORM_ID:Windows>:gdi32>
            $<$<PLATFORM_ID:Windows>:shell32>
    )
    
    # Add gRPC libraries if available
    if(GRPC_AVAILABLE)
        target_link_libraries(${target_name}
            PRIVATE
                ${GRPC_LIBRARIES}
        )
        
        # Try to find and link protobuf library
        find_package(Protobuf QUIET)
        if(Protobuf_FOUND)
            target_link_libraries(${target_name}
                PRIVATE
                    ${Protobuf_LIBRARIES}
            )
            target_include_directories(${target_name}
                PRIVATE
                    ${Protobuf_INCLUDE_DIRS}
            )
        endif()
    endif()
    
    # Set Visual Studio folder organization
    set_target_properties(${target_name} PROPERTIES FOLDER "Applications")

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
        
        # Set runtime library to match project settings
        set_property(TARGET ${target_name} PROPERTY
            MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
        
        # Add /bigobj flag for large object files
        target_compile_options(${target_name} PRIVATE /bigobj)
    endif()
endfunction()

# Configure all targets
configure_simpleGlGrpc_target(simpleGlGrpc)
configure_simpleGlGrpc_target(simpleGlGrpc_demo)
configure_simpleGlGrpc_target(simpleGlGrpc_test)

# Add gRPC libraries if available (optional)
find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    pkg_check_modules(GRPC QUIET grpc++)
    pkg_check_modules(PROTOBUF QUIET protobuf)
    
    if(GRPC_FOUND AND PROTOBUF_FOUND)
        # Apply gRPC configuration to all targets
        foreach(target simpleGlGrpc simpleGlGrpc_demo simpleGlGrpc_test)
            target_link_libraries(${target}
                PRIVATE
                    ${GRPC_LIBRARIES}
                    ${PROTOBUF_LIBRARIES}
            )
            target_include_directories(${target}
                PRIVATE
                    ${GRPC_INCLUDE_DIRS}
                    ${PROTOBUF_INCLUDE_DIRS}
            )
            target_compile_definitions(${target}
                PRIVATE
                    OCTANE_GRPC_ENABLED
            )
        endforeach()
        message(STATUS "simpleGlGrpc: gRPC functionality enabled")
    else()
        message(STATUS "simpleGlGrpc: gRPC functionality disabled (libraries not found)")
    endif()
else()
    message(STATUS "simpleGlGrpc: gRPC functionality disabled (PkgConfig not found)")
endif()
