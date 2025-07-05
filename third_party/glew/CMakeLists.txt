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
        # Windows-specific definitions
        $<$<PLATFORM_ID:Windows>:WIN32_LEAN_AND_MEAN>
)

# Find and link OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(glew
    PUBLIC
        ${OPENGL_LIBRARIES}
)

# Set folder for Visual Studio
set_target_properties(glew PROPERTIES FOLDER "ThirdParty")

# Windows MSVC specific configurations
if(MSVC)
    # Set runtime library to match project settings
    set_property(TARGET glew PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
        
    # Disable specific warnings for GLEW
    target_compile_options(glew PRIVATE /wd4996 /wd4267 /wd4244)
endif()