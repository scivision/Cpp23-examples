include(CheckSourceRuns)

add_executable(filesep filesep.cpp)
target_compile_features(filesep PRIVATE cxx_std_17)
add_test(NAME Filesep-17 COMMAND filesep)

add_executable(canonical_demo canonical_demo.cxx canonical.cxx)
target_compile_features(canonical_demo PRIVATE cxx_std_17)
add_test(NAME CanonicalC++ COMMAND canonical_demo)

add_executable(symlink is_symlink.cpp)
target_compile_features(symlink PRIVATE cxx_std_17)
add_test(NAME Symlink
COMMAND symlink ${CMAKE_CURRENT_SOURCE_DIR}/is_symlink.cpp ${CMAKE_CURRENT_BINARY_DIR}/test.lnk
)

if(WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL GNU)
  set_tests_properties(Symlink PROPERTIES DISABLED 1)
endif()

# if(NOT APPLE)  # FIXME: need to make check in Fortran not C.
# # has to be run() test for detecting defective system realpath()
# if(WIN32)
#   set(_code "
# #include <stdlib.h>
# #include <string.h>
# int main(void) {
# char resolved_path[_MAX_PATH];
# _fullpath(resolved_path, \"..\", _MAX_PATH);
# if(strcmp(\"..\", resolved_path) == 0 || strcmp(\".\", resolved_path) == 0) return 1;
# return 0; }")
# check_source_runs(C "${_code}" windowsio_OK)
#   set(posixio_OK false)
# else()
#   set(_code "
# #include <limits.h>
# #include <stdlib.h>
# #include <string.h>
# int main(void) {
# char resolved_path[PATH_MAX];
# realpath(\"..\", resolved_path);
# if(strcmp(\"..\", resolved_path) == 0 || strcmp(\".\", resolved_path) == 0) return 1;
# return 0; }")
#   check_source_runs(C "${_code}" posixio_OK)
#   set(windowsio_OK false)
# endif()


# # if(posixio_OK OR windowsio_OK)
# #   add_test(NAME io:canonical COMMAND $<TARGET_FILE:realpath>)
# #   set_tests_properties(io:canonical PROPERTIES
# #     SKIP_RETURN_CODE 77)
# # endif()
# endif(NOT APPLE)
