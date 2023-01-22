# https://gitlab.kitware.com/cmake/cmake/-/merge_requests/5562

set_property(DIRECTORY PROPERTY LABELS 20)

# https://www.kitware.com/import-cmake-c20-modules/
if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.25.3)
  set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
  set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a")
endif()

if(HAVE_MSVC_STDLIB_MODULE)
  add_executable(msvc_core msvc_core.cpp)
  add_test(NAME msvc_core COMMAND msvc_core)
endif()

add_executable(math_mod math.cpp)
if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.25.3)
  target_sources(math_mod PUBLIC
  FILE_SET cxx_modules
  TYPE CXX_MODULES
  FILES math.ixx
  )
else()
  # crude workaround for CMake < 3.25.3, don't rely on this in real projects
  target_sources(math_mod PRIVATE math.ixx)
endif()

add_test(NAME MathModule COMMAND math_mod)
