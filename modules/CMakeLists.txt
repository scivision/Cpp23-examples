cmake_minimum_required(VERSION 3.21...3.24)
project(Cxx20Modules LANGUAGES CXX)
enable_testing()
# https://gitlab.kitware.com/cmake/cmake/-/merge_requests/5562

set_directory_properties(PROPERTIES LABELS 20)

add_executable(modules main.cpp math.ixx)
target_compile_features(modules PRIVATE cxx_std_20)

add_test(NAME Modules COMMAND modules)
set_tests_properties(Modules PROPERTIES
TIMEOUT 5
)
