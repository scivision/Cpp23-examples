include(CheckSourceCompiles)
include(CheckCXXSymbolExists)
include(CheckIncludeFileCXX)

check_include_file_cxx(cstdlib HAVE_CSTDLIB)
if(NOT HAVE_CSTDLIB)
  message(FATAL_ERROR "cstdlib not found or incompatible.
  If using a custom built compiler, ensure that compiler's include dirs are set in environment variable CPLUS_INCLUDE_PATH
  If using macOS and you've recently upgraded macOS or Xcode, this may be incompatiable with the compiler until Homebrew (or whatever the compiler vendor is) has updated.")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|^Intel")
  add_compile_options(-Wall -Wextra)
endif()

add_compile_definitions($<$<BOOL:${WIN32}>:_CRT_SECURE_NO_WARNINGS>)
