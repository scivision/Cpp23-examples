cmake_minimum_required(VERSION 3.21...3.25)

project(CXX20examples
LANGUAGES CXX
)

enable_testing()

include(cmake/compilers.cmake)

if(HAVE_CXX20_MODULES)
  add_subdirectory(modules)
endif()

if(HAVE_CXX20_NUMBERS)
  add_executable(numbers src/numbers.cpp)
  add_test(NAME Numbers COMMAND numbers)
  set_property(TEST Numbers PROPERTY LABELS 20)
endif()

# --- C++ folding ---
add_executable(folding src/folding.cpp)
add_test(NAME Folding COMMAND folding)
set_property(TEST Folding PROPERTY LABELS 17)

if(HAVE_CXX17_FILESYSTEM)
  add_subdirectory(filesystem)
endif()

if(HAVE_CXX20_COROUTINE)
  add_executable(coro src/coroutine.cpp)
endif()

if(HAVE_CXX_THREAD)
  add_executable(thread_count src/thread_count.cpp)
  add_test(NAME Thread COMMAND thread_count)
  set_property(TEST Thread PROPERTY LABELS 14)
endif()
