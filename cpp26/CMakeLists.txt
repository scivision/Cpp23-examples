set_property(DIRECTORY PROPERTY LABELS 26)

# FIXME: workaround for oneAPI till CMake 3.30 is released.
if(CMAKE_VERSION VERSION_LESS 3.30 AND CMAKE_CXX_COMPILER_ID STREQUAL "IntelLLVM")
  if(WIN32)
    set(CMAKE_REQUIRED_FLAGS "/Qstd:c++26")
  else()
    set(CMAKE_REQUIRED_FLAGS "-std=c++26")
  endif()
  set(oneapi_workaround
  CMAKE_FLAGS -DCOMPILE_DEFINITIONS=${CMAKE_REQUIRED_FLAGS}
  CXX_STANDARD 26
  )
else()
  set(CMAKE_CXX_STANDARD 26)
endif()

# https://en.cppreference.com/w/cpp/numeric/linalg
check_cxx_symbol_exists(__cpp_lib_linalg "version" have_linalg)


if(have_format AND NOT DEFINED cpp_lib_format)
  # provide C++20 format feature level for all directories
  try_run(format_ret format_build_ok
  SOURCES ${PROJECT_SOURCE_DIR}/cpp20/format.cpp
  RUN_OUTPUT_STDOUT_VARIABLE cpp_lib_format
  ${oneapi_workaround}
  )
  if(format_ret EQUAL 0 AND format_build_ok AND cpp_lib_format)
    string(STRIP "${cpp_lib_format}" cpp_lib_format)
    set(cpp_lib_format "${cpp_lib_format}" CACHE STRING "C++ format feature level")
    message(STATUS "C++ format feature level: ${cpp_lib_format}")
  else()
    message(WARNING "C++ format feature level not determined")
  endif()
else()
  set(cpp_lib_format 0 CACHE STRING "C++ format feature level not available")
endif()

if(cpp_lib_format GREATER_EQUAL 202304)
  set(have_format_pointer true)
endif()


# not a useful test for adl_projected: __cpp_lib_default_template_type_for_algorithm_values
file(READ adl_projected.cpp src)
check_source_compiles(CXX "${src}" have_adl_projected)

set(f26 adl_projected format_pointer linalg)

foreach(t IN LISTS f26)
  if(have_${t})
    add_executable(${t} ${t}.cpp)

    add_test(NAME ${t} COMMAND ${t})
  endif()
endforeach()

if(APPLE AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
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
