# SDK CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# SDK CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Collect all SDK source files

file(GLOB SDK_CLIENT_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/client/*.*"
)
list(REMOVE_ITEM SDK_CLIENT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/client/apinodeinfoclient.cpp")
list(REMOVE_ITEM SDK_CLIENT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/client/apicontrol.h")
list(REMOVE_ITEM SDK_CLIENT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/client/apicontrol.cpp")
list(REMOVE_ITEM SDK_CLIENT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/client/framerangetclient.h")
list(REMOVE_ITEM SDK_CLIENT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/client/framerangetclient.cpp")


# Include protoc sources (protobuf-generated files)
list(APPEND SDK_SOURCES ${SDK_CLIENT_SOURCES})

# Collect all existing protoc files (no compilation needed)
file(GLOB_RECURSE PROTOC_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/protoc/*.*"
)

# Include protoc sources (protobuf-generated files)
list(APPEND SDK_SOURCES ${PROTOC_SOURCES})

# Collect all existing converter files 
file(GLOB_RECURSE CONVERTER_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/converters/*.*"
)

# Include converter sources
list(APPEND SDK_SOURCES ${CONVERTER_SOURCES})

# Collect all existing base files 
#file(GLOB_RECURSE GRPCBASE_SOURCES
#    "${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/*.*"
#)

# Include base sources
list(APPEND SDK_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/grpcbase.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/grpcbase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/grpcsettings.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/grpcsettings.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/convertmatrix.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/convertmatrix.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/clientcallbackmgr.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/clientcallbackmgr.h
#    ${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/grpccallbacks.h
#    ${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/grpccallbacks.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/grpcsettings.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/grpcsettings.cpp    
    ${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/objectmgr.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/objectmgr.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/stringmgr.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/stringmgr.cpp
)

# Exclude octanewrappers.cpp if it exists
list(REMOVE_ITEM SDK_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/octanewrappers.cpp")

# Create the SDK library
add_library(octane_sdk STATIC
    ${SDK_SOURCES}
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES 
    ${SDK_SOURCES} 
)

# Set include directories
target_include_directories(octane_sdk
    PUBLIC
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/api
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/api/module
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/api/module/gui
        ${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/protoc
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/converters
        ${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/client
        ${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc
        ${CMAKE_CURRENT_SOURCE_DIR}/src/api
        ${CMAKE_CURRENT_SOURCE_DIR}/src/api/ui

        $<$<PLATFORM_ID:Windows>:${CMAKE_CURRENT_SOURCE_DIR}/../third_party/protobuf/windows/include>
        $<$<PLATFORM_ID:Windows>:${CMAKE_CURRENT_SOURCE_DIR}/../third_party/grpc/windows/include>
        $<$<PLATFORM_ID:Windows>:${CMAKE_CURRENT_SOURCE_DIR}/../third_party/absl/windows/include>
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/api/ui
        ${CMAKE_CURRENT_SOURCE_DIR}/src/api/module/gui
        ${CMAKE_CURRENT_SOURCE_DIR}/src/api/module
        ${CMAKE_CURRENT_SOURCE_DIR}/src/api/grpc/converters
)

# Add Windows-specific compiler flags
if(WIN32 AND MSVC)
    target_compile_options(octane_sdk PRIVATE /bigobj)
endif()

# Windows MSVC specific configurations
if(MSVC)
    # Enable parallel compilation
    target_compile_options(octane_sdk PRIVATE /MP)
    
    # Set warning level and disable specific warnings
    target_compile_options(octane_sdk PRIVATE /W3)
    target_compile_options(octane_sdk PRIVATE /wd4996)  # Disable deprecated function warnings
    
    # Enable proper exception handling
    target_compile_options(octane_sdk PRIVATE /EHsc)
    
    # Set runtime library to static (to match third_party libraries)
    set_property(TARGET octane_sdk PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# Set folder for Visual Studio organization
set_target_properties(octane_sdk PROPERTIES FOLDER "SDK")

# Add compile definitions
target_compile_definitions(octane_sdk
    PRIVATE
        # Windows-specific definitions
        $<$<PLATFORM_ID:Windows>:WIN32_LEAN_AND_MEAN>
        $<$<PLATFORM_ID:Windows>:NOMINMAX>
        # Add any other necessary definitions here
        NO_PCH
)

# Platform-specific library linking
if(WIN32 AND MSVC)
    # Windows-specific library linking
    # Link with octane_standalone.lib
    target_link_libraries(octane_sdk
        PUBLIC
            "${CMAKE_CURRENT_SOURCE_DIR}/src/api/module/octane_standalone.lib"
    )
    message(STATUS "Windows MSVC SDK with octane_standalone.lib configured")

elseif(APPLE)
    # macOS: Use ALL available third_party libraries
    file(GLOB MACOS_GRPC_LIBS "${CMAKE_SOURCE_DIR}/third_party/grpc/macos/*.a")
    file(GLOB MACOS_PROTOBUF_LIBS "${CMAKE_SOURCE_DIR}/third_party/protobuf/macos/*.a")
    file(GLOB MACOS_ABSL_LIBS "${CMAKE_SOURCE_DIR}/third_party/absl/macos/*.a")
    file(GLOB MACOS_OPENSSL_LIBS "${CMAKE_SOURCE_DIR}/third_party/openssl/macos/*.a")
    file(GLOB MACOS_ZLIB_LIBS "${CMAKE_SOURCE_DIR}/third_party/zlib/macos/*.a")
    target_link_libraries(octane_sdk
        PRIVATE
            ${MACOS_GRPC_LIBS}
            ${MACOS_PROTOBUF_LIBS}
            ${MACOS_ABSL_LIBS}
            ${MACOS_OPENSSL_LIBS}
            ${MACOS_ZLIB_LIBS}
    )
else()
    # Linux: Use ALL available third_party libraries
    file(GLOB LINUX_GRPC_LIBS "${CMAKE_SOURCE_DIR}/third_party/grpc/linux/*.a")
    file(GLOB LINUX_PROTOBUF_LIBS "${CMAKE_SOURCE_DIR}/third_party/protobuf/linux/*.a")
    file(GLOB LINUX_ABSL_LIBS "${CMAKE_SOURCE_DIR}/third_party/absl/linux/*.a")
    file(GLOB LINUX_OPENSSL_LIBS "${CMAKE_SOURCE_DIR}/third_party/openssl/linux/*.a")
    file(GLOB LINUX_ZLIB_LIBS "${CMAKE_SOURCE_DIR}/third_party/zlib/linux/*.a")
    target_link_libraries(octane_sdk
        PRIVATE
            ${LINUX_GRPC_LIBS}
            ${LINUX_PROTOBUF_LIBS}
            ${LINUX_ABSL_LIBS}
            ${LINUX_OPENSSL_LIBS}
            ${LINUX_ZLIB_LIBS}
            # Linux system libraries
            pthread dl
    )
endif()

# Set output directory
set_target_properties(octane_sdk PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_SOURCE_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_SOURCE_DIR}/bin
)
