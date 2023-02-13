cmake_minimum_required(VERSION 3.25...3.26)

project(Cpp23examples LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 23)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  list(APPEND CMAKE_REQUIRED_FLAGS -Werror)
  # makes unsupported attributes checks error.
endif()

include(cmake/compilers.cmake)

add_subdirectory(cpp11)
add_subdirectory(cpp14)
add_subdirectory(cpp17)
add_subdirectory(cpp20)
add_subdirectory(cpp23)
