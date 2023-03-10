set_property(DIRECTORY PROPERTY LABELS 17)

check_cxx_symbol_exists(__cpp_fold_expressions "" cpp17_folding)
check_cxx_symbol_exists(__cpp_deduction_guides "" cpp17_ctad)
check_cxx_symbol_exists(__cpp_structured_bindings "" cpp17_structured_bindings)

# NOTE: this is not a complete c++17 filesystem check. See:
# https://github.com/scivision/fortran-filesystem/blob/main/cmake/CppCheck.cmake
check_cxx_symbol_exists(__cpp_lib_filesystem "filesystem" cpp17_filesystem)

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

check_source_compiles(CXX
"int main() {
  switch (int n = 1)
  case 1:
    return 0;
  return 0;
}"
cpp17_init_if_switch
)

foreach(t IN ITEMS fallthrough filesystem folding init_if_switch maybe_unused structured_bindings)
  if(cpp17_${t})
    add_executable(${t} ${t}.cpp)
    add_test(NAME ${t} COMMAND ${t})
  endif()
endforeach()

if(TARGET filesystem)
  target_link_libraries(filesystem PRIVATE
  "$<$<CXX_COMPILER_ID:NVHPC>:stdc++fs;stdc++>"
  )
endif()


if(cpp17_ctad)
  add_executable(random_string random_string.cpp)
  add_test(NAME random_string COMMAND random_string)
endif()
