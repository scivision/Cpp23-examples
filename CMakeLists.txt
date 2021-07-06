cmake_minimum_required(VERSION 3.19...3.21)

project(CXX20examples
  LANGUAGES C CXX)  # C is used in filesystem examples

enable_testing()

if(CMAKE_CXX_COMPILER_ID STREQUAL IntelLLVM AND CMAKE_VERSION VERSION_LESS 3.21.0)
  message(STATUS "Note: CMake has a bug with IntelLLVM icx where -std=c++* is not added.
  This makes this project not work well with IntelLLVM yet.")
endif()

# C++20 modules, if compiler is capable
if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.21)
  try_compile(mod_ok
    ${CMAKE_CURRENT_BINARY_DIR}/try_mod
    ${CMAKE_CURRENT_SOURCE_DIR}/modules
    Cxx20Modules)
  if(mod_ok)
    add_subdirectory(modules)
  endif()
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
