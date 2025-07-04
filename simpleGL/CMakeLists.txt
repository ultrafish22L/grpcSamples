cmake_minimum_required(VERSION 3.10)

# Define the simpleGL project
project(simpleGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create the main executable
add_executable(simpleGL
    main.cpp
)

# Include directories
target_include_directories(simpleGL
    PRIVATE
        ${CMAKE_SOURCE_DIR}/third_party/glew/include
        ${CMAKE_SOURCE_DIR}/third_party/glfw/include
        ${CMAKE_SOURCE_DIR}/third_party/glm
)

# Add gRPC compile definitions if enabled
if(ENABLE_OCTANE_GRPC)
    target_compile_definitions(simpleGL PRIVATE OCTANE_GRPC_ENABLED)
endif()

# Find OpenGL
find_package(OpenGL REQUIRED)

# Link libraries for main executable
target_link_libraries(simpleGL
    PRIVATE
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

# Set working directory for debugging in Visual Studio
set_target_properties(simpleGL PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

# Windows MSVC specific configurations for executables
if(MSVC)
    # Set subsystem to console for all executables
    set_target_properties(simpleGL PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:CONSOLE"
    )
    
    # Set runtime library to match third_party libraries (static runtime)
    set_property(TARGET simpleGL PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()
