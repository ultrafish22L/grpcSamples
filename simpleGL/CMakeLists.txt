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
)

target_include_directories(simpleGL_demo
    PRIVATE
        ${CMAKE_SOURCE_DIR}/third_party/glew/include
        ${CMAKE_SOURCE_DIR}/third_party/glfw/include
        ${CMAKE_SOURCE_DIR}/third_party/glm
        ${CMAKE_SOURCE_DIR}/sdk
)

target_include_directories(simpleGL_test
    PRIVATE
        ${CMAKE_SOURCE_DIR}/third_party/glew/include
        ${CMAKE_SOURCE_DIR}/third_party/glfw/include
        ${CMAKE_SOURCE_DIR}/sdk
)

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
)

# Link libraries for test executable
target_link_libraries(simpleGL_test
    PRIVATE
        octane_sdk
        glew
        glfw
        ${OPENGL_LIBRARIES}
)

# Link libraries for demo executable
target_link_libraries(simpleGL_demo
    PRIVATE
        octane_sdk
        glew
        glfw
        glm
        ${OPENGL_LIBRARIES}
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
