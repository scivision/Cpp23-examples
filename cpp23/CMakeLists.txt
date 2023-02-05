set_property(DIRECTORY PROPERTY LABELS 23)

check_cxx_symbol_exists(__cpp_lib_unreachable utility HAVE_UNREACHABLE)
if(HAVE_UNREACHABLE)
  add_executable(unreachable unreachable.cpp)
  add_test(NAME unreachable
    COMMAND ${CMAKE_COMMAND} -Dexe:FILEPATH=$<TARGET_FILE:unreachable> -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/will_fail.cmake)
  set_property(TEST unreachable PROPERTY WILL_FAIL TRUE)
endif()

check_cxx_symbol_exists(__cpp_lib_expected expected HAVE_EXPECTED)
if(HAVE_EXPECTED)
  add_executable(expected expected.cpp)
  add_test(NAME expected COMMAND expected)
  set_property(TEST expected PROPERTY PASS_REGULAR_EXPRESSION "42")
endif()

check_cxx_symbol_exists(__cpp_lib_print print HAVE_PRINT)
if(HAVE_PRINT)
  add_executable(print print.cpp)
  add_test(NAME print COMMAND print)
endif()

check_include_file_cxx(stdfloat HAVE_STDFLOAT)
if(HAVE_STDFLOAT)
  add_executable(stdfloat stdfloat.cpp)
  add_test(NAME stdfloat COMMAND stdfloat)
endif()
