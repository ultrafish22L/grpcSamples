# SDK CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Option to enable gRPC functionality (disabled by default until libraries are available)
option(ENABLE_OCTANE_GRPC "Enable Octane gRPC functionality" OFF)

# Collect all source files, excluding gRPC-dependent files for now
file(GLOB SDK_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

file(GLOB SDK_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

# Collect gRPC-dependent files
file(GLOB_RECURSE GRPC_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/*.cpp"
)

# Include or exclude gRPC sources based on option
if(ENABLE_OCTANE_GRPC)
    # Include gRPC sources
    list(APPEND SDK_SOURCES ${GRPC_SOURCES})
    message(STATUS "Octane gRPC functionality enabled")
else()
    # Remove gRPC sources from the main source list
    list(REMOVE_ITEM SDK_SOURCES ${GRPC_SOURCES})
    message(STATUS "Octane gRPC functionality disabled")
endif()

# Also exclude octanewrappers.cpp
list(REMOVE_ITEM SDK_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/octanewrappers.cpp")

# Create the SDK library
add_library(octane_sdk STATIC ${SDK_SOURCES} ${SDK_HEADERS})

# Add dependency on protobuf generation if it exists
if(TARGET protobuf_all)
    add_dependencies(octane_sdk protobuf_all)
endif()

# Set include directories
target_include_directories(octane_sdk
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/api
        ${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc
        ${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/protoc
)

# Set C++ standard
target_compile_features(octane_sdk PUBLIC cxx_std_17)

# Windows MSVC specific configurations
if(MSVC)
    # Enable parallel compilation
    target_compile_options(octane_sdk PRIVATE /MP)
    
    # Set warning level and disable specific warnings
    target_compile_options(octane_sdk PRIVATE /W3)
    target_compile_options(octane_sdk PRIVATE /wd4996)  # Disable deprecated function warnings
    
    # Enable proper exception handling
    target_compile_options(octane_sdk PRIVATE /EHsc)
    
    # Set runtime library to match project settings
    set_property(TARGET octane_sdk PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

# Set folder for Visual Studio organization
set_target_properties(octane_sdk PROPERTIES FOLDER "SDK")

# Add compile definitions
target_compile_definitions(octane_sdk
    PRIVATE
        # Windows-specific definitions
        $<$<PLATFORM_ID:Windows>:WIN32_LEAN_AND_MEAN>
        $<$<PLATFORM_ID:Windows>:NOMINMAX>
        # Add any other necessary definitions here
)

# Add gRPC-specific definitions when enabled
if(ENABLE_OCTANE_GRPC)
    target_compile_definitions(octane_sdk
        PUBLIC
            OCTANE_GRPC_ENABLED
    )
endif()

# Set output directory
set_target_properties(octane_sdk PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_SOURCE_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_SOURCE_DIR}/bin
)