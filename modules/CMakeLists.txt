cmake_minimum_required(VERSION 3.21...3.25)

project(Cxx20Modules LANGUAGES CXX)

enable_testing()
# https://gitlab.kitware.com/cmake/cmake/-/merge_requests/5562

set_property(DIRECTORY PROPERTY LABELS 20)

if(HAVE_MSVC_STDLIB_MODULES)
  add_executable(hello_mod hello.cpp)
  add_test(NAME HelloModule COMMAND hello_mod)
endif()

add_executable(math_mod math.cpp math.ixx)
add_test(NAME MathModule COMMAND math_mod)

get_property(test_names DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY TESTS)
set_property(TEST ${test_names} PROPERTY TIMEOUT 5)
