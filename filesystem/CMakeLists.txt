add_executable(filesep filesep.cpp)
target_compile_features(filesep PRIVATE cxx_std_17)
add_test(NAME Filesep-17 COMMAND filesep)

include(CheckCSourceRuns)
include(CheckCXXSourceCompiles)
include(CheckCXXSourceRuns)
include(CheckIncludeFileCXX)

if(NOT APPLE)  # FIXME: need to make check in Fortran not C.
# has to be run() test for detecting defective system realpath()
if(WIN32)
  set(_code "
#include <stdlib.h>
#include <string.h>
int main(void) {
char resolved_path[_MAX_PATH];
_fullpath(resolved_path, \"..\", _MAX_PATH);
if(strcmp(\"..\", resolved_path) == 0 || strcmp(\".\", resolved_path) == 0) return 1;
return 0; }")
check_c_source_runs("${_code}" windowsio_OK)
  set(posixio_OK false)
else()
  set(_code "
#include <limits.h>
#include <stdlib.h>
#include <string.h>
int main(void) {
char resolved_path[PATH_MAX];
realpath(\"..\", resolved_path);
if(strcmp(\"..\", resolved_path) == 0 || strcmp(\".\", resolved_path) == 0) return 1;
return 0; }")
  check_c_source_runs("${_code}" posixio_OK)
  set(windowsio_OK false)
endif()


# if(posixio_OK OR windowsio_OK)
#   add_test(NAME io:canonical COMMAND $<TARGET_FILE:realpath>)
#   set_tests_properties(io:canonical PROPERTIES
#     SKIP_RETURN_CODE 77)
# endif()
endif(NOT APPLE)


# verify C++ compiler can do C++17 filesystem
if(MSVC)
  set(CMAKE_REQUIRED_FLAGS /std:c++17)
else()
  set(CMAKE_REQUIRED_FLAGS -std=c++17)
endif()
check_include_file_cxx("filesystem" cxx17filesystem_ok)

if(NOT cxx17filesystem_ok)
  return()
endif()

add_library(canonical_cxx OBJECT canonical.cxx)
target_compile_features(canonical_cxx PRIVATE cxx_std_17)

# NOTE: icl canonical.cxx canonical_demo.cxx works, so this must be a CMake bug.
#  LNK2019: unresolved external symbol wmemcmp referenced in function "public: static int __cdecl std::_WChar_traits<wchar_t>::compare
if(WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL Intel)
  message(STATUS "CMake has a bug with Intel 2020 linking c++17")
else()
  add_executable(canonical_demo canonical_demo.cxx)
  target_link_libraries(canonical_demo PRIVATE canonical_cxx)
  target_compile_features(canonical_demo PRIVATE cxx_std_17)

  add_test(NAME CanonicalC++ COMMAND canonical_demo)
endif()
