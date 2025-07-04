# SDK CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Option to enable gRPC functionality
option(ENABLE_OCTANE_GRPC "Enable Octane gRPC functionality" ON)

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

# Set include directories
target_include_directories(octane_sdk
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/api
        ${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc
)

# Set C++ standard
target_compile_features(octane_sdk PUBLIC cxx_std_17)

# Set folder for Visual Studio organization
set_target_properties(octane_sdk PROPERTIES FOLDER "SDK")

# Add compile definitions if needed
target_compile_definitions(octane_sdk
    PRIVATE
        # Add any necessary definitions here
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