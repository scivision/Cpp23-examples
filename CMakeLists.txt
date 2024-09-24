cmake_minimum_required(VERSION 3.25...3.30)
# CMake 3.25 for try_run() new syntax
# CMake 3.30+ for C++26

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "Please use out of source build:
  cmake -Bbuild")
endif()

project(Cpp23examples LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
# This project isn't using C++ modules; avoid bugs in module scanning CMake 3.28, 3.29 with GCC >= 14.

option(cppcheck "run cppcheck")
option(tidy "Run clang-tidy")

message(STATUS "CMake ${CMAKE_VERSION}")

# set(CMAKE_CXX_STANDARD_REQUIRED ON)  causes configure errors if not known for the compiler
set(CMAKE_CXX_EXTENSIONS OFF)

# CPPcheck
if(cppcheck)
  find_program(cppcheck_exe NAMES cppcheck REQUIRED)
  set(cppcheck_opts --enable=all --inline-suppr --quiet --suppressions-list=${PROJECT_SOURCE_DIR}/cppcheck.supp)
  set(CMAKE_CXX_CPPCHECK ${cppcheck_exe} --std=c++${CMAKE_CXX_STANDARD} ${cppcheck_opts})
endif()

if(tidy)
  find_program(CLANG_TIDY
  NAMES clang-tidy
  REQUIRED
  PATHS /opt/homebrew/opt/llvm/bin
  )

  set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY})

endif()

include(cmake/compilers.cmake)

# --- features possible
set(cpp11features current_exception iota getenv nullptr)
if(WIN32)
  list(APPEND cpp11features GetLastError)
endif()

set(cpp14features make_unique thread)

set(cpp17features
deduction_guides fallthrough filesystem folding
init_if_switch maybe_unused
math_special_functions
sample
)

set(cpp20features
semaphore barrier
bit_width execution_policy
hardware_interference_size
format jthread latch lerp midpoint
likely math_constants ranges_find
source_location smart_ptr_for_overwrite
stop_callback stop_source
structured_bindings
)

set(cpp23features
assume expected flat_map flat_set mdspan print
stacktrace stdfloat unreachable
)

set(cpp26features adl_projected format_pointer linalg saturation_arithmetic)

# --- check for possible features

set(stds 11 14 17 20 23)
if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.30)
  list(APPEND stds 26)
endif()

foreach(s IN LISTS stds)
  add_subdirectory(cpp${s})
endforeach()


file(GENERATE OUTPUT .gitignore CONTENT "*")

# --- count features enabled by language standard
set(j "{}")

foreach(s IN LISTS stds)

get_property(has_features DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/cpp${s} PROPERTY BUILDSYSTEM_TARGETS)

list(LENGTH cpp${s}features Nf)

math(EXPR N "${Nf} - 1")
string(JSON j SET ${j} cpp${s} "{}")

foreach(i RANGE ${N})
  list(GET cpp${s}features ${i} feature)
  if(feature IN_LIST has_features)
    set(hasf true)
  else()
    set(hasf false)
  endif()

  string(JSON j SET ${j} cpp${s} ${feature} ${hasf})
endforeach()

endforeach()

if(have_coroutine)
  string(JSON j SET ${j} cpp20 coroutine true)
else()
  string(JSON j SET ${j} cpp20 coroutine false)
endif()

set(feature_file ${CMAKE_CURRENT_BINARY_DIR}/features.json)

file(WRITE ${feature_file} ${j})

message(STATUS "See ${feature_file} for features enabled by standard")
