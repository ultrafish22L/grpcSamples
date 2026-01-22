#  grpc examples CMakeLists.txt
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
SET(THIRDPARTY_BUILD_SUFFIX _cxx11)
SET(BUILD_TYPE release)
# set platform dependent parameters
IF(APPLE)
#    SET(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++ --sysroot ${CMAKE_OSX_SYSROOT} ${CMAKE_CXX_FLAGS}")
    SET(THIRDPARTY_PLATFORM osx)
ELSE(APPLE)
#    SET(CMAKE_CXX_FLAGS "-std=c++11")
    SET(THIRDPARTY_PLATFORM linux)
ENDIF(APPLE)

SET(THIRD_PARTY_PATH ${CMAKE_SOURCE_DIR}/../thirdparty)

# OpenSSL
SET(OPENSSL_LIB             ssl crypto)
SET(OPENSSL_INCLUDE_PATH    ${THIRD_PARTY_PATH}/openssl/${THIRDPARTY_PLATFORM}/include)
SET(OPENSSL_LIB_PATH        ${THIRD_PARTY_PATH}/openssl/${THIRDPARTY_PLATFORM}/${BUILD_TYPE})

# absl - protobuf & gRPC dependency
SET(ABSL_LIB                absl_str_format_internal
                            absl_strings
                            absl_strings_internal
                            absl_hash
                            absl_city
                            absl_civil_time
                            absl_cord
                            absl_cordz_functions
                            absl_cordz_info
                            absl_cordz_handle
                            absl_cordz_sample_token
                            absl_cord_internal
                            absl_crc_cord_state
                            absl_crc32c
                            absl_crc_cpu_detect
                            absl_crc_internal
                            absl_die_if_null
                            absl_exponential_biased
                            absl_failure_signal_handler
                            absl_flags_reflection
                            absl_flags_internal
                            absl_flags_config
                            absl_flags_commandlineflag
                            absl_flags_commandlineflag_internal
                            absl_flags_marshalling
                            absl_flags_parse
                            absl_flags_private_handle_accessor
                            absl_flags_program_name
                            absl_flags_usage
                            absl_flags_usage_internal
                            absl_graphcycles_internal
                            absl_status
                            absl_int128
                            absl_kernel_timeout_internal
                            absl_leak_check
                            absl_vlog_config_internal
                            absl_log_flags
                            absl_log_globals
                            absl_log_initialize
                            absl_log_internal_check_op
                            absl_log_internal_conditions
                            absl_log_internal_fnmatch
                            absl_log_internal_message
                            absl_log_internal_globals
                            absl_log_internal_log_sink_set
                            absl_log_internal_format
                            absl_log_internal_nullguard
                            absl_log_internal_proto
                            absl_log_internal_structured_proto
                            absl_log_severity
                            absl_log_sink
                            absl_examine_stack
                            absl_low_level_hash
                            absl_spinlock_wait
                            absl_periodic_sampler
                            absl_poison
                            absl_raw_hash_set
                            absl_hashtablez_sampler
                            absl_raw_logging_internal
                            absl_scoped_set_env
                            absl_stacktrace
                            absl_statusor
                            absl_symbolize
                            absl_debugging_internal
                            absl_demangle_internal
                            absl_demangle_rust
                            absl_decode_rust_punycode
                            absl_synchronization
                            absl_throw_delegate
                            absl_time
                            absl_time_zone
                            absl_random_distributions
                            absl_random_internal_distribution_test_util
                            absl_random_internal_entropy_pool
                            absl_random_internal_platform
                            absl_random_internal_randen
                            absl_random_internal_randen_hwaes
                            absl_random_internal_randen_hwaes_impl
                            absl_random_internal_randen_slow
                            absl_random_internal_seed_material
                            absl_random_seed_gen_exception
                            absl_random_seed_sequences
                            absl_random_internal_platform
                            absl_strerror
                            absl_utf8_for_code_point
                            absl_malloc_internal 
                            absl_string_view
                            absl_base
                            )
SET(ABSL_INCLUDE_PATH       ${THIRD_PARTY_PATH}/absl/${THIRDPARTY_PLATFORM}/include)
SET(ABSL_LIB_PATH           ${THIRD_PARTY_PATH}/absl/${THIRDPARTY_PLATFORM}/${BUILD_TYPE})

# Protocol Buffers
SET(PROTOBUF_LIB            protobuf
                            utf8_range
                            utf8_validity
                            )
SET(PROTOBUF_INCLUDE_PATH   ${THIRD_PARTY_PATH}/protobuf/${THIRDPARTY_PLATFORM}/include)
SET(PROTOBUF_LIB_PATH       ${THIRD_PARTY_PATH}/protobuf/${THIRDPARTY_PLATFORM}/${BUILD_TYPE})

# re2 - gRPC dependancy
SET(RE2_LIB              re2)
SET(RE2_INCLUDE_PATH     ${THIRD_PARTY_PATH}/re2/${THIRDPARTY_PLATFORM}/include)
SET(RE2_LIB_PATH         ${THIRD_PARTY_PATH}/re2/${THIRDPARTY_PLATFORM}/${BUILD_TYPE})

# gRPC
SET(GRPC_LIB            grpc++
                        grpc
                        grpc++_alts
                        gpr
                        address_sorting
                        upb_textformat_lib
                        upb_wire_lib
                        upb_json_lib
                        upb_message_lib
                        upb_mini_descriptor_lib
                        upb_mem_lib
                        utf8_range_lib
                        upb_base_lib
                        )
SET(GRPC_INCLUDE_PATH   ${THIRD_PARTY_PATH}/grpc/${THIRDPARTY_PLATFORM}/include)
SET(GRPC_LIB_PATH       ${THIRD_PARTY_PATH}/grpc/${THIRDPARTY_PLATFORM}/${BUILD_TYPE})

# Curl
SET(CURL_LIB            curl)
SET(CURL_LIB_PATH       ${THIRD_PARTY_PATH}/curl/${THIRDPARTY_PLATFORM}/${BUILD_TYPE})
SET(CURL_INCLUDE_PATH   ${THIRD_PARTY_PATH}/curl/${THIRDPARTY_PLATFORM}/include)
 

link_directories(
    #/home/user/vcpkg/installed/x64-linux-release/lib
    ${ABSL_LIB_PATH}
    ${RE2_LIB_PATH}
    ${PROTOBUF_LIB_PATH}
    ${GRPC_LIB_PATH}
    ${CURL_LIB_PATH}
    ${OPENSSL_LIB_PATH}
)

cmake_minimum_required(VERSION 3.10)
project(TestGrpcProxyLib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the library subdirectory
add_subdirectory(grpcproxy)

# Add the application subdirectories
add_subdirectory(render-example)
