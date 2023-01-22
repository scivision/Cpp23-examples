# https://www.kitware.com/import-cmake-c20-modules/

check_cxx_symbol_exists(__cpp_modules "" FEATURE_CXX20_MODULES)

if(FEATURE_CXX20_MODULES AND NOT DEFINED HAVE_MODULES)
  message(CHECK_START "Checking if C++ modules are working")

  try_compile(HAVE_MODULES
  SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/modules/math.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/modules/math.ixx
  OUTPUT_VARIABLE log
  )
  if(HAVE_MODULES)
    message(CHECK_PASS "Yes")
  else()
    message(CHECK_FAIL "No")
    message(VERBOSE "${log}")
  endif()
endif()

if(FEATURE_CXX20_MODULES)

check_source_compiles(CXX
[=[
import <iostream>;
int main(){ std::cout << "hello" << std::endl; return 0; }
]=]
HAVE_STDLIB_MODULE
)

if(MSVC)
check_source_compiles(CXX
[=[
import std.core;
int main(){
  std::cout << "hello" << std::endl;
  return 0;
}
]=]
HAVE_MSVC_STDLIB_MODULE
)
endif()

endif()
