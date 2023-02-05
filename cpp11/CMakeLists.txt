set_property(DIRECTORY PROPERTY LABELS 11)

add_executable(current_exception current_exception.cpp)
add_test(NAME current_exception COMMAND current_exception)

if(WIN32)
  add_executable(GetLastError GetLastError.cpp)
  add_test(NAME GetLastError COMMAND GetLastError)
  set_property(TEST GetLastError PROPERTY WILL_FAIL true)
endif()
