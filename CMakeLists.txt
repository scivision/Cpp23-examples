cmake_minimum_required(VERSION 3.12)  # for CXX_STANDARD 20
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Debug or Release")
endif()
project(CXX20examples CXX)
enable_testing()

set(CXX_STANDARD_REQUIRED ON)

# --- C++20 module ---
# not yet supported by CMake 3.15
if(false)
  add_executable(modules math.cpp math.cppm)
  set_target_properties(modules PROPERTIES CXX_STANDARD 20)
  add_test(NAME C++20Modules COMMAND modules)
endif()
# --- C++17 folding ---
add_executable(folding folding.cpp)
set_target_properties(folding PROPERTIES CXX_STANDARD 17)
add_test(NAME Folding-17 COMMAND folding)
# --- C++17 filesystem ---

add_executable(filesep filesep.cpp)
set_target_properties(filesep PROPERTIES CXX_STANDARD 17)
add_test(NAME Filesep-17 COMMAND filesep)