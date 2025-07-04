cmake_minimum_required(VERSION 3.10)

# Define the simpleGlGrpc project
project(simpleGlGrpc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Check for gRPC availability - prefer third_party, fallback to system
set(GRPC_AVAILABLE OFF)

# Try to use third_party gRPC libraries for Windows
if(WIN32)
    set(GRPC_LIB_DIR "${CMAKE_SOURCE_DIR}/third_party/grpc/windows/$<IF:$<CONFIG:Debug>,debug_64,release_64>")
    set(GRPC_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/third_party/grpc/windows/include")
    
    if(EXISTS "${CMAKE_SOURCE_DIR}/third_party/grpc/windows/include")
        set(GRPC_AVAILABLE ON)
        set(GRPC_LIBRARIES
            "${GRPC_LIB_DIR}/grpc++.lib"
            "${GRPC_LIB_DIR}/grpc.lib"
            "${GRPC_LIB_DIR}/gpr.lib"
            "${GRPC_LIB_DIR}/address_sorting.lib"
            "${GRPC_LIB_DIR}/upb_base_lib.lib"
            "${GRPC_LIB_DIR}/upb_message_lib.lib"
            "${GRPC_LIB_DIR}/upb_mem_lib.lib"
            "${GRPC_LIB_DIR}/upb_textformat_lib.lib"
            "${GRPC_LIB_DIR}/upb_json_lib.lib"
            "${GRPC_LIB_DIR}/upb_wire_lib.lib"
            "${GRPC_LIB_DIR}/upb_mini_descriptor_lib.lib"
            "${GRPC_LIB_DIR}/utf8_range_lib.lib"
        )
        message(STATUS "simpleGlGrpc: Using third_party gRPC libraries")
    endif()
endif()

# No system gRPC fallback - only use third_party libraries

if(GRPC_AVAILABLE)
    message(STATUS "simpleGlGrpc: gRPC functionality enabled")
else()
    message(STATUS "simpleGlGrpc: gRPC functionality disabled (libraries not found)")
endif()

# gRPC header files (simplified - removed problematic SDK-dependent files)
set(GRPC_HEADERS
    grpc_camera_sync.h
    octane_camera_sync.h
)

# Source files for all executables (simplified - removed problematic SDK-dependent files)
set(COMMON_SOURCES
    grpc_camera_sync.cpp
    octane_camera_sync.cpp
    grpc_settings.cpp
    # Add generated protobuf files for camera control
    generated/camera_control.pb.cc
    generated/camera_control.grpc.pb.cc
)

# Create the main executable with direct gRPC integration
add_executable(simpleGlGrpc
    main.cpp
    ${COMMON_SOURCES}
)

# Create a demo executable
add_executable(simpleGlGrpc_demo
    demo.cpp
    ${COMMON_SOURCES}
)

# Create a test executable
add_executable(simpleGlGrpc_test
    test_gl.cpp
    ${COMMON_SOURCES}
)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Function to configure a target
function(configure_simpleGlGrpc_target target_name)
    # Include directories
    target_include_directories(${target_name}
        PRIVATE
            ${CMAKE_SOURCE_DIR}/third_party/glew/include
            ${CMAKE_SOURCE_DIR}/third_party/glfw/include
            ${CMAKE_SOURCE_DIR}/third_party/glm
            ${CMAKE_SOURCE_DIR}/sdk
            ${CMAKE_SOURCE_DIR}/sdk/src/api/grpc/protodef
            ${CMAKE_SOURCE_DIR}/sdk/src/api/grpc/protoc
            ${CMAKE_SOURCE_DIR}/sdk/src/api/grpc
            ${CMAKE_SOURCE_DIR}/sdk/src/api/grpc/client
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/generated
            # Add third_party protobuf, gRPC, and absl headers for all platforms
            ${CMAKE_SOURCE_DIR}/third_party/protobuf/windows/include
            ${CMAKE_SOURCE_DIR}/third_party/grpc/windows/include
            ${CMAKE_SOURCE_DIR}/third_party/absl/windows/include
    )
    
    # Add dependency on protobuf generation
    if(TARGET protobuf_all)
        add_dependencies(${target_name} protobuf_all)
    endif()

    # Add gRPC include directories if available
    if(GRPC_AVAILABLE)
        target_include_directories(${target_name}
            PRIVATE
                ${GRPC_INCLUDE_DIR}
        )
        
        # Add compile definition for gRPC support
        target_compile_definitions(${target_name}
            PRIVATE
                GRPC_ENABLED
        )
    endif()

    # Link libraries
    target_link_libraries(${target_name}
        PRIVATE
            octane_sdk
            glew
            glfw
            glm
            ${OPENGL_LIBRARIES}
            # Windows-specific system libraries
            $<$<PLATFORM_ID:Windows>:user32>
            $<$<PLATFORM_ID:Windows>:gdi32>
            $<$<PLATFORM_ID:Windows>:shell32>
    )
    
    # Add gRPC libraries if available
    if(GRPC_AVAILABLE)
        if(WIN32)
            # Windows: Use third_party libraries
            target_link_libraries(${target_name}
                PRIVATE
                    # gRPC libraries
                    ${CMAKE_SOURCE_DIR}/third_party/grpc/windows/release_64/grpc++.lib
                    ${CMAKE_SOURCE_DIR}/third_party/grpc/windows/release_64/grpc.lib
                    ${CMAKE_SOURCE_DIR}/third_party/grpc/windows/release_64/gpr.lib
                    ${CMAKE_SOURCE_DIR}/third_party/grpc/windows/release_64/address_sorting.lib
                    # UPB libraries (required by gRPC)
                    ${CMAKE_SOURCE_DIR}/third_party/grpc/windows/release_64/upb_base_lib.lib
                    ${CMAKE_SOURCE_DIR}/third_party/grpc/windows/release_64/upb_mem_lib.lib
                    ${CMAKE_SOURCE_DIR}/third_party/grpc/windows/release_64/upb_message_lib.lib
                    ${CMAKE_SOURCE_DIR}/third_party/grpc/windows/release_64/upb_mini_descriptor_lib.lib
                    ${CMAKE_SOURCE_DIR}/third_party/grpc/windows/release_64/upb_json_lib.lib
                    ${CMAKE_SOURCE_DIR}/third_party/grpc/windows/release_64/upb_textformat_lib.lib
                    ${CMAKE_SOURCE_DIR}/third_party/grpc/windows/release_64/upb_wire_lib.lib
                    ${CMAKE_SOURCE_DIR}/third_party/grpc/windows/release_64/utf8_range_lib.lib
                    # Protobuf libraries
                    ${CMAKE_SOURCE_DIR}/third_party/protobuf/windows/release_64/libprotobuf.lib
                    ${CMAKE_SOURCE_DIR}/third_party/protobuf/windows/release_64/utf8_range.lib
                    ${CMAKE_SOURCE_DIR}/third_party/protobuf/windows/release_64/utf8_validity.lib
                    # Absl libraries - comprehensive set to resolve all link errors
                    # Core libraries
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_base.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_spinlock_wait.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_malloc_internal.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_throw_delegate.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_raw_logging_internal.lib
                    # String libraries
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_strings.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_strings_internal.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_str_format_internal.lib
                    # Random libraries
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_random_distributions.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_random_internal_platform.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_random_internal_pool_urbg.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_random_internal_randen.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_random_internal_randen_hwaes.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_random_internal_randen_hwaes_impl.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_random_internal_randen_slow.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_random_internal_seed_material.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_random_seed_gen_exception.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_random_seed_sequences.lib
                    # Logging libraries
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_log_severity.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_log_entry.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_log_flags.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_log_globals.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_log_initialize.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_log_internal_check_op.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_log_internal_conditions.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_log_internal_fnmatch.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_log_internal_format.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_log_internal_globals.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_log_internal_log_sink_set.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_log_internal_message.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_log_internal_nullguard.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_log_internal_proto.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_log_sink.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_vlog_config_internal.lib
                    # Synchronization libraries
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_synchronization.lib
                    # Time libraries
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_time.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_time_zone.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_civil_time.lib
                    # Status libraries
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_status.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_statusor.lib
                    # Flags libraries
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_flags_commandlineflag.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_flags_commandlineflag_internal.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_flags_config.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_flags_internal.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_flags_marshalling.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_flags_parse.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_flags_private_handle_accessor.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_flags_program_name.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_flags_reflection.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_flags_usage.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_flags_usage_internal.lib
                    # Container libraries
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_hashtablez_sampler.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_raw_hash_set.lib
                    # Cord libraries
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_cord.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_cord_internal.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_cordz_functions.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_cordz_handle.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_cordz_info.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_cordz_sample_token.lib
                    # CRC libraries
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_crc32c.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_crc_cord_state.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_crc_cpu_detect.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_crc_internal.lib
                    # Hash libraries
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_hash.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_city.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_low_level_hash.lib
                    # Debugging libraries
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_stacktrace.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_symbolize.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_debugging_internal.lib
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_demangle_internal.lib
                    # Numeric libraries
                    ${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_int128.lib
                    # OpenSSL libraries
                    ${CMAKE_SOURCE_DIR}/third_party/openssl/windows/release_64/libssl.lib
                    ${CMAKE_SOURCE_DIR}/third_party/openssl/windows/release_64/libcrypto.lib
                    # Zlib library
                    ${CMAKE_SOURCE_DIR}/third_party/zlib/win/x64_release/zlib.lib
                    # Windows system libraries
                    ws2_32 crypt32
            )
        else()
            # Linux: Use system libraries
            target_link_libraries(${target_name}
                PRIVATE
                    ${GRPC_LIBRARIES}
                    protobuf
            )
        endif()
    endif()
    
    # Set Visual Studio folder organization
    set_target_properties(${target_name} PROPERTIES FOLDER "Applications")

    # Set working directory for debugging in Visual Studio
    set_target_properties(${target_name} PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
    )

    # Windows MSVC specific configurations
    if(MSVC)
        # Set subsystem to console
        set_target_properties(${target_name} PROPERTIES
            LINK_FLAGS "/SUBSYSTEM:CONSOLE"
        )
        
        # Set runtime library to match third_party libraries (static runtime)
        set_property(TARGET ${target_name} PROPERTY
            MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
        
        # Add /bigobj flag for large object files
        target_compile_options(${target_name} PRIVATE /bigobj)
    endif()
endfunction()

# Configure all targets
configure_simpleGlGrpc_target(simpleGlGrpc)
configure_simpleGlGrpc_target(simpleGlGrpc_demo)
configure_simpleGlGrpc_target(simpleGlGrpc_test)

# gRPC functionality is provided by third_party libraries only
# No system gRPC dependencies
