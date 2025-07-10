# SDK CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Check for gRPC availability
message(STATUS "proto file build")

# Try to use third_party gRPC libraries for Windows
if(WIN32)
    # Windows: Try multiple locations for protoc and grpc_cpp_plugin
    set(PROTOC_EXECUTABLE "${CMAKE_SOURCE_DIR}/../../third_party/protobuf/windows/bin/protoc.exe")
    set(GRPC_CPP_PLUGIN "${CMAKE_SOURCE_DIR}/../../third_party/grpc/windows/bin/grpc_cpp_plugin.exe")
    
    # If not found, try system PATH
    if(NOT PROTOC_EXECUTABLE)
        find_program(PROTOC_EXECUTABLE protoc)
    endif()
    if(NOT GRPC_CPP_PLUGIN)
        find_program(GRPC_CPP_PLUGIN grpc_cpp_plugin)
    endif()
    
    get_filename_component(ABS_PROTO_INC_DIR "${CMAKE_SOURCE_DIR}/../../third_party/protobuf/windows/include" ABSOLUTE)
else()
    # Linux: Use system protoc and grpc_cpp_plugin (if available)
    find_program(PROTOC_EXECUTABLE protoc)
    find_program(GRPC_CPP_PLUGIN grpc_cpp_plugin)
    get_filename_component(ABS_PROTO_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../third_party/protobuf/linux/include" ABSOLUTE)
endif()


if(PROTOC_EXECUTABLE)
    if(GRPC_CPP_PLUGIN)
        message(STATUS "Found protoc: ${PROTOC_EXECUTABLE}")
        message(STATUS "Found grpc_cpp_plugin: ${GRPC_CPP_PLUGIN}")
        message(STATUS "Proto include dir: ${ABS_PROTO_INC_DIR}")
    else()
        message(STATUS "protoc found but grpc_cpp_plugin missing: ${GRPC_CPP_PLUGIN}")
    endif()
else()
    message(STATUS "protoc not found. Searched paths:")
    if(WIN32)
        foreach(PROTOC_PATH ${PROTOC_PATHS})
            message(STATUS "  - ${PROTOC_PATH}")
        endforeach()
    endif()
endif()

# Create generated directory if it doesn't exist
file(MAKE_DIRECTORY ${ABS_PROTO_OUT_DIR})

# Always populate the expected generated file lists
foreach(FIL ${PROTO_FILES})
    get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
    get_filename_component(FIL_PATH ${FIL} PATH)
    get_filename_component(FIL_WE ${FIL} NAME_WE)

    set(PROTO_SRC "${ABS_PROTO_OUT_DIR}/${FIL_WE}.pb.cc")
    set(PROTO_HEADER "${ABS_PROTO_OUT_DIR}/${FIL_WE}.pb.h")
    set(GRPC_SRC "${ABS_PROTO_OUT_DIR}/${FIL_WE}.grpc.pb.cc")
    set(GRPC_HEADER "${ABS_PROTO_OUT_DIR}/${FIL_WE}.grpc.pb.h")

    list(APPEND PROTO_SRCS ${PROTO_SRC} ${PROTO_HEADER})
    list(APPEND GRPC_SRCS ${GRPC_SRC} ${GRPC_HEADER})

    message(STATUS "Setting up protobuf generation for ${FIL_WE}")
    add_custom_command(
        OUTPUT "${PROTO_SRC}" "${PROTO_HEADER}" "${GRPC_SRC}" "${GRPC_HEADER}"
        COMMAND ${PROTOC_EXECUTABLE}
        ARGS --grpc_out="${ABS_PROTO_OUT_DIR}"
                --cpp_out="${ABS_PROTO_OUT_DIR}"
                -I"${ABS_PROTO_DIR}"
                -I"${ABS_PROTO_INC_DIR}"
                --plugin=protoc-gen-grpc="${GRPC_CPP_PLUGIN}"
                "${ABS_FIL}"
        DEPENDS "${ABS_FIL}"
        COMMENT "Generating gRPC files for ${FIL_WE}"
        VERBATIM
    )
    # Add to list of files that need generation
    list(APPEND PROTO_GENERATION_OUTPUTS "${PROTO_SRC}" "${PROTO_HEADER}" "${GRPC_SRC}" "${GRPC_HEADER}")
endforeach()

# Create a custom target for protobuf generation if needed
if(PROTO_GENERATION_OUTPUTS)
    add_custom_target(generate_protos
        DEPENDS ${PROTO_GENERATION_OUTPUTS}
        COMMENT "Generating protobuf files"
    )
endif()

