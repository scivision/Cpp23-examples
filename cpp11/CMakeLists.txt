set_property(DIRECTORY PROPERTY LABELS 11)

set(names current_exception iota getenv nullptr)
if(WIN32)
  list(APPEND names GetLastError)
endif()

foreach(t IN LISTS names)
  add_executable(${t} ${t}.cpp)
  add_test(NAME ${t} COMMAND ${t})
endforeach()

if(cppcheck)
set_property(TARGET current_exception PROPERTY CXX_CPPCHECK "${CMAKE_CXX_CPPCHECK};--suppress=containerOutOfBounds")
endif()

if(TEST GetLastError)
  set_property(TEST GetLastError PROPERTY WILL_FAIL true)
endif()
