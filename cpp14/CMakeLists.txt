set_property(DIRECTORY PROPERTY LABELS 14)

set(CMAKE_CXX_STANDARD 14)

check_cxx_symbol_exists(__cpp_lib_make_unique "memory" have_make_unique)

check_include_file_cxx(thread have_thread)

foreach(t IN LISTS cpp14features)
  if(have_${t})
    add_executable(${t} ${t}.cpp)

    add_test(NAME ${t} COMMAND ${t})
  endif()
endforeach()
