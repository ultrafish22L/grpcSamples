cmake_minimum_required(VERSION 3.10)
project(GrpcSamples)

# Cross-platform gRPC samples supporting:
# - Windows: Uses third_party prebuilt libraries
# - Linux: Uses system gRPC/protobuf packages
# - macOS: Uses Homebrew gRPC/protobuf packages (brew install grpc protobuf abseil)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(DO_GRPC_ENABLED ON)
set(DO_GRPC_SDK_ENABLED, OFF)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Windows MSVC specific configurations
if(WIN32)
#    add_compile_definitions(DO_GRPC_ENABLED)
#    set(DO_GRPC_SDK_ENABLED ON)
    set(DO_GRPC_SDK_ENABLED OFF)

    # Enable parallel compilation for all targets
    add_compile_options(/MP)
    
    # Set warning level
    add_compile_options(/W3)
    
    # Disable specific warnings that are common in third-party code
    add_compile_options(/wd4996)  # Deprecated function warnings
    add_compile_options(/wd4267)  # Size_t conversion warnings
    add_compile_options(/wd4244)  # Type conversion warnings

    # Ignore warnings about missing pdb
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ignore:4099")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /ignore:4099")
    set(CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} /ignore:4099")

    # Enable proper exception handling
    add_compile_options(/EHsc)
    
    # Set runtime library to static linking (to match third_party libraries)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    
    # Explicitly set runtime library flags to ensure static linking
    # Debug: /MTd (MultiThreaded Debug Static)
    # Release: /MT (MultiThreaded Static)
    
    # Replace any existing /MD flags with /MT flags in CMAKE_CXX_FLAGS
    foreach(flag_var CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
        if(${flag_var} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        endif()
        if(${flag_var} MATCHES "/MDd")
            string(REGEX REPLACE "/MDd" "/MTd" ${flag_var} "${${flag_var}}")
        endif()
    endforeach()
    
    # Force static runtime library flags
    add_compile_options(
        $<$<CONFIG:Debug>:/MTd>
        $<$<CONFIG:Release>:/MT>
        $<$<CONFIG:RelWithDebInfo>:/MT>
        $<$<CONFIG:MinSizeRel>:/MT>
    )
    
    # Add linker flags to ignore conflicting runtime libraries
    add_link_options(
        $<$<CONFIG:Debug>:/NODEFAULTLIB:msvcrt>
        $<$<CONFIG:Debug>:/NODEFAULTLIB:msvcprt>
        $<$<CONFIG:Release>:/NODEFAULTLIB:msvcrtd>
        $<$<CONFIG:Release>:/NODEFAULTLIB:msvcprtd>
    )
    
    # Add Windows-specific definitions
    add_compile_definitions(WIN32_LEAN_AND_MEAN NOMINMAX)
endif()

# Enable solution folders in Visual Studio
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set simpleGL as the default startup project in Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT simpleGlGrpc)

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

# Configure GLFW to use static runtime library (to match our project settings)
if(MSVC)
    set(USE_MSVC_RUNTIME_LIBRARY_DLL OFF CACHE BOOL "Use MSVC runtime library DLL")
endif()

add_subdirectory(third_party/glew)
add_subdirectory(third_party/glfw)
add_subdirectory(third_party/glm)

# Add grpc-web plugin for HTML demos (optional)
# Use the pre-built protoc-gen-grpc-web binary if available, otherwise skip
# The plugin is used to generate JavaScript files from proto definitions
message(STATUS "Checking for grpc-web plugin for HTML demos")

# Check if the pre-built binary exists
set(GRPC_WEB_BINARY "${CMAKE_SOURCE_DIR}/html/protoc-gen-grpc-web")
if(EXISTS "${GRPC_WEB_BINARY}")
    message(STATUS "Found pre-built protoc-gen-grpc-web at: ${GRPC_WEB_BINARY}")
    # Create a custom target that represents the pre-built binary
    add_custom_target(protoc-gen-grpc-web ALL
        COMMENT "Using pre-built protoc-gen-grpc-web binary"
    )
    set(BUILD_GRPC_WEB_PLUGIN ON)
else()
    message(STATUS "Pre-built protoc-gen-grpc-web binary not found - HTML demos will use system protoc")
    message(STATUS "This is normal for Linux builds - C++ applications will build normally")
    set(BUILD_GRPC_WEB_PLUGIN OFF)
endif()

# No additional configuration needed for pre-built binary
# The protoc-gen-grpc-web binary is already available in the html/ directory

# Set folder organization for third-party libraries in Visual Studio
set_target_properties(glew PROPERTIES FOLDER "ThirdParty")
set_target_properties(glfw PROPERTIES FOLDER "ThirdParty")
set_target_properties(glm PROPERTIES FOLDER "ThirdParty")

# Set grpc-web target properties
if(BUILD_GRPC_WEB_PLUGIN AND TARGET protoc-gen-grpc-web)
    set_target_properties(protoc-gen-grpc-web PROPERTIES FOLDER "ThirdParty/grpc-web")
endif()

# common projects
add_subdirectory(shared)
add_subdirectory(sdk)

# Add main projects
add_subdirectory(simpleGL)
add_subdirectory(simpleGlGrpc)
add_subdirectory(simpleGlSdk)
#add_subdirectory(appClient)