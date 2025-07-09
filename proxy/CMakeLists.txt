cmake_minimum_required(VERSION 3.10)

# Python gRPC Proxy Server Support
# This target generates Python protobuf files needed for the grpc_proxy.py server
# The proxy translates HTTP requests from HTML demos to gRPC calls to Octane

project(GrpcProxy)

# Find Python interpreter
find_package(Python3 COMPONENTS Interpreter REQUIRED)

# Define protobuf source files
set(PROTO_FILES
    "${CMAKE_SOURCE_DIR}/shared/protos/definitions/livelink.proto"
    "${CMAKE_SOURCE_DIR}/shared/protos/definitions/camera_control.proto"
)

# Define output directory for generated Python files
set(PYTHON_PROTO_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/shared/generated")

# Define generated Python files
set(GENERATED_PYTHON_FILES
    "${PYTHON_PROTO_OUTPUT_DIR}/livelink_pb2.py"
    "${PYTHON_PROTO_OUTPUT_DIR}/livelink_pb2_grpc.py"
    "${PYTHON_PROTO_OUTPUT_DIR}/camera_control_pb2.py"
    "${PYTHON_PROTO_OUTPUT_DIR}/camera_control_pb2_grpc.py"
)

# Create output directory
file(MAKE_DIRECTORY ${PYTHON_PROTO_OUTPUT_DIR})

if(WIN32)
    # Windows: Use protoc from third_party
    set(PROTOC_EXECUTABLE "${CMAKE_SOURCE_DIR}/third_party/protobuf/windows/bin/protoc.exe")
    set(PROTOBUF_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/third_party/protobuf/windows/include")
    
    # Check if protoc exists
    if(NOT EXISTS ${PROTOC_EXECUTABLE})
        message(WARNING "protoc.exe not found at ${PROTOC_EXECUTABLE}")
        message(STATUS "Python protobuf generation will be skipped on Windows")
        message(STATUS "To enable: ensure protobuf is built in third_party/protobuf/windows/")
        return()
    endif()
    
    # Generate Python protobuf files using Windows protoc
    add_custom_command(
        OUTPUT ${GENERATED_PYTHON_FILES}
        COMMAND ${PROTOC_EXECUTABLE}
            --python_out=${PYTHON_PROTO_OUTPUT_DIR}
            --grpc_python_out=${PYTHON_PROTO_OUTPUT_DIR}
            --proto_path=${CMAKE_SOURCE_DIR}/shared/protos/definitions
            --plugin=protoc-gen-grpc_python=${CMAKE_SOURCE_DIR}/third_party/grpc/windows/bin/grpc_python_plugin.exe
            ${PROTO_FILES}
        DEPENDS ${PROTO_FILES}
        COMMENT "Generating Python protobuf files for gRPC proxy server"
        VERBATIM
    )
    
else()
    # Linux: Use system protoc and grpcio-tools
    find_program(PROTOC_EXECUTABLE protoc)
    
    if(NOT PROTOC_EXECUTABLE)
        message(STATUS "protoc not found, trying to use Python grpcio-tools")
        
        # Use Python grpcio-tools to generate protobuf files
        add_custom_command(
            OUTPUT ${GENERATED_PYTHON_FILES}
            COMMAND ${Python3_EXECUTABLE} -m grpc_tools.protoc
                --python_out=${PYTHON_PROTO_OUTPUT_DIR}
                --grpc_python_out=${PYTHON_PROTO_OUTPUT_DIR}
                --proto_path=${CMAKE_SOURCE_DIR}/shared/protos/definitions
                ${PROTO_FILES}
            DEPENDS ${PROTO_FILES}
            COMMENT "Generating Python protobuf files using grpcio-tools"
            VERBATIM
        )
    else()
        # Use system protoc
        add_custom_command(
            OUTPUT ${GENERATED_PYTHON_FILES}
            COMMAND ${PROTOC_EXECUTABLE}
                --python_out=${PYTHON_PROTO_OUTPUT_DIR}
                --grpc_python_out=${PYTHON_PROTO_OUTPUT_DIR}
                --proto_path=${CMAKE_SOURCE_DIR}/shared/protos/definitions
                ${PROTO_FILES}
            DEPENDS ${PROTO_FILES}
            COMMENT "Generating Python protobuf files for gRPC proxy server"
            VERBATIM
        )
    endif()
endif()

# Create a custom target that depends on the generated files
add_custom_target(python_protobuf_generation
    DEPENDS ${GENERATED_PYTHON_FILES}
    COMMENT "Python protobuf files for gRPC proxy server"
)

# Create a target for the proxy server itself (informational)
add_custom_target(grpc_proxy_server
    COMMAND ${Python3_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/grpc_proxy.py"
    DEPENDS python_protobuf_generation
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Run Python gRPC proxy server (requires Octane running on port 51022)"
    VERBATIM
)

# Set folder organization in Visual Studio
set_target_properties(python_protobuf_generation PROPERTIES FOLDER "Proxy")
set_target_properties(grpc_proxy_server PROPERTIES FOLDER "Proxy")

# Add installation rules for Python files (optional)
if(WIN32)
    install(FILES ${GENERATED_PYTHON_FILES}
        DESTINATION python/generated
        COMPONENT proxy
    )
    
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/grpc_proxy.py"
        DESTINATION python
        COMPONENT proxy
    )
endif()

message(STATUS "Configured Python gRPC proxy server support")
message(STATUS "  - Generated files will be placed in: ${PYTHON_PROTO_OUTPUT_DIR}")
message(STATUS "  - Use 'python_protobuf_generation' target to generate Python protobuf files")
message(STATUS "  - Use 'grpc_proxy_server' target to run the proxy server")