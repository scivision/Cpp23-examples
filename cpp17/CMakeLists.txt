set_property(DIRECTORY PROPERTY LABELS 17)

check_cxx_symbol_exists(__cpp_fold_expressions "" HAVE_FOLD)
if(HAVE_FOLD)
  add_executable(folding folding.cpp)
  add_test(NAME folding COMMAND folding)
endif()

check_cxx_symbol_exists(__cpp_deduction_guides "" HAVE_CTAD)
if(HAVE_CTAD)
  add_executable(random_string random_string.cpp)
  add_test(NAME random_string COMMAND random_string)
endif()
