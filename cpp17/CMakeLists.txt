set_property(DIRECTORY PROPERTY LABELS 17)

check_cxx_symbol_exists(__cpp_fold_expressions "utility" HAVE_FOLD)
if(HAVE_FOLD)
  add_executable(folding folding.cpp)
  add_test(NAME folding COMMAND folding)
endif()
