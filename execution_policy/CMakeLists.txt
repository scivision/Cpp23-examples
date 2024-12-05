set_property(DIRECTORY PROPERTY LABELS "execution_policy")

include(CheckIncludeFileCXX)
include(CheckSourceCompiles)

set(CMAKE_CXX_STANDARD 20)
# C++17 execution policy with C++20 enhancements

set(stdpar_opt)

if(CMAKE_CXX_COMPILER_ID STREQUAL "NVHPC" AND
   CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 24.11)
  # set(stdpar_opt -stdpar=multicore)
  # makes error  undefined reference to `__acc_compiled' on link. Works if used in one-step plain command line.
  # Maybe a CMake + NVHPC bug.
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|IntelLLVM")
  find_package(TBB CONFIG)
  if(TBB_FOUND)
    message(STATUS "TBB found ${TBB_DIR}")
  else()
    message(VERBOSE "TBB not found")
  endif()
endif()

# check_include_file needs CMAKE_REQUIRED_LIBRARIES
if(TBB_FOUND)
  message(VERBOSE "checking for <execution> with TBB ${TBB_DIR}")
  set(CMAKE_REQUIRED_LIBRARIES TBB::tbb)
endif()

check_source_compiles(CXX "#include <execution>
int main(){
auto p = std::execution::par;
return 0; }"
have_execution_policy)

if(NOT have_execution_policy)
  return()
endif()

add_library(randgen OBJECT randgen.cpp)

foreach(t IN ITEMS adjacent_find sort)

  add_executable(execution_${t} ${t}.cpp $<TARGET_OBJECTS:randgen>)
  target_include_directories(execution_${t} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
  target_compile_options(execution_${t} PRIVATE ${stdpar_opt})
  target_link_libraries(execution_${t} PRIVATE $<$<BOOL:${TBB_FOUND}>:TBB::tbb>)

  add_test(NAME execution_${t} COMMAND execution_${t})

endforeach()
