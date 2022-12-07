cmake_minimum_required(VERSION 3.25...3.26)

project(Cpp23examples
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

# --- C++ 23 ---

if(HAVE_EXPECTED)
  add_executable(expected src/expected.cpp)
  add_test(NAME expected COMMAND expected)
  set_property(TEST expected PROPERTY LABELS 23)
  set_property(TEST expected PROPERTY PASS_REGULAR_EXPRESSION "42")
endif()

if(HAVE_PRINT)
  add_executable(print src/print.cpp)
  add_test(NAME Print COMMAND print)
  set_property(TEST Print PROPERTY LABELS 23)
endif()

if(HAVE_STDFLOAT)
  add_executable(stdfloat src/stdfloat.cpp)
  add_test(NAME stdfloat COMMAND stdfloat)
  set_property(TEST Print PROPERTY LABELS 23)
endif()

# --- filesystem

if(FEATURE_CXX17_FILESYSTEM)
  add_subdirectory(filesystem)
endif()

# --- coroutine

if(HAVE_CXX20_COROUTINE)
  add_executable(coro src/coroutine.cpp)
endif()

# --- thread

if(HAVE_CXX_THREAD)
  add_executable(thread_count src/thread_count.cpp)
  add_test(NAME Thread COMMAND thread_count)
  set_property(TEST Thread PROPERTY LABELS 14)
endif()
