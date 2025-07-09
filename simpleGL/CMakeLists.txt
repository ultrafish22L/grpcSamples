cmake_minimum_required(VERSION 3.10)

# Define the simpleGL project
project(simpleGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create the main executable
add_executable(simpleGL
    main.cpp
)

# Include directories
target_include_directories(simpleGL
    PRIVATE
)

# Link libraries for main executable
target_link_libraries(simpleGL
    PUBLIC
        shared_lib
)

# Set working directory for debugging in Visual Studio
set_target_properties(simpleGL PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

# Windows MSVC specific configurations for executables
if(MSVC)
    # Set subsystem to console for all executables
    set_target_properties(simpleGL PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:CONSOLE"
    )
    
    # Set runtime library to match third_party libraries (static runtime)
    set_property(TARGET simpleGL PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()
