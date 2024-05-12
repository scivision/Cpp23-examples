set_property(DIRECTORY PROPERTY LABELS 11)

set(CMAKE_CXX_STANDARD 11)

set(f11 current_exception iota getenv nullptr)
if(WIN32)
  list(APPEND f11 GetLastError)
endif()

foreach(t IN LISTS f11)
  add_executable(${t} ${t}.cpp)

  add_test(NAME ${t} COMMAND ${t})
endforeach()

if(cppcheck)
set_property(TARGET current_exception PROPERTY CXX_CPPCHECK "${CMAKE_CXX_CPPCHECK};--suppress=containerOutOfBounds")
endif()

if(TEST GetLastError)
  set_property(TEST GetLastError PROPERTY WILL_FAIL true)
endif()

# --- count features enabled
get_property(t DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY BUILDSYSTEM_TARGETS)
list(LENGTH f11 Nf)
list(LENGTH t Ne)
message(STATUS "C++11 features: ${Ne} / ${Nf}")
