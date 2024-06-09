#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "cjson_utils" for configuration ""
set_property(TARGET cjson_utils APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(cjson_utils PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "/usr/lib/x86_64-linux-gnu/libcjson_utils.so.1.7.18"
  IMPORTED_SONAME_NOCONFIG "libcjson_utils.so.1"
  )

list(APPEND _cmake_import_check_targets cjson_utils )
list(APPEND _cmake_import_check_files_for_cjson_utils "/usr/lib/x86_64-linux-gnu/libcjson_utils.so.1.7.18" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
