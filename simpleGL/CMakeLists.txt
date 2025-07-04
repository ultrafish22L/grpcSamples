cmake_minimum_required(VERSION 3.10)

# Define the simpleGL project
project(simpleGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    main.cpp
    demo.cpp
    test_gl.cpp
)

# Create the main executable
add_executable(simpleGL
    main.cpp
    octane_camera_sync.cpp
)

# Create additional executables for demo and test
add_executable(simpleGL_demo
    demo.cpp
    octane_camera_sync.cpp
)

add_executable(simpleGL_test
    test_gl.cpp
)

# Include directories
target_include_directories(simpleGL
    PRIVATE
        ${CMAKE_SOURCE_DIR}/third_party/glew/include
        ${CMAKE_SOURCE_DIR}/third_party/glfw/include
        ${CMAKE_SOURCE_DIR}/third_party/glm
        ${CMAKE_SOURCE_DIR}/sdk
        # Add third_party headers for gRPC dependencies in SDK
        ${CMAKE_SOURCE_DIR}/third_party/protobuf/windows/include
        ${CMAKE_SOURCE_DIR}/third_party/grpc/windows/include
        ${CMAKE_SOURCE_DIR}/third_party/absl/windows/include
)

target_include_directories(simpleGL_demo
    PRIVATE
        ${CMAKE_SOURCE_DIR}/third_party/glew/include
        ${CMAKE_SOURCE_DIR}/third_party/glfw/include
        ${CMAKE_SOURCE_DIR}/third_party/glm
        ${CMAKE_SOURCE_DIR}/sdk
        # Add third_party headers for gRPC dependencies in SDK
        ${CMAKE_SOURCE_DIR}/third_party/protobuf/windows/include
        ${CMAKE_SOURCE_DIR}/third_party/grpc/windows/include
        ${CMAKE_SOURCE_DIR}/third_party/absl/windows/include
)

target_include_directories(simpleGL_test
    PRIVATE
        ${CMAKE_SOURCE_DIR}/third_party/glew/include
        ${CMAKE_SOURCE_DIR}/third_party/glfw/include
        ${CMAKE_SOURCE_DIR}/sdk
        # Add third_party headers for gRPC dependencies in SDK
        ${CMAKE_SOURCE_DIR}/third_party/protobuf/windows/include
        ${CMAKE_SOURCE_DIR}/third_party/grpc/windows/include
        ${CMAKE_SOURCE_DIR}/third_party/absl/windows/include
)

# Add gRPC compile definitions if enabled
if(ENABLE_OCTANE_GRPC)
    target_compile_definitions(simpleGL PRIVATE OCTANE_GRPC_ENABLED)
    target_compile_definitions(simpleGL_demo PRIVATE OCTANE_GRPC_ENABLED)
    target_compile_definitions(simpleGL_test PRIVATE OCTANE_GRPC_ENABLED)
endif()

# Find OpenGL
find_package(OpenGL REQUIRED)

# Link libraries for main executable
target_link_libraries(simpleGL
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

# Link libraries for test executable
target_link_libraries(simpleGL_test
    PRIVATE
        octane_sdk
        glew
        glfw
        ${OPENGL_LIBRARIES}
        # Windows-specific system libraries
        $<$<PLATFORM_ID:Windows>:user32>
        $<$<PLATFORM_ID:Windows>:gdi32>
        $<$<PLATFORM_ID:Windows>:shell32>
)

# Link libraries for demo executable
target_link_libraries(simpleGL_demo
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

# Set Visual Studio folder organization
set_target_properties(simpleGL PROPERTIES FOLDER "Applications")
set_target_properties(simpleGL_demo PROPERTIES FOLDER "Applications")
set_target_properties(simpleGL_test PROPERTIES FOLDER "Applications")

# Set working directory for debugging in Visual Studio
set_target_properties(simpleGL PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)
set_target_properties(simpleGL_test PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)
set_target_properties(simpleGL_demo PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

# Windows MSVC specific configurations for executables
if(MSVC)
    # Set subsystem to console for all executables
    set_target_properties(simpleGL PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:CONSOLE"
    )
    set_target_properties(simpleGL_test PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:CONSOLE"
    )
    set_target_properties(simpleGL_demo PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:CONSOLE"
    )
    
    # Set runtime library to match project settings
    set_property(TARGET simpleGL PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
    set_property(TARGET simpleGL_test PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
    set_property(TARGET simpleGL_demo PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()
