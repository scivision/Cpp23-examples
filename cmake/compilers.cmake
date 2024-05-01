include(CheckSourceCompiles)
include(CheckCXXSymbolExists)
include(CheckIncludeFileCXX)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|^Intel")
  add_compile_options(-Wall -Wextra)
endif()

add_compile_definitions($<$<BOOL:${WIN32}>:_CRT_SECURE_NO_WARNINGS>)
