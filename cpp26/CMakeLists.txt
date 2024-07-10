set_property(DIRECTORY PROPERTY LABELS 26)

set(CMAKE_CXX_STANDARD 26)

foreach(f IN ITEMS debugging linalg saturation_arithmetic)
  check_cxx_symbol_exists(__cpp_lib_${f} "version" have_${f})
endforeach()

# using try_run was not adequate
file(READ format_pointer.cpp _src)
check_source_compiles(CXX "${_src}" have_format_pointer)

# not a useful test for adl_projected: __cpp_lib_default_template_type_for_algorithm_values
file(READ adl_projected.cpp src)
check_source_compiles(CXX "${src}" have_adl_projected)


set(f26 adl_projected format_pointer linalg saturation_arithmetic)

foreach(t IN LISTS f26)
  if(NOT have_${t})
    continue()
  endif()

  add_executable(${t} ${t}.cpp)

  add_test(NAME ${t} COMMAND ${t})
endforeach()

if(TARGET adl_projected AND
     APPLE AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(adl_projected PRIVATE -Wno-unused-variable)
endif()

# --- count features enabled
get_property(t DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY BUILDSYSTEM_TARGETS)
list(LENGTH f26 Nf)
list(LENGTH t Ne)
message(STATUS "C++26 features: ${Ne} / ${Nf}")
if(Ne LESS Nf)
  message(STATUS "enabled targets: ${t}")
endif()
