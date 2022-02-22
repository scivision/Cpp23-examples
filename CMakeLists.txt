cmake_minimum_required(VERSION 3.21...3.23)

project(CXX20examples
LANGUAGES C CXX
)

enable_testing()

include(CheckSourceCompiles)
include(CheckCXXSymbolExists)

add_compile_definitions($<$<BOOL:${MSVC}>:_CRT_SECURE_NO_WARNINGS>)

# C++20 modules, if compiler is capable
try_compile(HAVE_CXX20_MODULES
${CMAKE_CURRENT_BINARY_DIR}/try_mod
${CMAKE_CURRENT_SOURCE_DIR}/modules
dummy
OUTPUT_VARIABLE build_result
)
if(HAVE_CXX20_MODULES)
  add_subdirectory(modules)
else()
  message(STATUS "C++ 20 modules not available with ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
  message(VERBOSE "${build_result}")
endif()
# --- C++17 folding ---
add_executable(folding src/folding.cpp)
target_compile_features(folding PRIVATE cxx_std_17)
add_test(NAME Folding-17 COMMAND $<TARGET_FILE:folding>)

# --- C++17 filesystem ---
check_cxx_symbol_exists(__cpp_lib_filesystem filesystem HAVE_CXX17_FILESYSTEM)

if(HAVE_CXX17_FILESYSTEM)
  add_subdirectory(filesystem)
endif()
# --- C++11 threads ---

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
  target_compile_features(thread_count PRIVATE cxx_std_14)
  add_test(NAME ThreadCount-11 COMMAND $<TARGET_FILE:thread_count>)
endif()
