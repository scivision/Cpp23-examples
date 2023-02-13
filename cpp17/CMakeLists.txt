set_property(DIRECTORY PROPERTY LABELS 17)

check_cxx_symbol_exists(__cpp_fold_expressions "" cpp17_fold)

if(cpp17_fold)
  add_executable(folding folding.cpp)
  add_test(NAME folding COMMAND folding)
endif()

check_cxx_symbol_exists(__cpp_deduction_guides "" cpp17_ctad)
if(cpp17_ctad)
  add_executable(random_string random_string.cpp)
  add_test(NAME random_string COMMAND random_string)
endif()

check_source_compiles(CXX
"#if !__has_cpp_attribute(maybe_unused)
#error \"no maybe_unused attribute\"
#endif
int main(){ return 0; }"
cpp17_maybe_unused
)
if(cpp17_maybe_unused)
  add_executable(maybe_unused maybe_unused.cpp)
  add_test(NAME maybe_unused COMMAND maybe_unused)
endif()
