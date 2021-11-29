cmake_minimum_required(VERSION 3.21...3.22)

project(CXX20examples
LANGUAGES C CXX
)

enable_testing()

add_compile_definitions($<$<BOOL:${MSVC}>:_CRT_SECURE_NO_WARNINGS>)

# C++20 modules, if compiler is capable
try_compile(mod_ok
${CMAKE_CURRENT_BINARY_DIR}/try_mod
${CMAKE_CURRENT_SOURCE_DIR}/modules
HAVE_CXX20_MODULES
)
if(HAVE_CXX20_MODULES)
  add_subdirectory(modules)
else()
  message(WARNING "C++ 20 modules not available with ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
endif()
# --- C++17 folding ---
add_executable(folding src/folding.cpp)
target_compile_features(folding PRIVATE cxx_std_17)
add_test(NAME Folding-17 COMMAND $<TARGET_FILE:folding>)

# --- C++17 filesystem ---
add_subdirectory(filesystem)

# --- C++11 threads ---
add_executable(thread_count src/thread_count.cpp)
target_compile_features(thread_count PRIVATE cxx_std_11)
add_test(NAME ThreadCount-11 COMMAND $<TARGET_FILE:thread_count>)
