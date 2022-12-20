cmake_minimum_required(VERSION 3.25...3.26)

project(Cpp23examples
LANGUAGES CXX
)

enable_testing()

include(cmake/compilers.cmake)

if(HAVE_MODULES)
  add_subdirectory(src/modules)
endif()

if(HAVE_NUMBERS)
  add_executable(numbers src/numbers.cpp)
  add_test(NAME numbers COMMAND numbers)
  set_property(TEST numbers PROPERTY LABELS 20)
endif()

# --- C++ folding ---
add_executable(folding src/folding.cpp)
add_test(NAME folding COMMAND folding)
set_property(TEST folding PROPERTY LABELS 17)

# --- C++20 likely attribute ===
add_executable(likely src/likely.cpp)
add_test(NAME likely COMMAND likely)
set_property(TEST likely PROPERTY LABELS 20)

# --- C++ 23 ---

if(HAVE_EXPECTED)
  add_executable(expected src/expected.cpp)
  add_test(NAME expected COMMAND expected)
  set_property(TEST expected PROPERTY LABELS 23)
  set_property(TEST expected PROPERTY PASS_REGULAR_EXPRESSION "42")
endif()

if(HAVE_PRINT)
  add_executable(print src/print.cpp)
  add_test(NAME print COMMAND print)
  set_property(TEST print PROPERTY LABELS 23)
endif()

if(HAVE_STDFLOAT)
  add_executable(stdfloat src/stdfloat.cpp)
  add_test(NAME stdfloat COMMAND stdfloat)
  set_property(TEST stdfloat PROPERTY LABELS 23)
endif()

if(HAVE_UNREACHABLE)
add_executable(unreachable src/unreachable.cpp)
add_test(NAME unreachable COMMAND unreachable)
set_property(TEST unreachable PROPERTY LABELS 23)
set_property(TEST unreachable PROPERTY WILL_FAIL TRUE)
endif()

# --- filesystem

if(HAVE_FILESYSTEM)
  add_subdirectory(src/filesystem)
endif()

# --- coroutine

if(HAVE_COROUTINE)
  add_executable(coro src/coroutine.cpp)
endif()

# --- thread

if(HAVE_THREAD)
  add_executable(thread_count src/thread_count.cpp)
  add_test(NAME thread COMMAND thread_count)
  set_property(TEST thread PROPERTY LABELS 14)
endif()
