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
