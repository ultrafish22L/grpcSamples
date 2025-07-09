cmake_minimum_required(VERSION 3.10)
project(GrpcSamples)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OCTANE_SDK_ENABLED OFF)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Windows MSVC specific configurations
if(WIN32)
    set(OCTANE_SDK_ENABLED ON)
    
    # Enable parallel compilation for all targets
    add_compile_options(/MP)
    
    # Set warning level
    add_compile_options(/W3)
    
    # Disable specific warnings that are common in third-party code
    add_compile_options(/wd4996)  # Deprecated function warnings
    add_compile_options(/wd4267)  # Size_t conversion warnings
    add_compile_options(/wd4244)  # Type conversion warnings

    # Ignore warnings about missing pdb
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ignore:4099")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /ignore:4099")
    set(CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} /ignore:4099")

    # Enable proper exception handling
    add_compile_options(/EHsc)
    
    # Set runtime library to static linking (to match third_party libraries)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    
    # Explicitly set runtime library flags to ensure static linking
    # Debug: /MTd (MultiThreaded Debug Static)
    # Release: /MT (MultiThreaded Static)
    
    # Replace any existing /MD flags with /MT flags in CMAKE_CXX_FLAGS
    foreach(flag_var CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
        if(${flag_var} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        endif()
        if(${flag_var} MATCHES "/MDd")
            string(REGEX REPLACE "/MDd" "/MTd" ${flag_var} "${${flag_var}}")
        endif()
    endforeach()
    
    # Force static runtime library flags
    add_compile_options(
        $<$<CONFIG:Debug>:/MTd>
        $<$<CONFIG:Release>:/MT>
        $<$<CONFIG:RelWithDebInfo>:/MT>
        $<$<CONFIG:MinSizeRel>:/MT>
    )
    
    # Add linker flags to ignore conflicting runtime libraries
    add_link_options(
        $<$<CONFIG:Debug>:/NODEFAULTLIB:msvcrt>
        $<$<CONFIG:Debug>:/NODEFAULTLIB:msvcprt>
        $<$<CONFIG:Release>:/NODEFAULTLIB:msvcrtd>
        $<$<CONFIG:Release>:/NODEFAULTLIB:msvcprtd>
    )
    
    # Add Windows-specific definitions
    add_compile_definitions(WIN32_LEAN_AND_MEAN NOMINMAX)
endif()

# Enable solution folders in Visual Studio
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set simpleGL as the default startup project in Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT simpleGlGrpc)

# Set OpenGL preference to avoid warnings
if(POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()
set(OpenGL_GL_PREFERENCE GLVND)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# For multi-config generators (like Visual Studio)
foreach(CONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${CONFIG} CONFIG_UPPER)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG_UPPER} ${CMAKE_SOURCE_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIG_UPPER} ${CMAKE_SOURCE_DIR}/bin)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIG_UPPER} ${CMAKE_SOURCE_DIR}/bin)
endforeach()

# Add third-party libraries that have CMake support and are needed
# Configure GLFW to not build examples, tests, or docs
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE BOOL "Generate installation target")

# Configure GLFW to use static runtime library (to match our project settings)
if(MSVC)
    set(USE_MSVC_RUNTIME_LIBRARY_DLL OFF CACHE BOOL "Use MSVC runtime library DLL")
endif()

add_subdirectory(third_party/glew)
add_subdirectory(third_party/glfw)
add_subdirectory(third_party/glm)

# Add grpc-web plugin for HTML demos (all platforms)
# This builds the protoc-gen-grpc-web plugin used to generate JavaScript files from proto definitions
# The plugin is completely separate from C++ applications and SDK
message(STATUS "Building grpc-web plugin for HTML demos")

# grpc-web plugin configuration (integrated directly to avoid submodule CMakeLists.txt issues)
set(GRPC_WEB_GENERATOR_SOURCE
    "${CMAKE_SOURCE_DIR}/third_party/grpc-web/javascript/net/grpc/web/generator/grpc_generator.cc"
)

# Create the protoc-gen-grpc-web executable
add_executable(protoc-gen-grpc-web ${GRPC_WEB_GENERATOR_SOURCE})

# Platform-specific configuration for grpc-web plugin
if(WIN32)
    # Windows: Use the same library directories as the main project
    set(GRPC_LIB_DIR "${CMAKE_SOURCE_DIR}/third_party/grpc/windows/$<IF:$<CONFIG:Debug>,debug_64,release_64>")
    set(PROTOBUF_LIB_DIR "${CMAKE_SOURCE_DIR}/third_party/protobuf/windows/$<IF:$<CONFIG:Debug>,debug_64,release_64>")
    set(ABSL_LIB_DIR "${CMAKE_SOURCE_DIR}/third_party/absl/windows/$<IF:$<CONFIG:Debug>,debug_64,release_64>")

    # Set include directories to use existing third_party libraries
    set(PROTOBUF_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/third_party/protobuf/windows/include")
    set(GRPC_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/third_party/grpc/windows/include")
    set(ABSL_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/third_party/absl/windows/include")
    
    # Set include directories for Windows
    target_include_directories(protoc-gen-grpc-web
        PRIVATE
            ${PROTOBUF_INCLUDE_DIR}
            ${GRPC_INCLUDE_DIR}
            ${ABSL_INCLUDE_DIR}
    )
    
    # Use the same MSVC runtime library settings as the main project
    set_target_properties(protoc-gen-grpc-web PROPERTIES
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
    )
    
    # Add compile options to match main project
    target_compile_options(protoc-gen-grpc-web PRIVATE
        /MP  # Parallel compilation
        /W3  # Warning level
        /wd4996  # Deprecated function warnings
        /wd4267  # Size_t conversion warnings
        /wd4244  # Type conversion warnings
        /EHsc    # Exception handling
        $<$<CONFIG:Debug>:/MTd>
        $<$<CONFIG:Release>:/MT>
        $<$<CONFIG:RelWithDebInfo>:/MT>
        $<$<CONFIG:MinSizeRel>:/MT>
    )
    
    # Add Windows-specific definitions
    target_compile_definitions(protoc-gen-grpc-web PRIVATE
        WIN32_LEAN_AND_MEAN
        NOMINMAX
    )
    
    # Link with Windows third-party libraries
    target_link_libraries(protoc-gen-grpc-web
        PRIVATE
            # Protobuf libraries (required for protoc plugin)
            "${PROTOBUF_LIB_DIR}/libprotoc.lib"
            "${PROTOBUF_LIB_DIR}/libprotobuf.lib"
            "${PROTOBUF_LIB_DIR}/utf8_range.lib"
            "${PROTOBUF_LIB_DIR}/utf8_validity.lib"
            
            # Essential Abseil libraries for protobuf
            "${ABSL_LIB_DIR}/absl_base.lib"
            "${ABSL_LIB_DIR}/absl_strings.lib"
            "${ABSL_LIB_DIR}/absl_strings_internal.lib"
            "${ABSL_LIB_DIR}/absl_string_view.lib"
            "${ABSL_LIB_DIR}/absl_throw_delegate.lib"
            "${ABSL_LIB_DIR}/absl_int128.lib"
            "${ABSL_LIB_DIR}/absl_raw_logging_internal.lib"
            "${ABSL_LIB_DIR}/absl_log_severity.lib"
            "${ABSL_LIB_DIR}/absl_spinlock_wait.lib"
            "${ABSL_LIB_DIR}/absl_malloc_internal.lib"
            "${ABSL_LIB_DIR}/absl_time.lib"
            "${ABSL_LIB_DIR}/absl_time_zone.lib"
            "${ABSL_LIB_DIR}/absl_civil_time.lib"
            "${ABSL_LIB_DIR}/absl_debugging_internal.lib"
            "${ABSL_LIB_DIR}/absl_demangle_internal.lib"
            "${ABSL_LIB_DIR}/absl_stacktrace.lib"
            "${ABSL_LIB_DIR}/absl_symbolize.lib"
            "${ABSL_LIB_DIR}/absl_hash.lib"
            "${ABSL_LIB_DIR}/absl_city.lib"
            "${ABSL_LIB_DIR}/absl_low_level_hash.lib"
            "${ABSL_LIB_DIR}/absl_status.lib"
            "${ABSL_LIB_DIR}/absl_statusor.lib"
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
            "${ABSL_LIB_DIR}/absl_str_format_internal.lib"
            "${ABSL_LIB_DIR}/absl_synchronization.lib"
            "${ABSL_LIB_DIR}/absl_graphcycles_internal.lib"
            "${ABSL_LIB_DIR}/absl_kernel_timeout_internal.lib"
            
            # Windows system libraries
            kernel32.lib
            user32.lib
            gdi32.lib
            winspool.lib
            shell32.lib
            ole32.lib
            oleaut32.lib
            uuid.lib
            comdlg32.lib
            advapi32.lib
            ws2_32.lib
    )
    
    # Add linker flags to ignore conflicting runtime libraries
    target_link_options(protoc-gen-grpc-web PRIVATE
        $<$<CONFIG:Debug>:/NODEFAULTLIB:msvcrt>
        $<$<CONFIG:Debug>:/NODEFAULTLIB:msvcprt>
        $<$<CONFIG:Release>:/NODEFAULTLIB:msvcrtd>
        $<$<CONFIG:Release>:/NODEFAULTLIB:msvcprtd>
        /ignore:4099  # Ignore missing pdb warnings
    )

else()
    # Linux configuration
    target_compile_options(protoc-gen-grpc-web PRIVATE
        -std=c++17
        -pthread
    )
    
    # Find required system libraries using pkg-config
    find_package(PkgConfig REQUIRED)
    
    # Find protobuf and protoc
    pkg_check_modules(PROTOBUF REQUIRED protobuf)
    if(PROTOBUF_FOUND)
        target_include_directories(protoc-gen-grpc-web PRIVATE ${PROTOBUF_INCLUDE_DIRS})
        target_link_libraries(protoc-gen-grpc-web PRIVATE ${PROTOBUF_LIBRARIES})
        target_compile_options(protoc-gen-grpc-web PRIVATE ${PROTOBUF_CFLAGS_OTHER})
        message(STATUS "Found system protobuf libraries: ${PROTOBUF_LIBRARIES}")
    endif()
    
    # Also need libprotoc for the compiler functionality
    find_library(PROTOC_LIBRARY protoc)
    if(PROTOC_LIBRARY)
        target_link_libraries(protoc-gen-grpc-web PRIVATE ${PROTOC_LIBRARY})
        message(STATUS "Found protoc library: ${PROTOC_LIBRARY}")
    else()
        message(FATAL_ERROR "libprotoc not found - required for grpc-web plugin")
    endif()
    
    # Find grpc++
    pkg_check_modules(GRPCPP REQUIRED grpc++)
    if(GRPCPP_FOUND)
        target_include_directories(protoc-gen-grpc-web PRIVATE ${GRPCPP_INCLUDE_DIRS})
        target_link_libraries(protoc-gen-grpc-web PRIVATE ${GRPCPP_LIBRARIES})
        target_compile_options(protoc-gen-grpc-web PRIVATE ${GRPCPP_CFLAGS_OTHER})
        message(STATUS "Found system grpc++ libraries: ${GRPCPP_LIBRARIES}")
    endif()
    
    # Find absl (Abseil)
    pkg_check_modules(ABSL REQUIRED absl_base absl_strings absl_status)
    if(ABSL_FOUND)
        target_include_directories(protoc-gen-grpc-web PRIVATE ${ABSL_INCLUDE_DIRS})
        target_link_libraries(protoc-gen-grpc-web PRIVATE ${ABSL_LIBRARIES})
        target_compile_options(protoc-gen-grpc-web PRIVATE ${ABSL_CFLAGS_OTHER})
        message(STATUS "Found system abseil libraries: ${ABSL_LIBRARIES}")
    endif()
    
    # Additional system libraries
    target_link_libraries(protoc-gen-grpc-web
        PRIVATE
            pthread
            dl
    )
    
    message(STATUS "Configured grpc-web plugin for Linux with system libraries")
endif()

# Apply protobuf API compatibility patch
set(GRPC_WEB_PATCH_FILE "${CMAKE_SOURCE_DIR}/cmake/grpc-web-protobuf-fix.patch")
set(GRPC_WEB_SOURCE_FILE "${CMAKE_SOURCE_DIR}/third_party/grpc-web/javascript/net/grpc/web/generator/grpc_generator.cc")

# Check if patch needs to be applied (look for old API usage)
file(READ "${GRPC_WEB_SOURCE_FILE}" GRPC_WEB_SOURCE_CONTENT)
string(FIND "${GRPC_WEB_SOURCE_CONTENT}" "real_oneof_decl" NEEDS_PATCH)

if(NOT NEEDS_PATCH EQUAL -1)
    message(STATUS "Applying protobuf API compatibility patch to grpc-web")
    find_program(PATCH_PROGRAM patch)
    if(PATCH_PROGRAM)
        execute_process(
            COMMAND ${PATCH_PROGRAM} -p1 -i "${GRPC_WEB_PATCH_FILE}"
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/third_party/grpc-web"
            RESULT_VARIABLE PATCH_RESULT
            OUTPUT_QUIET
            ERROR_QUIET
        )
        if(PATCH_RESULT EQUAL 0)
            message(STATUS "Successfully applied protobuf API compatibility patch")
        else()
            message(WARNING "Failed to apply patch, but continuing build")
        endif()
    else()
        message(WARNING "patch program not found, manually applying fix")
        # Fallback: direct string replacement
        string(REPLACE "real_oneof_decl" "oneof_decl" GRPC_WEB_SOURCE_CONTENT_FIXED "${GRPC_WEB_SOURCE_CONTENT}")
        file(WRITE "${GRPC_WEB_SOURCE_FILE}" "${GRPC_WEB_SOURCE_CONTENT_FIXED}")
        message(STATUS "Applied protobuf API fix via string replacement")
    endif()
else()
    message(STATUS "Protobuf API compatibility patch already applied or not needed")
endif()

# Set output directory to html folder (for HTML demo tools)
set_target_properties(protoc-gen-grpc-web PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/html"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/html"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/html"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/html"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/html"
)

set(BUILD_GRPC_WEB_PLUGIN ON)

# Set folder organization for third-party libraries in Visual Studio
set_target_properties(glew PROPERTIES FOLDER "ThirdParty")
set_target_properties(glfw PROPERTIES FOLDER "ThirdParty")
set_target_properties(glm PROPERTIES FOLDER "ThirdParty")

# Set grpc-web target properties
if(BUILD_GRPC_WEB_PLUGIN AND TARGET protoc-gen-grpc-web)
    set_target_properties(protoc-gen-grpc-web PROPERTIES FOLDER "ThirdParty/grpc-web")
endif()

# common projects
add_subdirectory(shared)
add_subdirectory(sdk)

# Add Python proxy server support (generates protobuf files for proxy)
add_subdirectory(proxy)

# Add main projects
add_subdirectory(simpleGL)
add_subdirectory(simpleGlGrpc)
add_subdirectory(simpleGlSdk)
