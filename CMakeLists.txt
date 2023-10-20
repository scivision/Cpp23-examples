cmake_minimum_required(VERSION 3.20...3.28)
# CMake 3.20 for C++23
# CMake 3.25 for C++26

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "Please use out of source build:
  cmake -Bbuild")
endif()

project(Cpp23examples LANGUAGES CXX)

enable_testing()

option(cppcheck "run cppcheck")
option(tidy "Run clang-tidy")

message(STATUS "CMake ${CMAKE_VERSION}")

set(CMAKE_CXX_STANDARD 23)

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
add_subdirectory(cpp26)

file(GENERATE OUTPUT .gitignore CONTENT "*")
