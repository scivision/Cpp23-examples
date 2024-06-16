set_property(DIRECTORY PROPERTY LABELS 17)

set(CMAKE_CXX_STANDARD 17)

# GCC >= 5 added __has_include, __has_cpp_attribute
check_cxx_symbol_exists(__has_include "" has_include)
check_cxx_symbol_exists(__has_cpp_attribute "" has_cpp_attribute)

check_cxx_symbol_exists(__cpp_fold_expressions "" cpp17_folding)
check_cxx_symbol_exists(__cpp_deduction_guides "" cpp17_deduction_guides)
check_cxx_symbol_exists(__cpp_lib_sample "algorithm" cpp17_sample)
check_cxx_symbol_exists(__cpp_lib_math_special_functions "cmath" cpp17_math_special_functions)

# NOTE: this is not a complete c++17 filesystem check. See:
# https://github.com/scivision/fortran-filesystem/blob/main/cmake/CppCheck.cmake
check_cxx_symbol_exists(__cpp_lib_filesystem "filesystem" cpp17_filesystem)

if(has_cpp_attribute)

check_source_compiles(CXX
"#if !__has_cpp_attribute(maybe_unused)
#error \"no maybe_unused attribute\"
#endif
int main(){ return 0; }"
cpp17_maybe_unused
)

check_source_compiles(CXX
"#if !__has_cpp_attribute(fallthrough)
#error \"no fallthrough attribute\"
#endif
int main(){ return 0; }"
cpp17_fallthrough
)

endif()

check_source_compiles(CXX
"int main() {
  switch (int n = 1)
  case 1:
    return 0;
  return 0;
}"
cpp17_init_if_switch
)

set(f17
deduction_guides fallthrough filesystem folding
init_if_switch maybe_unused
math_special_functions
sample
)

foreach(t IN LISTS f17)
  if(cpp17_${t})
    add_executable(${t} ${t}.cpp)

    add_test(NAME ${t} COMMAND ${t})
  endif()
endforeach()

if(TARGET filesystem)
  if( (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "9.1.0") OR
    (LINUX AND CMAKE_CXX_COMPILER_ID STREQUAL "IntelLLVM" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "23") OR
    (CMAKE_CXX_COMPILER_ID STREQUAL "NVHPC" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "23.11") )
    target_link_libraries(filesystem PRIVATE stdc++fs stdc++)
  endif()
endif()

# --- count features enabled
get_property(t DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY BUILDSYSTEM_TARGETS)
list(LENGTH f17 Nf)
list(LENGTH t Ne)
message(STATUS "C++17 features: ${Ne} / ${Nf}")
if(Ne LESS Nf)
  message(STATUS "enabled targets: ${t}")
endif()
