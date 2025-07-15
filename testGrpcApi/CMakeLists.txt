cmake_minimum_required(VERSION 3.16)
project(testGrpcApi)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dear ImGui sources
set(IMGUI_SOURCES
    ../third_party/imgui/imgui.cpp
    ../third_party/imgui/imgui_demo.cpp
    ../third_party/imgui/imgui_draw.cpp
    ../third_party/imgui/imgui_tables.cpp
    ../third_party/imgui/imgui_widgets.cpp
    ../third_party/imgui/backends/imgui_impl_glfw.cpp
    ../third_party/imgui/backends/imgui_impl_opengl3.cpp
)

# Application sources
set(APP_SOURCES
    main.cpp
    ActivityLogger.cpp
    PerformanceTracker.cpp
)

# Create executable
add_executable(testGrpcApi 
    ${APP_SOURCES}
    ${IMGUI_SOURCES}
)

add_dependencies(testGrpcApi shared_lib)

# Add dependency on protobuf generation
if(TARGET protobuf_all)
    add_dependencies(testGrpcApi protobuf_all)
endif()
    
# Add dependency on gRPC file generation
if(TARGET generate_grpc_files_simpleGlGrpc)
    add_dependencies(testGrpcApi generate_grpc_files_simpleGlGrpc)
endif()

# Set include directories
target_include_directories(testGrpcApi
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        "${CMAKE_CURRENT_SOURCE_DIR}/../third_party/imgui"
        "${CMAKE_CURRENT_SOURCE_DIR}/../third_party/imgui/backends"
)

# Link libraries - use built targets from third_party
target_link_libraries(testGrpcApi
    PRIVATE
        shared_lib
)
    
# Set working directory for debugging in Visual Studio
set_target_properties(testGrpcApi PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

# Windows MSVC specific configurations
if(MSVC)
    # Set subsystem to console
    set_target_properties(testGrpcApi PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:CONSOLE"
    )
        
    # Set runtime library to match third_party libraries (static runtime)
    set_property(TARGET testGrpcApi PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
        
    # Add /bigobj flag for large object files
    target_compile_options(testGrpcApi PRIVATE /bigobj)
endif()

# Copy resources
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/imgui.ini ${CMAKE_CURRENT_BINARY_DIR}/imgui.ini COPYONLY)