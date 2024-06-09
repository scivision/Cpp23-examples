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

add_subdirectory(cpp11)
add_subdirectory(cpp14)
add_subdirectory(cpp17)
add_subdirectory(cpp20)
add_subdirectory(cpp23)

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.30)
  add_subdirectory(cpp26)
endif()

file(GENERATE OUTPUT .gitignore CONTENT "*")
