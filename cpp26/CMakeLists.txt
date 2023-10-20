set_property(DIRECTORY PROPERTY LABELS 26)

check_cxx_symbol_exists(__cpp_lib_fstream_native_handle "version" cpp26_fstream)

foreach(t IN ITEMS fstream)
  if(cpp26_${t})
    add_executable(${t} ${t}.cpp)
    add_test(NAME ${t} COMMAND ${t})
  endif()
endforeach()
