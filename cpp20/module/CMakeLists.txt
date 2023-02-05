# https://gitlab.kitware.com/cmake/cmake/-/merge_requests/5562
# https://www.kitware.com/import-cmake-c20-modules/
cmake_minimum_required(VERSION 3.26)

project(CXXModules LANGUAGES CXX)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a")

if(HAVE_MSVC_STDLIB_MODULE)
  add_executable(msvc_core msvc_core.cpp)
  add_test(NAME msvc_core COMMAND msvc_core)
endif()

add_executable(math_mod math.cpp)
target_sources(math_mod PUBLIC
FILE_SET cxx_modules
TYPE CXX_MODULES
FILES math.ixx
)

add_test(NAME MathModule COMMAND math_mod)
