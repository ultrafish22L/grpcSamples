# empty-module/CMakeLists.txt

set(THIRD_PARTY_INCLUDE_DIR
${CMAKE_SOURCE_DIR}/../libraries/libcommon
${CMAKE_SOURCE_DIR}/../src/globals
${CMAKE_SOURCE_DIR}/../src/api
${CMAKE_SOURCE_DIR}/../src/api/module
${CMAKE_SOURCE_DIR}/../src/api/module/gui
${CMAKE_SOURCE_DIR}/../src/api/grpc/protoc
${CMAKE_SOURCE_DIR}/../src/api/grpc/converters
${CMAKE_SOURCE_DIR}/../src/api/grpc/client
${CMAKE_SOURCE_DIR}/../src/api/grpc
${CMAKE_SOURCE_DIR}/../
${CMAKE_SOURCE_DIR}/../src/api/ui
${CMAKE_SOURCE_DIR}/grpcproxy
${CMAKE_SOURCE_DIR}/../thirdparty/grpc/${THIRDPARTY_PLATFORM}/include
)


INCLUDE_DIRECTORIES(SYSTEM ${THIRD_PARTY_INCLUDE_DIR})
INCLUDE_DIRECTORIES(SYSTEM ${ABSL_INCLUDE_PATH})
INCLUDE_DIRECTORIES(SYSTEM ${GRPC_INCLUDE_PATH})
INCLUDE_DIRECTORIES(SYSTEM ${PROTOBUF_INCLUDE_PATH})
INCLUDE_DIRECTORIES(SYSTEM ${RE2_INCLUDE_PATH})
INCLUDE_DIRECTORIES(SYSTEM ${OPENSSL_INCLUDE_PATH})
INCLUDE_DIRECTORIES(SYSTEM ${CURL_INCLUDE_PATH}) 

add_executable(renderexample_app
    render-example.cpp
)

if(NOT APPLE)
    find_package(ZLIB REQUIRED)
    target_link_libraries(renderexample_app PRIVATE ZLIB::ZLIB)
endif()


target_link_libraries(renderexample_app
  PRIVATE
    grpcproxylib 
    ${GRPC_LIB}
    ${PROTOBUF_LIB}
    ${RE2_LIB}
    ${OPENSSL_LIB}
    ${ABSL_LIB}
    dl
    rt
    pthread
    z
    resolv
)

# Include the grpcmodulelib headers if needed
target_include_directories(renderexample_app PRIVATE
  ${CMAKE_SOURCE_DIR}/grpcproxy
)