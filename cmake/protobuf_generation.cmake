# Protobuf and gRPC generation for Octane SDK
# This file handles the generation of protobuf and gRPC files from .proto definitions

# Find required tools
find_program(PROTOC_EXECUTABLE protoc)
find_program(GRPC_CPP_PLUGIN grpc_cpp_plugin)

# Check if we have the basic protobuf compiler
if(NOT PROTOC_EXECUTABLE)
    message(WARNING "protoc not found. Protobuf generation will be skipped.")
    return()
endif()

# Set up directories
set(PROTO_SOURCE_DIR "${CMAKE_SOURCE_DIR}/sdk/src/api/grpc/protodef")
set(PROTO_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/sdk/src/api/grpc/protoc")

# Create output directory
file(MAKE_DIRECTORY ${PROTO_OUTPUT_DIR})

# Find all .proto files
file(GLOB_RECURSE PROTO_FILES "${PROTO_SOURCE_DIR}/*.proto")

# Remove problematic proto files that cause conflicts
list(FILTER PROTO_FILES EXCLUDE REGEX ".*apinodearray\\.proto$")
list(FILTER PROTO_FILES EXCLUDE REGEX ".*apinodesystem\\.proto$")

# Separate base proto files (dependencies) from others
set(BASE_PROTO_FILES)
set(REMAINING_PROTO_FILES)

foreach(PROTO_FILE ${PROTO_FILES})
    get_filename_component(PROTO_NAME ${PROTO_FILE} NAME_WE)
    if(PROTO_NAME MATCHES "^(common|octaneenums|octanevectypes|octaneids)$")
        list(APPEND BASE_PROTO_FILES ${PROTO_FILE})
    else()
        list(APPEND REMAINING_PROTO_FILES ${PROTO_FILE})
    endif()
endforeach()

# Function to generate protobuf files
function(generate_protobuf_files PROTO_FILES_LIST TARGET_NAME)
    set(GENERATED_SOURCES)
    set(GENERATED_HEADERS)
    
    foreach(PROTO_FILE ${PROTO_FILES_LIST})
        get_filename_component(PROTO_NAME ${PROTO_FILE} NAME_WE)
        
        # Generated file paths
        set(PB_CC "${PROTO_OUTPUT_DIR}/${PROTO_NAME}.pb.cc")
        set(PB_H "${PROTO_OUTPUT_DIR}/${PROTO_NAME}.pb.h")
        
        list(APPEND GENERATED_SOURCES ${PB_CC})
        list(APPEND GENERATED_HEADERS ${PB_H})
        
        # Basic protobuf generation command with compatibility options
        set(PROTOC_COMMAND
            ${PROTOC_EXECUTABLE}
            --proto_path=${PROTO_SOURCE_DIR}
            --proto_path=${PROTO_OUTPUT_DIR}
            --cpp_out=${PROTO_OUTPUT_DIR}
            --experimental_allow_proto3_optional
            ${PROTO_FILE}
        )
        
        # Add gRPC generation if plugin is available
        if(GRPC_CPP_PLUGIN)
            set(GRPC_CC "${PROTO_OUTPUT_DIR}/${PROTO_NAME}.grpc.pb.cc")
            set(GRPC_H "${PROTO_OUTPUT_DIR}/${PROTO_NAME}.grpc.pb.h")
            
            list(APPEND GENERATED_SOURCES ${GRPC_CC})
            list(APPEND GENERATED_HEADERS ${GRPC_H})
            
            list(APPEND PROTOC_COMMAND
                --grpc_out=${PROTO_OUTPUT_DIR}
                --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN}
            )
        endif()
        
        # Create the generation command
        add_custom_command(
            OUTPUT ${PB_CC} ${PB_H} ${GRPC_CC} ${GRPC_H}
            COMMAND ${PROTOC_COMMAND}
            DEPENDS ${PROTO_FILE}
            COMMENT "Generating protobuf and gRPC files for ${PROTO_NAME}"
            VERBATIM
        )
    endforeach()
    
    # Create target
    add_custom_target(${TARGET_NAME}
        DEPENDS ${GENERATED_SOURCES} ${GENERATED_HEADERS}
        COMMENT "Generating protobuf files for ${TARGET_NAME}"
    )
    
    # Set generated sources property for use by other targets
    set_target_properties(${TARGET_NAME} PROPERTIES
        GENERATED_SOURCES "${GENERATED_SOURCES}"
        GENERATED_HEADERS "${GENERATED_HEADERS}"
    )
endfunction()

# Generate base protobuf files first (dependencies)
if(BASE_PROTO_FILES)
    generate_protobuf_files("${BASE_PROTO_FILES}" protobuf_base)
    message(STATUS "Protobuf generation: Base proto files configured")
endif()

# Generate remaining protobuf files
if(REMAINING_PROTO_FILES)
    generate_protobuf_files("${REMAINING_PROTO_FILES}" protobuf_remaining)
    
    # Make remaining depend on base
    if(TARGET protobuf_base)
        add_dependencies(protobuf_remaining protobuf_base)
    endif()
    
    message(STATUS "Protobuf generation: Remaining proto files configured")
endif()

# Create a combined target for all protobuf generation
add_custom_target(protobuf_all)

if(TARGET protobuf_base)
    add_dependencies(protobuf_all protobuf_base)
endif()

if(TARGET protobuf_remaining)
    add_dependencies(protobuf_all protobuf_remaining)
endif()

# Report status
if(GRPC_CPP_PLUGIN)
    message(STATUS "Protobuf generation: gRPC plugin found at ${GRPC_CPP_PLUGIN}")
    message(STATUS "Protobuf generation: Both protobuf and gRPC files will be generated")
else()
    message(STATUS "Protobuf generation: gRPC plugin not found, only protobuf files will be generated")
endif()

message(STATUS "Protobuf generation: Configured for ${CMAKE_SOURCE_DIR}/sdk/src/api/grpc/protoc/")