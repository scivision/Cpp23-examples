include(CheckSourceCompiles)
include(CheckCXXSymbolExists)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_compile_definitions($<$<BOOL:${MSVC}>:_CRT_SECURE_NO_WARNINGS>)

# --- modules


if(CMAKE_CXX_COMPLIER_ID STREQUAL "MSVC")
  add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:/experimental:module;/std:c++latest;/EHsc;/MD>")
  set(CMAKE_REQUIRED_FLAGS /experimental:module /std:c++latest /EHsc /MD)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 11)
  add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-fmodules-ts>")
  set(CMAKE_REQUIRED_FLAGS -fmodules-ts)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-fmodules>")
  set(CMAKE_REQUIRED_FLAGS -fmodules)
endif()

check_source_compiles(CXX
[=[
import std.core;
int main(){
  std::cout << "hello" << std::endl;
  return 0;
}
]=]
HAVE_MSVC_STDLIB_MODULES
)


check_cxx_symbol_exists(__cpp_lib_coroutine coroutine HAVE_CXX20_COROUTINE)

check_cxx_symbol_exists(__cpp_lib_filesystem filesystem HAVE_CXX17_FILESYSTEM)

check_cxx_symbol_exists(__cpp_lib_math_constants numbers HAVE_CXX20_NUMBERS)

check_cxx_symbol_exists(__cpp_modules "" FEATURE_CXX20_MODULES)

if(FEATURE_CXX20_MODULES AND NOT DEFINED HAVE_CXX20_MODULES)
  message(CHECK_START "Checking if C++ modules are working")

  try_compile(HAVE_CXX20_MODULES
  PROJECT cppMod_check
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/modules
  CMAKE_FLAGS ${CMAKE_REQUIRED_FLAGS}
  )
  if(HAVE_CXX20_MODULES)
    message(CHECK_PASS "Yes")
  else()
    message(CHECK_FAIL "No")
  endif()
endif()


check_source_compiles(CXX
[=[
#include <cstdlib>
#include <thread>
int main() {
    unsigned int n = std::thread::hardware_concurrency();
    return EXIT_SUCCESS;
}
]=]
HAVE_CXX_THREAD
)

# --- auto-ignore build directory
if(NOT EXISTS ${PROJECT_BINARY_DIR}/.gitignore)
  file(WRITE ${PROJECT_BINARY_DIR}/.gitignore "*")
endif()
