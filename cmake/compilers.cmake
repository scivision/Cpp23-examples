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

add_compile_definitions($<$<BOOL:${WIN32}>:_CRT_SECURE_NO_WARNINGS>)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # /std:c++20 or newer implicitly enables modules
  # https://learn.microsoft.com/en-us/cpp/build/reference/experimental-module
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 14.1)
  add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-fmodules-ts>")
  string(APPEND CMAKE_REQUIRED_FLAGS " -fmodules-ts")
  # -x c++-system-header not work
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 17)
  # -std=c++20 or higher implicitly enables modules
  # https://releases.llvm.org/17.0.1/tools/clang/docs/StandardCPlusPlusModules.html#how-to-enable-standard-c-modules
endif()

message(VERBOSE "CMAKE_REQUIRED_FLAGS: ${CMAKE_REQUIRED_FLAGS}")

include(${CMAKE_CURRENT_LIST_DIR}/cpp_modules.cmake)
