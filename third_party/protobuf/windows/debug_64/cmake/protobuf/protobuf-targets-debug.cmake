#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "protobuf::libprotobuf-lite" for configuration "Debug"
set_property(TARGET protobuf::libprotobuf-lite APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(protobuf::libprotobuf-lite PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX;RC"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug_64/libprotobuf-lite.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS protobuf::libprotobuf-lite )
list(APPEND _IMPORT_CHECK_FILES_FOR_protobuf::libprotobuf-lite "${_IMPORT_PREFIX}/debug_64/libprotobuf-lite.lib" )

# Import target "protobuf::libprotobuf" for configuration "Debug"
set_property(TARGET protobuf::libprotobuf APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(protobuf::libprotobuf PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX;RC"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug_64/libprotobuf.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS protobuf::libprotobuf )
list(APPEND _IMPORT_CHECK_FILES_FOR_protobuf::libprotobuf "${_IMPORT_PREFIX}/debug_64/libprotobuf.lib" )

# Import target "protobuf::libprotoc" for configuration "Debug"
set_property(TARGET protobuf::libprotoc APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(protobuf::libprotoc PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX;RC"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug_64/libprotoc.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS protobuf::libprotoc )
list(APPEND _IMPORT_CHECK_FILES_FOR_protobuf::libprotoc "${_IMPORT_PREFIX}/debug_64/libprotoc.lib" )

# Import target "protobuf::protoc" for configuration "Debug"
set_property(TARGET protobuf::protoc APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(protobuf::protoc PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/protoc.exe"
  )

list(APPEND _IMPORT_CHECK_TARGETS protobuf::protoc )
list(APPEND _IMPORT_CHECK_FILES_FOR_protobuf::protoc "${_IMPORT_PREFIX}/bin/protoc.exe" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
