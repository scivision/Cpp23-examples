set_property(DIRECTORY PROPERTY LABELS 11)

set(CMAKE_CXX_STANDARD 11)

foreach(t IN LISTS cpp11features)
  add_executable(${t} ${t}.cpp)

  add_test(NAME ${t} COMMAND ${t})
endforeach()

if(MSVC OR CMAKE_CXX_SIMULATE_ID STREQUAL "MSVC")
# the CMAKE_CXX_SIMULATE_ID catches when frontend is GNU but MSVC runtime headers are used
  target_compile_definitions(getenv PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

if(cppcheck)
  set_property(TARGET current_exception PROPERTY CXX_CPPCHECK "${CMAKE_CXX_CPPCHECK};--suppress=containerOutOfBounds")
endif()

if(TEST GetLastError)
  set_property(TEST GetLastError PROPERTY WILL_FAIL true)
endif()
