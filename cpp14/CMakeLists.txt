set_property(DIRECTORY PROPERTY LABELS 14)

check_cxx_symbol_exists(__cpp_lib_make_unique "memory" cpp14_make_unique)

file(READ thread.cpp src)
check_source_compiles(CXX "${src}" cpp14_thread)


foreach(t IN ITEMS thread make_unique)
  if(cpp14_${t})
    add_executable(${t} ${t}.cpp)
    add_test(NAME ${t} COMMAND ${t})
  endif()
endforeach()
