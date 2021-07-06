include(CheckSourceRuns)
include(CheckSourceCompiles)
include(CheckIncludeFileCXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

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
check_source_runs(C "${_code}" windowsio_OK)
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
  check_source_runs(C "${_code}" posixio_OK)
  set(windowsio_OK false)
endif()


# if(posixio_OK OR windowsio_OK)
#   add_test(NAME io:canonical COMMAND $<TARGET_FILE:realpath>)
#   set_tests_properties(io:canonical PROPERTIES
#     SKIP_RETURN_CODE 77)
# endif()
endif(NOT APPLE)


# verify C++ compiler can do C++17 filesystem
check_source_compiles(CXX
"#include <filesystem>
int main(){
std::filesystem::path p;
return EXIT_SUCCESS; }"
HAVE_CXX17_FILESYSTEM)

if(NOT HAVE_CXX17_FILESYSTEM)
  return()
endif()

add_executable(filesep filesep.cpp)
add_test(NAME Filesep-17 COMMAND filesep)

add_library(canonical_cxx OBJECT canonical.cxx)

# NOTE:
# icl /std:c++17 canonical.cxx canonical_demo.cxx
# or
# icx /std:c++17 canonical.cxx canonical_demo.cxx
# works.
#  LNK2019: unresolved external symbol wmemcmp referenced in function "public: static int __cdecl std::_WChar_traits<wchar_t>::compare
# this is a known bug since Intel 19.0 at least
if(WIN32 AND CMAKE_CXX_COMPILER_ID MATCHES Intel)
  message(STATUS "CMake has a bug with Intel 2020 linking c++17")
else()
  add_executable(canonical_demo canonical_demo.cxx)
  target_link_libraries(canonical_demo PRIVATE canonical_cxx)

  add_test(NAME CanonicalC++ COMMAND canonical_demo)
endif()
