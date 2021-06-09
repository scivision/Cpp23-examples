cmake_minimum_required(VERSION 3.12...3.21)  # for CXX_STANDARD 20

project(CXX20examples
LANGUAGES C CXX)  # C is used in filesystem examples

enable_testing()

option(cxx20 "compile targets needing cxx20")
if(cxx20)
  add_subdirectory(modules)
endif()

# --- C++17 folding ---
add_executable(folding folding.cpp)
target_compile_features(folding PRIVATE cxx_std_17)
add_test(NAME Folding-17 COMMAND folding)
# --- C++17 filesystem ---
add_subdirectory(filesystem)

# --- C++11 threads ---
add_executable(thread_count thread_count.cpp)
add_test(NAME ThreadCount-11 COMMAND $<TARGET_FILE:thread_count>)

# ---
include(FeatureSummary)
add_feature_info(C++20 cxx20 "C++20 targets")
feature_summary(WHAT ALL)
