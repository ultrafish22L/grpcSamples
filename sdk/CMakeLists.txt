# SDK CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Collect all SDK source files
file(GLOB SDK_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

file(GLOB SDK_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

# Collect all existing protoc files (no compilation needed)
file(GLOB_RECURSE PROTOC_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/protoc/*.cc"
)

# Include all protoc sources
list(APPEND SDK_SOURCES ${PROTOC_SOURCES})

# Exclude octanewrappers.cpp if it exists
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
        ${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/protoc
    PRIVATE
        # Use third_party protobuf, gRPC, and absl headers for all platforms
        ${CMAKE_SOURCE_DIR}/third_party/protobuf/windows/include
        ${CMAKE_SOURCE_DIR}/third_party/grpc/windows/include
        ${CMAKE_SOURCE_DIR}/third_party/absl/windows/include
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

# Platform-specific library linking
if(WIN32 AND MSVC)
    # Windows-specific library linking
    # Link with octane_standalone.lib
    target_link_libraries(octane_sdk
        PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/octane_standalone.lib"
    )
    
    # Link with Windows third-party libraries
    # Set library directories based on build configuration
    set(GRPC_LIB_DIR "${CMAKE_SOURCE_DIR}/third_party/grpc/windows/$<IF:$<CONFIG:Debug>,debug_64,release_64>")
    set(PROTOBUF_LIB_DIR "${CMAKE_SOURCE_DIR}/third_party/protobuf/windows/$<IF:$<CONFIG:Debug>,debug_64,release_64>")
    set(ABSL_LIB_DIR "${CMAKE_SOURCE_DIR}/third_party/absl/windows/$<IF:$<CONFIG:Debug>,debug_64,release_64>")
    set(OPENSSL_LIB_DIR "${CMAKE_SOURCE_DIR}/third_party/openssl/windows/$<IF:$<CONFIG:Debug>,debug_64,release_64>")
    set(ZLIB_LIB_DIR "${CMAKE_SOURCE_DIR}/third_party/zlib/win/$<IF:$<CONFIG:Debug>,x64_debug,x64_release>")
    set(CARES_LIB_DIR "${CMAKE_SOURCE_DIR}/third_party/cares/windows/$<IF:$<CONFIG:Debug>,debug_64,release_64>")
    set(RE2_LIB_DIR "${CMAKE_SOURCE_DIR}/third_party/re2/windows/$<IF:$<CONFIG:Debug>,debug_64,release_64>")
    
    # Add include directories for Windows libraries
    target_include_directories(octane_sdk
        PRIVATE
            "${CMAKE_SOURCE_DIR}/third_party/grpc/windows/include"
            "${CMAKE_SOURCE_DIR}/third_party/protobuf/windows/include"
    )
    
    # Link with all required third-party libraries
    target_link_libraries(octane_sdk
        PRIVATE
            # gRPC libraries
            "${GRPC_LIB_DIR}/grpc++.lib"
            "${GRPC_LIB_DIR}/grpc.lib"
            "${GRPC_LIB_DIR}/gpr.lib"
            "${GRPC_LIB_DIR}/address_sorting.lib"
            "${GRPC_LIB_DIR}/upb_json_lib.lib"
            "${GRPC_LIB_DIR}/upb_mini_descriptor_lib.lib"
            # Protobuf libraries
            "${PROTOBUF_LIB_DIR}/libprotobuf.lib"
            "${PROTOBUF_LIB_DIR}/utf8_range.lib"
            "${PROTOBUF_LIB_DIR}/utf8_validity.lib"
            # Abseil libraries
            "${ABSL_LIB_DIR}/absl_strings.lib"
            "${ABSL_LIB_DIR}/absl_base.lib"
            "${ABSL_LIB_DIR}/absl_synchronization.lib"
            "${ABSL_LIB_DIR}/absl_time.lib"
            "${ABSL_LIB_DIR}/absl_status.lib"
            "${ABSL_LIB_DIR}/absl_statusor.lib"
            "${ABSL_LIB_DIR}/absl_strings_internal.lib"
            "${ABSL_LIB_DIR}/absl_throw_delegate.lib"
            "${ABSL_LIB_DIR}/absl_raw_logging_internal.lib"
            "${ABSL_LIB_DIR}/absl_log_severity.lib"
            "${ABSL_LIB_DIR}/absl_spinlock_wait.lib"
            "${ABSL_LIB_DIR}/absl_malloc_internal.lib"
            "${ABSL_LIB_DIR}/absl_time_zone.lib"
            "${ABSL_LIB_DIR}/absl_civil_time.lib"
            "${ABSL_LIB_DIR}/absl_int128.lib"
            "${ABSL_LIB_DIR}/absl_cord.lib"
            "${ABSL_LIB_DIR}/absl_cord_internal.lib"
            "${ABSL_LIB_DIR}/absl_cordz_functions.lib"
            "${ABSL_LIB_DIR}/absl_cordz_handle.lib"
            "${ABSL_LIB_DIR}/absl_cordz_info.lib"
            "${ABSL_LIB_DIR}/absl_hash.lib"
            "${ABSL_LIB_DIR}/absl_city.lib"
            "${ABSL_LIB_DIR}/absl_low_level_hash.lib"
            # OpenSSL libraries
            "${OPENSSL_LIB_DIR}/libssl.lib"
            "${OPENSSL_LIB_DIR}/libcrypto.lib"
            # Other libraries
            "${ZLIB_LIB_DIR}/zlib.lib"
            "${CARES_LIB_DIR}/cares.lib"
            "${RE2_LIB_DIR}/re2.lib"
            # Windows system libraries
            ws2_32.lib
            crypt32.lib
            advapi32.lib
            user32.lib
            kernel32.lib
    )
    
    # Add compile definitions for SDK functionality
    target_compile_definitions(octane_sdk
        PUBLIC
            OCTANE_SDK_ENABLED
            OCTANE_GRPC_ENABLED
    )
    
    message(STATUS "Windows MSVC SDK with octane_standalone.lib configured")
else()
    # Linux/other platforms - use third_party headers but no libraries (will have link errors)
    # Add compile definitions for SDK functionality
    target_compile_definitions(octane_sdk
        PUBLIC
            OCTANE_SDK_ENABLED
            OCTANE_GRPC_ENABLED
    )
    
    message(STATUS "Linux/other platform SDK configured with third_party headers (will have link errors without libraries)")
endif()

# Set output directory
set_target_properties(octane_sdk PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_SOURCE_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_SOURCE_DIR}/bin
)