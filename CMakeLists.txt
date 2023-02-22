cmake_minimum_required(VERSION 3.25...3.26)

project(Cpp23examples LANGUAGES CXX)

enable_testing()

option(tidy "Run clang-tidy")

set(CMAKE_CXX_STANDARD 23)

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

file(GENERATE OUTPUT .gitignore CONTENT "*")
