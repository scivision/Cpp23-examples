cmake_minimum_required(VERSION 3.12)  # for CXX_STANDARD 20

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Debug or Release")
endif()

project(CXX20examples
LANGUAGES C CXX)

enable_testing()
include(FeatureSummary)

option(cxx20 "compile targets needing cxx20")

# --- C++20 module ---
# not yet supported by CMake 3.17
if(cxx20)
  add_executable(modules math.cpp math.cppm)
  target_compile_features(modules PRIVATE cxx_std_20)
  add_test(NAME C++20Modules COMMAND modules)
endif()
# --- C++17 folding ---
add_executable(folding folding.cpp)
target_compile_features(folding PRIVATE cxx_std_17)
add_test(NAME Folding-17 COMMAND folding)
# --- C++17 filesystem ---
add_subdirectory(filesystem)


add_feature_info(C++20 cxx20 "C++20 targets")
feature_summary(WHAT ALL)
