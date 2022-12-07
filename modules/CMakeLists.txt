# https://gitlab.kitware.com/cmake/cmake/-/merge_requests/5562

set_property(DIRECTORY PROPERTY LABELS 20)

if(HAVE_MSVC_STDLIB_MODULES)
  add_executable(hello_mod hello.cpp)
  add_test(NAME HelloModule COMMAND hello_mod)
endif()

add_executable(math_mod math.cpp math.ixx)
add_test(NAME MathModule COMMAND math_mod)
