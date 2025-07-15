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
        "${CMAKE_CURRENT_SOURCE_DIR}/../shared"
        "${CMAKE_CURRENT_SOURCE_DIR}/../shared/protos"
)

# Link libraries - use built targets from third_party
target_link_libraries(testGrpcApi
    PRIVATE
        shared_lib
        # Windows-specific libraries for ImGui
        $<$<PLATFORM_ID:Windows>:opengl32>
        $<$<PLATFORM_ID:Windows>:gdi32>
        $<$<PLATFORM_ID:Windows>:user32>
        $<$<PLATFORM_ID:Windows>:kernel32>
        $<$<PLATFORM_ID:Windows>:shell32>
        # Linux-specific libraries
        $<$<PLATFORM_ID:Linux>:GL>
        $<$<PLATFORM_ID:Linux>:X11>
        $<$<PLATFORM_ID:Linux>:pthread>
        $<$<PLATFORM_ID:Linux>:dl>
)
    
# Set working directory for debugging in Visual Studio
set_target_properties(testGrpcApi PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

# Add compile definitions
target_compile_definitions(testGrpcApi
    PRIVATE
        # Platform-specific definitions
        $<$<PLATFORM_ID:Windows>:_CRT_SECURE_NO_WARNINGS>
        $<$<PLATFORM_ID:Windows>:_WIN32_WINNT=0x0601>  # Windows 7 minimum
        $<$<PLATFORM_ID:Windows>:WINVER=0x0601>        # Windows 7 minimum
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
    
    # Enable parallel compilation
    target_compile_options(testGrpcApi PRIVATE /MP)
    
    # Set warning level and disable specific warnings
    target_compile_options(testGrpcApi PRIVATE /W3)
    target_compile_options(testGrpcApi PRIVATE /wd4996)  # Disable deprecated function warnings
    target_compile_options(testGrpcApi PRIVATE /wd4267)  # Size_t conversion warnings
    target_compile_options(testGrpcApi PRIVATE /wd4244)  # Type conversion warnings
    
    # Enable proper exception handling
    target_compile_options(testGrpcApi PRIVATE /EHsc)
endif()

# Copy resources
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/imgui.ini ${CMAKE_CURRENT_BINARY_DIR}/imgui.ini COPYONLY)