include(CheckSourceCompiles)
include(CheckCXXSymbolExists)
include(CheckIncludeFileCXX)

check_include_file_cxx(cstdlib HAVE_CSTDLIB)
if(NOT HAVE_CSTDLIB)
  message(FATAL_ERROR "cstdlib not found. If using a custom built compiler, ensure that compiler's include dirs are set in environment variable CPLUS_INCLUDE_PATH")
endif()

set(stdpar_opt)

if(CMAKE_CXX_COMPILER_ID STREQUAL "NVHPC" AND
   CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 24.11)
  # set(stdpar_opt -stdpar=multicore)
  # makes error  undefined reference to `__acc_compiled' on link. Works if used in one-step plain command line.
  # Maybe a CMake + NVHPC bug.
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "IntelLLVM")
  find_package(TBB CONFIG)
  if(TBB_FOUND)
    message(STATUS "TBB found ${TBB_DIR}")
  else()
    message(VERBOSE "TBB not found")
  endif()
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|^Intel")
  add_compile_options(-Wall -Wextra)
endif()

add_compile_definitions($<$<BOOL:${WIN32}>:_CRT_SECURE_NO_WARNINGS>)
