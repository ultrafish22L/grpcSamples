cmake_minimum_required(VERSION 3.10)
project(GrpcSamples)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Windows MSVC specific configurations
if(MSVC)
    # Enable parallel compilation for all targets
    add_compile_options(/MP)
    
    # Set warning level
    add_compile_options(/W3)
    
    # Disable specific warnings that are common in third-party code
    add_compile_options(/wd4996)  # Deprecated function warnings
    add_compile_options(/wd4267)  # Size_t conversion warnings
    add_compile_options(/wd4244)  # Type conversion warnings
    
    # Enable proper exception handling
    add_compile_options(/EHsc)
    
    # Set runtime library to static linking (to match third_party libraries)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    
    # Add Windows-specific definitions
    add_compile_definitions(WIN32_LEAN_AND_MEAN NOMINMAX)
endif()

# Enable solution folders in Visual Studio
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set OpenGL preference to avoid warnings
if(POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()
set(OpenGL_GL_PREFERENCE GLVND)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# For multi-config generators (like Visual Studio)
foreach(CONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${CONFIG} CONFIG_UPPER)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG_UPPER} ${CMAKE_SOURCE_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIG_UPPER} ${CMAKE_SOURCE_DIR}/bin)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIG_UPPER} ${CMAKE_SOURCE_DIR}/bin)
endforeach()

# Add third-party libraries that have CMake support and are needed
# Configure GLFW to not build examples, tests, or docs
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE BOOL "Generate installation target")

add_subdirectory(third_party/glew)
add_subdirectory(third_party/glfw)
add_subdirectory(third_party/glm)

# Set folder organization for third-party libraries in Visual Studio
set_target_properties(glfw PROPERTIES FOLDER "ThirdParty")
if(TARGET glm)
    set_target_properties(glm PROPERTIES FOLDER "ThirdParty")
endif()

# SDK folder organization is handled in sdk/CMakeLists.txt

# Generate protobuf files before building SDK
# include(cmake/protobuf_generation.cmake)  # Disabled - using existing protoc files

# Add SDK (Windows only - Linux has protobuf version conflicts)
if(WIN32)
    add_subdirectory(sdk)
else()
    message(STATUS "SDK build disabled on Linux due to protobuf version conflicts")
endif()

# Add main projects
add_subdirectory(simpleGL)
add_subdirectory(simpleGlGrpc)
