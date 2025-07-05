cmake_minimum_required(VERSION 3.10)

# Define the simpleGlGrpc project
project(simpleGlGrpc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Check for gRPC availability
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
else()
    # Linux: Disable gRPC functionality due to protobuf version conflicts
    message(STATUS "simpleGlGrpc: gRPC functionality disabled on Linux due to protobuf version conflicts")
    set(GRPC_AVAILABLE OFF)
endif()

if(GRPC_AVAILABLE)
    message(STATUS "simpleGlGrpc: gRPC functionality enabled")
    
    # Generate protobuf and gRPC files if they don't exist
    set(PROTO_FILE "${CMAKE_CURRENT_SOURCE_DIR}/camera_control.proto")
    set(GENERATED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/generated")
    set(PROTOBUF_GENERATED_FILES
        "${GENERATED_DIR}/camera_control.pb.h"
        "${GENERATED_DIR}/camera_control.pb.cc"
    )
    set(GRPC_GENERATED_FILES
        "${GENERATED_DIR}/camera_control.grpc.pb.h"
        "${GENERATED_DIR}/camera_control.grpc.pb.cc"
    )
    
    # Create generated directory if it doesn't exist
    file(MAKE_DIRECTORY ${GENERATED_DIR})
    
    if(WIN32)
        # Windows: Use third_party protoc and grpc_cpp_plugin
        set(PROTOC_EXECUTABLE "${CMAKE_SOURCE_DIR}/third_party/protobuf/windows/bin/protoc.exe")
        set(GRPC_CPP_PLUGIN "${CMAKE_SOURCE_DIR}/third_party/grpc/windows/bin/grpc_cpp_plugin.exe")
        
        # Generate protobuf files
        add_custom_command(
            OUTPUT ${PROTOBUF_GENERATED_FILES}
            COMMAND ${PROTOC_EXECUTABLE}
            ARGS --cpp_out=${GENERATED_DIR}
                 --proto_path=${CMAKE_CURRENT_SOURCE_DIR}
                 ${PROTO_FILE}
            DEPENDS ${PROTO_FILE}
            COMMENT "Generating protobuf files with ${PROTOC_EXECUTABLE}"
            VERBATIM
        )
        
        # Generate gRPC files
        add_custom_command(
            OUTPUT ${GRPC_GENERATED_FILES}
            COMMAND ${PROTOC_EXECUTABLE}
            ARGS --grpc_out=${GENERATED_DIR}
                 --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN}
                 --proto_path=${CMAKE_CURRENT_SOURCE_DIR}
                 ${PROTO_FILE}
            DEPENDS ${PROTO_FILE}
            COMMENT "Generating gRPC files with ${GRPC_CPP_PLUGIN}"
            VERBATIM
        )
        
        # Create a target for all generated files
        add_custom_target(generate_grpc_files
            DEPENDS ${PROTOBUF_GENERATED_FILES} ${GRPC_GENERATED_FILES}
        )
    else()
        # Linux: Use system protoc and grpc_cpp_plugin (if available)
        find_program(PROTOC_EXECUTABLE protoc)
        find_program(GRPC_CPP_PLUGIN grpc_cpp_plugin)
        
        if(PROTOC_EXECUTABLE)
            # Generate protobuf files
            add_custom_command(
                OUTPUT ${PROTOBUF_GENERATED_FILES}
                COMMAND ${PROTOC_EXECUTABLE}
                ARGS --cpp_out=${GENERATED_DIR}
                     --proto_path=${CMAKE_CURRENT_SOURCE_DIR}
                     ${PROTO_FILE}
                DEPENDS ${PROTO_FILE}
                COMMENT "Generating protobuf files"
                VERBATIM
            )
            
            # Generate gRPC files if plugin is available
            if(GRPC_CPP_PLUGIN)
                add_custom_command(
                    OUTPUT ${GRPC_GENERATED_FILES}
                    COMMAND ${PROTOC_EXECUTABLE}
                    ARGS --grpc_out=${GENERATED_DIR}
                         --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN}
                         --proto_path=${CMAKE_CURRENT_SOURCE_DIR}
                         ${PROTO_FILE}
                    DEPENDS ${PROTO_FILE}
                    COMMENT "Generating gRPC files"
                    VERBATIM
                )
                
                # Create a target for all generated files
                add_custom_target(generate_grpc_files
                    DEPENDS ${PROTOBUF_GENERATED_FILES} ${GRPC_GENERATED_FILES}
                )
            else()
                # Create a target for protobuf files only
                add_custom_target(generate_grpc_files
                    DEPENDS ${PROTOBUF_GENERATED_FILES}
                )
            endif()
        endif()
    endif()
else()
    message(STATUS "simpleGlGrpc: gRPC functionality disabled (libraries not found)")
endif()

# gRPC header files (simplified - removed problematic SDK-dependent files)
set(GRPC_HEADERS
    grpc_camera_sync.h
    octane_camera_sync.h
)

# Source files for all executables
set(COMMON_SOURCES
    grpc_camera_sync.cpp
    grpc_settings.cpp
)

# Add generated protobuf files if gRPC is available
if(GRPC_AVAILABLE)
    list(APPEND COMMON_SOURCES
        generated/camera_control.pb.cc
    )
    
    # Add gRPC files if plugin is available
    if(GRPC_CPP_PLUGIN)
        list(APPEND COMMON_SOURCES
            generated/camera_control.grpc.pb.cc
        )
    endif()
endif()

# Add SDK-dependent files only on Windows
if(WIN32)
    list(APPEND COMMON_SOURCES octane_camera_sync.cpp)
endif()

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
            # Only include SDK headers on Windows due to protobuf version conflicts on Linux
            $<$<PLATFORM_ID:Windows>:${CMAKE_SOURCE_DIR}/sdk>
            $<$<PLATFORM_ID:Windows>:${CMAKE_SOURCE_DIR}/sdk/src/api/grpc/protodef>
            $<$<PLATFORM_ID:Windows>:${CMAKE_SOURCE_DIR}/sdk/src/api/grpc/protoc>
            $<$<PLATFORM_ID:Windows>:${CMAKE_SOURCE_DIR}/sdk/src/api/grpc>
            $<$<PLATFORM_ID:Windows>:${CMAKE_SOURCE_DIR}/sdk/src/api/grpc/client>
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/generated
            # Add third_party headers for Windows
            $<$<PLATFORM_ID:Windows>:${CMAKE_SOURCE_DIR}/third_party/protobuf/windows/include>
            $<$<PLATFORM_ID:Windows>:${CMAKE_SOURCE_DIR}/third_party/grpc/windows/include>
            $<$<PLATFORM_ID:Windows>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/include>
    )
    
    # Add dependency on protobuf generation
    if(TARGET protobuf_all)
        add_dependencies(${target_name} protobuf_all)
    endif()
    
    # Add dependency on gRPC file generation
    if(TARGET generate_grpc_files)
        add_dependencies(${target_name} generate_grpc_files)
    endif()

    # Add gRPC include directories if available
    if(GRPC_AVAILABLE)
        if(WIN32)
            target_include_directories(${target_name}
                PRIVATE
                    ${GRPC_INCLUDE_DIR}
            )
        else()
            # Linux: Add system gRPC include directories
            target_include_directories(${target_name}
                PRIVATE
                    ${GRPC_INCLUDE_DIRS}
            )
        endif()
        
        # Add compile definition for gRPC support
        target_compile_definitions(${target_name}
            PRIVATE
                GRPC_ENABLED
        )
    endif()

    # Link libraries
    target_link_libraries(${target_name}
        PRIVATE
            # Only link octane_sdk on Windows due to protobuf version conflicts on Linux
            $<$<PLATFORM_ID:Windows>:octane_sdk>
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
            # Windows: Use third_party libraries (configuration-specific)
            target_link_libraries(${target_name}
                PRIVATE
                    # gRPC libraries
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/grpc/windows/debug_64/grpc++.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/grpc/windows/release_64/grpc++.lib>
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/grpc/windows/debug_64/grpc.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/grpc/windows/release_64/grpc.lib>
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/grpc/windows/debug_64/gpr.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/grpc/windows/release_64/gpr.lib>
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/grpc/windows/debug_64/address_sorting.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/grpc/windows/release_64/address_sorting.lib>
                    # UPB libraries (required by gRPC)
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/grpc/windows/debug_64/upb_base_lib.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/grpc/windows/release_64/upb_base_lib.lib>
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/grpc/windows/debug_64/upb_mem_lib.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/grpc/windows/release_64/upb_mem_lib.lib>
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/grpc/windows/debug_64/upb_message_lib.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/grpc/windows/release_64/upb_message_lib.lib>
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/grpc/windows/debug_64/upb_mini_descriptor_lib.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/grpc/windows/release_64/upb_mini_descriptor_lib.lib>
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/grpc/windows/debug_64/upb_json_lib.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/grpc/windows/release_64/upb_json_lib.lib>
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/grpc/windows/debug_64/upb_textformat_lib.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/grpc/windows/release_64/upb_textformat_lib.lib>
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/grpc/windows/debug_64/upb_wire_lib.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/grpc/windows/release_64/upb_wire_lib.lib>
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/grpc/windows/debug_64/utf8_range_lib.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/grpc/windows/release_64/utf8_range_lib.lib>
                    # Protobuf libraries
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/protobuf/windows/debug_64/libprotobuf.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/protobuf/windows/release_64/libprotobuf.lib>
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/protobuf/windows/debug_64/utf8_range.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/protobuf/windows/release_64/utf8_range.lib>
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/protobuf/windows/debug_64/utf8_validity.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/protobuf/windows/release_64/utf8_validity.lib>
                    # Absl libraries - comprehensive set to resolve all link errors (configuration-specific)
                    # Core libraries
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/debug_64/absl_base.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_base.lib>
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/debug_64/absl_spinlock_wait.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_spinlock_wait.lib>
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/debug_64/absl_malloc_internal.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_malloc_internal.lib>
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/debug_64/absl_throw_delegate.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_throw_delegate.lib>
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/debug_64/absl_raw_logging_internal.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_raw_logging_internal.lib>
                    # String libraries
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/debug_64/absl_strings.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_strings.lib>
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/debug_64/absl_strings_internal.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_strings_internal.lib>
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/debug_64/absl_str_format_internal.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_str_format_internal.lib>
                    # Status libraries
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/debug_64/absl_status.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_status.lib>
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/debug_64/absl_statusor.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_statusor.lib>
                    # Time libraries
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/debug_64/absl_time.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_time.lib>
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/debug_64/absl_time_zone.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_time_zone.lib>
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/debug_64/absl_civil_time.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_civil_time.lib>
                    # Synchronization libraries
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/debug_64/absl_synchronization.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_synchronization.lib>
                    # Hash libraries
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/debug_64/absl_hash.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_hash.lib>
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/debug_64/absl_city.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_city.lib>
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/debug_64/absl_low_level_hash.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_low_level_hash.lib>
                    # Numeric libraries
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/debug_64/absl_int128.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/absl/windows/release_64/absl_int128.lib>
                    # OpenSSL libraries
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/openssl/windows/debug_64/libssl.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/openssl/windows/release_64/libssl.lib>
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/openssl/windows/debug_64/libcrypto.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/openssl/windows/release_64/libcrypto.lib>
                    # Zlib library
                    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/third_party/zlib/win/x64_debug/zlib.lib>
                    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/third_party/zlib/win/x64_release/zlib.lib>
                    # Windows system libraries
                    ws2_32 crypt32
            )
        else()
            # Linux: Use system libraries
            target_link_libraries(${target_name}
                PRIVATE
                    ${GRPC_LIBRARIES}
            )
        endif()
    endif()
    
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
