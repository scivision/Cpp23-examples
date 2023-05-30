include(CheckSourceCompiles)
include(CheckCXXSymbolExists)
include(CheckIncludeFileCXX)

# makes unsupported attributes checks error.
if(MSVC)
  string(APPEND CMAKE_REQUIRED_FLAGS " /WX")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|^Intel")
  string(APPEND CMAKE_REQUIRED_FLAGS " -Werror")
  add_compile_options(-Wall -Wextra)
endif()

add_compile_definitions($<$<BOOL:${MSVC}>:_CRT_SECURE_NO_WARNINGS>)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:/experimental:module;/std:c++latest;/EHsc>")
  string(APPEND CMAKE_REQUIRED_FLAGS " /experimental:module /std:c++latest /EHsc")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 11)
  add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-fmodules-ts>")
  string(APPEND CMAKE_REQUIRED_FLAGS " -fmodules-ts")
  # -x c++-system-header not work
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-fmodules>")
  string(APPEND CMAKE_REQUIRED_FLAGS " -fmodules")
endif()

message(VERBOSE "CMAKE_REQUIRED_FLAGS: ${CMAKE_REQUIRED_FLAGS}")

# https://en.cppreference.com/w/cpp/feature_test

include(${CMAKE_CURRENT_LIST_DIR}/cpp_modules.cmake)
