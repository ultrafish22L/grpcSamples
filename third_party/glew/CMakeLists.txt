cmake_minimum_required(VERSION 3.10)
project(GLEW C)

# GLEW static library
add_library(glew STATIC
    src/glew.c
)

target_include_directories(glew
    PUBLIC
        include
)

# Define GLEW_STATIC for static linking
target_compile_definitions(glew
    PUBLIC
        GLEW_STATIC
)

# Find and link OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(glew
    PUBLIC
        ${OPENGL_LIBRARIES}
)

# Set folder for Visual Studio
set_target_properties(glew PROPERTIES FOLDER "ThirdParty")