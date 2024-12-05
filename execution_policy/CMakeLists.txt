set_property(DIRECTORY PROPERTY LABELS "execution_policy")

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
  message(VERBOSE "checking for execution policy with TBB ${TBB_DIR}")
  set(CMAKE_REQUIRED_LIBRARIES TBB::tbb)
endif()
check_include_file_cxx(execution have_execution_policy)

if(have_execution_policy)
  file(READ execution_policy.cpp _src)
  check_source_compiles(CXX "${_src}" execution_policy_parallel)
  if(NOT execution_policy_parallel)
    set_property(CACHE have_execution_policy PROPERTY VALUE false)
  endif()
endif()


if(NOT have_execution_policy)
  return()
endif()

add_executable(execution_policy execution_policy.cpp)
add_test(NAME execution_policy COMMAND execution_policy)

target_compile_options(execution_policy PRIVATE ${stdpar_opt})
target_link_libraries(execution_policy PRIVATE $<$<BOOL:${TBB_FOUND}>:TBB::tbb>)
