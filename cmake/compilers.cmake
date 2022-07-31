include(CheckSourceCompiles)
include(CheckCXXSymbolExists)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_compile_definitions($<$<BOOL:${MSVC}>:_CRT_SECURE_NO_WARNINGS>)

# --- modules

add_compile_options("$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/experimental:module;/std:c++latest;/EHsc;/MD>")

if(MSVC)
  # can't use get_property(DIRECTORY COMPILE_OPTIONS) due to generator expressions not yet evaluated
  set(CMAKE_REQUIRED_FLAGS /experimental:module /std:c++latest /EHsc /MD)
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

check_cxx_symbol_exists(__cpp_modules "" HAVE_CXX20_MODULES)


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
