cmake_minimum_required(VERSION 3.21...3.25)

project(Cxx20Modules LANGUAGES CXX)

enable_testing()
# https://gitlab.kitware.com/cmake/cmake/-/merge_requests/5562

set_property(DIRECTORY PROPERTY LABELS 20)

add_executable(modules math.cpp math.ixx)

add_test(NAME Modules COMMAND modules)
set_property(TEST Modules PROPERTY TIMEOUT 5)
