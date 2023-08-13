set_property(DIRECTORY PROPERTY LABELS 23)

if(NOT DEFINED cpp23_assume)
message(STATUS "Checking for C++23 features with CMAKE_REQUIRED_FLAGS: ${CMAKE_REQUIRED_FLAGS}")
endif()

check_source_compiles(CXX
"#if !__has_cpp_attribute(assume)
#error \"no assume attribute\"
#endif
int main(){ return 0; }"
cpp23_assume
)

# https://en.cppreference.com/w/cpp/header/version
check_cxx_symbol_exists(__cpp_lib_print "version" cpp23_print)
check_cxx_symbol_exists(__cpp_lib_expected "version" cpp23_expected)
check_include_file_cxx(stdfloat cpp23_stdfloat)
check_cxx_symbol_exists(__cpp_lib_unreachable "version" cpp23_unreachable)

foreach(t IN ITEMS assume expected print stdfloat)
  if(cpp23_${t})
    add_executable(${t} ${t}.cpp)
    add_test(NAME ${t} COMMAND ${t})
  endif()
endforeach()


if(cpp23_unreachable)
  add_executable(unreachable unreachable.cpp)
  add_test(NAME unreachable
    COMMAND ${CMAKE_COMMAND} -Dexe:FILEPATH=$<TARGET_FILE:unreachable> -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/will_fail.cmake)
  set_property(TEST unreachable PROPERTY WILL_FAIL TRUE)
endif()


if(TEST expected)
  set_property(TEST expected PROPERTY PASS_REGULAR_EXPRESSION "42")
endif()
