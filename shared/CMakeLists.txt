# SDK CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# shared_lib_base
# Create the shared library
add_library(shared_lib_base STATIC 
    file_dialog.h
    model_loader.h
    model_manager.h
    camera_system.h
    camera_sync_sdk.cpp
    camera_sync_sdk.h
)

# Set include directories
target_include_directories(shared_lib_base
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/third_party/glew/include
        ${CMAKE_SOURCE_DIR}/third_party/glfw/include
        ${CMAKE_SOURCE_DIR}/third_party/glm
)
target_link_directories(shared_lib_base
    PUBLIC
)
# Link with ALL available third-party libraries for comprehensive coverage
target_link_libraries(shared_lib_base
    PUBLIC
        glew
        glfw
        glm
        # Platform-specific OpenGL libraries
        $<$<PLATFORM_ID:Windows>:opengl32.lib>
        $<$<PLATFORM_ID:Linux>:GL>
        $<$<PLATFORM_ID:Darwin>:"-framework OpenGL">

        # Windows-specific system libraries
        $<$<PLATFORM_ID:Windows>:user32>
        $<$<PLATFORM_ID:Windows>:gdi32>
        $<$<PLATFORM_ID:Windows>:shell32>
        $<$<PLATFORM_ID:Windows>:ws2_32>
        $<$<PLATFORM_ID:Windows>:crypt32>
        $<$<PLATFORM_ID:Windows>:advapi32>
        $<$<PLATFORM_ID:Windows>:kernel32>
        
        # Linux-specific system libraries
        $<$<PLATFORM_ID:Linux>:X11>
        $<$<PLATFORM_ID:Linux>:Xrandr>
        $<$<PLATFORM_ID:Linux>:Xinerama>
        $<$<PLATFORM_ID:Linux>:Xcursor>
        $<$<PLATFORM_ID:Linux>:pthread>
        $<$<PLATFORM_ID:Linux>:dl>
        
        # macOS-specific frameworks
        $<$<PLATFORM_ID:Darwin>:-framework Cocoa>
        $<$<PLATFORM_ID:Darwin>:-framework IOKit>
        $<$<PLATFORM_ID:Darwin>:-framework CoreVideo>
)

# Windows MSVC specific configurations
if(MSVC)
    # Enable parallel compilation
    target_compile_options(shared_lib_base PRIVATE /MP)
    
    # Set warning level and disable specific warnings
    target_compile_options(shared_lib_base PRIVATE /W3)
    target_compile_options(shared_lib_base PRIVATE /wd4996)  # Disable deprecated function warnings
    
    # Enable proper exception handling
    target_compile_options(shared_lib_base PRIVATE /EHsc)
    
    # Set runtime library to static (to match third_party libraries)
    set_property(TARGET shared_lib_base PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# Add compile definitions
target_compile_definitions(shared_lib_base
    PUBLIC
        # Platform-specific definitions
        $<$<PLATFORM_ID:Windows>:WIN32_LEAN_AND_MEAN>
        $<$<PLATFORM_ID:Windows>:NOMINMAX>
)

# grpc proto definition files - always process these
get_filename_component(ABS_PROTO_DIR "${CMAKE_CURRENT_SOURCE_DIR}/protos/definitions" ABSOLUTE)
get_filename_component(ABS_PROTO_OUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/protos" ABSOLUTE)
file(GLOB PROTO_FILES "${ABS_PROTO_DIR}/*.proto")
#list(APPEND PROTO_FILES  "${ABS_PROTO_DIR}/protos/camera_control.proto")
#list(APPEND PROTO_FILES  "${ABS_PROTO_DIR}/protos/livelink.proto")

#add_subdirectory(protos)

# Check for gRPC availability
message(STATUS "proto file build")

# Try to use third_party gRPC libraries for Windows
if(WIN32)
    # Windows: Try multiple locations for protoc and grpc_cpp_plugin
    set(PROTOC_EXECUTABLE "${CMAKE_SOURCE_DIR}/../../third_party/protobuf/windows/bin/protoc.exe")
    set(GRPC_CPP_PLUGIN "${CMAKE_SOURCE_DIR}/../../third_party/grpc/windows/bin/grpc_cpp_plugin.exe")
    
    # If not found, try system PATH
    if(NOT PROTOC_EXECUTABLE)
        find_program(PROTOC_EXECUTABLE protoc)
    endif()
    if(NOT GRPC_CPP_PLUGIN)
        find_program(GRPC_CPP_PLUGIN grpc_cpp_plugin)
    endif()
    
    get_filename_component(ABS_PROTO_INC_DIR "${CMAKE_SOURCE_DIR}/../../third_party/protobuf/windows/include" ABSOLUTE)
else()
    # Linux: Use system protoc and grpc_cpp_plugin (if available)
    find_program(PROTOC_EXECUTABLE protoc)
    find_program(GRPC_CPP_PLUGIN grpc_cpp_plugin)
    get_filename_component(ABS_PROTO_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../third_party/protobuf/linux/include" ABSOLUTE)
endif()


if(PROTOC_EXECUTABLE)
    if(GRPC_CPP_PLUGIN)
        message(STATUS "Found protoc: ${PROTOC_EXECUTABLE}")
        message(STATUS "Found grpc_cpp_plugin: ${GRPC_CPP_PLUGIN}")
        message(STATUS "Proto include dir: ${ABS_PROTO_INC_DIR}")
    else()
        message(STATUS "protoc found but grpc_cpp_plugin missing: ${GRPC_CPP_PLUGIN}")
    endif()
else()
    message(STATUS "protoc not found. Searched paths:")
    if(WIN32)
        foreach(PROTOC_PATH ${PROTOC_PATHS})
            message(STATUS "  - ${PROTOC_PATH}")
        endforeach()
    endif()
endif()

# Create generated directory if it doesn't exist
file(MAKE_DIRECTORY ${ABS_PROTO_OUT_DIR})

# Always populate the expected generated file lists
foreach(FIL ${PROTO_FILES})
    get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
    get_filename_component(FIL_PATH ${FIL} PATH)
    get_filename_component(FIL_WE ${FIL} NAME_WE)

    set(PROTO_SRC "${ABS_PROTO_OUT_DIR}/${FIL_WE}.pb.cc")
    set(PROTO_HEADER "${ABS_PROTO_OUT_DIR}/${FIL_WE}.pb.h")
    set(GRPC_SRC "${ABS_PROTO_OUT_DIR}/${FIL_WE}.grpc.pb.cc")
    set(GRPC_HEADER "${ABS_PROTO_OUT_DIR}/${FIL_WE}.grpc.pb.h")

    list(APPEND PROTO_SRCS ${PROTO_SRC} ${PROTO_HEADER})
    list(APPEND GRPC_SRCS ${GRPC_SRC} ${GRPC_HEADER})

    message(STATUS "Setting up protobuf generation for ${FIL_WE}")
    add_custom_command(
        OUTPUT "${PROTO_SRC}" "${PROTO_HEADER}" "${GRPC_SRC}" "${GRPC_HEADER}"
        COMMAND ${PROTOC_EXECUTABLE}
        ARGS --grpc_out="${ABS_PROTO_OUT_DIR}"
                --cpp_out="${ABS_PROTO_OUT_DIR}"
                -I"${ABS_PROTO_DIR}"
                -I"${ABS_PROTO_INC_DIR}"
                --plugin=protoc-gen-grpc="${GRPC_CPP_PLUGIN}"
                "${ABS_FIL}"
        DEPENDS "${ABS_FIL}"
        COMMENT "Generating gRPC files for ${FIL_WE}"
        VERBATIM
    )
    # Add to list of files that need generation
    list(APPEND PROTO_GENERATION_OUTPUTS "${PROTO_SRC}" "${PROTO_HEADER}" "${GRPC_SRC}" "${GRPC_HEADER}")
endforeach()

# Create a custom target for protobuf generation if needed
if(PROTO_GENERATION_OUTPUTS)
    add_custom_target(generate_protos
        DEPENDS ${PROTO_GENERATION_OUTPUTS}
        COMMENT "Generating protobuf files"
    )
endif()

message(STATUS "Proto files: ${PROTO_FILES}")
message(STATUS "PROTO_GENERATION_OUTPUTS ${PROTO_GENERATION_OUTPUTS}")

# shared_lib
set(DO_GRPC_ENABLED ON)
message(STATUS )
# Link with Windows third-party libraries
# Set library directories based on build configuration
set(GRPC_LIB_DIR "${CMAKE_SOURCE_DIR}/third_party/grpc/windows/$<IF:$<CONFIG:Debug>,debug_64,release_64>")
set(PROTOBUF_LIB_DIR "${CMAKE_SOURCE_DIR}/third_party/protobuf/windows/$<IF:$<CONFIG:Debug>,debug_64,release_64>")
set(ABSL_LIB_DIR "${CMAKE_SOURCE_DIR}/third_party/absl/windows/$<IF:$<CONFIG:Debug>,debug_64,release_64>")
set(OPENSSL_LIB_DIR "${CMAKE_SOURCE_DIR}/third_party/openssl/windows/$<IF:$<CONFIG:Debug>,debug_64,release_64>")
set(ZLIB_LIB_DIR "${CMAKE_SOURCE_DIR}/third_party/zlib/win/$<IF:$<CONFIG:Debug>,x64_debug,x64_release>")
set(CARES_LIB_DIR "${CMAKE_SOURCE_DIR}/third_party/cares/windows/$<IF:$<CONFIG:Debug>,debug_64,release_64>")
set(RE2_LIB_DIR "${CMAKE_SOURCE_DIR}/third_party/re2/windows/$<IF:$<CONFIG:Debug>,debug_64,release_64>")
    
# Add CURL library directory
set(CURL_LIB_DIR "${CMAKE_SOURCE_DIR}/third_party/curl/windows/$<IF:$<CONFIG:Debug>,debug_64,release_64>")

# Collect all Shared source files
file(GLOB SHARED_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)
file(GLOB SHARED_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)
list(REMOVE_ITEM SHARED_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/file_dialog.h")
list(REMOVE_ITEM SHARED_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/model_loader.h")
list(REMOVE_ITEM SHARED_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/model_manager.h")
list(REMOVE_ITEM SHARED_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/camera_system.h")
list(REMOVE_ITEM SHARED_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/camera_sync_sdk.h")
list(REMOVE_ITEM SHARED_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/camera_sync_sdk.cpp")

# Always include the expected protobuf generated sources
# These will either exist already or be generated by custom commands
list(APPEND SHARED_SOURCES ${PROTO_SRCS} ${GRPC_SRCS})

# Create the shared library
add_library(shared_lib STATIC ${SHARED_SOURCES} ${SHARED_HEADERS} ${PROTO_FILES} ${PROTO_GENERATION_OUTPUTS})

# Make sure protobuf files are generated before building the library
if(TARGET generate_protos)
    add_dependencies(shared_lib shared_lib_base generate_protos)
endif()
    
# Set include directories
target_include_directories(shared_lib
    PUBLIC
        ${ABS_PROTO_INC_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/protos

        $<$<PLATFORM_ID:Windows>:${CMAKE_SOURCE_DIR}/third_party/protobuf/windows/include>
        $<$<PLATFORM_ID:Windows>:${CMAKE_SOURCE_DIR}/third_party/grpc/windows/include>
        $<$<PLATFORM_ID:Windows>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/include>
        
        # Linux system includes
        $<$<PLATFORM_ID:Linux>:/usr/include>
        $<$<PLATFORM_ID:Linux>:/usr/include/grpcpp>
)
target_link_directories(shared_lib
    PUBLIC
        ${GRPC_LIB_DIR}
)
# Link with ALL available third-party libraries for comprehensive coverage
target_link_libraries(shared_lib
    PUBLIC
        shared_lib_base
)
if (WIN32)
target_link_libraries(shared_lib
    PUBLIC
        # gRPC libraries - ALL available
        "${GRPC_LIB_DIR}/grpc++.lib"
        "${GRPC_LIB_DIR}/grpc.lib"
        "${GRPC_LIB_DIR}/gpr.lib"
        "${GRPC_LIB_DIR}/address_sorting.lib"
        "${GRPC_LIB_DIR}/grpc++_alts.lib"
        "${GRPC_LIB_DIR}/grpc++_error_details.lib"
        "${GRPC_LIB_DIR}/grpc++_reflection.lib"
        "${GRPC_LIB_DIR}/grpc++_unsecure.lib"
        "${GRPC_LIB_DIR}/grpc_unsecure.lib"
        "${GRPC_LIB_DIR}/grpc_authorization_provider.lib"
        "${GRPC_LIB_DIR}/grpc_plugin_support.lib"
        "${GRPC_LIB_DIR}/grpcpp_channelz.lib"
        # UPB libraries (required by gRPC)
        "${GRPC_LIB_DIR}/upb_base_lib.lib"
        "${GRPC_LIB_DIR}/upb_mem_lib.lib"
        "${GRPC_LIB_DIR}/upb_message_lib.lib"
        "${GRPC_LIB_DIR}/upb_mini_descriptor_lib.lib"
        "${GRPC_LIB_DIR}/upb_json_lib.lib"
        "${GRPC_LIB_DIR}/upb_textformat_lib.lib"
        "${GRPC_LIB_DIR}/upb_wire_lib.lib"
        "${GRPC_LIB_DIR}/utf8_range_lib.lib"
        # Protobuf libraries - ALL available
        "${PROTOBUF_LIB_DIR}/libprotobuf.lib"
        "${PROTOBUF_LIB_DIR}/libprotobuf-lite.lib"
        "${PROTOBUF_LIB_DIR}/libprotoc.lib"
        "${PROTOBUF_LIB_DIR}/utf8_range.lib"
        "${PROTOBUF_LIB_DIR}/utf8_validity.lib"
        # Abseil libraries - ALL available for comprehensive coverage
        "${ABSL_LIB_DIR}/absl_bad_any_cast_impl.lib"
        "${ABSL_LIB_DIR}/absl_bad_optional_access.lib"
        "${ABSL_LIB_DIR}/absl_bad_variant_access.lib"
        "${ABSL_LIB_DIR}/absl_base.lib"
        "${ABSL_LIB_DIR}/absl_city.lib"
        "${ABSL_LIB_DIR}/absl_civil_time.lib"
        "${ABSL_LIB_DIR}/absl_cord.lib"
        "${ABSL_LIB_DIR}/absl_cord_internal.lib"
        "${ABSL_LIB_DIR}/absl_cordz_functions.lib"
        "${ABSL_LIB_DIR}/absl_cordz_handle.lib"
        "${ABSL_LIB_DIR}/absl_cordz_info.lib"
        "${ABSL_LIB_DIR}/absl_cordz_sample_token.lib"
        "${ABSL_LIB_DIR}/absl_crc32c.lib"
        "${ABSL_LIB_DIR}/absl_crc_cord_state.lib"
        "${ABSL_LIB_DIR}/absl_crc_cpu_detect.lib"
        "${ABSL_LIB_DIR}/absl_crc_internal.lib"
        "${ABSL_LIB_DIR}/absl_debugging_internal.lib"
        "${ABSL_LIB_DIR}/absl_decode_rust_punycode.lib"
        "${ABSL_LIB_DIR}/absl_demangle_internal.lib"
        "${ABSL_LIB_DIR}/absl_demangle_rust.lib"
        "${ABSL_LIB_DIR}/absl_die_if_null.lib"
        "${ABSL_LIB_DIR}/absl_examine_stack.lib"
        "${ABSL_LIB_DIR}/absl_exponential_biased.lib"
        "${ABSL_LIB_DIR}/absl_failure_signal_handler.lib"
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
        "${ABSL_LIB_DIR}/absl_graphcycles_internal.lib"
        "${ABSL_LIB_DIR}/absl_hash.lib"
        "${ABSL_LIB_DIR}/absl_hashtablez_sampler.lib"
        "${ABSL_LIB_DIR}/absl_int128.lib"
        "${ABSL_LIB_DIR}/absl_kernel_timeout_internal.lib"
        "${ABSL_LIB_DIR}/absl_leak_check.lib"
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
        "${ABSL_LIB_DIR}/absl_log_severity.lib"
        "${ABSL_LIB_DIR}/absl_log_sink.lib"
        "${ABSL_LIB_DIR}/absl_low_level_hash.lib"
        "${ABSL_LIB_DIR}/absl_malloc_internal.lib"
        "${ABSL_LIB_DIR}/absl_periodic_sampler.lib"
        "${ABSL_LIB_DIR}/absl_poison.lib"
        "${ABSL_LIB_DIR}/absl_random_distributions.lib"
        "${ABSL_LIB_DIR}/absl_random_internal_distribution_test_util.lib"
        "${ABSL_LIB_DIR}/absl_random_internal_platform.lib"
        "${ABSL_LIB_DIR}/absl_random_internal_pool_urbg.lib"
        "${ABSL_LIB_DIR}/absl_random_internal_randen.lib"
        "${ABSL_LIB_DIR}/absl_random_internal_randen_hwaes.lib"
        "${ABSL_LIB_DIR}/absl_random_internal_randen_hwaes_impl.lib"
        "${ABSL_LIB_DIR}/absl_random_internal_randen_slow.lib"
        "${ABSL_LIB_DIR}/absl_random_internal_seed_material.lib"
        "${ABSL_LIB_DIR}/absl_random_seed_gen_exception.lib"
        "${ABSL_LIB_DIR}/absl_random_seed_sequences.lib"
        "${ABSL_LIB_DIR}/absl_raw_hash_set.lib"
        "${ABSL_LIB_DIR}/absl_raw_logging_internal.lib"
        "${ABSL_LIB_DIR}/absl_scoped_set_env.lib"
        "${ABSL_LIB_DIR}/absl_spinlock_wait.lib"
        "${ABSL_LIB_DIR}/absl_stacktrace.lib"
        "${ABSL_LIB_DIR}/absl_status.lib"
        "${ABSL_LIB_DIR}/absl_statusor.lib"
        "${ABSL_LIB_DIR}/absl_str_format_internal.lib"
        "${ABSL_LIB_DIR}/absl_strerror.lib"
        "${ABSL_LIB_DIR}/absl_string_view.lib"
        "${ABSL_LIB_DIR}/absl_strings.lib"
        "${ABSL_LIB_DIR}/absl_strings_internal.lib"
        "${ABSL_LIB_DIR}/absl_symbolize.lib"
        "${ABSL_LIB_DIR}/absl_synchronization.lib"
        "${ABSL_LIB_DIR}/absl_throw_delegate.lib"
        "${ABSL_LIB_DIR}/absl_time.lib"
        "${ABSL_LIB_DIR}/absl_time_zone.lib"
        "${ABSL_LIB_DIR}/absl_utf8_for_code_point.lib"
        "${ABSL_LIB_DIR}/absl_vlog_config_internal.lib"
        # OpenSSL libraries
        "${OPENSSL_LIB_DIR}/libssl.lib"
        "${OPENSSL_LIB_DIR}/libcrypto.lib"
        # Other third-party libraries
        "${ZLIB_LIB_DIR}/zlib.lib"
        "${CARES_LIB_DIR}/cares.lib"
        "${RE2_LIB_DIR}/re2.lib"
        "${CURL_LIB_DIR}/libcurl.lib"
)
endif()

# Linux gRPC libraries (when available)
if(UNIX AND NOT APPLE)
    # Only link gRPC libraries if they're available on the system
    find_library(GRPC_GRPCPP_LIB grpc++)
    find_library(GRPC_GRPC_LIB grpc)
    find_library(PROTOBUF_LIB protobuf)
    
    if(GRPC_GRPCPP_LIB AND GRPC_GRPC_LIB AND PROTOBUF_LIB)
        target_link_libraries(shared_lib
            PUBLIC
                ${GRPC_GRPCPP_LIB}
                ${GRPC_GRPC_LIB}
                ${PROTOBUF_LIB}
        )
        message(STATUS "Found and linking system gRPC libraries")
    else()
        message(STATUS "System gRPC libraries not found - building without gRPC support")
    endif()
endif()

# Windows MSVC specific configurations
if(MSVC)
    # Enable parallel compilation
    target_compile_options(shared_lib PRIVATE /MP)
    
    # Set warning level and disable specific warnings
    target_compile_options(shared_lib PRIVATE /W3)
    target_compile_options(shared_lib PRIVATE /wd4996)  # Disable deprecated function warnings
    
    # Enable proper exception handling
    target_compile_options(shared_lib PRIVATE /EHsc)
    
    # Set runtime library to static (to match third_party libraries)
    set_property(TARGET shared_lib PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# Add compile definitions
target_compile_definitions(shared_lib
    PUBLIC
        # Enable GRPC integration 
        DO_GRPC_ENABLED
)
