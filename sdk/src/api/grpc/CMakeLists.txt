# SDK CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Collect all SDK source files

#[[
file(GLOB SDK_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.*"
)
]]

file(GLOB SDK_CLIENT_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/client/*.*"
)
# Include protoc sources (protobuf-generated files)
list(APPEND SDK_SOURCES ${SDK_CLIENT_SOURCES})


# Collect all existing protoc files (no compilation needed)
file(GLOB_RECURSE PROTOC_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/protoc/*.*"
)

# Include protoc sources (protobuf-generated files)
list(APPEND SDK_SOURCES ${PROTOC_SOURCES})

# Collect all existing converter files 
file(GLOB_RECURSE CONVERTER_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/converter/*.*"
)

# Include converter sources
list(APPEND SDK_SOURCES ${CONVERTER_SOURCES})

# Exclude octanewrappers.cpp if it exists
list(REMOVE_ITEM SDK_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/octanewrappers.cpp")

# Create the SDK library
add_library(octane_sdk STATIC ${SDK_SOURCES})

# Set include directories
target_include_directories(octane_sdk
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/client
        ${CMAKE_CURRENT_SOURCE_DIR}/protoc
        ${CMAKE_CURRENT_SOURCE_DIR}/converters
#        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../../..

        $<$<PLATFORM_ID:Windows>:${CMAKE_SOURCE_DIR}/../third_party/protobuf/windows/include>
        $<$<PLATFORM_ID:Windows>:${CMAKE_SOURCE_DIR}/../third_party/grpc/windows/include>
        $<$<PLATFORM_ID:Windows>:${CMAKE_SOURCE_DIR}/../third_party/absl/windows/include>
)

# Set C++ standard
target_compile_features(octane_sdk PUBLIC cxx_std_17)

# Add Windows-specific compiler flags
if(WIN32 AND MSVC)
    target_compile_options(octane_sdk PRIVATE /bigobj)
endif()

# Windows MSVC specific configurations
if(MSVC)
    # Enable parallel compilation
    target_compile_options(octane_sdk PRIVATE /MP)
    
    # Set warning level and disable specific warnings
    target_compile_options(octane_sdk PRIVATE /W3)
    target_compile_options(octane_sdk PRIVATE /wd4996)  # Disable deprecated function warnings
    
    # Enable proper exception handling
    target_compile_options(octane_sdk PRIVATE /EHsc)
    
    # Set runtime library to static (to match third_party libraries)
    set_property(TARGET octane_sdk PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
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

# Platform-specific library linking
if(WIN32 AND MSVC)
    # Windows-specific library linking
    # Link with octane_standalone.lib
    target_link_libraries(octane_sdk
        PUBLIC
            shared_lib
            "${CMAKE_CURRENT_SOURCE_DIR}/../../../octane_standalone.lib"
    )
    message(STATUS "Windows MSVC SDK with octane_standalone.lib configured")

elseif(APPLE)
    # macOS: Use ALL available third_party libraries
    file(GLOB MACOS_GRPC_LIBS "${CMAKE_SOURCE_DIR}/third_party/grpc/macos/*.a")
    file(GLOB MACOS_PROTOBUF_LIBS "${CMAKE_SOURCE_DIR}/third_party/protobuf/macos/*.a")
    file(GLOB MACOS_ABSL_LIBS "${CMAKE_SOURCE_DIR}/third_party/absl/macos/*.a")
    file(GLOB MACOS_OPENSSL_LIBS "${CMAKE_SOURCE_DIR}/third_party/openssl/macos/*.a")
    file(GLOB MACOS_ZLIB_LIBS "${CMAKE_SOURCE_DIR}/third_party/zlib/macos/*.a")
    target_link_libraries(octane_sdk
        PRIVATE
            ${MACOS_GRPC_LIBS}
            ${MACOS_PROTOBUF_LIBS}
            ${MACOS_ABSL_LIBS}
            ${MACOS_OPENSSL_LIBS}
            ${MACOS_ZLIB_LIBS}
    )
    target_compile_definitions(octane_sdk
        PUBLIC
            OCTANE_SDK_ENABLED
    )
else()
    # Linux: Use ALL available third_party libraries
    file(GLOB LINUX_GRPC_LIBS "${CMAKE_SOURCE_DIR}/third_party/grpc/linux/*.a")
    file(GLOB LINUX_PROTOBUF_LIBS "${CMAKE_SOURCE_DIR}/third_party/protobuf/linux/*.a")
    file(GLOB LINUX_ABSL_LIBS "${CMAKE_SOURCE_DIR}/third_party/absl/linux/*.a")
    file(GLOB LINUX_OPENSSL_LIBS "${CMAKE_SOURCE_DIR}/third_party/openssl/linux/*.a")
    file(GLOB LINUX_ZLIB_LIBS "${CMAKE_SOURCE_DIR}/third_party/zlib/linux/*.a")
    target_link_libraries(octane_sdk
        PRIVATE
            ${LINUX_GRPC_LIBS}
            ${LINUX_PROTOBUF_LIBS}
            ${LINUX_ABSL_LIBS}
            ${LINUX_OPENSSL_LIBS}
            ${LINUX_ZLIB_LIBS}
            # Linux system libraries
            pthread dl
    )
    target_compile_definitions(octane_sdk
        PUBLIC
            OCTANE_SDK_ENABLED
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