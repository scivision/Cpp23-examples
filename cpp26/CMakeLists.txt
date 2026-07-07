set_property(DIRECTORY PROPERTY LABELS 26)

set(CMAKE_CXX_STANDARD 26)

foreach(f IN LISTS cpp26features)
  if(f STREQUAL "embed")
    check_cxx_symbol_exists(__cpp_pp_embed "" have_embed)
  elseif(f STREQUAL "saturation_arithmetic")
    block()
    set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
    check_source_compiles(CXX
    [=[
    #include <numeric>
    #if !defined(__cpp_lib_saturation_arithmetic) || __cpp_lib_saturation_arithmetic < 202603L
    #error "saturation_arithmetic not available"
    #endif
    ]=]
    have_saturation_arithmetic)
    endblock()
  else()
    check_cxx_symbol_exists(__cpp_lib_${f} "version" have_${f})
  endif()
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
  target_include_directories(${t} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

  add_test(NAME ${t} COMMAND ${t})
endforeach()
