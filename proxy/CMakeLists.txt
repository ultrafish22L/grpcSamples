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

# Visual Studio configuration for proxy targets
if(WIN32)
    # Create a comprehensive proxy setup executable for Visual Studio
    add_executable(proxy_setup_and_run
        "${CMAKE_CURRENT_SOURCE_DIR}/proxy_build_helper.cpp"
    )
    
    # Add custom command to install Python dependencies and run proxy
    add_custom_command(TARGET proxy_setup_and_run POST_BUILD
        COMMAND ${Python3_EXECUTABLE} -m pip install grpcio grpcio-tools aiohttp
        COMMAND ${CMAKE_COMMAND} -E echo "Python dependencies installed successfully"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Installing Python dependencies for gRPC proxy"
        VERBATIM
    )
    
    # Make the executable depend on protobuf generation
    add_dependencies(proxy_setup_and_run python_protobuf_generation)
    
    # Set properties for Visual Studio
    set_target_properties(proxy_setup_and_run PROPERTIES
        FOLDER "Proxy"
        OUTPUT_NAME "proxy_setup"
        EXCLUDE_FROM_DEFAULT_BUILD FALSE  # Include in default build
    )
    
    # Create a separate target that actually runs the proxy server
    add_custom_target(run_proxy_server
        COMMAND ${CMAKE_COMMAND} -E echo "Starting gRPC proxy server..."
        COMMAND ${CMAKE_COMMAND} -E echo "Server will run on: http://127.0.0.1:51023"
        COMMAND ${CMAKE_COMMAND} -E echo "Octane connection: 127.0.0.1:51022"
        COMMAND ${CMAKE_COMMAND} -E echo "Press Ctrl+C to stop the server"
        COMMAND ${Python3_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/grpc_proxy.py"
        DEPENDS proxy_setup_and_run
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Run gRPC proxy server (requires Octane running on port 51022)"
        VERBATIM
    )
    
    # Set protobuf generation properties
    set_target_properties(python_protobuf_generation PROPERTIES
        EXCLUDE_FROM_DEFAULT_BUILD FALSE
        EXCLUDE_FROM_ALL FALSE
    )
    
    # Original proxy server target (for backward compatibility)
    set_target_properties(grpc_proxy_server PROPERTIES
        EXCLUDE_FROM_DEFAULT_BUILD TRUE  # Don't run automatically
        EXCLUDE_FROM_ALL FALSE
    )
    
    # Set properties for the new run target
    set_target_properties(run_proxy_server PROPERTIES
        FOLDER "Proxy"
        EXCLUDE_FROM_DEFAULT_BUILD TRUE  # Available but not automatic
        EXCLUDE_FROM_ALL FALSE
    )
    
    message(STATUS "Visual Studio Proxy Targets:")
    message(STATUS "  - 'proxy_setup_and_run': Installs dependencies and generates protobuf files")
    message(STATUS "  - 'run_proxy_server': Runs the gRPC proxy server")
    message(STATUS "  - 'grpc_proxy_server': Original proxy server target")
else()
    # Linux: Custom targets work normally
    set_target_properties(python_protobuf_generation PROPERTIES
        EXCLUDE_FROM_DEFAULT_BUILD FALSE
        EXCLUDE_FROM_ALL FALSE
    )
    set_target_properties(grpc_proxy_server PROPERTIES
        EXCLUDE_FROM_DEFAULT_BUILD FALSE
        EXCLUDE_FROM_ALL FALSE
    )
endif()

# Set folder organization in Visual Studio
set_target_properties(python_protobuf_generation PROPERTIES FOLDER "Proxy")
set_target_properties(grpc_proxy_server PROPERTIES FOLDER "Proxy")

# Set folder for Windows-specific targets
if(WIN32)
    if(TARGET proxy_setup_and_run)
        set_target_properties(proxy_setup_and_run PROPERTIES FOLDER "Proxy")
    endif()
    if(TARGET run_proxy_server)
        set_target_properties(run_proxy_server PROPERTIES FOLDER "Proxy")
    endif()
endif()

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