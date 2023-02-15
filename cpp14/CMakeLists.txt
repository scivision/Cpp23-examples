set_property(DIRECTORY PROPERTY LABELS 14)

file(READ thread_count.cpp src)
check_source_compiles(CXX "${src}" cpp14_thread)

if(cpp14_thread)
  add_executable(thread_count thread_count.cpp)
  add_test(NAME thread COMMAND thread_count)
endif()
