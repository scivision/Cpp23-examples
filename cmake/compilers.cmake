include(CheckSourceCompiles)
include(CheckCXXSymbolExists)
include(CheckIncludeFileCXX)


set(CMAKE_CXX_STANDARD 23)

add_compile_definitions($<$<BOOL:${MSVC}>:_CRT_SECURE_NO_WARNINGS>)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:/experimental:module;/std:c++latest;/EHsc>")
  set(CMAKE_REQUIRED_FLAGS /experimental:module /std:c++latest /EHsc)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 11)
  add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-fmodules-ts>")
  set(CMAKE_REQUIRED_FLAGS -fmodules-ts)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-fmodules>")
  set(CMAKE_REQUIRED_FLAGS -fmodules)
endif()

message(VERBOSE "CMAKE_REQUIRED_FLAGS: ${CMAKE_REQUIRED_FLAGS}")

check_include_file_cxx(stdfloat HAVE_STDFLOAT)

# https://en.cppreference.com/w/cpp/feature_test

check_cxx_symbol_exists(__cpp_lib_expected expected HAVE_EXPECTED)
check_cxx_symbol_exists(__cpp_lib_print print HAVE_PRINT)

check_cxx_symbol_exists(__cpp_lib_filesystem filesystem FEATURE_CXX17_FILESYSTEM)
check_cxx_symbol_exists(__cpp_lib_coroutine coroutine HAVE_COROUTINE)
check_cxx_symbol_exists(__cpp_lib_math_constants numbers HAVE_NUMBERS)

# --- likely
check_source_compiles(CXX
[=[

#if !__has_cpp_attribute(likely)
#error "no likely attribute"
#endif

int main(){
if (0) [[likely]]
return 0;
else [[unlikely]]
return 1;
}
]=]
HAVE_LIKELY
)

# --- modules

check_cxx_symbol_exists(__cpp_modules "" FEATURE_CXX20_MODULES)

if(FEATURE_CXX20_MODULES AND NOT DEFINED HAVE_MODULES)
  message(CHECK_START "Checking if C++ modules are working")

  try_compile(HAVE_MODULES
  SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/modules/math.cpp ${CMAKE_CURRENT_SOURCE_DIR}/modules/math.ixx
  OUTPUT_VARIABLE log
  )
  if(HAVE_MODULES)
    message(CHECK_PASS "Yes")
  else()
    message(CHECK_FAIL "No")
    message(VERBOSE "${log}")
  endif()
endif()

if(HAVE_MODULES)

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

endif()

# --- threads

check_source_compiles(CXX
[=[
#include <cstdlib>
#include <thread>
int main() {
    unsigned int n = std::thread::hardware_concurrency();
    return 0;
}
]=]
HAVE_THREAD
)

# --- auto-ignore build directory
if(NOT EXISTS ${PROJECT_BINARY_DIR}/.gitignore)
  file(WRITE ${PROJECT_BINARY_DIR}/.gitignore "*")
endif()
