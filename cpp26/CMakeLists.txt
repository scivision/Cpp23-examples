set_property(DIRECTORY PROPERTY LABELS 26)

set(CMAKE_CXX_STANDARD 26)

foreach(f IN LISTS cpp26features)
  check_cxx_symbol_exists(__cpp_lib_${f} "version" have_${f})
endforeach()

# using try_run was not adequate
file(READ format_pointer.cpp _src)
check_source_compiles(CXX "${_src}" have_format_pointer)

# not a useful test for adl_projected: __cpp_lib_default_template_type_for_algorithm_values
file(READ adl_projected.cpp src)
check_source_compiles(CXX "${src}" have_adl_projected)


foreach(t IN LISTS cpp26features)
  if(NOT have_${t})
    continue()
  endif()

  add_executable(${t} ${t}.cpp)

  add_test(NAME ${t} COMMAND ${t})
endforeach()
