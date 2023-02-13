cmake_minimum_required(VERSION 3.25...3.26)

project(Cpp23examples LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 23)

# makes unsupported attributes checks error.
if(MSVC)
  list(APPEND CMAKE_REQUIRED_FLAGS /WX)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|^Intel")
  list(APPEND CMAKE_REQUIRED_FLAGS -Werror)
endif()

include(cmake/compilers.cmake)

add_subdirectory(cpp11)
add_subdirectory(cpp14)
add_subdirectory(cpp17)
add_subdirectory(cpp20)
add_subdirectory(cpp23)
