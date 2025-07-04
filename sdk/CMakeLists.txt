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

# Include protoc sources (protobuf-generated files)
list(APPEND SDK_SOURCES ${PROTOC_SOURCES})

# Only include gRPC sources on Windows (Linux simpleGL doesn't need gRPC)
if(WIN32)
    set(GRPC_ESSENTIAL_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/grpcsettings.cpp"
    )
    list(APPEND SDK_SOURCES ${GRPC_ESSENTIAL_SOURCES})
endif()

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
        ${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/client
        ${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/converters
    PRIVATE
        # Use third_party headers only on Windows
        $<$<PLATFORM_ID:Windows>:${CMAKE_SOURCE_DIR}/third_party/protobuf/windows/include>
        $<$<PLATFORM_ID:Windows>:${CMAKE_SOURCE_DIR}/third_party/grpc/windows/include>
        $<$<PLATFORM_ID:Windows>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/include>
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
            # UPB libraries (required by gRPC)
            "${GRPC_LIB_DIR}/upb_base_lib.lib"
            "${GRPC_LIB_DIR}/upb_mem_lib.lib"
            "${GRPC_LIB_DIR}/upb_message_lib.lib"
            "${GRPC_LIB_DIR}/upb_mini_descriptor_lib.lib"
            "${GRPC_LIB_DIR}/upb_json_lib.lib"
            "${GRPC_LIB_DIR}/upb_textformat_lib.lib"
            "${GRPC_LIB_DIR}/upb_wire_lib.lib"
            "${GRPC_LIB_DIR}/utf8_range_lib.lib"
            # Protobuf libraries
            "${PROTOBUF_LIB_DIR}/libprotobuf.lib"
            "${PROTOBUF_LIB_DIR}/utf8_range.lib"
            "${PROTOBUF_LIB_DIR}/utf8_validity.lib"
            # Abseil libraries - comprehensive set to resolve all link errors
            # Core libraries
            "${ABSL_LIB_DIR}/absl_base.lib"
            "${ABSL_LIB_DIR}/absl_spinlock_wait.lib"
            "${ABSL_LIB_DIR}/absl_malloc_internal.lib"
            "${ABSL_LIB_DIR}/absl_throw_delegate.lib"
            "${ABSL_LIB_DIR}/absl_raw_logging_internal.lib"
            # String libraries
            "${ABSL_LIB_DIR}/absl_strings.lib"
            "${ABSL_LIB_DIR}/absl_strings_internal.lib"
            "${ABSL_LIB_DIR}/absl_str_format_internal.lib"
            # Random libraries
            "${ABSL_LIB_DIR}/absl_random_distributions.lib"
            "${ABSL_LIB_DIR}/absl_random_internal_platform.lib"
            "${ABSL_LIB_DIR}/absl_random_internal_pool_urbg.lib"
            "${ABSL_LIB_DIR}/absl_random_internal_randen.lib"
            "${ABSL_LIB_DIR}/absl_random_internal_randen_hwaes.lib"
            "${ABSL_LIB_DIR}/absl_random_internal_randen_hwaes_impl.lib"
            "${ABSL_LIB_DIR}/absl_random_internal_randen_slow.lib"
            "${ABSL_LIB_DIR}/absl_random_internal_seed_material.lib"
            "${ABSL_LIB_DIR}/absl_random_seed_gen_exception.lib"
            "${ABSL_LIB_DIR}/absl_random_seed_sequences.lib"
            # Logging libraries
            "${ABSL_LIB_DIR}/absl_log_severity.lib"
            "${ABSL_LIB_DIR}/absl_log_entry.lib"
            "${ABSL_LIB_DIR}/absl_log_flags.lib"
            "${ABSL_LIB_DIR}/absl_log_globals.lib"
            "${ABSL_LIB_DIR}/absl_log_initialize.lib"
            "${ABSL_LIB_DIR}/absl_log_internal_check_op.lib"
            "${ABSL_LIB_DIR}/absl_log_internal_conditions.lib"
            "${ABSL_LIB_DIR}/absl_log_internal_fnmatch.lib"
            "${ABSL_LIB_DIR}/absl_log_internal_format.lib"
            "${ABSL_LIB_DIR}/absl_log_internal_globals.lib"
            "${ABSL_LIB_DIR}/absl_log_internal_log_sink_set.lib"
            "${ABSL_LIB_DIR}/absl_log_internal_message.lib"
            "${ABSL_LIB_DIR}/absl_log_internal_nullguard.lib"
            "${ABSL_LIB_DIR}/absl_log_internal_proto.lib"
            "${ABSL_LIB_DIR}/absl_log_sink.lib"
            "${ABSL_LIB_DIR}/absl_vlog_config_internal.lib"
            # Synchronization libraries
            "${ABSL_LIB_DIR}/absl_synchronization.lib"
            # Time libraries
            "${ABSL_LIB_DIR}/absl_time.lib"
            "${ABSL_LIB_DIR}/absl_time_zone.lib"
            "${ABSL_LIB_DIR}/absl_civil_time.lib"
            # Status libraries
            "${ABSL_LIB_DIR}/absl_status.lib"
            "${ABSL_LIB_DIR}/absl_statusor.lib"
            # Flags libraries
            "${ABSL_LIB_DIR}/absl_flags_commandlineflag.lib"
            "${ABSL_LIB_DIR}/absl_flags_commandlineflag_internal.lib"
            "${ABSL_LIB_DIR}/absl_flags_config.lib"
            "${ABSL_LIB_DIR}/absl_flags_internal.lib"
            "${ABSL_LIB_DIR}/absl_flags_marshalling.lib"
            "${ABSL_LIB_DIR}/absl_flags_parse.lib"
            "${ABSL_LIB_DIR}/absl_flags_private_handle_accessor.lib"
            "${ABSL_LIB_DIR}/absl_flags_program_name.lib"
            "${ABSL_LIB_DIR}/absl_flags_reflection.lib"
            "${ABSL_LIB_DIR}/absl_flags_usage.lib"
            "${ABSL_LIB_DIR}/absl_flags_usage_internal.lib"
            # Container libraries
            "${ABSL_LIB_DIR}/absl_hashtablez_sampler.lib"
            # Cord libraries
            "${ABSL_LIB_DIR}/absl_cord.lib"
            "${ABSL_LIB_DIR}/absl_cord_internal.lib"
            "${ABSL_LIB_DIR}/absl_cordz_functions.lib"
            "${ABSL_LIB_DIR}/absl_cordz_handle.lib"
            "${ABSL_LIB_DIR}/absl_cordz_info.lib"
            "${ABSL_LIB_DIR}/absl_cordz_sample_token.lib"
            # CRC libraries
            "${ABSL_LIB_DIR}/absl_crc32c.lib"
            "${ABSL_LIB_DIR}/absl_crc_cord_state.lib"
            "${ABSL_LIB_DIR}/absl_crc_cpu_detect.lib"
            "${ABSL_LIB_DIR}/absl_crc_internal.lib"
            # Hash libraries
            "${ABSL_LIB_DIR}/absl_hash.lib"
            "${ABSL_LIB_DIR}/absl_city.lib"
            "${ABSL_LIB_DIR}/absl_low_level_hash.lib"
            # Debugging libraries
            "${ABSL_LIB_DIR}/absl_stacktrace.lib"
            "${ABSL_LIB_DIR}/absl_symbolize.lib"
            "${ABSL_LIB_DIR}/absl_debugging_internal.lib"
            "${ABSL_LIB_DIR}/absl_demangle_internal.lib"
            # Numeric libraries
            "${ABSL_LIB_DIR}/absl_int128.lib"
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