cmake_minimum_required(VERSION 3.21...3.25)

project(CXX20examples
LANGUAGES C CXX
)

enable_testing()

include(CheckSourceCompiles)
include(CheckCXXSymbolExists)
include(CheckIncludeFileCXX)

add_compile_definitions($<$<BOOL:${MSVC}>:_CRT_SECURE_NO_WARNINGS>)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include(cmake/compilers.cmake)

if(HAVE_CXX20_MODULES)
  add_subdirectory(modules)
endif()

# --- C++ numbers
check_include_file_cxx(numbers HAVE_CXX20_NUMBERS)

if(HAVE_CXX20_NUMBERS)
  add_executable(numbers src/numbers.cpp)
  add_test(NAME Numbers COMMAND numbers)
  set_property(TEST Numbers PROPERTY LABELS 20)
endif()
# --- C++ folding ---
add_executable(folding src/folding.cpp)
add_test(NAME Folding COMMAND folding)
set_property(TEST Folding PROPERTY LABELS 17)

# --- C++ filesystem ---
check_cxx_symbol_exists(__cpp_lib_filesystem filesystem HAVE_CXX17_FILESYSTEM)

if(HAVE_CXX17_FILESYSTEM)
  add_subdirectory(filesystem)
endif()

# --- C++ coroutine ---
check_cxx_symbol_exists(__cpp_lib_coroutine coroutine HAVE_CXX20_COROUTINE)
if(HAVE_CXX20_COROUTINE)
  add_executable(coro src/coroutine.cpp)
endif()

# --- C++ threads ---

check_source_compiles(CXX
[=[
#include <cstdlib>
#include <thread>
int main() {
    unsigned int n = std::thread::hardware_concurrency();
    return EXIT_SUCCESS;
}
]=]
HAS_CXX_THREAD
)

if(HAS_CXX_THREAD)
  add_executable(thread_count src/thread_count.cpp)
  add_test(NAME Thread COMMAND thread_count)
  set_property(TEST Thread PROPERTY LABELS 14)
endif()
