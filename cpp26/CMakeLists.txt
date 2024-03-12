set_property(DIRECTORY PROPERTY LABELS 26)

check_cxx_symbol_exists(__cpp_lib_fstream_native_handle "version" cpp26_fstream)

file(READ ${CMAKE_CURRENT_SOURCE_DIR}/adl_projected.cpp src)
check_source_compiles(CXX "${src}" cpp26_adl_projected)

foreach(t IN ITEMS adl_projected fstream)
  if(cpp26_${t})
    add_executable(${t} ${t}.cpp)
    add_test(NAME ${t} COMMAND ${t})
  endif()
endforeach()

if(APPLE AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(adl_projected PRIVATE -Wno-unused-variable)
endif()
