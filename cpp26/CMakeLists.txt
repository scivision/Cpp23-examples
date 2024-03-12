set_property(DIRECTORY PROPERTY LABELS 26)

check_cxx_symbol_exists(__cpp_lib_fstream_native_handle "version" cpp26_fstream)

file(READ adl_projected.cpp src)
check_source_compiles(CXX "${src}" cpp26_adl_projected)

if(cpp20_format)
  file(READ format_pointer.cpp src)
  check_source_compiles(CXX "${src}" cpp26_format_pointer)
endif()

foreach(t IN ITEMS adl_projected format_pointer fstream)
  if(cpp26_${t})
    add_executable(${t} ${t}.cpp)
    add_test(NAME ${t} COMMAND ${t})
  endif()
endforeach()

if(APPLE AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(adl_projected PRIVATE -Wno-unused-variable)
endif()
