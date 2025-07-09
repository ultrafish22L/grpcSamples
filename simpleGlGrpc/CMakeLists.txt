cmake_minimum_required(VERSION 3.10)

# Define the simpleGlGrpc project
project(simpleGlGrpc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create the main executable with direct gRPC integration
add_executable(simpleGlGrpc
    main.cpp
    ${COMMON_SOURCES}
)

# Function to configure a target
function(configure_simpleGlGrpc_target target_name)
    
    # Add dependency on protobuf generation
    if(TARGET protobuf_all)
        add_dependencies(${target_name} protobuf_all)
    endif()
    
    # Add dependency on gRPC file generation
    if(TARGET generate_grpc_files_simpleGlGrpc)
        add_dependencies(${target_name} generate_grpc_files_simpleGlGrpc)
    endif()

    # Link libraries - use built targets from third_party
    target_link_libraries(${target_name}
        PRIVATE
            shared_lib
    )
    
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


#[[
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
configure_simpleGlGrpc_target(simpleGlGrpc_demo)
configure_simpleGlGrpc_target(simpleGlGrpc_test)
]]

# gRPC functionality is provided by third_party libraries only
# No system gRPC dependencies
