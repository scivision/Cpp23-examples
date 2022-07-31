include(CheckSourceCompiles)
include(CheckCXXSymbolExists)

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


check_cxx_symbol_exists(__cpp_lib_coroutine coroutine HAVE_CXX20_COROUTINE)

check_cxx_symbol_exists(__cpp_lib_filesystem filesystem HAVE_CXX17_FILESYSTEM)

check_cxx_symbol_exists(__cpp_lib_math_constants numbers HAVE_CXX20_NUMBERS)

check_cxx_symbol_exists(__cpp_modules "" HAVE_CXX20_MODULES)

add_compile_definitions($<$<BOOL:${MSVC}>:_CRT_SECURE_NO_WARNINGS>)

# --- auto-ignore build directory
if(NOT EXISTS ${PROJECT_BINARY_DIR}/.gitignore)
  file(WRITE ${PROJECT_BINARY_DIR}/.gitignore "*")
endif()
