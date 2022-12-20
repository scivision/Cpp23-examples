set_property(DIRECTORY PROPERTY LABELS 17)

add_executable(filesep filesep.cpp)
add_test(NAME Filesep COMMAND filesep)

add_executable(canonical_demo canonical_demo.cxx canonical.cxx)
add_test(NAME CanonicalC++ COMMAND canonical_demo)

add_executable(symlink is_symlink.cpp)
add_test(NAME Symlink
COMMAND symlink ${CMAKE_CURRENT_SOURCE_DIR}/is_symlink.cpp ${CMAKE_CURRENT_BINARY_DIR}/test.lnk
)

if(WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL GNU)
  set_property(TEST Symlink PROPERTY DISABLED 1)
endif()
