#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "utf8_range::utf8_validity" for configuration "Debug"
set_property(TARGET utf8_range::utf8_validity APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(utf8_range::utf8_validity PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C;CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug_64/utf8_validity.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS utf8_range::utf8_validity )
list(APPEND _IMPORT_CHECK_FILES_FOR_utf8_range::utf8_validity "${_IMPORT_PREFIX}/debug_64/utf8_validity.lib" )

# Import target "utf8_range::utf8_range" for configuration "Debug"
set_property(TARGET utf8_range::utf8_range APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(utf8_range::utf8_range PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug_64/utf8_range.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS utf8_range::utf8_range )
list(APPEND _IMPORT_CHECK_FILES_FOR_utf8_range::utf8_range "${_IMPORT_PREFIX}/debug_64/utf8_range.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
