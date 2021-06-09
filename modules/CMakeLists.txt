cmake_minimum_required(VERSION 3.20)  # actually 3.21, using dev branch
project(Cxx20Modules LANGUAGES CXX)

# https://gitlab.kitware.com/cmake/cmake/-/merge_requests/5562

add_executable(modules main.cpp math.ixx)
target_link_libraries(modules PRIVATE math)
target_compile_features(modules PRIVATE cxx_std_20)

add_test(NAME C++20Modules COMMAND modules)
