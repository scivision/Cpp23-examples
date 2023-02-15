set_property(DIRECTORY PROPERTY LABELS 17)

check_cxx_symbol_exists(__cpp_fold_expressions "" cpp17_folding)
check_cxx_symbol_exists(__cpp_deduction_guides "" cpp17_ctad)

check_source_compiles(CXX
"#if !__has_cpp_attribute(maybe_unused)
#error \"no maybe_unused attribute\"
#endif
int main(){ return 0; }"
cpp17_maybe_unused
)

foreach(t IN ITEMS folding maybe_unused)
  if(cpp17_${t})
    add_executable(${t} ${t}.cpp)
    add_test(NAME ${t} COMMAND ${t})
  endif()
endforeach()


if(cpp17_ctad)
  add_executable(random_string random_string.cpp)
  add_test(NAME random_string COMMAND random_string)
endif()
