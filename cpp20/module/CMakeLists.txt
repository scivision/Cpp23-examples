# https://www.kitware.com/import-cmake-c20-modules/
cmake_minimum_required(VERSION 3.28)

project(CXXModules LANGUAGES CXX)

set_property(DIRECTORY PROPERTY LABELS "CppModules")

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

if(HAVE_STD_MODULES)
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
