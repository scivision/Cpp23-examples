include(CheckSourceCompiles)
include(CheckCXXSymbolExists)
include(CheckIncludeFileCXX)

add_compile_definitions($<$<BOOL:${MSVC}>:_CRT_SECURE_NO_WARNINGS>)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:/experimental:module;/std:c++latest;/EHsc>")
  set(CMAKE_REQUIRED_FLAGS /experimental:module /std:c++latest /EHsc)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 11)
  add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-fmodules-ts>")
  set(CMAKE_REQUIRED_FLAGS -fmodules-ts)
  # -x c++-system-header not work
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-fmodules>")
  set(CMAKE_REQUIRED_FLAGS -fmodules)
endif()

message(VERBOSE "CMAKE_REQUIRED_FLAGS: ${CMAKE_REQUIRED_FLAGS}")

# https://en.cppreference.com/w/cpp/feature_test

include(${CMAKE_CURRENT_LIST_DIR}/cpp_modules.cmake)

# --- auto-ignore build directory
if(NOT EXISTS ${PROJECT_BINARY_DIR}/.gitignore)
  file(WRITE ${PROJECT_BINARY_DIR}/.gitignore "*")
endif()
