# https://gitlab.kitware.com/cmake/cmake/-/merge_requests/5562
# https://www.kitware.com/import-cmake-c20-modules/
cmake_minimum_required(VERSION 3.25.2...3.28)

project(CXXModules LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)

# UUID at https://gitlab.kitware.com/cmake/cmake/-/blob/master/Help/dev/experimental.rst
if(CMAKE_VERSION VERSION_LESS 3.26)
  set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "3c375311-a3c9-4396-a187-3227ef642046")
elseif(CMAKE_VERSION VERSION_LESS 3.27)
  set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a")
elseif(CMAKE_VERSION VERSION_LESS 3.28)
  set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "aa1f7df0-828a-4fcd-9afc-2dc80491aca7")
elseif(CMAKE_VERSION VERSION_LESS 3.29)
  set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "a816ed09-43d1-40e5-bc8c-1a2824ee194e")
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
# FIXME: remove when CMake updates this internally (3.27 maybe?)
# https://www.kitware.com/import-cmake-c20-modules/
# Currently, GCC isn't released with this support--see link above.
  if(NOT CMAKE_EXPERIMENTAL_CXX_SCANDEP_SOURCE)
  string(CONCAT CMAKE_EXPERIMENTAL_CXX_SCANDEP_SOURCE
    "<CMAKE_CXX_COMPILER> <DEFINES> <INCLUDES> <FLAGS> <SOURCE>"
    " -MT <DYNDEP_FILE> -MD -MF <DEP_FILE>"
    " ${flags_to_scan_deps} -fdep-file=<DYNDEP_FILE> -fdep-output=<OBJECT>"
    )

  set(CMAKE_EXPERIMENTAL_CXX_MODULE_MAP_FORMAT "gcc")
  set(CMAKE_EXPERIMENTAL_CXX_MODULE_MAP_FLAG
    "${compiler_flags_for_module_map} -fmodule-mapper=<MODULE_MAP_FILE>")
  endif()
endif()

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
