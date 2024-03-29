# https://www.kitware.com/import-cmake-c20-modules/
# https://cmake.org/cmake/help/latest/manual/cmake-cxxmodules.7.html

check_cxx_symbol_exists(__cpp_modules "" FEATURE_CXX20_MODULES)

if(NOT FEATURE_CXX20_MODULES AND NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
# even Clang 19 didn't yet have __cpp_modules
  return()
endif()

check_cxx_symbol_exists(__cpp_lib_modules "version" HAVE_STD_MODULES)


if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.28 AND
   CMAKE_GENERATOR MATCHES "Ninja" AND
   NOT DEFINED HAVE_MODULES)
  message(CHECK_START "Checking if C++ modules are working")

  try_compile(HAVE_MODULES PROJECT cxxmod SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cpp20/module)
  if(HAVE_MODULES)
    message(CHECK_PASS "Yes")
  else()
    message(CHECK_FAIL "No")
    return()
  endif()
endif()
