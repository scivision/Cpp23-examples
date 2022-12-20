# https://gitlab.kitware.com/cmake/cmake/-/merge_requests/5562

set_property(DIRECTORY PROPERTY LABELS 20)

if(HAVE_MSVC_STDLIB_MODULE)
  add_executable(msvc_core msvc_core.cpp)
  add_test(NAME msvc_core COMMAND msvc_core)
endif()

add_executable(math_mod math.cpp math.ixx)
add_test(NAME MathModule COMMAND math_mod)
