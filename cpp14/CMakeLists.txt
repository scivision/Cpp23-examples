set_property(DIRECTORY PROPERTY LABELS 14)

set(CMAKE_CXX_STANDARD 14)

check_cxx_symbol_exists(__cpp_lib_make_unique "memory" have_make_unique)

check_include_file_cxx(thread have_thread)

set(f14 make_unique thread)

foreach(t IN LISTS f14)
  if(have_${t})
    add_executable(${t} ${t}.cpp)

    add_test(NAME ${t} COMMAND ${t})
  endif()
endforeach()

get_property(t DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY BUILDSYSTEM_TARGETS)
list(LENGTH f14 Nf)
list(LENGTH t Ne)
message(STATUS "C++14 features: ${Ne} / ${Nf}")
